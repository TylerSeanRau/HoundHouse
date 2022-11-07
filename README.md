# HoundHouse
This is a C++ client that interfaces with the [Houndify](http://houndify.com) platform and is meant to be run on a Raspberry Pi 3 B+ running Ubuntu 18.04 LTS.

I personally work on this repository via Elementary OS 5.0 (which runs Ubuntu 18.04 LTS under the hood) on a Dell XPS 13 9370. In addition I'm also using a handful of my personal Raspberry Pi 3 B+s that are running Ubuntu 18.04 LTS. To create Ubuntu 18.04 SD cards for use with my Pi 3 B+s I followed the instructions in the second post in [this thread on the Raspberry Pi forums](https://www.raspberrypi.org/forums/viewtopic.php?t=215724).

## Hardware Recommendations

These are the prodcuts that I recommend and they are also the ones that I will test. This must be kept in mind when developing any and all features for this repository; however note that the **Simple Drivers** in this repository should be able to function with any ALSA compatible microphone and speaker.

| Name | Function | Link To Source | Purchase Link |
| --- | --- | --- | --- |
| Raspberry Pi 3 B+ | **THE HEART OF IT ALL!!** | [Source](https://www.raspberrypi.org/products/raspberry-pi-3-model-b-plus/) | [Purchase](https://www.digikey.com/product-detail/en/raspberry-pi/RASPBERRY-PI-3-MODEL-B-/1690-1025-ND/8571724) |
| ReSpeaker 4-Mic Array | Microphone | [Source](http://wiki.seeedstudio.com/ReSpeaker_4_Mic_Array_for_Raspberry_Pi/) | [Purchase](https://www.digikey.com/product-detail/en/seeed-technology-co-ltd/103030216/1597-1549-ND/7650463) |
| Pibow 3 B+ Coupé Flotilla | Case/Protection | [Source](https://shop.pimoroni.com/products/pibow-coupe-for-raspberry-pi-3-b-plus?variant=2601078358026) | [Purchase](https://www.digikey.com/product-detail/en/pimoroni-ltd/PIM343/PIM343-ND/8574328) |
| Raspberry Pi Universal Power Supply | Power Supply | [Source](https://www.raspberrypi.org/products/raspberry-pi-universal-power-supply/) | [Purchase](https://www.digikey.com/product-detail/en/pimoroni-ltd/PIM343/PIM343-ND/8574328) |
| Sony XB10 | Speaker | [Source](https://www.sony.com/electronics/wireless-speakers/srs-xb10) | [Purchase](https://www.amazon.com/gp/product/B01N5UT6FC/ref=ppx_yo_dt_b_asin_title_o01__o00_s00?ie=UTF8&psc=1) |
| 6 Inch 3.5mm audio cable | Pi to Speaker link | | [Purchase](https://www.amazon.com/gp/product/B008A81PT4/ref=ppx_yo_dt_b_asin_title_o01__o00_s00?ie=UTF8&psc=1) |

Note: Yes, initially this project uses a speaker via the audio jack; however it may not in the future. The only stipulation about what speaker can be used is that it must be ALSA compatible. This could change in the future.

## Getting started

These are the steps you'll need to take to get up and running with this repository!

1. Clone this repository somewhere nice to work with

        git clone https://github.com/Harrian/HoundHouse.git ~/Downloads/HoundHouse

    * I use `~/Downloads/` throughout this README but feel free to use any directory you'd like, just be sure you always use the same substitute directory in its place.

2. Download and build the Houndify C++ Standard SDK
    1. Download the C++ Standard SDK from the Houndify [C++ SDKs page](https://www.houndify.com/sdks#CPP)

    2. Extract the file you downloaded in step one.

            tar -xvf HoundCpp.tar.gz -C ~/Downloads

    3. If you're working with this repository on an actual Raspberry Pi 3 B+ then you'll need to do a couple extra steps before making or you'll run into memory issues, both during compiling and during linking.
        * I've been running the following commands:

                cd ~/Downloads/HoundCpp
                for i in CFLAGS= CPP_FLAGS=; do for j in `grep -R "^$i" -l`; do sed -i "s/^$i/$i -Os -Wl,--no-keep-memory -Wl,--reduce-memory-overhead /g" $j; done; done
                for i in `grep -R -F '$(LINK_CPP) -o $(LINK_FLAGS)' -l`; do sed -i 's/^LINK_FLAGS=/LINK_FLAGS= -Os -Wl,--no-keep-memory -Wl,--reduce-memory-overhead /g; s/$(LINK_CPP) -o $(LINK_FLAGS)/$(LINK_CPP) $(LINK_FLAGS) -o/g' $i; done

    4. Run make
        * If you're on Linux with a decent machine running an 8 thread CPU

                cd ~/Downloads/HoundCpp
                make -j 8

        * If you're on OSX with a decent machine running an 8 thread CPU

                cd ~/Downloads/HoundCpp
                make -j 8 -f Makefile.OSX

        * If you're on a Raspberry Pi 3 B+ and running bash

                cd ~/Downloads/HoundCpp
                nohup bash -c 'make -j 2' > ../makelog 2>&1 & disown

3. Obtain the "Ok Hound" phrase spotter
    * A. If you're running Linux x86-64 follow these instructions
        1. First create a directory for these files in your local clone of this repository.

                mkdir -p ~/Downloads/HoundHouse/OkHound/linux-x86_64

        1. Download the **"Ok Hound" Phrase Spotter for Node.js Linux x86-64 (1.0.0)** from the Houndify [Javascript SDKs page](https://www.houndify.com/sdks#javascript)
            * **DO NOT DOWNLOAD TO THE DIRECTORY YOU CREATED IN 3.A.1**

        2. Extract the file you just downloaded

                tar -xvf okhound-nodejs-1.0.0-linux-x86_64.tar.gz -C ~/Downloads

        3. Extract the okhound library

                tar -xvf ~/Downloads/okhound-linux-x86_64/okhound-1.0.0.tgz -C ~/Downloads/okhound-linux-x86_64/

        4. Copy the needed files to the folder you created in step 3.A.1

                cp ~/Downloads/okhound-linux-x86_64/package/libPhraseSpotter.a ~/Downloads/okhound-linux-x86_64/package/PhraseSpotterAPI.h ~/Downloads/okhound-linux-x86_64/package/LICENSE* ~/Downloads/HoundHouse/OkHound/linux-x86_64

        5. Clean up files that are no longer needed

                rm -rf ~/Downloads/okhound-linux-x86_64/ ~/Downloads/okhound-nodejs-1.0.0-linux-x86_64.tar.gz

    * B. If you're running on a Raspberry Pi 3 B+ follow these instructions
        1. First create a directory for these files in your local clone of this repository.

                mkdir -p ~/Downloads/HoundHouse/OkHound/raspberrypi

        1. Download the **"Ok Hound" Phrase Spotter for Node.js Raspberry Pi 2 & 3 (1.0.0)** from the Houndify [Javascript SDKs page](https://www.houndify.com/sdks#javascript)
            * **DO NOT DOWNLOAD TO THE DIRECTORY YOU CREATED IN 3.B.1**

        2. Extract the file you just downloaded

                tar -xvf okhound-nodejs-1.0.0-pi2+3.tar.gz -C ~/Downloads

        3. Extract the okhound library

                tar -xvf ~/Downloads/okhound-pi2\&3/okhound-1.0.0.tgz -C ~/Downloads/okhound-pi2\&3/

        4. Copy the needed files to the folder you created in step 3.B.1

                cp ~/Downloads/okhound-pi2\&3/package/libPhraseSpotter.a ~/Downloads/okhound-pi2\&3/package/PhraseSpotterAPI.h ~/Downloads/okhound-pi2\&3/package/LICENSE* ~/Downloads/HoundHouse/OkHound/raspberrypi

        5. Clean up files that are no longer needed

                rm -rf ~/Downloads/okhound-pi2\&3/ ~/Downloads/okhound-nodejs-1.0.0-pi2+3.tar.gz

4. Extract useful utilities from HoundifyExplorer
    * Note, at some point I may create these utilities myself but for now the easiest thing to do was to use the files bundled with HoundifyExplorer

    1. First create a directory for these files in your local clone of this repository.

            mkdir -p ~/Downloads/HoundHouse/HoundifyExplorerUtils

    2. Download the **Houndify Explorer Source** from the Houndify [Houndify Explorer page](https://www.houndify.com/sdks#HoundifyExplorer)

    3. Extract the file you just downloaded.

            tar -xvf HoundifyExplorer.tar.gz -C ~/Downloads

    4. Copy utilities used by this repo

            cp ~/Downloads/HoundifyExplorer/HoundClientALSAAudio.cpp ~/Downloads/HoundHouse/HoundifyExplorerUtils
            cp ~/Downloads/HoundifyExplorer/HoundClientALSAAudio.h ~/Downloads/HoundHouse/HoundifyExplorerUtils
            cp ~/Downloads/HoundifyExplorer/PlatformSpecificClientCapabilities.h ~/Downloads/HoundHouse/HoundifyExplorerUtils
            cp ~/Downloads/HoundifyExplorer/PlatformSpecificClientCapabilitiesLinux.cpp ~/Downloads/HoundHouse/HoundifyExplorerUtils
            cp ~/Downloads/HoundifyExplorer/HoundAudioVerifier.h ~/Downloads/HoundHouse/HoundifyExplorerUtils

    5. **OPTIONAL** Clean up files that are no longer needed

            rm -rf ~/Downloads/HoundifyExplorer ~/Downloads/HoundifyExplorer.tar.gz

        * **_I strongly recommend you keep HoundifyExplorer and read its README. It's an invaluable debugging tool._**

## Building the SmartDevice libray

If you would like to take advantage of the smart devices libray that is included here then you'll need to build
the library.

To do so cd to `SmartDevices/lib` and run `make` this will build all the smart devices libraries and unify them
into a single SmartDevices library located `SmartDevices/lib/libSmartDevices.a`. It should be straight forward
to change makefiles to only use the specific subsection you'd like included in your project. (If space is a
concern.)

The simple demos make files should allow `-DWITHALLSMARTDEVICESUPPORT` to be added to `DEFINE_FEATURE_FLAGS` and
then the appopriate -I/-L/-l flags will be added to the different steps. Note, the `-I` flag goes from the
the `SmartDevices/include` directory. So you'll need to write `#include "*.h"` paths with the appopriate path.
(Or add the desired `include` folder to the `-I`.)

## Simple Demos

### SimplePhraseSpotter
SimplePhraseSpotter.cpp is a basic driver that uses an ALSA compatible microphone to watch for utterances of "Ok Hound"

* Normally the OkHoundSink class prints no ouput however when HOUNDHOUSEDEBUG is defined a print message is compiled in.
    * This is so that -DHOUNDHOUSEDEBUG can be used for debugging but doesn't change performance when not debugging.
    * -DHOUNDHOUSEDEBUG is passed to g++ by the different make files that are used to create the SimplePhraseSpotter

* To build on Linux x86_64

        cd ~/Downloads/HoundHouse/SimplePhraseSpotter
        make -f Makefile.Linux

* To build on a Raspberry Pi 3 B+

        cd ~/Downloads/HoundHouse/SimplePhraseSpotter
        make -f Makefile.Rpi

* To find a device name to use run `arecord -L`

* To run try:

        cd ~/Downloads/HoundHouse/SimplePhraseSpotter
        ./SimplePhraseSpotter.out alsa:plughw:CARD=PCH,DEV=0

    * Note you must prefix the ALSA device name with 'alsa:' when passing it to the simple spotter

### SimpleAudioQueriesOnlyWrittenResponse
SimpleAudioQueriesOnlyWrittenResponse.cpp is another basic driver that uses an ALSA compatible microphone to listen for utterences of "Ok Hound" and responds only with text on the screen. * *Note, it would not take much modification to make this driver support audio responses, most of the required changes would be inside the classes it uses not in the main .cpp file*

##### Basic Walkthrough
1. After hearing "Ok Hound" the client beings an audio query. This includes, but is not limited to, preparing the request info, sending the request info, and starting to transmit audio data.
2. The request info is prepared via the `prepare` method of the `SimpleRequestInfoPreparer` class. The only change to the request info that the preparer makes is that it asks the server to tell the client when it thinks that the user has finished speaking.
    * `SimpleRequestInfoPreparer` communicates that it would like the server to do this via `request_info->setServerDeterminesEndOfAudio(true);` in its `prepare` method.
3. `SimpleSinkWithoutClosingSound` will continue to send audio to the server until it tells it to stop or the `more_ok` method on the voice request returns false.
4. Finally the SimpleDynamicResponseHandlerWithNoAudioOutput will print the long written response.

#### Configuring

Currently to configure the `SimpleAudioQueriesOnlyWrittenResponse` to connect to the Houndify API properly one needs to make make a copy of `LocalConfig.cpp.example` named `LocalConfig.cpp`

        cd ~/Downloads/HoundHouse/SimpleAudioQueriesOnlyWrittenResponse
        cp LocalConfig.cpp.example LocalConfig.cpp

After that LocalConfig.cpp will look like the following:

```
/* file "LocalConfig.cpp" */

#include "SimpleHoundCloudRequesterConfig.h"

const SimpleHoundCloudRequesterConfig simple_config = {
  "YOUR CLIENT ID HERE", //this can be found on www.houndify.com
  "YOUR CLIENT KEY HERE", //this can be found on www.houndify.com
  "YOUR USER ID HERE" //you can make up whatever you'd like for this
};
```

From here information about your client will be required, you can obtain this info by creating a client on Houndify.com. After creating the client navigate to it and look for the **Overview & API Keys** section and you should find the Client Id and Client Key under the **Client Information** section on that page and then insert them into the appropriate places. Finally, give a user name to this client, this can be anything.

#### Building and Running
**You must configure LocalConfig.cpp before SimpleAudioQueriesOnlyWrittenResponse.out will build correctly**

* To build on Linux x86_64

        cd ~/Downloads/HoundHouse/SimpleAudioQueriesOnlyWrittenResponse
        make -f Makefile.Linux

* To build on a Raspberry Pi 3 B+

        cd ~/Downloads/HoundHouse/SimpleAudioQueriesOnlyWrittenResponse
        make -f Makefile.Rpi

    * To build on a Raspberry Pi 3 B+ with support for the ReSpeaker 4 Mic Array's LED Ring use:

        * First Build and install the WiringPi Library:

                cd ~/Downloads
                git clone git://git.drogon.net/wiringPi
                cd wiringPi
                ./build

        * Build on a Raspberry Pi 3 B+, with ReSpeaker 4 Mic Array LED support:

                cd ~/Downloads/HoundHouse/SimpleAudioQueriesOnlyWrittenResponse
                make -f Makefile.Rpi -j 2 DEFINE_FEATURE_FLAGS='-DRESPEAKERLEDRING'

* To find a device name to use run `arecord -L`

* To run try:

        cd ~/Downloads/HoundHouse/SimpleAudioQueriesOnlyWrittenResponse
        ./SimpleAudioQueriesOnlyWrittenResponse.out alsa:plughw:CARD=PCH,DEV=0

    * Note you must prefix the ALSA device name with 'alsa:' when passing it to the simple spotter
    * If you compiled with WiringPi support you'll need to run with `sudo`, this is to get hardware access the GPIO port. I'm looking into ways to remove the need for the use of `sudo`.

