#pragma once

namespace easy {
class AudioProcessor : public juce::AudioProcessor,
                       public juce::AudioProcessorValueTreeState::Listener {
public:
  struct Listener {
    virtual ~Listener() {}

    virtual void onParameterChanged(const juce::String &id, float value) = 0;
  };
  //  inline AudioProcessor(juce::AudioProcessor *audio_processor);
  inline AudioProcessor() : _parameters(*this, nullptr) {}

  inline AudioProcessor(const juce::AudioProcessor::BusesProperties &ioLayouts)
      : juce::AudioProcessor(ioLayouts), _parameters(*this, nullptr) {}

  inline void addListener(Listener *listener) {
    _listeners.push_back(listener);
  }

  inline void addFloatParameter(const juce::String &name, float min_value,
                                float max_value, float default_value);

  inline void addIntParameter(const juce::String &name, int min_value,
                              int max_value, int default_value);

  inline juce::AudioProcessorValueTreeState &getParametersState() {
    return _parameters;
  }

protected:
  inline void parameterChanged(const juce::String &id, float value) override;

private:
  //  juce::AudioProcessor *_audio_processor;
  juce::AudioProcessorValueTreeState _parameters;
  std::vector<Listener *> _listeners;
};

/*
 * Implementation.
 */
// AudioProcessor::AudioProcessor(juce::AudioProcessor *audio_processor)
//  : _audio_processor(audio_processor), _parameters(*audio_processor, nullptr)
//{
//}

void AudioProcessor::parameterChanged(const juce::String &id, float value) {
  for (auto listener : _listeners) {
    listener->onParameterChanged(id, value);
  }
}

void AudioProcessor::addFloatParameter(const juce::String &name,
                                       float min_value, float max_value,
                                       float default_value) {
  _parameters.createAndAddParameter(
      name, name, name, juce::NormalisableRange<float>(min_value, max_value),
      default_value, nullptr, nullptr, false, true, false);
  _parameters.addParameterListener(name, this);
}

void AudioProcessor::addIntParameter(const juce::String &name, int min_value,
                                     int max_value, int default_value) {
  _parameters.createAndAddParameter(
      name, name, name,
      juce::NormalisableRange<float>((float)min_value, (float)max_value),
      (float)default_value, nullptr, nullptr, false, true, false);
  _parameters.addParameterListener(name, this);
}

} // namespace easy
