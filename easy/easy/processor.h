#pragma once

namespace easy {
class AudioProcessor : public juce::AudioProcessor,
                       public juce::AudioProcessorValueTreeState::Listener {
public:
  inline AudioProcessor() : _parameters(*this, nullptr) {}

  inline AudioProcessor(const juce::AudioProcessor::BusesProperties &ioLayouts)
      : juce::AudioProcessor(ioLayouts), _parameters(*this, nullptr) {}

  inline void addFloatParameter(const juce::String &name, float min_value,
                                float max_value, float default_value);

  inline void changeFloatParameterRange(const juce::String &name,
                                        float min_value, float max_value);

  inline void addIntParameter(const juce::String &name, int min_value,
                              int max_value, int default_value);

  inline juce::AudioProcessorValueTreeState &getParametersState() {
    return _parameters;
  }

protected:
  inline void parameterChanged(const juce::String &id, float value) override{};

private:
  juce::AudioProcessorValueTreeState _parameters;
};

/*
 * Implementation.
 */
void AudioProcessor::addFloatParameter(const juce::String &name,
                                       float min_value, float max_value,
                                       float default_value) {
  _parameters.createAndAddParameter(
      name, name, name, juce::NormalisableRange<float>(min_value, max_value),
      default_value, nullptr, nullptr, false, true, false);
  _parameters.addParameterListener(name, this);
}

void AudioProcessor::changeFloatParameterRange(const juce::String &name,
                                               float min_value,
                                               float max_value) {}

void AudioProcessor::addIntParameter(const juce::String &name, int min_value,
                                     int max_value, int default_value) {
  _parameters.createAndAddParameter(
      name, name, name,
      juce::NormalisableRange<float>((float)min_value, (float)max_value),
      (float)default_value, nullptr, nullptr, false, true, false);
  _parameters.addParameterListener(name, this);
}

} // namespace easy
