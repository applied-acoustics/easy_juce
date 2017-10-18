#include "Effect.h"

void Effect::init(int sampling_rate) {

}

void Effect::process(juce::AudioSampleBuffer &buffer, juce::MidiBuffer &midi)
{
  updateParameters();

  const float *in_left = buffer.getReadPointer(0);
  const float *in_right = buffer.getReadPointer(1);

  float *out_left = buffer.getWritePointer(0);
  float *out_right = buffer.getWritePointer(1);

  const int buffer_size = buffer.getNumSamples();
  const float const_pan = 0.7071067811865476;


  if(_on == 0.0f) {
    for (int i = 0; i < buffer_size; i++) {
      out_left[i] = 0.0f;
      out_right[i] = 0.0f;
    }
  } else {
  for (int i = 0; i < buffer_size; i++) {
    if (_choice == kChoice_Normal) {
      out_left[i] = _gain * const_pan * _pan * in_left[i];
      out_right[i] = _gain * const_pan * (1.0f - _pan) * in_right[i];
    } else if (_choice == kChoice_LeftOnly) {
      out_left[i] = _gain * const_pan * _pan * in_left[i];
      out_right[i] = 0.0f;
    } else {
      out_left[i] = 0.0f;
      out_right[i] = _gain * const_pan * (1.0f - _pan) * in_right[i];
    }
  }
  }
}

void Effect::updateParameters()
{
  if (_gain != _temp_params[kGain]) {
    _gain = _temp_params[kGain];
  }

  if (_pan != _temp_params[kPan]) {
    _pan = _temp_params[kPan];
  }

  if (_choice != _temp_params[kChoice]) {
    _choice = _temp_params[kChoice];
  }
  
  if (_on != _temp_params[kOnOff]) {
    _on = _temp_params[kOnOff];
  }
}
