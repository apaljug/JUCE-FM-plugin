# JUCE-FM plugin
modifications to the juce synthesizer plugin demo to incorporate FM synthesis.

This file has some small changes built on top of a JUCE tutorial to support some aspects of FM synthesis for your DAW plugin.  

####The current iteration supports: 
 - (Added by Andreas) slider for index of modulation
 - (From Original Demo) Midi Playback with Volume Adjustment
 - (From Original Demo) Basic Envelope w/ Delay parameter
 
####Todo: (Add the following)
 + Adjustment for ratio selector between mod freq and carrier freq
 + Envelope adjustment
    + Signal
    + ADSR adjustors
    
    
##To run this adaption of the program (Mac os installation guide)

Step 1: (intsallations)
Install JUCE from source 
Install Xcode

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

Walk thru link for step 5: https://producersociety.com/plug-ins-garageband/

