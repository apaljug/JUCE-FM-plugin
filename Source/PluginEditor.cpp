//
//  PluginProcessorEditor.hpp
//  AudioPluginDemo - All
//
//  Copyright © 2022 JUCE. All rights reserved.
//

#include "PluginEditor.h"




JuceDemoPluginAudioProcessorEditor::JuceDemoPluginAudioProcessorEditor (JuceDemoPluginAudioProcessor& owner)
   : AudioProcessorEditor       (owner),
     midiKeyboard               (owner.keyboardState, MidiKeyboardComponent::horizontalKeyboard),
     gainAttachment             (owner.state, "gain",  gainSlider),
     delayAttachment            (owner.state, "delay", delaySlider),
     modAttachment              (owner.state, "mod", modSlider),
     iNumAttachment             (owner.state, "indexNum", iNumBox),
     iDenAttachment             (owner.state, "indexDen", iDenBox),
     attackAttachment           (owner.state, "attack", attackSlider),
     sustainAttachment          (owner.state, "sustain", sustainSlider),
     releaseAttachment          (owner.state, "release", releaseSlider),
     mattackAttachment          (owner.state, "mattack", mattackSlider),
     msustainAttachment         (owner.state, "msustain", msustainSlider),
     mreleaseAttachment         (owner.state, "mrelease", mreleaseSlider),
     iEnvAttachment             (owner.state, "expLineEnv", iEnvBox),
     iModEnvAttachment          (owner.state, "expLinModEnv", iModBox),
     presetsAttachment          (owner.state, "presets", presetsBox),
     chebyshevAmpAttachment1    (owner.state, "chebyshevAmp1", chebyshevAmpSliders[chebyshev1]),
     chebyshevAmpAttachment2    (owner.state, "chebyshevAmp2", chebyshevAmpSliders[chebyshev2]),
     chebyshevAmpAttachment3    (owner.state, "chebyshevAmp3", chebyshevAmpSliders[chebyshev3]),
     chebyshevAmpAttachment4    (owner.state, "chebyshevAmp4", chebyshevAmpSliders[chebyshev4]),
     chebyshevAmpAttachment5    (owner.state, "chebyshevAmp5", chebyshevAmpSliders[chebyshev5]),
     chebyshevAmpAttachment6    (owner.state, "chebyshevAmp6", chebyshevAmpSliders[chebyshev6]),
     chebyshevAmpAttachment7    (owner.state, "chebyshevAmp7", chebyshevAmpSliders[chebyshev7]),
     chebyshevAmpAttachment8    (owner.state, "chebyshevAmp8", chebyshevAmpSliders[chebyshev8]),
     chebyshevAmpAttachment9    (owner.state, "chebyshevAmp9", chebyshevAmpSliders[chebyshev9])


