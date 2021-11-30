/*
  ==============================================================================

   This file is part of the JUCE examples.
   Copyright (c) 2020 - Raw Material Software Limited

   The code included in this file is provided under the terms of the ISC license
   http://www.isc.org/downloads/software-support-policy/isc-license. Permission
   To use, copy, modify, and/or distribute this software for any purpose with or
   without fee is hereby granted provided that the above copyright notice and
   this permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES,
   WHETHER EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR
   PURPOSE, ARE DISCLAIMED.

  ==============================================================================
*/

/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

 name:                  AudioPluginDemo
 version:               1.0.0
 vendor:                JUCE
 website:               http://juce.com
 description:           Synthesiser audio plugin.g

 dependencies:          juce_audio_basics, juce_audio_devices, juce_audio_formats,
                        juce_audio_plugin_client, juce_audio_processors,
                        juce_audio_utils, juce_core, juce_data_structures,
                        juce_events, juce_graphics, juce_gui_basics, juce_gui_extra
 exporters:             xcode_mac, vs2017, vs2019, linux_make, xcode_iphone, androidstudio

 moduleFlags:           JUCE_STRICT_REFCOUNTEDPOINTER=1

 type:                  AudioProcessor
 mainClass:             JuceDemoPluginAudioProcessor

 useLocalCopy:          1

 pluginCharacteristics: pluginIsSynth, pluginWantsMidiIn, pluginProducesMidiOut,
                        pluginEditorRequiresKeys
 extraPluginFormats:    AUv3

 END_JUCE_PIP_METADATA

*******************************************************************************/

#pragma once

//yuh yuh yuh yuh yuh
//==============================================================================
/** A demo synth sound that's just a basic sine wave.. */
class SineWaveSound : public SynthesiserSound
{
public:
    SineWaveSound() {}

    bool appliesToNote (int /*midiNoteNumber*/) override    { return true; }
    bool appliesToChannel (int /*midiChannel*/) override    { return true; }
};

//==============================================================================
/** A simple demo synth voice that just plays a sine wave.. */
class SineWaveVoice   : public SynthesiserVoice
{
public:
    SineWaveVoice() {}

