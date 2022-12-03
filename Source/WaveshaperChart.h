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
#include "SineWaveVoice.h"
#pragma once


class WaveshaperChart  : public Component
{
public:
    enum ChartSettingsEnum{straightChart, sinChart, noneChart};
    WaveshaperChart ();
    ~WaveshaperChart() override;
    void resized() override;
    void setTitle(String titleString);
    void setChebyshevAmplitudes(float amplitude, SineWaveVoice::ChebyshevLevels chebyshevLevel);
    void plotChebyshev(float min, float max, ChartSettingsEnum setting);
    float chebyshevCalculation(int chebyshev, float x);
    float getChebyshevSignal(float currentSample);
    void plotFunction(float x, std::function<float(float, float)> func);
    void paint (Graphics& g) override;
    
    
    private:
        String title;
        std::function<int(int, int)> plotFunc;
        float plotMin, plotMax;
        int chebyshevLevel = 1;
        float chebyshevAmplitudes[SineWaveVoice::chebyshevLevelEnd];
        ChartSettingsEnum plotSetting = ChartSettingsEnum::noneChart;
        SineWaveVoice myVoice;
};
