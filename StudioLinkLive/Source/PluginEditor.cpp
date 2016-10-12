/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
StudioLinkLiveAudioProcessorEditor::StudioLinkLiveAudioProcessorEditor (StudioLinkLiveAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
}

StudioLinkLiveAudioProcessorEditor::~StudioLinkLiveAudioProcessorEditor()
{
}

//==============================================================================
void StudioLinkLiveAudioProcessorEditor::paint (Graphics& g)
{

}

void StudioLinkLiveAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
