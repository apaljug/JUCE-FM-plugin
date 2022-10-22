//
//  WaveshaperChart.h
//  FM Plugin
//
//  Created by Keary Mobley on 10/22/22.
//  Copyright © 2022 JUCE. All rights reserved.
//

#ifndef WaveshaperChart_h
#define WaveshaperChart_h
#endif /* WaveshaperChart_h */


#include <JuceHeader.h>
#pragma once


class WaveshaperChart  : public Component
{
public:
    WaveshaperChart ();
    ~WaveshaperChart() override;
    void setTitle(String titleString);
    void paint (Graphics& g) override;
    
    private:
        String title;
    
};
