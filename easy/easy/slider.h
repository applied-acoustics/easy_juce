#pragma once

namespace easy {
class Slider : public juce::Component {
public:
  inline Slider(const juce::String &name,
                juce::AudioProcessorValueTreeState &parameters,
                const juce::String& suffix = "");

protected:
  inline void resized() override;
  inline void paint(juce::Graphics &gc) override;

private:
  juce::Label _min_label;
  juce::Label _max_label;
  juce::Label _label;
  juce::Slider _slider;
  std::shared_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      _slider_attachement;
};

/*
 * Implementation.
 */
Slider::Slider(const juce::String &name,
               juce::AudioProcessorValueTreeState &parameters,
               const juce::String& suffix) {
  setName(name);
  addAndMakeVisible(_label);
  _label.setText(name, juce::NotificationType::dontSendNotification);
  _label.setBorderSize(juce::BorderSize<int>(1, 1, 1, 1));
  _label.setColour(juce::Label::outlineColourId, {142, 152, 155});
  _label.setJustificationType(juce::Justification::centred);

  addAndMakeVisible(_slider);
  _slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxRight,
                          false, 80, 20);
  if(!suffix.isEmpty()) {
    _slider.setTextValueSuffix(suffix);
  }

  _slider_attachement =
      std::make_shared<juce::AudioProcessorValueTreeState::SliderAttachment>(
          parameters, name, _slider);

  addAndMakeVisible(_min_label);
  _min_label.setText(juce::String(_slider.getMinimum()),
  juce::NotificationType::dontSendNotification);
  _min_label.setFont(juce::Font(10));
  _min_label.setBorderSize(juce::BorderSize<int>(1, 1, 1, 1));
  _min_label.setColour(juce::Label::outlineColourId, {142, 152, 155});
  _min_label.setColour(juce::Label::textColourId, {0, 0, 0});
  _min_label.setJustificationType(juce::Justification::centred);

  addAndMakeVisible(_max_label);
  _max_label.setText(juce::String(_slider.getMaximum()),
    juce::NotificationType::dontSendNotification);
  _max_label.setFont(juce::Font(10));
  _max_label.setBorderSize(juce::BorderSize<int>(1, 1, 1, 1));
  _max_label.setColour(juce::Label::outlineColourId, {142, 152, 155});
  _max_label.setColour(juce::Label::textColourId, {0, 0, 0});
  _max_label.setJustificationType(juce::Justification::centred);
}

void Slider::resized() {
  _label.setBounds(0, 0, 200, getHeight());
  _min_label.setBounds(_label.getRight() - 1, 0, 50, getHeight());
  _slider.setBounds(_min_label.getRight(), 0, getWidth() - _label.getWidth() - 100,
                    getHeight());
  _max_label.setBounds(_slider.getRight() - 1, 0, 50, getHeight());
}

void Slider::paint(juce::Graphics &gc) { gc.fillAll({180, 180, 180}); }
} // namespace easy
