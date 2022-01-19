# JUCE-FM Plugin
Modifications to the JUCE Synthesizer Plugin Demo to incorporate FM synthesis.

This file has some small changes built on top of a JUCE tutorial to support some aspects of FM synthesis for your DAW plugin.  

#### The current iteration supports: 
 - (Added by Andreas) slider for index of modulation
 - (From Original Demo) Midi Playback with Volume Adjustment
 - (From Original Demo) Basic Envelope w/ Delay parameter
 
#### Todo: (Add the following)
 + Adjustment for ratio selector between mod freq and carrier freq
 + Envelope adjustment
    + Signal
    + ADSR adjustors
    
    
## Installation Guide (Mac OS)

Step 1: (intsallations)
Install [JUCE](https://juce.com) from source

Install [Xcode](https://developer.apple.com/xcode/)

Step 2: Open Audio Plugin Demo
Open "Audio Plugin Demo" within Juce tutorials directory, Make a copy of this demo in another location

Step 3: Replace build files with our custom source code
Replace "Source Code with our files from github"
This includes: 
- AudioPluginDemo.h
- Main.cpp

Step 4: Build 
Build tutorial in Xcode. Click the play button to build. Confirm no errors occur

Step 5: Move plugin to daw
- Find build file in this subdirectory within your project folder:
AudioPluginDemo/Builds/MacOSX/build/Debug/AudioPluginDemo.component
- Copy this file into:
/Library/Audio/Plug-Ins/Components
- Open Logic or garage band. (Restart if already open)
Check available plugins for "3rd party" plugins. Open this for testing of plugin.

[Walk thru link](https://producersociety.com/plug-ins-garageband/) for step 5 


## FM Synthesizer Links

[FM SYNTHS in under 4 minutes](https://www.youtube.com/watch?v=vvBl3YUBUyY)

[Logic Pro Guide to Frequency Modulation](https://support.apple.com/guide/logicpro/frequency-modulation-fm-synthesis-lgsife418213/mac)
