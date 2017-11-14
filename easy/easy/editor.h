#pragma once

namespace easy {
class AudioProcessorEditor : public juce::AudioProcessorEditor {
public:
  inline AudioProcessorEditor(easy::AudioProcessor &easy_proc);

  inline AudioProcessorEditor(easy::AudioProcessor *easy_proc);

  inline void addSlider(const juce::String &name,
                        const juce::String &suffix = "");

  inline void addSlider2D(const juce::String &name,
                          const juce::String &x_slider_name,
                          const juce::String &y_slider_name);

  inline void addComboBox(const juce::String &name,
                          const std::vector<juce::String> &choices);

  inline void addToggle(const juce::String &name);

  inline void addSection(const juce::String &name);

  inline void setParameterVisibility(const juce::String &name, bool visible);

  inline void resize();

private:
  easy::AudioProcessor &_easy_proc;
  std::vector<juce::ScopedPointer<juce::Component>> _children;

  inline int getNumberOfVisibleParameters() const {
    int num = 0;
    for (auto &n : _children) {
      if (n->isVisible()) {
        num++;
      }
    }

    return num;
  }

  inline int getTotalHeight() const {
    int height = 10;
    for (auto &n : _children) {
      if (n->isVisible()) {
        height += n->getHeight() + 5;
      }
    }

    return height;
  }
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
    if (child->isVisible()) {
      child->setBounds(5, y, getWidth() - 10, child->getHeight());
      y = child->getBottom() + 5;
    }
  }
}

void AudioProcessorEditor::addSlider(const juce::String &name,
                                     const juce::String &suffix) {
  _children.push_back(
      new easy::Slider(name, _easy_proc.getParametersState(), suffix));
  addAndMakeVisible(_children.back());
  _children.back()->setSize(getWidth(), 20);
  setSize(800, getTotalHeight());
}

void AudioProcessorEditor::addSlider2D(const juce::String &name,
                                       const juce::String &x_slider_name,
                                       const juce::String &y_slider_name) {
  _children.push_back(new easy::Slider2D(name, x_slider_name, y_slider_name,
                                         _easy_proc.getParametersState()));
  addAndMakeVisible(_children.back());
  _children.back()->setSize(getWidth(), 200);
  setSize(800, getTotalHeight());
}

void AudioProcessorEditor::addComboBox(
    const juce::String &name, const std::vector<juce::String> &choices) {
  _children.push_back(
      new ComboBox(name, _easy_proc.getParametersState(), choices));
  addAndMakeVisible(_children.back());
  _children.back()->setSize(getWidth(), 20);
  setSize(800, getTotalHeight());
}

void AudioProcessorEditor::addToggle(const juce::String &name) {
  _children.push_back(new easy::Button(name, _easy_proc.getParametersState()));
  addAndMakeVisible(_children.back());
  _children.back()->setSize(getWidth(), 20);
  setSize(800, getTotalHeight());
}

void AudioProcessorEditor::addSection(const juce::String &name) {
  _children.push_back(new easy::Section(name));
  addAndMakeVisible(_children.back());
  _children.back()->setSize(getWidth(), 20);
  setSize(800, getTotalHeight());
}

void AudioProcessorEditor::setParameterVisibility(const juce::String &name,
                                                  bool visible) {
  for (auto &n : _children) {
    if (n->getName() == name) {
      n->setVisible(visible);
    }
  }

  setSize(800, getTotalHeight());
}
} // namespace easy
