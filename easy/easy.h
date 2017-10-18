#pragma once
#define AAS_EASY_H_INCLUDED

// BEGIN_JUCE_MODULE_DECLARATION
//
// ID:               easy
// vendor:           Applied Acoustics Systems
// version:          0.1.0
// name:             Easy prototyping
// description:
// website:          www.applied-acoustics.com
// license:          GPL/Commercial
//
// dependencies:     juce_core, juce_audio_basics, juce_events,
// juce_audio_processors, juce_graphics, juce_audio_devices OSXFrameworks:
// CoreAudio CoreMIDI DiscRecording iOSFrameworks:    CoreAudio CoreMIDI
// AudioToolbox AVFoundation linuxLibs: mingwLibs:
//
// END_JUCE_MODULE_DECLARATION

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_audio_plugin_client/juce_audio_plugin_client.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_opengl/juce_opengl.h>
#include <juce_video/juce_video.h>

#include <memory>
#include <vector>

#include "easy/button.h"
#include "easy/combobox.h"
#include "easy/slider.h"
#include "easy/section.h"

#include "easy/processor.h"
#include "easy/editor.h"

