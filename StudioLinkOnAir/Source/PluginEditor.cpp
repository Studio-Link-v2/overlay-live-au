/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
StudioLinkOnAirAudioProcessorEditor::StudioLinkOnAirAudioProcessorEditor (StudioLinkOnAirAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
}

StudioLinkOnAirAudioProcessorEditor::~StudioLinkOnAirAudioProcessorEditor()
{
}

//==============================================================================
void StudioLinkOnAirAudioProcessorEditor::paint (Graphics& g)
{

}

void StudioLinkOnAirAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
