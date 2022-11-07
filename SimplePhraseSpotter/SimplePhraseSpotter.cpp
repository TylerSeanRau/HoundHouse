/* file "SimplePhraseSpotter.cpp" */

#include "OkHoundSink.h"
#include "ClientCapabilityRegistry.h"
#include "PlatformSpecificClientCapabilities.h"
#include "throwf.h"
#include <iostream>

extern "C"
{
#include "o_integer.h"
}

int main(int argc, char** argv){
  
  if(argc!=2){
    std::cout << "Usage: "
              << (*(argv))
              << " "
              << "ALSARECORDINGDEVICE"
              << std::endl;

    std::cout << "ALSARECORDINGDEVICE should be a device name from `arecord -L` prefixed"
              << std::endl
              << "with 'alsa:' ex: alsa:plughw:CARD=PCH,DEV=0"
              << std::endl;
    return 1;
  }

  init_o_integer_module();

  ClientCapabilityRegistry capability_registry;
  do_platform_specific_client_capability_registration(&capability_registry);
  try{
    ClientCapabilityRegistry::AudioSource * audio_source_to_use =
      capability_registry.lookup_audio_source(*(argv+1));
    if (audio_source_to_use == NULL) {
      throwf("Specified using audio input `%s', but no audio "
             "input by that name is known.\n", *(argv+1));
    }
    while(true){
      OkHoundSink ok_hound_sink;
      audio_source_to_use->capture(16000, 1, 16, true, &ok_hound_sink);
    }
  }
  catch (char *e1){
    std::cerr<<"Error: "<<e1<<std::endl;
    free(e1);
    return 1;
  }
  catch (const char *e1)
  {
    std::cerr<<"Error: "<<e1<<std::endl;
    return 1;
  }

  cleanup_o_integer_module();
  return 0;

}
