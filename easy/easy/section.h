#pragma once

namespace easy {
class Section : public juce::Component {
public:
  inline Section(const juce::String &name);

protected:
  inline void resized() override;
  inline void paint(juce::Graphics &gc) override;

private:
  juce::Label _label;
};

/*
 * Implementation.
 */
Section::Section(const juce::String &name) {
  setName(name);
  addAndMakeVisible(_label);
  _label.setText(name, juce::NotificationType::dontSendNotification);
  _label.setJustificationType(juce::Justification::centred);
}

void Section::resized() { _label.setBounds(0, 0, getWidth(), getHeight()); }

void Section::paint(juce::Graphics &gc) { gc.fillAll({180, 180, 180}); }
} // namespace easy