{
    //TODO: Is it possible to convert this to a for loop?
    // add some sliders..
    int w = lastUIWidth.getValue();
    int h = lastUIHeight.getValue();
    
    
    
    container.addAndMakeVisible (gainSlider);
    gainSlider.setSliderStyle (Slider::Rotary);
    
    container.addAndMakeVisible (delaySlider);
    delaySlider.setSliderStyle (Slider::Rotary);
    
    container.addAndMakeVisible (modSlider);
    modSlider.setSliderStyle (Slider::Rotary);
    
    
    
    container.addAndMakeVisible(attackSlider);
    attackSlider.setSliderStyle(Slider::Rotary);

    container.addAndMakeVisible(sustainSlider);
    sustainSlider.setSliderStyle(Slider::Rotary);

    container.addAndMakeVisible(releaseSlider);
    releaseSlider.setSliderStyle(Slider::Rotary);
   
    container.addAndMakeVisible(mattackSlider);
    mattackSlider.setSliderStyle(Slider::Rotary);

    container.addAndMakeVisible(msustainSlider);
    msustainSlider.setSliderStyle(Slider::Rotary);

    container.addAndMakeVisible(mreleaseSlider);
    mreleaseSlider.setSliderStyle(Slider::Rotary);
   
   
    for (int i = (int) chebyshev1; i < numberOfChebyshevs; i++)
    {
        container.addAndMakeVisible(chebyshevAmpSliders[i]);
        chebyshevAmpSliders[i].setTextBoxStyle(juce::Slider::NoTextBox, true, 20, 20);
    }
   
    container.addAndMakeVisible (resetEnvelope);
    resetEnvelope.setButtonText ("Reset Envelope.");
    resetEnvelope.addListener (this);
   
    container.addAndMakeVisible(resetModEnvelope);
    resetModEnvelope.setButtonText ("Reset Modulation Envelope.");
    resetModEnvelope.addListener (this);
   
    container.addAndMakeVisible(savePreset);
    savePreset.setButtonText("Save Preset");
    savePreset.addListener(this);
   
    container.addAndMakeVisible(presetsBox);

    container.addAndMakeVisible(iNumBox);
   
    for (int i = 2; i < 100; i++)
    {
        iNumBox.addItem(std::to_string(i), i);
    }
   
    container.addAndMakeVisible(iDenBox);
    for (int i = 2; i <= 20; i++)
    {
        iDenBox.addItem(std::to_string(i), i);
    }
   
    iDenBox.setSelectedId(2);
    iNumBox.setSelectedId(2);

   
    container.addAndMakeVisible(iEnvBox);
    iEnvBox.addItem("Lin Att. - Lin Dec.", 1);
    iEnvBox.addItem("Exp Att.. - Lin Dec.", 2);
    iEnvBox.addItem("Lin Att.. - Exp Dec.", 3);

    iEnvBox.addItem("Exp Att.. - Exp Dec.", 4);
   
    container.addAndMakeVisible(iModBox);
    iModBox.addItem("Lin Att. - Lin Dec.", 1);
    iModBox.addItem("Exp Att.. - Lin Dec.", 2);
    iModBox.addItem("Lin Att.. - Exp Dec.", 3);

    iModBox.addItem("Exp Att.. - Exp Dec.", 4);


           

    // add some labels for the sliders..
    const Font sliderLabelFont = Font(16.0f);
    gainLabel.attachToComponent (&gainSlider, false);
    gainLabel.setFont (sliderLabelFont);
    gainLabel.setJustificationType(juce::Justification::centred);

    delayLabel.attachToComponent (&delaySlider, false);
    delayLabel.setFont (sliderLabelFont);
    delayLabel.setJustificationType(juce::Justification::centred);
   
    modLabel.attachToComponent (&modSlider, false);
    modLabel.setFont (sliderLabelFont);
    modLabel.setJustificationType(juce::Justification::centred);
   
    numLabel.attachToComponent (&iNumBox, false);
    numLabel.setFont (sliderLabelFont);
    numLabel.setJustificationType(juce::Justification::centred);
   
    denLabel.attachToComponent (&iDenBox, false);
    denLabel.setFont (sliderLabelFont);
    denLabel.setJustificationType(juce::Justification::centred);

    attackLabel.attachToComponent(&attackSlider, false);
    attackLabel.setFont(sliderLabelFont);
    attackLabel.setJustificationType(juce::Justification::centred);

    sustainLabel.attachToComponent(&sustainSlider, false);
    sustainLabel.setFont(sliderLabelFont);
    sustainLabel.setJustificationType(juce::Justification::centred);

    releaseLabel.attachToComponent(&releaseSlider, false);
    releaseLabel.setFont(sliderLabelFont);
    releaseLabel.setJustificationType(juce::Justification::centred);
   
    mattackLabel.attachToComponent(&mattackSlider, false);
    mattackLabel.setFont(sliderLabelFont);
    mattackLabel.setJustificationType(juce::Justification::centred);

    msustainLabel.attachToComponent(&msustainSlider, false);
    msustainLabel.setFont(sliderLabelFont);
    msustainLabel.setJustificationType(juce::Justification::centred);

    mreleaseLabel.attachToComponent(&mreleaseSlider, false);
    mreleaseLabel.setFont(sliderLabelFont);
    mreleaseLabel.setJustificationType(juce::Justification::centred);

    presetsLabel.attachToComponent(&presetsBox, false);
    presetsLabel.setFont(sliderLabelFont);
    presetsLabel.setJustificationType(juce::Justification::centred);
   
    //Add Chebyshev Labels
    for (int i = (int) chebyshev1; i < numberOfChebyshevs; i++)
    {
        chebyshevLabels[i].setText("Chebyshev " + std::to_string(i+1), {});
        chebyshevLabels[i].attachToComponent(&chebyshevAmpSliders[i], false);
        chebyshevLabels[i].setFont(sliderLabelFont);
        chebyshevLabels[i].setJustificationType(juce::Justification::centred);
    }

    // add the midi keyboard component..
    addAndMakeVisible (midiKeyboard);

    // add a label that will display the current timecode and status..
    addAndMakeVisible (timecodeDisplayLabel);
    timecodeDisplayLabel.setFont (Font (Font::getDefaultMonospacedFontName(), 15.0f, Font::plain));
    timecodeDisplayLabel.setJustificationType(juce::Justification::centred);
    
    
    //setResizable(true, true);

    lastUIWidth .referTo (owner.state.state.getChildWithName ("uiState").getPropertyAsValue ("width",  nullptr));
    lastUIHeight.referTo (owner.state.state.getChildWithName ("uiState").getPropertyAsValue ("height", nullptr));

    // set our component's initial size to be the last one that was stored in the filter's settings
    
    myViewport.setViewedComponent(&container, false);
    addAndMakeVisible(myViewport);
    setResizable(true, true);
    setSize (lastUIWidth.getValue(), lastUIHeight.getValue());

    lastUIWidth. addListener (this);
    lastUIHeight.addListener (this);

    updateTrackProperties();

    // start a timer which will keep our timecode display updated
    startTimerHz (30);
}
   
   

