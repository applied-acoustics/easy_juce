/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
GainAudioProcessorEditor::GainAudioProcessorEditor(GainAudioProcessor &p)
    : easy::AudioProcessorEditor(&p), processor(p) {
  addSection("Mixer");
  addSlider("Gain");
  addSlider("Pan");
  addComboBox("Choice", {"Both", "Left", "Right"});
  addSlider2D("Room", "X", "Y");
  addToggle("Active");
}

GainAudioProcessorEditor::~GainAudioProcessorEditor() {}

//==============================================================================
void GainAudioProcessorEditor::paint(Graphics &g) {
  // (Our component is opaque, so we must completely fill the background with a
  // solid colour)
  g.fillAll({180, 180, 180});
}

void GainAudioProcessorEditor::resized() { resize(); }
