//
//  SpinLockedPosInfo.hpp
//  AudioPluginDemo - All
//
//  Created by Keary Mobley on 1/13/22.
//  Copyright © 2022 JUCE. All rights reserved.
//

//TODO: Remember to change Juce Header include to ifndef
#include <JuceHeader.h>

class SpinLockedPosInfo
{
public:
    SpinLockedPosInfo();
    void set (const AudioPlayHead::CurrentPositionInfo& newInfo);
    AudioPlayHead::CurrentPositionInfo get() const noexcept;

private:
    juce::SpinLock mutex;
    AudioPlayHead::CurrentPositionInfo info;
};
