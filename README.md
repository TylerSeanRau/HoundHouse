# HoundHouse
This is a C++ client that interfaces with the [Houndify](http://houndify.com) platform and is meant to be run on a Raspberry Pi 3 B+ running Ubuntu 18.04 LTS.

I personally work on this repository via Elementary OS 5.0 (which runs Ubuntu 18.04 LTS under the hood) on a Dell XPS 13 9370. In addition I'm also using a handful of my personal Rasberry Pi 3 B+s that are running Ubuntu 18.04 LTS. To create Ubuntu 18.04 SD cards for use with my Pi 3 B+s I followed the instructions in the second post in [this thread on the Raspberry Pi forums](https://www.raspberrypi.org/forums/viewtopic.php?t=215724).

### Getting started

These are the steps you'll need to take to get up and running with this repository!

1.  Download and build the Houndify C++ Standard SDK
    1. Download the C++ Standard SDK from the Houndify [C++ SDKs page](https://www.houndify.com/sdks#CPP)

    2. Extract the file you downloaded in step one to somewhere nice to work wtih.
        *  I use `~/Downloads/` myself ex: `tar -xvf HoundCpp.tar.gz -C ~/Downloads`

    3. If you're working with this repository on an actual Raspberry Pi 3 B+ then you'll need to do a couple extra steps before making or you'll run into memory issues, both during compiling and during linking.
        * I've been running the following commands:

    cd ~/Downloads/HoundCpp
    for i in CFLAGS= CPP_FLAGS=; do for j in `grep -R "^$i" -l`; do sed -i "s/^$i/$i -Os -Wl,--no-keep-memory -Wl,--reduce-memory-overhead /g" $j; done; done
    for i in `grep -R -F '$(LINK_CPP) -o $(LINK_FLAGS)' -l`; do sed -i 's/^LINK_FLAGS=/LINK_FLAGS= -Os -Wl,--no-keep-memory -Wl,--reduce-memory-overhead /g; s/$(LINK_CPP) -o $(LINK_FLAGS)/$(LINK_CPP) $(LINK_FLAGS) -o/g' $i; done

        * Note, these aren't the only ways to account for the memory constraints of the Pi 3 B+ but they're the ones that I found got me off the ground fastest.  I plan to dig around later to see if there's a better solution.

    4. Run make

        * If you're on Linux with a decent machine running an 8 thread CPU

    cd ~/Downloads/HoundCpp
    make -j 8

        * If you're on OSX with a decent machine running an 8 thread CPU

    cd ~/Downloads/HoundCpp
    make -j 8 -f Makefile.OSX

        * If you're on a Raspberry Pi 3 B+ and running bash

    cd ~/Downloads/HoundCpp
    nohup bash -c 'make -j 4' > ../makelog 2>&1 & disown

