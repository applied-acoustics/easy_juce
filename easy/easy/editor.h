#pragma once
#include <iostream>

namespace easy {
class Editor {
public:
  inline Editor(juce::Component *editor, Processor &easy_proc);
  inline void addSlider(const juce::String &name);

  inline void addComboBox(const juce::String &name,
                          const std::vector<juce::String> &choices);
  
  inline void addToggle(const juce::String &name);

  inline void resize();

private:
  juce::Component *_editor;
  Processor &_easy_proc;
  std::vector<juce::ScopedPointer<juce::Component>> _children;
};

/*
 * Implementation.
 */
Editor::Editor(juce::Component *editor, Processor &easy_proc)
  : _editor(editor), _easy_proc(easy_proc)
{
}

void Editor::resize()
{
  int y = 5;
  for (auto child : _editor->getChildren()) {
    child->setBounds(5, y, _editor->getWidth() - 10, 20);
    y += 25;
  }
}

void Editor::addSlider(const juce::String &name)
{
  _children.push_back(new easy::Slider(name, _easy_proc.getParametersState()));
  _editor->addAndMakeVisible(_children.back());

  _editor->setSize(600, 10 + (int)_children.size() * 25);
}

void Editor::addComboBox(const juce::String &name,
                         const std::vector<juce::String> &choices)
{
  _children.push_back(
      new ComboBox(name, _easy_proc.getParametersState(), choices));
  _editor->addAndMakeVisible(_children.back());

  _editor->setSize(600, 10 + (int)_children.size() * 25);
}

void Editor::addToggle(const juce::String &name) {
  _children.push_back(
      new easy::Button(name, _easy_proc.getParametersState()));
  _editor->addAndMakeVisible(_children.back());

  _editor->setSize(600, 10 + (int)_children.size() * 25);
}
} // namespace easy
