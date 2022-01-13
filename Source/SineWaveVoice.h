//
//  SineWaveVoice.hpp
//  AudioPluginDemo - All
//
//  Created by Keary Mobley on 1/13/22.
//  Copyright © 2022 JUCE. All rights reserved.
//
//==============================================================================
/** A simple demo synth voice that just plays a sine wave.. */

//TODO: Remember to change Juce Header include to ifndef
#include <JuceHeader.h>

class SineWaveVoice   : public SynthesiserVoice
{
public:
    SineWaveVoice();

    bool canPlaySound (SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound* /*sound*/, int) override;
    void stopNote (float /*velocity*/, bool allowTailOff) override;
    void pitchWheelMoved (int /*newValue*/) override;
    void controllerMoved (int paramNum, int value) override;
    void renderNextBlock (AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
    
    using SynthesiserVoice::renderNextBlock;

private:
    //sine parameters
    double currentAngle = 0.0;
    double angleDelta   = 0.0;
    double level        = 0.0;
    //adsr parameters
    //double attack       = 0.5;
    //TODO: add decay, sustain, etc.
    double release      = 0.5;
    
    //FM parameters
    double modCurrentAngle = 0.0;
    double modAngleDelta = 0.0;
    double modIndex = 0.0;
    int freqDev = 100;
    int modRatioNum = 1;
    int modRatioDen = 2;
    double modRatio = 0.5;
};