    bool canPlaySound (SynthesiserSound* sound) override
    {
        return dynamic_cast<SineWaveSound*> (sound) != nullptr;
    }
  
    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound* /*sound*/, int) override
    {
    
        
       
        //release  = release_param;
        
        /*adsrParams.attack = attack_param;//0.01f;
        adsrParams.sustain = sustain_param;//1.0f;
        adsrParams.release = release_param;//0.01f;
        */
        adsrParams.decay = 10.0f;

        currentAngle = 0.0;
        level = velocity * adsrParams.sustain;
        release = 0.0;
        attack = .1;
        
        mrelease = 0.0;
        mattack = .1;

        if (modRatioDen == 0) {
            modRatio = 1.0;
        } else {
            modRatio = (float(modRatioNum) / float(modRatioDen));
        }
        auto cyclesPerSecond = MidiMessage::getMidiNoteInHertz (midiNoteNumber);
        auto cyclesPerSample = (cyclesPerSecond)/ getSampleRate();

        angleDelta = cyclesPerSample * MathConstants<double>::twoPi;
        int modFreq = int(cyclesPerSecond * modRatio); //new
        // float freqDev = 10; //new
        
        auto modCyclesPerSample = modFreq / getSampleRate(); //new
        modAngleDelta = modCyclesPerSample * MathConstants<double>::twoPi;//new
        modIndex = freqDev / float(modFreq); //new
        adsr.noteOn();
        
    }

    void stopNote (float /*velocity*/, bool allowTailOff) override
    {
        if (allowTailOff)
        {
            // start a tail-off by setting this flag. The render callback will pick up on
            // this and do a fade out, calling clearCurrentNote() when it's finished.

            if (release == 0.0) {// we only need to begin a tail-off if it's not already doing so - the
                                // stopNote method could be called more than once.
                release = adsrParams.release;
            }
        }
        else
        {
            // we're being told to stop playing immediately, so reset everything..

            clearCurrentNote();
            angleDelta = 0.0;
        }
        adsr.noteOff();
    }

    void pitchWheelMoved (int /*newValue*/) override
    {
        // not implemented for the purposes of this demo!
    }
    
    
    void controllerMoved (int paramNum, int value) override
    {
        
        if (paramNum == 0) { //freqDev
            freqDev = value;
        } else if (paramNum == 1) {
            modRatioNum = value;
        } else if (paramNum == 2) {
            modRatioDen = value;
        } else if (paramNum == 3) {
            adsrParams.attack = float(value / 100.0f);
        } else if (paramNum == 4) {
            adsrParams.sustain = 0.185 * float(value / 100.0f) ;
        } else if (paramNum == 5) {
            adsrParams.release    = float(value / 100.0f);
        } else if (paramNum == 6) {
            modAdsrParams.attack = float(value / 100.0f);
       } else if (paramNum == 7) {
           modAdsrParams.sustain = float(value / 100.0f) ;
       } else if (paramNum == 8) {
           modAdsrParams.release    = float(value / 100.0f);
       } /*else if (paramNum == 9) {
           if (value == 0) {
               att_is_exp = 1;
           } else {
               att_is_exp = 0;
           }
           if (value == 0) {
               dec_is_exp = 1;
           } else {
               dec_is_exp = 0;
           }
       } else if (paramNum == 10) {
           if (value == 1) {
               att_is_exp = 1;
           } else {
               att_is_exp = 0;
           }
           if (value == 1) {
               dec_is_exp = 1;
           } else {
               dec_is_exp = 0;
           }
          
        dec_is_exp = value;
       } else if (paramNum == 11) {
               
           if (value == 2) {
               dec_is_exp = 0;
           } else {
               att_is_exp = 1;
           }
           if (value == 2) {
               modatt_is_exp = 1;
           } else {
               modatt_is_exp = 0;
           }
       } else if (paramNum == 12) {
           if (value == 3) {
               att_is_exp = 1;
           } else {
               att_is_exp = 0;
           }
           if (value == 3) {
               moddec_is_exp = 1;
           } else {
               moddec_is_exp = 0;
           }
       }*/
    }

    void renderNextBlock (AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
    {
        if (angleDelta != 0.0)
        {
           
          if (release > 0.0)
            {
                while (--numSamples >= 0)
                {
                    // auto currentSample = (float) (sin (currentAngle) * level * release);
                    auto currentSample = (float) (sin (currentAngle + mrelease * mattack * modAdsrParams.sustain * modIndex * sin( modCurrentAngle ) ) * level * release * attack);

                    for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                        outputBuffer.addSample (i, startSample, currentSample);

                    currentAngle += angleDelta;
                    modCurrentAngle += modAngleDelta;
                    ++startSample;

                    if (adsrParams.release != 0) {
                        release *= 1.0 - pow(.1, adsrParams.release * 5.0) ;
                    } else {
                        release *= 1.0;
                    }
                    
                    if (modAdsrParams.release != 0) {
                        mrelease *= 1.0 - pow(.1, modAdsrParams.release * 5.0) ;
                    } else {
                        mrelease = 1.0;
                    }
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
                    if (attack >= .999)
                    {
                        attack = 1.0;
                    } else {
                        if (adsrParams.attack != 0.0){
                            if (att_is_exp) {
                                attack *= 1.0 + pow(.1, adsrParams.attack * 5.0);
                            } else {
                                attack +=  pow(.1, adsrParams.attack * 5.0);
                            }
                        } else {
                            attack = 1.0;
                        }
                    }
                    
                    if (mattack >= .999)
                    {
                        mattack = 1.0;
                    } else {
                        if (modAdsrParams.attack != 0.0){
                            mattack *= 1.0 + pow(.1, modAdsrParams.attack * 5.0);
                        } else {
                            mattack = 1.0;
                        }
                    }
                    
                    
                    
                    //auto currentSample = (float) (sin (currentAngle )) * level);
                    auto currentSample = (float) (sin (currentAngle  +  mattack * modAdsrParams.sustain * modIndex * sin( modCurrentAngle )) * level * attack);
                    
                    for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                        outputBuffer.addSample (i, startSample, currentSample);

                    currentAngle += angleDelta;
                    modCurrentAngle += modAngleDelta;

                    ++startSample;
                    
                    
                }
            }
            
            //adsr.setParameters(adsrParams);
            //adsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
        }
    }

    using SynthesiserVoice::renderNextBlock;
    

private:
    //sine parameters
    double currentAngle = 0.0;
    double angleDelta   = 0.0;
    double level        = 1.0;
    //adsr parameters
    int att_is_exp = 0;
    int dec_is_exp = 0;
    int modatt_is_exp = 1;
    int moddec_is_exp = 1;
    double attack_param       = 0.5;
    //TODO: add decay, sustain, etc.
    double sustain_param      = 1.0;
    double decay_param      = 1.0;
    double release_param     = 0.5;
    
    double release       = 0.0;
    double attack = .01;
  
    double mattack = 0.1;
    double mrelease = 0.0;
    
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
    juce::ADSR::Parameters modAdsrParams;
    //FM parameters
    double modCurrentAngle = 0.0;
    double modAngleDelta = 0.0;
    double modIndex = 0.0;
    int freqDev = 50;
    int modRatioNum = 1;
    int modRatioDen = 1;
    double modRatio = 1.0;
};

