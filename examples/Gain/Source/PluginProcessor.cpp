/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GainAudioProcessor::GainAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : easy::AudioProcessor(
          BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
              .withInput("Input", AudioChannelSet::stereo(), true)
#endif
              .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
      )
#endif
{
  addFloatParameter("Gain", 0.145f, 1.0f, 1.0f);
  addFloatParameter("Pan", 0.0f, 1.0f, 0.5f);
  addIndexedParameter("Choice", 2, 0);
  addFloatParameter("X", -1.0f, 1.0f, 0.0f);
  addFloatParameter("Y", 0.0f, 1.0f, 0.5f);
  addIntParameter("Active", 0, 1, 1);
}

GainAudioProcessor::~GainAudioProcessor() {}

void GainAudioProcessor::parameterChanged(const juce::String &id, float value) {
  if (id == "Gain") {
    _effect.setGain(value);
  } else if (id == "Pan") {
    _effect.setPan(value);
  } else if (id == "Choice") {
    _effect.setChoice(value);
  } else if (id == "Active") {
    _effect.setOnOff(value);
  }
}

//==============================================================================
const String GainAudioProcessor::getName() const { return JucePlugin_Name; }

bool GainAudioProcessor::acceptsMidi() const {
#if JucePlugin_WantsMidiInput
  return true;
#else
  return false;
#endif
}

bool GainAudioProcessor::producesMidi() const {
#if JucePlugin_ProducesMidiOutput
  return true;
#else
  return false;
#endif
}

bool GainAudioProcessor::isMidiEffect() const {
#if JucePlugin_IsMidiEffect
  return true;
#else
  return false;
#endif
}

double GainAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int GainAudioProcessor::getNumPrograms() {
  return 1; // NB: some hosts don't cope very well if you tell them there are 0
            // programs, so this should be at least 1, even if you're not really
            // implementing programs.
}

int GainAudioProcessor::getCurrentProgram() { return 0; }

void GainAudioProcessor::setCurrentProgram(int index) {}

const String GainAudioProcessor::getProgramName(int index) { return {}; }

void GainAudioProcessor::changeProgramName(int index, const String &newName) {}

//==============================================================================
void GainAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
  // Use this method as the place to do any pre-playback
  // initialisation that you need..
  _effect.init(sampleRate);
}

void GainAudioProcessor::releaseResources() {
  // When playback stops, you can use this as an opportunity to free up any
  // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GainAudioProcessor::isBusesLayoutSupported(
    const BusesLayout &layouts) const {
#if JucePlugin_IsMidiEffect
  ignoreUnused(layouts);
  return true;
#else
  // This is the place where you check if the layout is supported.
  // In this template code we only support mono or stereo.
  if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono() &&
      layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
    return false;

// This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
  if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
    return false;
#endif

  return true;
#endif
}
#endif

void GainAudioProcessor::processBlock(AudioSampleBuffer &buffer,
                                      MidiBuffer &midiMessages) {
  ScopedNoDenormals noDenormals;
  const int totalNumInputChannels = getTotalNumInputChannels();
  const int totalNumOutputChannels = getTotalNumOutputChannels();

  // In case we have more outputs than inputs, this code clears any output
  // channels that didn't contain input data, (because these aren't
  // guaranteed to be empty - they may contain garbage).
  // This is here to avoid people getting screaming feedback
  // when they first compile a plugin, but obviously you don't need to keep
  // this code if your algorithm always overwrites all the output channels.
  for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    buffer.clear(i, 0, buffer.getNumSamples());

  _effect.process(buffer, midiMessages);
}

//==============================================================================
bool GainAudioProcessor::hasEditor() const {
  return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor *GainAudioProcessor::createEditor() {
  return new GainAudioProcessorEditor(*this);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
  return new GainAudioProcessor();
}
