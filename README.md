# easy_juce
Create fast Juce project for prototyping

# How to setup.

- Create a Juce audio plug-in project.

![Create project](/readme_images/choose_project.png?raw=true "Create project")

- Add easy module by adding `easy_juce/easy` folder.

![Add Module](/readme_images/add_module.png?raw=true "Add module")

- In the generated PluginEditor files. Change parent from `AudioProcessorEditor` to `easy::AudioProcessorEditor` in PluginEditor.h and do the same thing for the constructor in PluginEditor.cpp.

![Change heritage](/readme_images/plugin_editor_heritage.png?raw=true "Change heritage")

![Change constructor](/readme_images/plugin_editor_constructor.png?raw=true "Change constructor")

- In the generated PluginProcessor files. Change parent from `AudioProcessor` to `easy::AudioProcessor ` in PluginProcessor.h and do the same thing for the constructor in PluginProcessor.cpp.

![Change heritage](/readme_images/audio_heritage.png?raw=true "Change heritage")

![Change constructor](/readme_images/audio_constructor.png?raw=true "Change constructor")

- Then go back to PluginEditor.cpp and add replace the `resized()` and `paint()` function with this code :

```cpp
void paint (Graphics& g)
{
    g.fillAll ({180, 180, 180});
}

void resized()
{
    resize();
}
```

![Resize and repaint](/readme_images/resize_and_repaint.png?raw=true "Resize and repaint")

- Finally go back to PluginProcessor.h and override the `void parameterChanged(const juce::String &id, float value)` method and implement it in the .cpp file.

![Overload](/readme_images/param.png?raw=true "Overload")

That's it for the setup. You're now ready to add parameters to your plug-in.

# How to use.

## Add a slider parameter.

#### PluginProcessor
In the constructor of PluginProcessor.cpp add a float parameter :

```cpp
addFloatParameter("Gain", 0.0f, 1.0f, 1.0f);
```

Then in the `parameterChanged()` method you can implement the logic for the parameter change.

```cpp
void EffectAudioProcessor::parameterChanged(const juce::String &id, float value) {
  if(id == "Gain") {
    // Do something with Gain value.
  } 
}
```

#### PluginEditor
In the constructor of the editor in PluginEditor.cpp, you only need to add a slider _with the same name as the one created in PluginProcessor_.

```cpp
addSlider("Gain");
```

## Add a combo box parameter.

#### PluginProcessor
In the constructor of PluginProcessor.cpp add a int parameter :

```cpp
addIntParameter("Choice", 0, 2, 0);
```

Then in the `parameterChanged()` method you can implement the logic for the parameter change.

```cpp
void EffectAudioProcessor::parameterChanged(const juce::String &id, float value) {
  if(id == "Gain") {
    // Do something with Gain value.
  } else if(id == "Choice") {
    // Do something with Choice value.
  }
}
```

#### PluginEditor
In the constructor of the editor in PluginEditor.cpp, you only need to add a combo box _with the same name as the one created in PluginProcessor_. The number of choice has to be as the range given in PluginProcessor.

```cpp
addComboBox("Choice", {"A", "B", "C"});
```