//==============================================================================
/** As the name suggest, this class does the actual audio processing. */
class JuceDemoPluginAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    JuceDemoPluginAudioProcessor()
        : AudioProcessor (getBusesProperties()),
          state (*this, nullptr, "state",
                 { std::make_unique<AudioParameterFloat> ("gain",  "Gain",           NormalisableRange<float> (0.0f, 1.0f), 1.0f),
                  std::make_unique<AudioParameterFloat> ("delay", "Delay Feedback", NormalisableRange<float> (0.0f, 100.0f), 0.0f),
                 std::make_unique<AudioParameterFloat> ("mod", "Modulation", NormalisableRange<float> (0.0f, 100.0f), 0.5f),
              std::make_unique<AudioParameterInt> ("indexNum", "Index Numerator", 2, 99, 2),
              std::make_unique<AudioParameterInt> ("indexDen", "Index Denominator", 2, 20, 2), //min, max, default
              std::make_unique<AudioParameterFloat>("attack", "Attack", NormalisableRange<float>(0.0f, 100.0f), 0.5f),
              std::make_unique<AudioParameterFloat>("sustain", "Sustain", NormalisableRange<float>(0.0f, 100.0f), 0.5f),
              std::make_unique<AudioParameterFloat>("release", "Release", NormalisableRange<float>(0.0f, 100.0f), 0.5f),
              
              std::make_unique<AudioParameterFloat>("mattack", "mAttack", NormalisableRange<float>(0.0f, 100.0f), 0.5f),
              std::make_unique<AudioParameterFloat>("msustain", "mSustain", NormalisableRange<float>(0.0f, 100.0f), 0.5f),
              std::make_unique<AudioParameterFloat>("mrelease", "mRelease", NormalisableRange<float>(0.0f, 100.0f), 0.5f),
              std::make_unique<AudioParameterInt> ("expLineEnv", "Index Numerator", 0, 3, 0),
              std::make_unique<AudioParameterInt> ("expLinModEnv", "Index Denominator", 0, 3, 0), //min, max, default
              })

               //    std::make_unique<AudioParameterFloat> ("delay", "Delay Feedback", NormalisableRange<float> (0.0f, 1.0f), 0.5f) })
    {
        // Add a sub-tree to store the state of our UI
        state.state.addChild ({ "uiState", { { "width",  800 }, { "height", 400 } }, {} }, -1, nullptr);

        initialiseSynth();
    }

    ~JuceDemoPluginAudioProcessor() override = default;

    //==============================================================================
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override
    {
        // Only mono/stereo and input/output must have same layout
        const auto& mainOutput = layouts.getMainOutputChannelSet();
        const auto& mainInput  = layouts.getMainInputChannelSet();

        // input and output layout must either be the same or the input must be disabled altogether
        if (! mainInput.isDisabled() && mainInput != mainOutput)
            return false;

        // do not allow disabling the main buses
        if (mainOutput.isDisabled())
            return false;

        // only allow stereo and mono
        if (mainOutput.size() > 2)
            return false;

        return true;
    }

    void prepareToPlay (double newSampleRate, int /*samplesPerBlock*/) override
    {
        // Use this method as the place to do any pre-playback
        // initialisation that you need..
        synth.setCurrentPlaybackSampleRate (newSampleRate);
        keyboardState.reset();

        if (isUsingDoublePrecision())
        {
            delayBufferDouble.setSize (2, 12000);
            delayBufferFloat .setSize (1, 1);
        }
        else
        {
            delayBufferFloat .setSize (2, 12000);
            delayBufferDouble.setSize (1, 1);
        }

        reset();
    }

    void releaseResources() override
    {
        // When playback stops, you can use this as an opportunity to free up any
        // spare memory, etc.
        keyboardState.reset();
    }

    void reset() override
    {
        // Use this method as the place to clear any delay lines, buffers, etc, as it
        // means there's been a break in the audio's continuity.
        delayBufferFloat .clear();
        delayBufferDouble.clear();
    }

    //==============================================================================
    void processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override
    {
        jassert (! isUsingDoublePrecision());
        process (buffer, midiMessages, delayBufferFloat);
    }

    void processBlock (AudioBuffer<double>& buffer, MidiBuffer& midiMessages) override
    {
        jassert (isUsingDoublePrecision());
        process (buffer, midiMessages, delayBufferDouble);
    }

    //==============================================================================
    bool hasEditor() const override                                   { return true; }

    AudioProcessorEditor* createEditor() override
    {
        return new JuceDemoPluginAudioProcessorEditor (*this);
    }

    //==============================================================================
    const String getName() const override                             { return "AudioPluginDemo"; }
    bool acceptsMidi() const override                                 { return true; }
    bool producesMidi() const override                                { return true; }
    double getTailLengthSeconds() const override                      { return 0.0; }

    //==============================================================================
    int getNumPrograms() override                                     { return 0; }
    int getCurrentProgram() override                                  { return 0; }
    void setCurrentProgram (int) override                             {}
    const String getProgramName (int) override                        { return {}; }
    void changeProgramName (int, const String&) override              {}

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override
    {
        // Store an xml representation of our state.
        if (auto xmlState = state.copyState().createXml())
            copyXmlToBinary (*xmlState, destData);
    }

    void setStateInformation (const void* data, int sizeInBytes) override
    {
        // Restore our plug-in's state from the xml representation stored in the above
        // method.
        if (auto xmlState = getXmlFromBinary (data, sizeInBytes))
            state.replaceState (ValueTree::fromXml (*xmlState));
    }

    //==============================================================================
    void updateTrackProperties (const TrackProperties& properties) override
    {
        {
            const ScopedLock sl (trackPropertiesLock);
            trackProperties = properties;
        }

        MessageManager::callAsync ([this]
        {
            if (auto* editor = dynamic_cast<JuceDemoPluginAudioProcessorEditor*> (getActiveEditor()))
                 editor->updateTrackProperties();
        });
    }

    TrackProperties getTrackProperties() const
    {
        const ScopedLock sl (trackPropertiesLock);
        return trackProperties;
    }

    class SpinLockedPosInfo
    {
    public:
        SpinLockedPosInfo() { info.resetToDefault(); }

        // Wait-free, but setting new info may fail if the main thread is currently
        // calling `get`. This is unlikely to matter in practice because
        // we'll be calling `set` much more frequently than `get`.
        void set (const AudioPlayHead::CurrentPositionInfo& newInfo)
        {
            const juce::SpinLock::ScopedTryLockType lock (mutex);

            if (lock.isLocked())
                info = newInfo;
        }

        AudioPlayHead::CurrentPositionInfo get() const noexcept
        {
            const juce::SpinLock::ScopedLockType lock (mutex);
            return info;
        }

    private:
        juce::SpinLock mutex;
        AudioPlayHead::CurrentPositionInfo info;
    };

    //==============================================================================
    // These properties are public so that our editor component can access them
    // A bit of a hacky way to do it, but it's only a demo! Obviously in your own
    // code you'll do this much more neatly..

    // this is kept up to date with the midi messages that arrive, and the UI component
    // registers with it so it can represent the incoming messages
    MidiKeyboardState keyboardState;

    // this keeps a copy of the last set of time info that was acquired during an audio
    // callback - the UI component will read this and display it.
    SpinLockedPosInfo lastPosInfo;

    // Our plug-in's current state
    AudioProcessorValueTreeState state;

