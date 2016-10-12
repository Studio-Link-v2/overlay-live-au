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

//==============================================================================
StudioLinkLiveAudioProcessor::StudioLinkLiveAudioProcessor()
{
	(void)re_fprintf(stderr, "activate baresip v%s"
			" Copyright (C) 2010 - 2016"
			" Alfred E. Heggestad et al.\n",
			BARESIP_VERSION);

	(void)re_fprintf(stderr, "activate baresip v%s"
			" Copyright (C) 2010 - 2015"
			" Alfred E. Heggestad et al.\n",
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
}

StudioLinkLiveAudioProcessor::~StudioLinkLiveAudioProcessor()
{
	ua_stop_all(false);
	//(void)pthread_join(tid, NULL);
	sys_msleep(500);
	ua_close();
	re_cancel();
	conf_close();
	baresip_close();
	libre_close();
        tmr_debug();
        mem_debug();
}

//==============================================================================
const String StudioLinkLiveAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool StudioLinkLiveAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool StudioLinkLiveAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double StudioLinkLiveAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int StudioLinkLiveAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int StudioLinkLiveAudioProcessor::getCurrentProgram()
{
    return 0;
}

void StudioLinkLiveAudioProcessor::setCurrentProgram (int index)
{
}

const String StudioLinkLiveAudioProcessor::getProgramName (int index)
{
    return String();
}

void StudioLinkLiveAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void StudioLinkLiveAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void StudioLinkLiveAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool StudioLinkLiveAudioProcessor::setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet)
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

void StudioLinkLiveAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
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
bool StudioLinkLiveAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* StudioLinkLiveAudioProcessor::createEditor()
{
    return new StudioLinkLiveAudioProcessorEditor (*this);
}

//==============================================================================
void StudioLinkLiveAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void StudioLinkLiveAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new StudioLinkLiveAudioProcessor();
}
