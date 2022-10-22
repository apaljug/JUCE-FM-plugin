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
     gainAttachment             (owner.state, "gain",  sliders[gainSlider]),
     delayAttachment            (owner.state, "delay", sliders[delaySlider]),
     modAttachment              (owner.state, "mod", sliders[modSlider]),
     iNumAttachment             (owner.state, "indexNum", comboBoxes[iNumBox]),
     iDenAttachment             (owner.state, "indexDen", comboBoxes[iDenBox]),
     attackAttachment           (owner.state, "attack", sliders[attackSlider]),
     sustainAttachment          (owner.state, "sustain", sliders[sustainSlider]),
     releaseAttachment          (owner.state, "release", sliders[releaseSlider]),
     mattackAttachment          (owner.state, "mattack", sliders[mattackSlider]),
     msustainAttachment         (owner.state, "msustain", sliders[msustainSlider]),
     mreleaseAttachment         (owner.state, "mrelease", sliders[mreleaseSlider]),
     iEnvAttachment             (owner.state, "expLineEnv", comboBoxes[iEnvBox]),
     iModEnvAttachment          (owner.state, "expLinModEnv", comboBoxes[iModBox]),
     presetsAttachment          (owner.state, "presets", comboBoxes[presetsBox]),
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
    // Constants
    const int textBoxWidth  = 50;
    const int textBoxHeight = 20;
    const int numDecimalPlaces = 0;
    const Font sliderLabelFont = Font(16.0f);
    
    //Sliders
    for (int i = (int) gainSlider; i < numberOfSliders; i++)
    {
        container.addAndMakeVisible(sliders[i]);
        sliders[i].setSliderStyle(Slider::Rotary);
        sliders[i].setNumDecimalPlacesToDisplay(numDecimalPlaces);
        sliders[i].setTextBoxStyle(juce::Slider::TextBoxBelow, true, textBoxWidth, textBoxHeight);
    }
   
    for (int i = (int) chebyshev1; i < numberOfChebyshevs; i++)
    {
        container.addAndMakeVisible(chebyshevAmpSliders[i]);
        chebyshevAmpSliders[i].setNumDecimalPlacesToDisplay(numDecimalPlaces);
        chebyshevAmpSliders[i].setTextBoxStyle(juce::Slider::TextBoxBelow, true, textBoxWidth, textBoxHeight);
    }
    
    for (int i = (int) resetEnvelope; i < numberOfButtons; i++)
    {
        container.addAndMakeVisible (buttons[i]);
        buttons[i].addListener (this);
    }
    
    buttons[resetEnvelope].setButtonText ("Reset Envelope");
    buttons[resetModEnvelope].setButtonText ("Reset Modulation Envelope");
    buttons[savePreset].setButtonText("Save Preset");
    
    for (int i = (int) iNumBox; i < numberOfComboBoxes; i++)
    {
        container.addAndMakeVisible (comboBoxes[i]);
    }
   
    for (int i = 2; i < 100; i++)
    {
        comboBoxes[iNumBox].addItem(std::to_string(i), i);
    }
   
    
    for (int i = 2; i <= 20; i++)
    {
        comboBoxes[iDenBox].addItem(std::to_string(i), i);
    }
   
    comboBoxes[iDenBox].setSelectedId(2);
    comboBoxes[iNumBox].setSelectedId(2);

   
    
    comboBoxes[iEnvBox].addItem("Lin Att. - Lin Dec.", 1);
    comboBoxes[iEnvBox].addItem("Exp Att.. - Lin Dec.", 2);
    comboBoxes[iEnvBox].addItem("Lin Att.. - Exp Dec.", 3);

    comboBoxes[iEnvBox].addItem("Exp Att.. - Exp Dec.", 4);
   
    
    comboBoxes[iModBox].addItem("Lin Att. - Lin Dec.", 1);
    comboBoxes[iModBox].addItem("Exp Att.. - Lin Dec.", 2);
    comboBoxes[iModBox].addItem("Lin Att.. - Exp Dec.", 3);

    comboBoxes[iModBox].addItem("Exp Att.. - Exp Dec.", 4);


           

    // Add Labels to Sliders
    
    for (int i = (int) gainSlider; i < numberOfSliders; i++)
    {
        sliderLabels[i].setText(sliderLabelText[i], {});
        sliderLabels[i].attachToComponent (&sliders[i], false);
        sliderLabels[i].setFont (sliderLabelFont);
        sliderLabels[i].setJustificationType(juce::Justification::centred);
    }

    presetsLabel.attachToComponent(&comboBoxes[presetsBox], false);
    presetsLabel.setFont(sliderLabelFont);
    presetsLabel.setJustificationType(juce::Justification::centred);
    
    numeratorLabel.attachToComponent(&comboBoxes[iNumBox], false);
    numeratorLabel.setFont(sliderLabelFont);
    numeratorLabel.setJustificationType(juce::Justification::centred);
    
    denominatorLabel.attachToComponent(&comboBoxes[iDenBox], false);
    denominatorLabel.setFont(sliderLabelFont);
    denominatorLabel.setJustificationType(juce::Justification::centred);
    
    
   
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
    midiKeyboard.setScrollButtonWidth(getWidth()/20);

    // add a label that will display the current timecode and status..
    addAndMakeVisible (timecodeDisplayLabel);
    timecodeDisplayLabel.setFont (Font (Font::getDefaultMonospacedFontName(), 15.0f, Font::plain));
    timecodeDisplayLabel.setJustificationType(juce::Justification::centred);
    

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
    if (button == &buttons[resetEnvelope])
    {
        sliders[releaseSlider].setValue(0.0);
        sliders[sustainSlider].setValue(100.0);
        sliders[attackSlider].setValue(0.0);
   }else  if (button == &buttons[resetModEnvelope])  {
       // [6]
       sliders[mreleaseSlider].setValue(0.0);
       sliders[msustainSlider].setValue(100.0);
       sliders[mattackSlider].setValue(0.0);
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
    midiKeyboard.setScrollButtonWidth(getWidth()/20);
    
    juce::FlexBox sliderFlexBox;
    sliderFlexBox.flexWrap = juce::FlexBox::Wrap::wrap;
    sliderFlexBox.justifyContent = juce::FlexBox::JustifyContent::spaceAround;
    sliderFlexBox.alignContent = juce::FlexBox::AlignContent::spaceAround;
    sliderFlexBox.flexDirection = juce::FlexBox::Direction::row;
    
    juce::FlexBox comboBoxFlexBox;
    comboBoxFlexBox.flexWrap = juce::FlexBox::Wrap::wrap;
    comboBoxFlexBox.justifyContent = juce::FlexBox::JustifyContent::spaceAround;
    comboBoxFlexBox.alignContent = juce::FlexBox::AlignContent::spaceAround;
    comboBoxFlexBox.flexDirection = juce::FlexBox::Direction::row;
    
    juce::FlexBox chebyshevFlexBox;
    chebyshevFlexBox.flexWrap = juce::FlexBox::Wrap::wrap;
    chebyshevFlexBox.justifyContent = juce::FlexBox::JustifyContent::spaceAround;
    chebyshevFlexBox.alignContent = juce::FlexBox::AlignContent::spaceAround;
    chebyshevFlexBox.flexDirection = juce::FlexBox::Direction::row;
    
    juce::FlexBox fb5;
    fb5.flexWrap = juce::FlexBox::Wrap::wrap;
    fb5.justifyContent = juce::FlexBox::JustifyContent::spaceAround;
    fb5.alignContent = juce::FlexBox::AlignContent::spaceAround;
    fb5.flexDirection = juce::FlexBox::Direction::row;
    
    container.setBounds(0, 0, getWidth(), getHeight());
    myViewport.setBounds(0, timecodeDisplayLabel.getHeight(), getWidth(), getHeight() - midiKeyboard.getHeight() - timecodeDisplayLabel.getHeight() - 8);
    
    
    auto bounds = container.getLocalBounds();
    
    
    for (int i = (int) gainSlider; i < numberOfSliders; i++)
    {
        //sliderLabels[i].setFont(Font(getHeight()/getWidth()));
        sliderFlexBox.items.add(juce::FlexItem (sliders[i]).withMinWidth (flexw).withMinHeight (flexh));
    }
    
    for (int i= chebyshev1; i < numberOfChebyshevs; i++)
    {
        chebyshevFlexBox.items.add(juce::FlexItem (chebyshevAmpSliders[i]).withMinWidth (flexw).withMinHeight (flexh));
    }
    
    for (int i= iNumBox; i < numberOfComboBoxes; i++)
    {
        comboBoxFlexBox.items.add(juce::FlexItem (comboBoxes[i]).withMinWidth (flexw).withMinHeight (flexh));
    }
    
    for (int i= resetEnvelope; i < numberOfButtons; i++)
    {
        comboBoxFlexBox.items.add(juce::FlexItem (buttons[i]).withMinWidth (flexw).withMinHeight (flexh));
    }
    
    
    auto left = bounds.removeFromLeft(bounds.getWidth()/2);
    auto topLeft = left.removeFromTop(left.getHeight()/2);
    auto bottomLeft = left;
    auto right = bounds;
    auto topRight = right.removeFromTop(right.getHeight()/2);
    auto bottomRight = right;
    sliderFlexBox.performLayout(topLeft);
    chebyshevFlexBox.performLayout(bottomLeft);
    comboBoxFlexBox.performLayout(topRight);
    fb5.performLayout(bottomRight);
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
    if (&control == &sliders[gainSlider])
        return 0;
    if (&control == &sliders[delaySlider])
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