private:
    //==============================================================================
    /** This is the editor component that our filter will display. */
    class JuceDemoPluginAudioProcessorEditor  : public AudioProcessorEditor,
                                                private Timer,
                                                private Value::Listener,//,
                                                public Button::Listener
    {
    public:
        JuceDemoPluginAudioProcessorEditor (JuceDemoPluginAudioProcessor& owner)
            : AudioProcessorEditor (owner),
              midiKeyboard         (owner.keyboardState, MidiKeyboardComponent::horizontalKeyboard),
              gainAttachment       (owner.state, "gain",  gainSlider),
              delayAttachment      (owner.state, "delay", delaySlider),
              modAttachment        (owner.state, "mod", modSlider),
              iNumAttachment   (owner.state, "indexNum", iNumBox),
              iDenAttachment   (owner.state, "indexDen", iDenBox),
              attackAttachment (owner.state, "attack", attackSlider),
              sustainAttachment(owner.state, "sustain", sustainSlider),
              releaseAttachment (owner.state, "release", releaseSlider),
                mattackAttachment (owner.state, "mattack", mattackSlider),
                msustainAttachment(owner.state, "msustain", msustainSlider),
                mreleaseAttachment (owner.state, "mrelease", mreleaseSlider),
                iEnvAttachment   (owner.state, "expLineEnv", iEnvBox),
                iModEnvAttachment   (owner.state, "expLinModEnv", iModBox)
        {
            // add some sliders..
            addAndMakeVisible (gainSlider);
            gainSlider.setSliderStyle (Slider::Rotary);

            addAndMakeVisible (delaySlider);
            delaySlider.setSliderStyle (Slider::Rotary);
            
            addAndMakeVisible (modSlider);
            modSlider.setSliderStyle (Slider::Rotary);

            addAndMakeVisible(attackSlider);
            attackSlider.setSliderStyle(Slider::Rotary);

            addAndMakeVisible(sustainSlider);
            sustainSlider.setSliderStyle(Slider::Rotary);

            addAndMakeVisible(releaseSlider);
            releaseSlider.setSliderStyle(Slider::Rotary);
            
            addAndMakeVisible(mattackSlider);
            mattackSlider.setSliderStyle(Slider::Rotary);

            addAndMakeVisible(msustainSlider);
            msustainSlider.setSliderStyle(Slider::Rotary);

            addAndMakeVisible(mreleaseSlider);
            mreleaseSlider.setSliderStyle(Slider::Rotary);
            
            addAndMakeVisible (resetEnvelope);
            resetEnvelope.setButtonText ("Reset Envelope.");
            resetEnvelope.addListener (this);
            
            addAndMakeVisible (resetModEnvelope);
            resetModEnvelope.setButtonText ("Reset Modulation Envelope.");
            resetModEnvelope.addListener (this);            /*addAndMakeVisible (iNumSlider);
            iNumSlider.setSliderStyle (Slider::Rotary);
            
            addAndMakeVisible (iDenSlider);
            iDenSlider.setSliderStyle (Slider::Rotary);*/
            
            addAndMakeVisible(iNumBox);
            
            for (int i = 2; i < 100; i++)
            { iNumBox.addItem(std::to_string(i), i);
            }
            
            addAndMakeVisible(iDenBox);
            for (int i = 2; i <= 20; i++)
            {
                iDenBox.addItem(std::to_string(i), i);
            }
            iDenBox.setSelectedId(2);
            iNumBox.setSelectedId(2);

            
            addAndMakeVisible(iEnvBox);
            iEnvBox.addItem("Lin Att. - Lin Dec.", 0);
            iEnvBox.addItem("Exp Att.. - Lin Dec.", 1);
            iEnvBox.addItem("Lin Att.. - Exp Dec.", 2);

            iEnvBox.addItem("Exp Att.. - Exp Dec.", 3);
            
            addAndMakeVisible(iModBox);
            iModBox.addItem("Lin Att. - Lin Dec.", 0);
            iModBox.addItem("Exp Att.. - Lin Dec.", 1);
            iModBox.addItem("Lin Att.. - Exp Dec.", 2);

            iModBox.addItem("Exp Att.. - Exp Dec.", 3);


                    

            // add some labels for the sliders..
            gainLabel.attachToComponent (&gainSlider, false);
            gainLabel.setFont (Font (11.0f));

            delayLabel.attachToComponent (&delaySlider, false);
            delayLabel.setFont (Font (11.0f));
            
            modLabel.attachToComponent (&modSlider, false);
            modLabel.setFont (Font (11.0f));
            
            numLabel.attachToComponent (&iNumBox, false);
            numLabel.setFont (Font (11.0f));
            
            denLabel.attachToComponent (&iDenBox, false);
            denLabel.setFont (Font (11.0f));

            attackLabel.attachToComponent(&attackSlider, false);
            attackLabel.setFont(Font(11.0f));

            sustainLabel.attachToComponent(&sustainSlider, false);
            sustainLabel.setFont(Font(11.0f));

            releaseLabel.attachToComponent(&releaseSlider, false);
            releaseLabel.setFont(Font(11.0f));
            
            mattackLabel.attachToComponent(&mattackSlider, false);
            attackLabel.setFont(Font(11.0f));

            msustainLabel.attachToComponent(&msustainSlider, false);
            msustainLabel.setFont(Font(11.0f));

            mreleaseLabel.attachToComponent(&mreleaseSlider, false);
            mreleaseLabel.setFont(Font(11.0f));

            // add the midi keyboard component..
            addAndMakeVisible (midiKeyboard);

            // add a label that will display the current timecode and status..
            addAndMakeVisible (timecodeDisplayLabel);
            timecodeDisplayLabel.setFont (Font (Font::getDefaultMonospacedFontName(), 15.0f, Font::plain));

            // set resize limits for this plug-in
            setResizeLimits (800, 400, 1024, 700);

            lastUIWidth .referTo (owner.state.state.getChildWithName ("uiState").getPropertyAsValue ("width",  nullptr));
            lastUIHeight.referTo (owner.state.state.getChildWithName ("uiState").getPropertyAsValue ("height", nullptr));

            // set our component's initial size to be the last one that was stored in the filter's settings
            setSize (lastUIWidth.getValue(), lastUIHeight.getValue());

            lastUIWidth. addListener (this);
            lastUIHeight.addListener (this);

            updateTrackProperties();

            // start a timer which will keep our timecode display updated
            startTimerHz (30);
        }
        
        
  
        ~JuceDemoPluginAudioProcessorEditor() override {}
        void buttonClicked (juce::Button* button) override  // [2]
        {
            if (button == &resetEnvelope)                                                      // [3]
            {
              
                 
              
                   // [6]
                   releaseSlider.setValue(0.0);
                   sustainSlider.setValue(100.0);
                   attackSlider.setValue(0.0);

            }else  if (button == &resetModEnvelope)  {                                                    // [3]
              
           
              
                   // [6]
                   mreleaseSlider.setValue(0.0);
                   msustainSlider.setValue(100.0);
                   mattackSlider.setValue(0.0);

           }
        }

        //============ ==================================================================
        void paint (Graphics& g) override
        {
            g.setColour (backgroundColour);
            g.fillAll();
        }

        void resized() override
        {
            // This lays out our child components...

            auto r = getLocalBounds().reduced (8);

            timecodeDisplayLabel.setBounds (r.removeFromTop (26));
            midiKeyboard        .setBounds (r.removeFromBottom (70));

            r.removeFromTop (20);
            auto sliderArea = r.removeFromTop (60);
            auto spacer = r.removeFromTop(20);
            auto sliderArea2 = r.removeFromTop (60);
            auto spacer2 = r.removeFromTop(20);
            auto sliderArea3 = r.removeFromTop (60);

            gainSlider.setBounds  (sliderArea.removeFromLeft (jmin (180, sliderArea.getWidth() / 2)));
            delaySlider.setBounds (sliderArea.removeFromLeft (jmin (180, sliderArea.getWidth())));
            modSlider.setBounds (sliderArea.removeFromLeft (jmin (180, sliderArea.getWidth())));
            iNumBox.setBounds (sliderArea.removeFromLeft (jmin (180, sliderArea.getWidth())));
            auto boxSpacer = sliderArea.removeFromLeft(20);
            iDenBox.setBounds (sliderArea.removeFromLeft (jmin (180, sliderArea.getWidth())));

            attackSlider.setBounds(sliderArea2.removeFromLeft(jmin(180, sliderArea2.getWidth())));
            sustainSlider.setBounds(sliderArea2.removeFromLeft(jmin(180, sliderArea2.getWidth())));
            releaseSlider.setBounds(sliderArea2.removeFromLeft(jmin(180, sliderArea2.getWidth())));
            resetEnvelope.setBounds(sliderArea2.removeFromLeft(jmin(180, sliderArea2.getWidth())));
            auto boxSpacer2 = sliderArea2.removeFromLeft(20);
            iEnvBox.setBounds (sliderArea2.removeFromLeft (jmin (180, sliderArea2.getWidth())));

            mattackSlider.setBounds(sliderArea3.removeFromLeft(jmin(180, sliderArea3.getWidth())));
            msustainSlider.setBounds(sliderArea3.removeFromLeft(jmin(180, sliderArea3.getWidth())));
            mreleaseSlider.setBounds(sliderArea3.removeFromLeft(jmin(180, sliderArea3.getWidth())));
            resetModEnvelope.setBounds(sliderArea3.removeFromLeft(jmin(180, sliderArea3.getWidth())));
            auto boxSpacer3 = sliderArea3.removeFromLeft(20);
            iModBox.setBounds (sliderArea3.removeFromLeft (jmin (180, sliderArea3.getWidth())));

            
            lastUIWidth  = getWidth();
            lastUIHeight = getHeight();
        }

        void timerCallback() override
        {
            updateTimecodeDisplay (getProcessor().lastPosInfo.get());
        }

        void hostMIDIControllerIsAvailable (bool controllerIsAvailable) override
        {
            midiKeyboard.setVisible (! controllerIsAvailable);
        }

        int getControlParameterIndex (Component& control) override
        {
            if (&control == &gainSlider)
                return 0;

            if (&control == &delaySlider)
                return 1;

            return -1;
        }

        void updateTrackProperties()
        {
            auto trackColour = getProcessor().getTrackProperties().colour;
            auto& lf = getLookAndFeel();

            backgroundColour = (trackColour == Colour() ? lf.findColour (ResizableWindow::backgroundColourId)
                                                        : trackColour.withAlpha (1.0f).withBrightness (0.266f));
            repaint();
        }

    private:
        MidiKeyboardComponent midiKeyboard;

        Label timecodeDisplayLabel,
            gainLabel{ {}, "Throughput level:" },
            delayLabel{ {}, "Delay:" },
            modLabel{ {}, "Freq Mod (deviation):" },
            numLabel{ {},  "Index Numerator:" },
            denLabel{ {},  "Index Denominator:" },
            attackLabel{ {}, "Attack Speed:" },
            sustainLabel{ {}, "Sustain Magnitude:" },
            releaseLabel{ {}, "Release Speed:" },
        mattackLabel{ {}, "Mod Attack Speed:" },
        msustainLabel{ {}, "Mod Sustain Magnitude:" },

        mreleaseLabel{ {}, "Mod Release Speed:" };


        Slider gainSlider, delaySlider, modSlider, attackSlider, sustainSlider, releaseSlider, mattackSlider, msustainSlider, mreleaseSlider/*, iNumSlider, iDenSlider*/;
        
        ComboBox iNumBox, iDenBox, iEnvBox, iModBox;
        
        juce::TextButton resetEnvelope, resetModEnvelope;
        
        AudioProcessorValueTreeState::SliderAttachment gainAttachment, delayAttachment, modAttachment, attackAttachment, sustainAttachment, releaseAttachment, mattackAttachment, msustainAttachment, mreleaseAttachment ;
        /*,indexNumAttachment, indexDenAttachment;*/
        
        AudioProcessorValueTreeState::ComboBoxAttachment iNumAttachment, iDenAttachment, iEnvAttachment, iModEnvAttachment;
        Colour backgroundColour;

        // these are used to persist the UI's size - the values are stored along with the
        // filter's other parameters, and the UI component will update them when it gets
        // resized.
        Value lastUIWidth, lastUIHeight;

        //==============================================================================
        JuceDemoPluginAudioProcessor& getProcessor() const
        {
            return static_cast<JuceDemoPluginAudioProcessor&> (processor);
        }

        //==============================================================================
        // quick-and-dirty function to format a timecode string
        static String timeToTimecodeString (double seconds)
        {
            auto millisecs = roundToInt (seconds * 1000.0);
            auto absMillisecs = std::abs (millisecs);

            return String::formatted ("%02d:%02d:%02d.%03d",
                                      millisecs / 3600000,
                                      (absMillisecs / 60000) % 60,
                                      (absMillisecs / 1000)  % 60,
                                      absMillisecs % 1000);
        }

        // quick-and-dirty function to format a bars/beats string
        static String quarterNotePositionToBarsBeatsString (double quarterNotes, int numerator, int denominator)
        {
            if (numerator == 0 || denominator == 0)
                return "1|1|000";

            auto quarterNotesPerBar = (numerator * 4 / denominator);
            auto beats  = (fmod (quarterNotes, quarterNotesPerBar) / quarterNotesPerBar) * numerator;

            auto bar    = ((int) quarterNotes) / quarterNotesPerBar + 1;
            auto beat   = ((int) beats) + 1;
            auto ticks  = ((int) (fmod (beats, 1.0) * 960.0 + 0.5));

            return String::formatted ("%d|%d|%03d", bar, beat, ticks);
        }

        // Updates the text in our position label.
        void updateTimecodeDisplay (AudioPlayHead::CurrentPositionInfo pos)
        {
            MemoryOutputStream displayText;

            displayText << "[" << SystemStats::getJUCEVersion() << "]   "
            << String (pos.bpm, 2) << " bpm, "
            << pos.timeSigNumerator << '/' << pos.timeSigDenominator
            << "  -  " << timeToTimecodeString (pos.timeInSeconds)
            << "  -  " << quarterNotePositionToBarsBeatsString (pos.ppqPosition,
                                                                pos.timeSigNumerator,
                                                                pos.timeSigDenominator);

            if (pos.isRecording)
                displayText << "  (recording)";
            else if (pos.isPlaying)
                displayText << "  (playing)";

            timecodeDisplayLabel.setText (displayText.toString(), dontSendNotification);
        }

        // called when the stored window size changes
        void valueChanged (Value&) override
        {
            setSize (lastUIWidth.getValue(), lastUIHeight.getValue());
        }
    };

    //==============================================================================
    template <typename FloatType>
    void process (AudioBuffer<FloatType>& buffer, MidiBuffer& midiMessages, AudioBuffer<FloatType>& delayBuffer)
    {
        auto gainParamValue  = state.getParameter ("gain") ->getValue();
        auto delayParamValue = state.getParameter ("delay")->getValue();
        auto modParamValue = state.getParameter ("mod")->getValue();
        auto numParamValue = state.getParameter ("indexNum")->getValue();
        auto denParamValue = state.getParameter ("indexDen")->getValue();

        auto att = state.getParameter ("attack")->getValue();
        auto sus = state.getParameter ("sustain")->getValue();
        auto rel = state.getParameter ("release")->getValue();
        
        auto matt = state.getParameter ("mattack")->getValue();
        auto msus = state.getParameter ("msustain")->getValue();
        auto mrel = state.getParameter ("mrelease")->getValue();
        
        
        auto lexenv = state.getParameter ("expLineEnv")->getValue();
        auto lexmenv = state.getParameter ("expLinModEnv")->getValue();


        auto numSamples = buffer.getNumSamples();

        // In case we have more outputs than inputs, we'll clear any output
        // channels that didn't contain input data, (because these aren't
        // guaranteed to be empty - they may contain garbage).
        for (auto i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
            buffer.clear (i, 0, numSamples);

        //synth.defineModulation(1.0, delayParamValue);
        // Now pass any incoming midi messages to our keyboard state object, and let it
        // add messages to the buffer if the user is clicking on the on-screen keys
        keyboardState.processNextMidiBuffer (midiMessages, 0, numSamples, true);

        for (int i = 0; i < synth.getNumVoices(); i++) {
            (synth.getVoice(i))->controllerMoved(0, 100 * modParamValue);
            (synth.getVoice(i))->controllerMoved(1, 100 * numParamValue);
            (synth.getVoice(i))->controllerMoved(2, 100 * denParamValue);
            (synth.getVoice(i))->controllerMoved(3, 100 * att);
            (synth.getVoice(i))->controllerMoved(4, 100 * sus);

            (synth.getVoice(i))->controllerMoved(5, 65 + 35 * (rel));
            
            
            (synth.getVoice(i))->controllerMoved(6, 100 * matt);
            (synth.getVoice(i))->controllerMoved(7, 100 * msus);
            (synth.getVoice(i))->controllerMoved(8, 65 + 35 * (mrel));
            
            for (int j = 9; j < 13; j++){
                if (lexenv < 2) {
                    if (j % 2== lexenv) {
                        (synth.getVoice(i))->controllerMoved(j, lexenv);
                    } else {
                        (synth.getVoice(i))->controllerMoved(j, lexenv);
                    }
                } else {
                    if (j % 2 == lexmenv) {
                        (synth.getVoice(i))->controllerMoved(j, lexmenv);
                    } else {
                        (synth.getVoice(i))->controllerMoved(j, lexmenv);
                    }
                }
            }


        }
        // and now get our synth to process these midi events and generate its output.
        synth.renderNextBlock (buffer, midiMessages, 0, numSamples);

        // Apply our delay effect to the new output..
        applyDelay (buffer, delayBuffer, delayParamValue);

        // Apply our gain change to the outgoing data..
        applyGain (buffer, delayBuffer, gainParamValue);

        // Now ask the host for the current time so we can store it to be displayed later...
        updateCurrentTimeInfoFromHost();
    }
    
    template <typename FloatType>
    void applyGain (AudioBuffer<FloatType>& buffer, AudioBuffer<FloatType>& delayBuffer, float gainLevel)
    {
        ignoreUnused (delayBuffer);

        for (auto channel = 0; channel < getTotalNumOutputChannels(); ++channel)
            buffer.applyGain (channel, 0, buffer.getNumSamples(), gainLevel);
    }

    template <typename FloatType>
    void applyDelay (AudioBuffer<FloatType>& buffer, AudioBuffer<FloatType>& delayBuffer, float delayLevel)
    {
        auto numSamples = buffer.getNumSamples();

        auto delayPos = 0;

        for (auto channel = 0; channel < getTotalNumOutputChannels(); ++channel)
        {
            auto channelData = buffer.getWritePointer (channel);
            auto delayData = delayBuffer.getWritePointer (jmin (channel, delayBuffer.getNumChannels() - 1));
            delayPos = delayPosition;

            for (auto i = 0; i < numSamples; ++i)
            {
                auto in = channelData[i];
                channelData[i] += delayData[delayPos];
                delayData[delayPos] = (delayData[delayPos] + in) * delayLevel;

                if (++delayPos >= delayBuffer.getNumSamples())
                    delayPos = 0;
            }
        }
        delayPosition = delayPos;
    }
    

    AudioBuffer<float> delayBufferFloat;
    AudioBuffer<double> delayBufferDouble;

    int delayPosition = 0;

    Synthesiser synth;

    CriticalSection trackPropertiesLock;
    TrackProperties trackProperties;
    

    void initialiseSynth()
    {
        auto numVoices = 8;

        // Add some voices...
        for (auto i = 0; i < numVoices; ++i)
            synth.addVoice (new SineWaveVoice());

        // ..and give the synth a sound to play
        synth.addSound (new SineWaveSound());
    }

    void updateCurrentTimeInfoFromHost()
    {
        const auto newInfo = [&]
        {
            if (auto* ph = getPlayHead())
            {
                AudioPlayHead::CurrentPositionInfo result;

                if (ph->getCurrentPosition (result))
                    return result;
            }

            // If the host fails to provide the current time, we'll just use default values
            AudioPlayHead::CurrentPositionInfo result;
            result.resetToDefault();
            return result;
        }();

        lastPosInfo.set (newInfo);
    }

    static BusesProperties getBusesProperties()
    {
        return BusesProperties().withInput  ("Input",  AudioChannelSet::stereo(), true)
                                .withOutput ("Output", AudioChannelSet::stereo(), true);
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceDemoPluginAudioProcessor)
};
