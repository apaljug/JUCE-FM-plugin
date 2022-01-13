
//  SineWaveVoice.hpp
//  AudioPluginDemo - All
//
//  Created by Keary Mobley on 1/13/22.
//  Copyright © 2022 JUCE. All rights reserved.
//
#include "SineWaveVoice.h"
#include "SineWaveSound.h"
//==============================================================================
/** A simple demo synth voice that just plays a sine wave.. */
SineWaveVoice::SineWaveVoice() {}

bool SineWaveVoice::canPlaySound (SynthesiserSound* sound)
{
    return dynamic_cast<SineWaveSound*> (sound) != nullptr;
}

void SineWaveVoice::startNote (int midiNoteNumber, float velocity,
                SynthesiserSound* /*sound*/, int)
{
    
    
    currentAngle = 0.0;
    level = velocity * 0.15;
    release = 0.0;

    if (modRatioDen == 0) {
        modRatio = 0.5;
    } else {
        modRatio = (modRatioNum * 1.0 / modRatioDen);
    }
    auto cyclesPerSecond = MidiMessage::getMidiNoteInHertz (midiNoteNumber);
    auto cyclesPerSample = (cyclesPerSecond)/ getSampleRate();

    angleDelta = cyclesPerSample * MathConstants<double>::twoPi;
    int modFreq = int(cyclesPerSecond * modRatio); //new
    // float freqDev = 10; //new
    
    auto modCyclesPerSample = modFreq / getSampleRate(); //new
    modAngleDelta = modCyclesPerSample * MathConstants<double>::twoPi;//new
    modIndex = freqDev / float(modFreq); //new
}

void SineWaveVoice::stopNote (float /*velocity*/, bool allowTailOff)
{
    if (allowTailOff)
    {
        // start a tail-off by setting this flag. The render callback will pick up on
        // this and do a fade out, calling clearCurrentNote() when it's finished.

        if (release == 0.0) // we only need to begin a tail-off if it's not already doing so - the
                            // stopNote method could be called more than once.
            release = 1.0;
    }
    else
    {
        // we're being told to stop playing immediately, so reset everything..

        clearCurrentNote();
        angleDelta = 0.0;
    }
}

void SineWaveVoice::pitchWheelMoved (int /*newValue*/)
{
    // not implemented for the purposes of this demo!
}
    
    
void SineWaveVoice::controllerMoved (int paramNum, int value)
{
    
    if (paramNum == 0) { //freqDev
        freqDev = value;
    } else if (paramNum == 1) {
        modRatioNum = value;
    } else if (paramNum == 2) {
        modRatioDen = value;
    }

}

void SineWaveVoice::renderNextBlock (AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    if (angleDelta != 0.0)
    {
        /*if (attack < 1) {
            while (--numSamples >= 0)
            {
                // auto currentSample = (float) (sin (currentAngle) * level * release);
                auto currentSample = (float) (sin (currentAngle + modIndex * sin( modCurrentAngle ) ) * level * attack);

                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample (i, startSample, currentSample);

                currentAngle += angleDelta;
                modCurrentAngle += modAngleDelta;
                ++startSample;

                attack *= 1.01;
         /Users/andreaspaljug/Downloads/olddownloads/JUCE 2/modules/juce_audio_plugin_client                }
        }
        else */ if (release > 0.0)
        {
            while (--numSamples >= 0)
            {
                // auto currentSample = (float) (sin (currentAngle) * level * release);
                auto currentSample = (float) (sin (currentAngle + modIndex * sin( modCurrentAngle ) ) * level * release);

                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample (i, startSample, currentSample);

                currentAngle += angleDelta;
                modCurrentAngle += modAngleDelta;
                ++startSample;

                release *= 0.99;
                if (release <= 0.005)
                {
                    // tells the synth that this voice has stopped
                    clearCurrentNote();

                    angleDelta = 0.0;
                    break;
                }
            }
        }
        else
        {
            while (--numSamples >= 0)
            {
                //auto currentSample = (float) (sin (currentAngle )) * level);
                auto currentSample = (float) (sin (currentAngle  + modIndex * sin( modCurrentAngle )) * level);
                
                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample (i, startSample, currentSample);

                currentAngle += angleDelta;
                modCurrentAngle += modAngleDelta;

                ++startSample;
            }
        }
    }
}
//TODO: Figure out what this is doing
//using SynthesiserVoice::renderNextBlock;
