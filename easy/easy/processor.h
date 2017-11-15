#pragma once
#include <iostream>

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

  inline void addIndexedParameter(const juce::String &name, int size,
                                  int default_value);

  inline juce::AudioProcessorValueTreeState &getParametersState() {
    return _parameters;
  }

  void getStateInformation(juce::MemoryBlock &destData) override {
    juce::String json =
        "{ \"preset\" : {\n\t\"version\" : \"0.0.1\",\n\t\"easy_juce\" : {\n";
    {
      for (int i = 0; i < getNumParameters() - 1; i++) {
        juce::String str = getParameterName(i);
        juce::String name = getParameterName(i);
        float value = *_parameters.getRawParameterValue(str);
        json += "\t\t\"" + str + "\" : " + juce::String(value) + ",\n";
      }

      // Last element.
      int i = getNumParameters() - 1;
      juce::String str = getParameterName(i);
      juce::String name = getParameterName(i);
      float value = *_parameters.getRawParameterValue(str);
      json += "\t\t\"" + str + "\" : " + juce::String(value) + "\n\t}\n}}";
    }

    destData = juce::MemoryBlock(json.toUTF8(), json.length() + 1);
  }

  void setUnnormalizedValue(const juce::String &name, float value) {
    if (juce::AudioProcessorParameter *p = _parameters.getParameter(name)) {
      const float newValue =
          _parameters.getParameterRange(name).convertTo0to1(value);
      p->setValueNotifyingHost(newValue);
    }
  }

  void setStateInformation(const void *raw_data, int sizeInBytes) override {
    juce::String json =
        juce::String::createStringFromData(raw_data, (int)sizeInBytes);
    juce::var data;
    juce::Result result = juce::JSON::parse(json, data);

    if (result) {
      const juce::var &preset = data["preset"];
      const juce::var &objeq = preset["easy_juce"];

      for (int i = 0; i < getNumParameters(); i++) {
        const juce::String name = getParameterName(i);
        const float value = objeq[name.toStdString().c_str()];
        setUnnormalizedValue(name, value);
      }
    }
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

void AudioProcessor::addIndexedParameter(const juce::String &name, int size,
                                         int default_value) {
  _parameters.createAndAddParameter(
      name, name, name,
      juce::NormalisableRange<float>((float)0, (float)(size - 1)),
      (float)default_value, nullptr, nullptr, false, true, false);
  _parameters.addParameterListener(name, this);
}

} // namespace easy
