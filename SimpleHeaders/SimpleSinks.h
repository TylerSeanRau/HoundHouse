/* file "SimpleSinks.h" */

#ifndef SIMPLESINKS_H
#define SIMPLESINKS_H

#include "HoundConverser.h"
#include "ClientCapabilityRegistry.h"
#include "SimpleAudioVerifier.h"
#include "SimplePartialHandler.h"

#ifdef RESPEAKERLEDRING
#include <wiringPi.h>
#endif /* RESPEAKERLEDRING */

class SimpleSinkWithoutClosingSound : public ClientCapabilityRegistry::DataSink
{
  protected:
    HoundConverser::VoiceRequest * voice_request;
    SimplePartialHandler * partial_handler;
    SimpleAudioVerifier verifier;

  public:
      SimpleSinkWithoutClosingSound(
         HoundConverser::VoiceRequest *voice_request,
         SimplePartialHandler * partial_handler
      )
        :
          voice_request(voice_request),
          partial_handler(partial_handler)
      {
      }

      ~SimpleSinkWithoutClosingSound(void)  { }

      virtual size_t write_data(const uint8_t *data, size_t byte_count){
        if((!(voice_request->more_ok()))||partial_handler->getServerSaysStop()){
          return 0;
        }

        verifier.add_bytes(&(data[0]), byte_count);
        voice_request->add_audio(byte_count, data);
        return byte_count;
      }
};

#ifdef RESPEAKERLEDRING
class SimpleSinkTurnOffLight : public SimpleSinkWithoutClosingSound
{
  public:
    SimpleSinkTurnOffLight(
      HoundConverser::VoiceRequest *voice_request,
      SimplePartialHandler * partial_handler
    )
      :
        SimpleSinkWithoutClosingSound(
          voice_request,
          partial_handler
        )
    {
    }

    ~SimpleSinkTurnOffLight(void)  { }

    virtual size_t write_data(const uint8_t *data, size_t byte_count){
      if((!(voice_request->more_ok()))||partial_handler->getServerSaysStop()){
        digitalWrite(5,LOW);
        return 0;
      }

      verifier.add_bytes(&(data[0]), byte_count);
      voice_request->add_audio(byte_count, data);
      return byte_count;
    }
};
#endif /* RESPEAKERLEDRING */

#endif /* SIMPLESINKS_H */
