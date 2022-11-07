# SimpleAudioQueriesOnlyWrittenResponse
SimpleAudioQueriesOnlyWrittenResponse.cpp is another basic driver that uses an ALSA compatible microphone to listen for utterences of "Ok Hound" and responds only with text on the screen. * *Note, it would not take much modification to make this driver support audio responses, most of the required changes would be inside the classes it uses not in the main .cpp file*

### Basic Walkthrough
1. After hearing "Ok Hound" the client beings an audio query. This includes, but is not limited to, preparing the request info, sending the request info, and starting to transmit audio data.
2. The request info is prepared via the `prepare` method of the `SimpleRequestInfoPreparer` class. The only change to the request info that the preparer makes is that it asks the server to tell the client when it thinks that the user has finished speaking.
    * `SimpleRequestInfoPreparer` communicates that it would like the server to do this via `request_info->setServerDeterminesEndOfAudio(true);` in its `prepare` method.
3. `SimpleSinkWithoutClosingSound` will continue to send audio to the server until it tells it to stop or the `more_ok` method on the voice request returns false.
4. Finally the SimpleDynamicResponseHandlerWithNoAudioOutput will print the long written response.

## Configuring

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

## Building and Running
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

