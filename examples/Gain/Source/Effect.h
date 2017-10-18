#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <array>

class Effect {
public:
  enum Parameters {
    kGain,
    kPan,
    kChoice,
    kOnOff,
    kNumberOfParameters
  };

  enum Choice {
    kChoice_Normal,
    kChoice_LeftOnly,
    kChoice_RightOnly
  };

  inline Effect()
  {
    _temp_params[kGain] = _gain;
    _temp_params[kPan] = _pan;
    _temp_params[kChoice] = _choice;
    _temp_params[kOnOff] = _on;
  }

  void init(int sampling_rate);
  void process(juce::AudioSampleBuffer &buffer, juce::MidiBuffer &midi);

  inline void setGain(float value)
  {
    _temp_params[kGain] = value;
  }

  inline void setPan(float value)
  {
    _temp_params[kPan] = value;
  }

  inline void setChoice(float value)
  {
    _temp_params[kChoice] = value;
  }
  
  inline void setOnOff(float value)
  {
    _temp_params[kOnOff] = value;
  }

private:
  float _gain = 1.0f;
  float _pan = 0.5f;
  int _choice = kChoice_Normal;
  int _on = 1;

  std::array<float, kNumberOfParameters> _temp_params;

  void updateParameters();
};
