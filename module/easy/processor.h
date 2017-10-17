#pragma once

namespace easy {
class Processor : public juce::AudioProcessorValueTreeState::Listener {
public:
  struct Listener {
    virtual ~Listener() {}

    virtual void onParameterChanged(const juce::String &id, float value) = 0;
  };
  inline Processor(juce::AudioProcessor *audio_processor);

  inline void addListener(Listener *listener)
  {
    _listeners.push_back(listener);
  }

  inline void addFloatParameter(const juce::String &name, float min_value,
                                float max_value, float default_value);

  inline void addIntParameter(const juce::String &name, int min_value,
                              int max_value, int default_value);

  inline juce::AudioProcessorValueTreeState &getParametersState()
  {
    return _parameters;
  }

protected:
  inline void parameterChanged(const juce::String &id, float newValue) override;

private:
  juce::AudioProcessor *_audio_processor;
  juce::AudioProcessorValueTreeState _parameters;
  std::vector<Listener *> _listeners;
};

/*
 * Implementation.
 */
Processor::Processor(juce::AudioProcessor *audio_processor)
  : _audio_processor(audio_processor), _parameters(*audio_processor, nullptr)
{
}

void Processor::parameterChanged(const juce::String &id, float value)
{
  for (auto listener : _listeners) {
    listener->onParameterChanged(id, value);
  }
}

void Processor::addFloatParameter(const juce::String &name, float min_value,
                                  float max_value, float default_value)
{
  _parameters.createAndAddParameter(
      name, name, name, juce::NormalisableRange<float>(min_value, max_value),
      default_value, nullptr, nullptr, false, true, false);
  _parameters.addParameterListener(name, this);
}

void Processor::addIntParameter(const juce::String &name, int min_value,
                                int max_value, int default_value)
{
  _parameters.createAndAddParameter(
      name, name, name,
      juce::NormalisableRange<float>((float)min_value, (float)max_value),
      (float)default_value, nullptr, nullptr, false, true, false);
  _parameters.addParameterListener(name, this);
}

} // namespace easy
