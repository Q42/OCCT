# Building occt (OpenCascade technologies) as a static library for Apple platforms

Git clone:

```bash
git clone git@github.com:Q42/OCCT.git
cd OCCT
```

Generate an Xcode project using CMake:

```bash
mkdir build && cd build

cmake .. \
-G Xcode \
-DIOS=1 \
-DCMAKE_OSX_SYSROOT=/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS16.1.sdk \
-DCMAKE_OSX_DEPLOYMENT_TARGET=16.0 \
-DCMAKE_BUILD_TYPE=Release \
-DBUILD_LIBRARY_TYPE=Static \
-DUSE_FREETYPE=0 \
-DUSE_FREEIMAGE=0 \
-DUSE_OPENVR=0 \
-DUSE_OPENGL=0 \
-DUSE_GLES2=0 \
-DUSE_RAPIDJSON=0 \
-DUSE_DRACO=0 \
-DUSE_TK=0 \
-DUSE_TCL=0 \
-DUSE_TBB=0 \
-DUSE_VTK=0
```

Perform these manual steps:
1. Open the Xcode project
2. Select all targets, and under build settings (customized), delete the following build settings:
  * Architectures
  * Build products path
  * Installation directory

Now we can build the static libraries:

```bash
mkdir xcarchives
DEVELOPMENT_TEAM="team_id_here"

echo "==> Archiving for iOS..."
xcodebuild archive \
-project OCCT.xcodeproj \
-scheme ALL_BUILD \
-destination generic/platform=iOS \
-archivePath "xcarchives/OCCT-iOS.xcarchive" \
SKIP_INSTALL=NO \
BUILD_LIBRARY_FOR_DISTRIBUTION=YES \
DEVELOPMENT_TEAM=$DEVELOPMENT_TEAM

echo "==> Archiving for iOS Simulator (arm64)..."
xcodebuild archive \
-project OCCT.xcodeproj \
-scheme ALL_BUILD \
-destination "generic/platform=iOS Simulator" \
-archivePath "xcarchives/OCCT-iOS-Simulator-arm64.xcarchive" \
SKIP_INSTALL=NO \
BUILD_LIBRARY_FOR_DISTRIBUTION=YES \
DEVELOPMENT_TEAM=$DEVELOPMENT_TEAM \
ARCHS='arm64'

echo "==> Archiving for iOS Simulator (x86_64)..."
xcodebuild archive \
-project OCCT.xcodeproj \
-scheme ALL_BUILD \
-destination "generic/platform=iOS Simulator" \
-archivePath "xcarchives/OCCT-iOS-Simulator-x86_64.xcarchive" \
SKIP_INSTALL=NO \
BUILD_LIBRARY_FOR_DISTRIBUTION=YES \
DEVELOPMENT_TEAM=$DEVELOPMENT_TEAM \
ARCHS='x86_64'
```

Combine the built libraries into a single archive file for each architecture:

```bash
for ARCHIVE in "OCCT-iOS.xcarchive" "OCCT-iOS-Simulator-arm64.xcarchive" "OCCT-iOS-Simulator-x86_64.xcarchive"
do
    libtool -static -o xcarchives/$ARCHIVE/Products/usr/local/lib/occt.a xcarchives/$ARCHIVE/Products/usr/local/lib/*.a
done
```

Combine the Intel + ARM Simulator archives into a single one:

```bash
lipo -create xcarchives/OCCT-iOS-Simulator-arm64.xcarchive/Products/usr/local/lib/occt.a xcarchives/OCCT-iOS-Simulator-x86_64.xcarchive/Products/usr/local/lib/occt.a -output occt-simulator.a
```

Collect all the header files that need to be bundled with the final XCFramework:

```bash
mkdir -p xcheaders/opencascade
# Resolves the header files to find their actual contents and copies them to the 'xcheaders/opencascade' directory.
cp $(sed -nr 's/\#include "(.*)"/\1/p' /Users/mathijs/Developer/occt/build/include/opencascade/*) ./xcheaders/opencascade/
```

Finally, create the XCFramework:

```bash
mkdir xcframeworks

echo "==> Creating xcframework..."
xcodebuild -create-xcframework \
-library xcarchives/OCCT-iOS.xcarchive/Products/usr/local/lib/occt.a \
-headers xcheaders/opencascade \
-library occt-simulator.a \
-headers xcheaders/opencascade \
-output xcframeworks/occt.xcframework
```

You final framework can be found at `xcframeworks/occt.xcframework`! 
Zip it and host it wherever you want to use it with the Swift Package Manager.
