#pragma once

namespace easy {
class AudioProcessorEditor : public juce::AudioProcessorEditor {
public:
  inline AudioProcessorEditor(easy::AudioProcessor &easy_proc);

  inline AudioProcessorEditor(easy::AudioProcessor *easy_proc);

  inline void addSlider(const juce::String &name);

  inline void addComboBox(const juce::String &name,
                          const std::vector<juce::String> &choices);

  inline void addToggle(const juce::String &name);

  inline void addSection(const juce::String &name);

  inline void resize();

private:
  easy::AudioProcessor &_easy_proc;
  std::vector<juce::ScopedPointer<juce::Component>> _children;
};

/*
 * Implementation.
 */
AudioProcessorEditor::AudioProcessorEditor(easy::AudioProcessor &easy_proc)
    : juce::AudioProcessorEditor(easy_proc), _easy_proc(easy_proc) {}

AudioProcessorEditor::AudioProcessorEditor(easy::AudioProcessor *easy_proc)
    : juce::AudioProcessorEditor(easy_proc), _easy_proc(*easy_proc) {}

void AudioProcessorEditor::resize() {
  int y = 5;
  for (auto child : getChildren()) {
    child->setBounds(5, y, getWidth() - 10, 20);
    y += 25;
  }
}

void AudioProcessorEditor::addSlider(const juce::String &name) {
  _children.push_back(new easy::Slider(name, _easy_proc.getParametersState()));
  addAndMakeVisible(_children.back());
  setSize(600, 10 + (int)_children.size() * 25);
}

void AudioProcessorEditor::addComboBox(
    const juce::String &name, const std::vector<juce::String> &choices) {
  _children.push_back(
      new ComboBox(name, _easy_proc.getParametersState(), choices));
  addAndMakeVisible(_children.back());
  setSize(600, 10 + (int)_children.size() * 25);
}

void AudioProcessorEditor::addToggle(const juce::String &name) {
  _children.push_back(new easy::Button(name, _easy_proc.getParametersState()));
  addAndMakeVisible(_children.back());
  setSize(600, 10 + (int)_children.size() * 25);
}

void AudioProcessorEditor::addSection(const juce::String &name) {
  _children.push_back(new easy::Section(name));
  addAndMakeVisible(_children.back());
  setSize(600, 10 + (int)_children.size() * 25);
}
} // namespace easy