JuceDemoPluginAudioProcessorEditor::~JuceDemoPluginAudioProcessorEditor(){}
void JuceDemoPluginAudioProcessorEditor::buttonClicked (juce::Button* button)
{
    if (button == &resetEnvelope)
    {
        releaseSlider.setValue(0.0);
        sustainSlider.setValue(100.0);
        attackSlider.setValue(0.0);
   }else  if (button == &resetModEnvelope)  {
       // [6]
       mreleaseSlider.setValue(0.0);
       msustainSlider.setValue(100.0);
       mattackSlider.setValue(0.0);
  }
}

//===============================================================================
void JuceDemoPluginAudioProcessorEditor::paint (Graphics& g)
{
    g.setColour (backgroundColour);
    g.fillAll();
}

void JuceDemoPluginAudioProcessorEditor::resized()
{
    // This lays out our child components...
    auto r  = getLocalBounds();
        
    timecodeDisplayLabel.setBounds (r.removeFromTop (30));
    midiKeyboard        .setBounds (r.removeFromBottom (70));
    
    container.setBounds(0, timecodeDisplayLabel.getHeight(), 1200, 700);
    myViewport.setBounds(0, timecodeDisplayLabel.getHeight(), getWidth(), getHeight() - midiKeyboard.getHeight() - timecodeDisplayLabel.getHeight() - 8);
    
    auto r2 = container.getLocalBounds();
    r2.removeFromTop (20);
    auto sliderArea     =   r2.removeFromTop(60);
    auto spacer         =   r2.removeFromTop(20);
    auto sliderArea2    =   r2.removeFromTop(60);
    auto spacer2        =   r2.removeFromTop(20);
    auto sliderArea3    =   r2.removeFromTop(60);
    auto sliderArea4    =   r2.removeFromTop(60);
    auto sliderArea5    =   r2.removeFromTop(60);
    auto sliderArea6    =   r2.removeFromTop(60);
    auto sliderArea7    =   r2.removeFromTop(60);
    
    gainSlider.setBounds(sliderArea.removeFromLeft (jmin (180, sliderArea.getWidth() / 2)));
    delaySlider.setBounds(sliderArea.removeFromLeft (jmin (180, sliderArea.getWidth())));
    modSlider.setBounds(sliderArea.removeFromLeft (jmin (180, sliderArea.getWidth())));
    iNumBox.setBounds(sliderArea.removeFromLeft (jmin (180, sliderArea.getWidth()/2)));
    auto boxSpacer_1a = sliderArea.removeFromLeft(20);
    iDenBox.setBounds(sliderArea.removeFromLeft (jmin (180, sliderArea.getWidth())));
    auto boxSpacer_1b = sliderArea.removeFromLeft(20);
    savePreset.setBounds(sliderArea.removeFromLeft(jmin(180, sliderArea.getWidth())));

    attackSlider.setBounds(sliderArea2.removeFromLeft(jmin(180, sliderArea2.getWidth())));
    sustainSlider.setBounds(sliderArea2.removeFromLeft(jmin(180, sliderArea2.getWidth())));
    releaseSlider.setBounds(sliderArea2.removeFromLeft(jmin(180, sliderArea2.getWidth())));
    resetEnvelope.setBounds(sliderArea2.removeFromLeft(jmin(180, sliderArea2.getWidth() /2)));
    auto boxSpacer_2a = sliderArea2.removeFromLeft(20);
    iEnvBox.setBounds (sliderArea2.removeFromLeft (jmin (180, sliderArea2.getWidth())));
    auto boxSpacer_2b = sliderArea2.removeFromLeft(20);
    presetsBox.setBounds(sliderArea2.removeFromLeft(jmin(180, sliderArea2.getWidth())));

    mattackSlider.setBounds(sliderArea3.removeFromLeft(jmin(180, sliderArea3.getWidth())));
    msustainSlider.setBounds(sliderArea3.removeFromLeft(jmin(180, sliderArea3.getWidth())));
    mreleaseSlider.setBounds(sliderArea3.removeFromLeft(jmin(180, sliderArea3.getWidth())));
    resetModEnvelope.setBounds(sliderArea3.removeFromLeft(jmin(180, sliderArea3.getWidth())));
    auto boxSpacer3a = sliderArea3.removeFromLeft(20);
    iModBox.setBounds (sliderArea3.removeFromLeft (jmin (180, sliderArea3.getWidth())));
    auto boxSpacer3b = sliderArea3.removeFromLeft(20);
    
    chebyshevAmpSliders[chebyshev1].setBounds(sliderArea4.removeFromLeft(jmin(180, sliderArea4.getWidth())));
    chebyshevAmpSliders[chebyshev2].setBounds(sliderArea4.removeFromLeft(jmin(180, sliderArea4.getWidth())));
    chebyshevAmpSliders[chebyshev3].setBounds(sliderArea4.removeFromLeft(jmin(180, sliderArea4.getWidth())));
   
    chebyshevAmpSliders[chebyshev4].setBounds(sliderArea5.removeFromLeft(jmin(180, sliderArea5.getWidth())));
    chebyshevAmpSliders[chebyshev5].setBounds(sliderArea5.removeFromLeft(jmin(180, sliderArea5.getWidth())));
    chebyshevAmpSliders[chebyshev6].setBounds(sliderArea5.removeFromLeft(jmin(180, sliderArea5.getWidth())));
   
    chebyshevAmpSliders[chebyshev7].setBounds(sliderArea6.removeFromLeft(jmin(180, sliderArea6.getWidth())));
    chebyshevAmpSliders[chebyshev8].setBounds(sliderArea6.removeFromLeft(jmin(180, sliderArea6.getWidth())));
    chebyshevAmpSliders[chebyshev9].setBounds(sliderArea6.removeFromLeft(jmin(180, sliderArea6.getWidth())));
    
    lastUIWidth  = getWidth();
    lastUIHeight = getHeight();
}

