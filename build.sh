#!/bin/bash -e

#cd JUCE/extras/Projucer/Builds/MacOSX/
#xcodebuild -configuration Release
#cd ../../../../../

JUCE/extras/Projucer/Builds/MacOSX/build/Release/Projucer.app/Contents/MacOS/Projucer --resave StudioLinkOnAir/StudioLinkOnAir.jucer

cd StudioLinkOnAir/Builds/MacOSX/
xcodebuild -configuration Release -xcconfig ../../../build.xconfig
cd ../../../
