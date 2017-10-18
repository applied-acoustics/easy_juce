#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

namespace easy {
class Slider : public juce::Component {
public:
  inline Slider(const juce::String &name,
                juce::AudioProcessorValueTreeState &parameters);

protected:
  inline void resized() override;
  inline void paint(juce::Graphics &gc) override;

private:
  juce::Label _label;
  juce::Slider _slider;
  std::shared_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      _slider_attachement;
};

/*
 * Implementation.
 */
Slider::Slider(const juce::String &name,
               juce::AudioProcessorValueTreeState &parameters) {
  addAndMakeVisible(_label);
  _label.setText(name, juce::NotificationType::dontSendNotification);
  _label.setBorderSize(juce::BorderSize<int>(1, 1, 1, 1));
  _label.setColour(juce::Label::outlineColourId, {142, 152, 155});
  _label.setJustificationType(juce::Justification::centred);

  addAndMakeVisible(_slider);
  _slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxRight,
                          false, 80, 20);
  _slider_attachement =
      std::make_shared<juce::AudioProcessorValueTreeState::SliderAttachment>(
          parameters, name, _slider);
}

void Slider::resized() {
  _label.setBounds(0, 0, 80, getHeight());
  _slider.setBounds(_label.getRight(), 0, getWidth() - _label.getWidth(),
                    getHeight());
}

void Slider::paint(juce::Graphics &gc) { gc.fillAll({180, 180, 180}); }
} // namespace easy