void JuceDemoPluginAudioProcessorEditor::timerCallback()
{
    updateTimecodeDisplay (getProcessor().lastPosInfo.get());
}

void JuceDemoPluginAudioProcessorEditor::hostMIDIControllerIsAvailable (bool controllerIsAvailable)
{
    midiKeyboard.setVisible (! controllerIsAvailable);
}

int JuceDemoPluginAudioProcessorEditor::getControlParameterIndex (Component& control)
{
    if (&control == &gainSlider)
        return 0;
    if (&control == &delaySlider)
        return 1;
    return -1;
}

void JuceDemoPluginAudioProcessorEditor::updateTrackProperties()
{
    auto trackColour = getProcessor().getTrackProperties().colour;
    auto& lf = getLookAndFeel();
    
    backgroundColour = (trackColour == Colour() ? lf.findColour (ResizableWindow::backgroundColourId)
                                               : trackColour.withAlpha (1.0f).withBrightness (0.266f));
    repaint();
}


//==============================================================================
JuceDemoPluginAudioProcessor& JuceDemoPluginAudioProcessorEditor::getProcessor() const
{
    return static_cast<JuceDemoPluginAudioProcessor&> (processor);
}

//==============================================================================
// quick-and-dirty function to format a timecode string
String JuceDemoPluginAudioProcessorEditor::timeToTimecodeString (double seconds)
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
String JuceDemoPluginAudioProcessorEditor::quarterNotePositionToBarsBeatsString (double quarterNotes, int numerator, int denominator)
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
void JuceDemoPluginAudioProcessorEditor::updateTimecodeDisplay (AudioPlayHead::CurrentPositionInfo pos)
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
void JuceDemoPluginAudioProcessorEditor::valueChanged (Value&)
{
    setSize (lastUIWidth.getValue(), lastUIHeight.getValue());
}
