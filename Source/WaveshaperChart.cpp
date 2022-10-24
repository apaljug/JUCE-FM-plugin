//
//  WaveshaperChart.cpp
//  FM Plugin
//
//  Created by Keary Mobley on 10/22/22.
//  Copyright © 2022 JUCE. All rights reserved.
//

#include "WaveshaperChart.h"


WaveshaperChart::WaveshaperChart(){}
WaveshaperChart::~WaveshaperChart(){}


void WaveshaperChart::paint(Graphics &g){
    g.setColour(juce::Colours::skyblue);
    auto textBox = getLocalBounds().removeFromTop(50);
    //g.drawRect (getLocalBounds());
    //g.drawRect (textBox);
    g.setFont(textBox.getHeight()/3);
    g.drawText(title, textBox, juce::Justification::centred, true);
    g.setColour(juce::Colours::peachpuff);
    Path wavePath;
    
    
    
    auto chartArea = getLocalBounds().reduced(50);
    g.drawRect(chartArea);
    auto w = chartArea.getWidth();
    auto h = chartArea.getHeight();
    auto startx = chartArea.getX();
    auto starty = chartArea.getCentreY();
    wavePath.startNewSubPath (startx, starty);
    for (auto x = 0; x < w; ++x)
    {
        wavePath.lineTo (startx++ , starty+ h/2 * std::sin (x* .2f));
    }
    
    g.setColour (getLookAndFeel().findColour (Slider::thumbColourId));
    g.strokePath (wavePath, PathStrokeType (2.0f));
}

void WaveshaperChart::setTitle(String titleString)
{
    title = titleString;
}

