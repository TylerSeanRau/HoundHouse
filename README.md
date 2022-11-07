# HoundHouse
This is a C++ client that interfaces with the [Houndify](http://houndify.com) platform and is meant to be run on a Raspberry Pi 3 B+ running Ubuntu 18.04 LTS.

I personally work on this repository via Elementary OS 5.0 (which runs Ubuntu 18.04 LTS under the hood) on a Dell XPS 13 9370. In addition I'm also using a handful of my personal Rasberry Pi 3 B+s that are running Ubuntu 18.04 LTS. To create Ubuntu 18.04 SD cards for use with my Pi 3 B+s I followed the instructions in the second post in [this thread on the Raspberry Pi forums](https://www.raspberrypi.org/forums/viewtopic.php?t=215724).

### Getting started

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

    5. **OPTIONAL** Clean up files that are no longer needed

            rm -rf ~/Downloads/HoundifyExplorer ~/Downloads/HoundifyExplorer.tar.gz

        * **_I strongly recommend you keep HoundifyExplorer and read its README. It's an invaluable debugging tool._**

