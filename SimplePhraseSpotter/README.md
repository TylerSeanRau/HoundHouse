# SimplePhraseSpotter
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
