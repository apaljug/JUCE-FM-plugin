//
//  PluginProcessorEditor.hpp
//  AudioPluginDemo - All
//
//  Copyright © 2022 JUCE. All rights reserved.
//
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
 class JuceDemoPluginAudioProcessorEditor  : public AudioProcessorEditor,
                                                private Timer,
                                                private Value::Listener
    {
    public:
        JuceDemoPluginAudioProcessorEditor (JuceDemoPluginAudioProcessor& owner);
        ~JuceDemoPluginAudioProcessorEditor() override;

        //==============================================================================
        void paint (Graphics& g) override;
        void resized() override;
        void timerCallback() override;
        void hostMIDIControllerIsAvailable (bool controllerIsAvailable) override;
        int getControlParameterIndex (Component& control) override;
        void updateTrackProperties();

    private:
        MidiKeyboardComponent midiKeyboard;

        Label timecodeDisplayLabel,
              gainLabel  { {}, "Throughput level:" },
              delayLabel { {}, "Delay:" },
              modLabel { {}, "Freq Mod (deviation):" },
              numLabel { {},  "Index Numerator:"},
              denLabel { {},  "Index Denominator:"},
              attackLabel {{}, "Attack Magnitude"},
            sustainLabel { {}, "Sustain"};
                //TODO: add sustain and gain labels
            

        Slider gainSlider, delaySlider, modSlider, attackSlider/*, iNumSlider, iDenSlider*/;
        
        ComboBox iNumBox, iDenBox;
        
        AudioProcessorValueTreeState::SliderAttachment gainAttachment, delayAttachment, modAttachment, attackAttachment; //Sustain attachment;

        /*,indexNumAttachment, indexDenAttachment;*/
        
        AudioProcessorValueTreeState::ComboBoxAttachment iNumAttachment, iDenAttachment;
        Colour backgroundColour;

        // these are used to persist the UI's size - the values are stored along with the
        // filter's other parameters, and the UI component will update them when it gets
        // resized.
        Value lastUIWidth, lastUIHeight;

        //==============================================================================
        JuceDemoPluginAudioProcessor& getProcessor() const;

        //==============================================================================
        // quick-and-dirty function to format a timecode string
        static String timeToTimecodeString (double seconds);

        // quick-and-dirty function to format a bars/beats string
        static String quarterNotePositionToBarsBeatsString (double quarterNotes, int numerator, int denominator);

        // Updates the text in our position label.
        void updateTimecodeDisplay (AudioPlayHead::CurrentPositionInfo pos);

        // called when the stored window size changes
        void valueChanged (Value&) override;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceDemoPluginAudioProcessorEditor)
    };
