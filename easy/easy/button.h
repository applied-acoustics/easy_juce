#pragma once

//#include "../JuceLibraryCode/JuceHeader.h"

namespace easy {
class Button : public juce::Component, public juce::Button::Listener {
public:
  inline Button(const juce::String &name,
                juce::AudioProcessorValueTreeState &parameters);

protected:
  inline void resized() override;
  inline void paint(juce::Graphics &gc) override;
  inline void buttonClicked(juce::Button *button) override;

private:
  juce::Label _label;
  juce::TextButton _button;
  std::shared_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>
      _button_attachement;
};

/*
 * Implementation.
 */
Button::Button(const juce::String &name,
               juce::AudioProcessorValueTreeState &parameters) {
  addAndMakeVisible(_label);
  _label.setText(name, juce::NotificationType::dontSendNotification);
  _label.setBorderSize(juce::BorderSize<int>(1, 1, 1, 1));
  _label.setColour(juce::Label::outlineColourId, {142, 152, 155});
  _label.setJustificationType(juce::Justification::centred);

  addAndMakeVisible(_button);
  _button.addListener(this);

  _button.setClickingTogglesState(true);
  _button.setColour(juce::TextButton::buttonColourId, {180, 180, 180});
  _button.setColour(juce::TextButton::buttonOnColourId, {255, 0, 0});

  if (*parameters.getRawParameterValue(name)) {
    _button.setButtonText("ON");
    _button.setToggleState(true, juce::NotificationType::dontSendNotification);
  } else {
    _button.setButtonText("OFF");
    _button.setToggleState(false, juce::NotificationType::dontSendNotification);
  }

  _button_attachement =
      std::make_shared<juce::AudioProcessorValueTreeState::ButtonAttachment>(
          parameters, name, _button);
}

void Button::buttonClicked(juce::Button *button) {
  if (button->getToggleState() == false) {
    _button.setButtonText("OFF");

  } else {
    _button.setButtonText("ON");
  }
}

void Button::resized() {
  _label.setBounds(0, 0, 80, getHeight());
  _button.setBounds(_label.getRight() + 10, 0,
                    getWidth() - _label.getWidth() - 10, getHeight());
}

void Button::paint(juce::Graphics &gc) { gc.fillAll({180, 180, 180}); }
} // namespace easy
