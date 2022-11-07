/* file "SimpleDynamicResponseHandlers.h" */

#ifndef SIMPLEDYNAMICRESPONSEHANDLERS_H
#define SIMPLEDYNAMICRESPONSEHANDLERS_H

#include "ClientCapabilityRegistry.h"

#include "DynamicResponseHandler.h"
#include "DynamicResponseJSON.h"
#include "SimplePartialHandler.h"
#ifdef WITHAUDIOOUTPUTFEATURES
#include "SimpleDataSourceFromBase64EncodedString.h"
#endif /* WITHAUDIOOUTPUTFEATURES */

#include <iostream>

class SimpleDynamicResponseHandlerWithNoAudioOutput : public DynamicResponseHandler
{
  protected:
    bool saw_output;
    SimplePartialHandler * partial_handler;

  public:
    SimpleDynamicResponseHandlerWithNoAudioOutput(
      SimplePartialHandler * partial_handler
    )
      :
        saw_output(false),
        partial_handler(partial_handler)
    {
    }

    ~SimpleDynamicResponseHandlerWithNoAudioOutput(void)
    {
    }

    void start_query(void){
      saw_output = false;
    }

    void finish_query(void){
      if(!saw_output)
        std::cerr<<"No response from server."<<std::endl;
    }

    virtual void handle(DynamicResponseJSON *dynamic_response){
      partial_handler->finishQuery();
      assert(dynamic_response != NULL);
#ifdef HOUNDHOUSEDEBUG
      std::cout<<"CommandKind: "<<dynamic_response->getCommandKind()<<std::endl;
#endif /* HOUNDHOUSEDEBUG */
      std::cout<<"Response: "<<dynamic_response->getWrittenResponseLong()<<std::endl;
      saw_output = true;
    }
};

#ifdef WITHAUDIOOUTPUTFEATURES
class SimpleDynamicResponseHandler : public SimpleDynamicResponseHandlerWithNoAudioOutput
{
  protected:
    ClientCapabilityRegistry * capability_registry;
    ClientCapabilityRegistry::AudioPlayer * audio_player_to_use;

  public:
    SimpleDynamicResponseHandler(
      SimplePartialHandler * partial_handler,
      ClientCapabilityRegistry * capability_registry,
      ClientCapabilityRegistry::AudioPlayer * audio_player_to_use
    )
      :
        SimpleDynamicResponseHandlerWithNoAudioOutput(partial_handler),
        capability_registry(capability_registry),
        audio_player_to_use(audio_player_to_use)
    {
    }

    ~SimpleDynamicResponseHandler(void)
    {
    }

    void handle(DynamicResponseJSON *dynamic_response){
      SimpleDynamicResponseHandlerWithNoAudioOutput::handle(dynamic_response);
      try {
        if (dynamic_response->hasResponseAudioBytes()){
          std::string audio_string =
            dynamic_response->getResponseAudioBytes();
          SimpleDataSourceFromBase64EncodedString data_source(audio_string.c_str());
          capability_registry->lookup_audio_decoder("WAV")->play(
            audio_player_to_use, &data_source
          );
        }
      } catch (char *e1){
        std::cerr << "Error handling audio output: "
                  << e1
                  << std::endl;
        free(e1);
      } catch (const char *e1){
        std::cerr << "Error handling audio output: "
                  << e1
                  << std::endl;
      }
    }
};
#endif /* WITHAUDIOOUTPUTFEATURES */

#endif /* SIMPLEDYNAMICRESPONSEHANDLERS_H */
