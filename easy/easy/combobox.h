#pragma once

namespace easy {
class ComboBox : public juce::Component {
public:
  inline ComboBox(const juce::String &name,
                  juce::AudioProcessorValueTreeState &parameters,
                  const std::vector<juce::String> &choices);

protected:
  inline void resized() override;
  inline void paint(juce::Graphics &gc) override;

private:
  juce::Label _label;
  juce::ComboBox _box;
  std::shared_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment>
      _box_attachement;
};

/*
 * Implementation.
 */
ComboBox::ComboBox(const juce::String &name,
                   juce::AudioProcessorValueTreeState &parameters,
                   const std::vector<juce::String> &choices) {
  setName(name);
  addAndMakeVisible(_label);
  _label.setText(name, juce::NotificationType::dontSendNotification);
  _label.setBorderSize(juce::BorderSize<int>(1, 1, 1, 1));
  _label.setColour(juce::Label::outlineColourId, {142, 152, 155});
  _label.setJustificationType(juce::Justification::centred);

  addAndMakeVisible(_box);
  _box.setColour(juce::ComboBox::outlineColourId, {142, 152, 155});
  _box.setColour(juce::ComboBox::backgroundColourId, {180, 180, 180});

  for (std::size_t i = 0; i < choices.size(); i++) {
    _box.addItem(choices[i], int(i + 1));
  }

  _box.setSelectedId(*parameters.getRawParameterValue(name));

  _box_attachement =
      std::make_shared<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(
          parameters, name, _box);
}

void ComboBox::resized() {
  _label.setBounds(0, 0, 200, getHeight());
  _box.setBounds(_label.getRight() + 10, 0, getWidth() - _label.getWidth() - 10,
                 getHeight());
}

void ComboBox::paint(juce::Graphics &gc) { gc.fillAll({180, 180, 180}); }
} // namespace easy
