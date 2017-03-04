/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <pthread.h>
#include "re/re.h"
#include "baresip.h"

pthread_t tid;

bool running = false;

//==============================================================================
StudioLinkOnAirAudioProcessor::StudioLinkOnAirAudioProcessor()
{

	if (!running) {
		(void)re_fprintf(stderr, "activate baresip v%s"
				" Copyright (C) 2010 - 2016"
				" Alfred E. Heggestad et al. STUDIO LINK DEBUG\n",
				BARESIP_VERSION);

		(void)sys_coredump_set(true);
		libre_init();
		log_enable_debug(true);
		conf_configure();
		baresip_init(conf_config(), false);
		ua_init("baresip v" BARESIP_VERSION " (" ARCH "/" OS ")",
				true, true, true, false);
		conf_modules();
		pthread_create(&tid, NULL, (void*(*)(void*))&re_main, NULL);

		running = true;
	}
}

StudioLinkOnAirAudioProcessor::~StudioLinkOnAirAudioProcessor()
{
	if (running) {
		ua_stop_all(false);
		//(void)pthread_join(tid, NULL);
		sys_msleep(800);
		ua_close();
		re_cancel();
		conf_close();
		baresip_close();
		libre_close();
		tmr_debug();
		mem_debug();
		running = false;
	}
}

//==============================================================================
const String StudioLinkOnAirAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool StudioLinkOnAirAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool StudioLinkOnAirAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double StudioLinkOnAirAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int StudioLinkOnAirAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int StudioLinkOnAirAudioProcessor::getCurrentProgram()
{
    return 0;
}

void StudioLinkOnAirAudioProcessor::setCurrentProgram (int index)
{
}

const String StudioLinkOnAirAudioProcessor::getProgramName (int index)
{
    return String();
}

void StudioLinkOnAirAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void StudioLinkOnAirAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void StudioLinkOnAirAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool StudioLinkOnAirAudioProcessor::setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet)
{
    // Reject any bus arrangements that are not compatible with your plugin

    const int numChannels = preferredSet.size();

   #if JucePlugin_IsMidiEffect
    if (numChannels != 0)
        return false;
   #elif JucePlugin_IsSynth
    if (isInput || (numChannels != 1 && numChannels != 2))
        return false;
   #else
    if (numChannels != 1 && numChannels != 2)
        return false;

    if (! AudioProcessor::setPreferredBusArrangement (! isInput, bus, preferredSet))
        return false;
   #endif

    return AudioProcessor::setPreferredBusArrangement (isInput, bus, preferredSet);
}
#endif

void StudioLinkOnAirAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    const float* input0 = buffer.getReadPointer(0);
    const float* input1 = input0;

    if(getNumInputChannels() > 1) {
        input1 = buffer.getReadPointer(1);
    } 

    effectlive_src(input0, input1, buffer.getNumSamples());
}

//==============================================================================
bool StudioLinkOnAirAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* StudioLinkOnAirAudioProcessor::createEditor()
{
    return new StudioLinkOnAirAudioProcessorEditor (*this);
}

//==============================================================================
void StudioLinkOnAirAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void StudioLinkOnAirAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new StudioLinkOnAirAudioProcessor();
}
