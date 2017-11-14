#pragma once

namespace easy {
class Slider2DWidget : public juce::Component, public juce::Slider::Listener {
public:
  Slider2DWidget() {
    _normalized_x_value = 0.0f;
    _normalized_y_value = 0.0f;
  }

  virtual ~Slider2DWidget() {}

  inline void SetXSlider(juce::Slider *x_slider) {
    _x_slider = x_slider;
    _x_slider->addListener(this);
    _normalized_x_value = (x_slider->getValue() - x_slider->getMinimum()) /
                          (x_slider->getMaximum() - x_slider->getMinimum());
  }

  inline void SetYSlider(juce::Slider *y_slider) {
    _y_slider = y_slider;
    _y_slider->addListener(this);

    _normalized_y_value =
        1.0 - ((y_slider->getValue() - y_slider->getMinimum()) /
               (y_slider->getMaximum() - y_slider->getMinimum()));
  }

protected:
  inline virtual void sliderValueChanged(juce::Slider *slider) override;
  inline void mouseDown(const juce::MouseEvent &evt) override;
  inline void mouseDrag(const juce::MouseEvent &evt) override;
  inline void resized() override;
  inline void paint(juce::Graphics &gc) override;

private:
  double _normalized_x_value;
  double _normalized_y_value;
  juce::Slider *_x_slider = nullptr;
  juce::Slider *_y_slider = nullptr;
};

class Slider2D : public juce::Component {
public:
  inline Slider2D(const juce::String &name, const juce::String &x_slider_name,
                  const juce::String &y_slider_name,
                  juce::AudioProcessorValueTreeState &parameters);

protected:
  inline void resized() override;
  inline void paint(juce::Graphics &gc) override;

private:
  juce::Label _label;
  Slider2DWidget _slider;
  juce::Slider _x_slider;
  juce::Slider _y_slider;
  std::shared_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      _y_slider_attachement;

  std::shared_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      _x_slider_attachement;
};

template <typename T> inline T clamp(T d, T min, T max) {
  const T t = d < min ? min : d;
  return t > max ? max : t;
}

void Slider2DWidget::sliderValueChanged(juce::Slider *slider) {
  if (slider == _y_slider) {
    _normalized_y_value = 1.0 - ((slider->getValue() - slider->getMinimum()) /
                                 (slider->getMaximum() - slider->getMinimum()));
    repaint();
  } else if (slider == _x_slider) {

    _normalized_x_value = (slider->getValue() - slider->getMinimum()) /
                          (slider->getMaximum() - slider->getMinimum());
    repaint();
  }
}

void Slider2DWidget::mouseDown(const juce::MouseEvent &evt) {
  const float r = 15 * 0.5;
  const juce::Point<int> pos = evt.getPosition() - juce::Point<int>(r, r);
  _normalized_x_value = pos.x / (double)(getWidth() - 15);
  _normalized_y_value = pos.y / (double)(getHeight() - 15);
  _normalized_x_value = clamp(_normalized_x_value, 0.0, 1.0);
  _normalized_y_value = clamp(_normalized_y_value, 0.0, 1.0);

  const double y_value =
      (_y_slider->getMaximum() - _y_slider->getMinimum()) * _normalized_y_value;
  _y_slider->setValue(1.0 - y_value);

  const double x_value =
      (_x_slider->getMaximum() - _x_slider->getMinimum()) * _normalized_x_value;
  _x_slider->setValue(x_value);
  repaint();
}

void Slider2DWidget::mouseDrag(const juce::MouseEvent &evt) {
  const float r = 15 * 0.5;
  const juce::Point<int> pos = evt.getPosition() - juce::Point<int>(r, r);
  _normalized_x_value = pos.x / (double)(getWidth() - 15);
  _normalized_y_value = pos.y / (double)(getHeight() - 15);
  _normalized_x_value = clamp(_normalized_x_value, 0.0, 1.0);
  _normalized_y_value = clamp(_normalized_y_value, 0.0, 1.0);

  const double y_value =
      _y_slider->getMinimum() +
      (_y_slider->getMaximum() - _y_slider->getMinimum()) * _normalized_y_value;
  _y_slider->setValue(1.0 - y_value);

  const double x_value =
      _x_slider->getMinimum() +
      (_x_slider->getMaximum() - _x_slider->getMinimum()) * _normalized_x_value;
  _x_slider->setValue(x_value);
  repaint();
}

void Slider2DWidget::resized() { repaint(); }

void Slider2DWidget::paint(juce::Graphics &gc) {
  gc.setColour({24, 31, 34});
  gc.fillRoundedRectangle(0, 0, getWidth(), getHeight(), 6);
  gc.setColour(juce::Colour(71, 163, 198));
  gc.fillEllipse(_normalized_x_value * (getWidth() - 15),
                 _normalized_y_value * (getHeight() - 15), 15, 15);
}

/*
 * Implementation.
 */
Slider2D::Slider2D(const juce::String &name, const juce::String &x_slider_name,
                   const juce::String &y_slider_name,
                   juce::AudioProcessorValueTreeState &parameters) {
  setName(name);
  addAndMakeVisible(_label);
  _label.setText(name, juce::NotificationType::dontSendNotification);
  _label.setBorderSize(juce::BorderSize<int>(1, 1, 1, 1));
  _label.setColour(juce::Label::outlineColourId, {142, 152, 155});
  _label.setJustificationType(juce::Justification::centred);

  addAndMakeVisible(_slider);

  _x_slider_attachement =
      std::make_shared<juce::AudioProcessorValueTreeState::SliderAttachment>(
          parameters, x_slider_name, _x_slider);

  _x_slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxRight,
                            false, 80, 20);
  _x_slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
  addAndMakeVisible(_x_slider);

  _y_slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
  addAndMakeVisible(_y_slider);

  _y_slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxLeft,
                            false, 80, 20);
  _y_slider_attachement =
      std::make_shared<juce::AudioProcessorValueTreeState::SliderAttachment>(
          parameters, y_slider_name, _y_slider);

  _slider.SetXSlider(&_x_slider);
  _slider.SetYSlider(&_y_slider);
}

void Slider2D::resized() {
  _label.setBounds(0, 0, 200, 20);

  _slider.setBounds(_label.getRight() + 150, 0,
                    getWidth() - _label.getWidth() - 300, getHeight() - 30);

  _x_slider.setBounds(_slider.getX(), _slider.getBottom() + 5,
                      _slider.getWidth() + 80, 20);

  _y_slider.setBounds(_slider.getX() - 125, 0, 100, getHeight() - 25);
}

void Slider2D::paint(juce::Graphics &gc) { gc.fillAll({180, 180, 180}); }
} // namespace easy
