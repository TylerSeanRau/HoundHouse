/* file "SimpleAudioQueriesOnlyWrittenResponse.cpp" */

#include "PhraseSpotterAPI.h"
#include "HoundCloudRequester.h"
#include "HoundConverser.h"
#include "ClientCapabilityRegistry.h"
#include "PlatformSpecificClientCapabilities.h"
#include "throwf.h"

#include "SimpleHoundCloudRequesterConfig.h"
#include "OkHoundSink.h"
#include "SimpleRequestInfoPreparer.h"
#include "SimplePartialHandler.h"
#include "SimpleSinks.h"
#include "SimpleDynamicResponseHandlers.h"

extern "C"
{
#include "o_integer.h"
}

#include <iostream>
#include <cstring>


static void process_request(
  HoundConverser * converser,
  ClientCapabilityRegistry::AudioSource * audio_device,
  SimplePartialHandler * local_handler);

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

  if(std::strncmp("alsa:",*(argv+1),5)!=0){
    std::cerr << "ALSARECORDINGDEVICE should be a device name from `arecord -L` prefixed"
              << std::endl
              << "with 'alsa:' ex: alsa:plughw:CARD=PCH,DEV=0"
              << std::endl;
    return 1;
  }

#ifdef HOUNDHOUSEDEBUG
  std::cout<<"Running with debug messages compiled in."<<std::endl;
#endif /* HOUNDHOUSEDEBUG */

  init_o_integer_module();

  PhraseSpotterSetThreshold(0.4);

  HoundCloudRequester requester(
    simple_config.clientId,
    simple_config.clientKey,
    simple_config.userId
  );

  static SimplePartialHandler local_handler;
  static SimpleRequestInfoPreparer simple_request_info_preparer;
  static SimpleDynamicResponseHandlerWithNoAudioOutput
    simple_dynamic_response_handler_with_no_audio_output(&local_handler);

  HoundConverser converser(&requester);
  converser.register_partial_handler(&local_handler);
  converser.register_request_info_preparer(
    &simple_request_info_preparer
  );
  converser.register_dynamic_response_handler(
    &simple_dynamic_response_handler_with_no_audio_output
  );

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
      process_request(&converser, audio_source_to_use, &local_handler);
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

static void process_request(
  HoundConverser * converser,
  ClientCapabilityRegistry::AudioSource * audio_device,
  SimplePartialHandler * local_handler)
{
  HoundConverser::VoiceRequest *voice_request =
    converser->start_voice_request();

  local_handler->beginQuery();

  SimpleSinkWithoutClosingSound sink(voice_request, local_handler);
  audio_device->capture(16000, 1, 16, true, &sink);

  voice_request->finish();
  delete voice_request;
}
