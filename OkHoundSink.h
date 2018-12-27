/* file "OkHoundSink.h" */

#ifndef OKHOUNDSINK_H
#define OKHOUNDSINK_H

#include "PhraseSpotterAPI.h"
#include "ClientCapabilityRegistry.h"

#ifdef HOUNDHOUSEDEBUG
#include <iostream>
#endif /* HOUNDHOUSEDEBUG */

class OkHoundSink : public ClientCapabilityRegistry::DataSink
{
  private:
    bool found_ok_hound;

  public:
    OkHoundSink(void):
      found_ok_hound(false)
    {
    }

    ~OkHoundSink(void)
    {
    }

    size_t write_data(
      const uint8_t *data,
      size_t byte_count
    ){
      if(PhraseSpotterProcessSamples((int16_t *)data,byte_count/2)){
        found_ok_hound=true;
#ifdef HOUNDHOUSEDEBUG
        std::cout<<"Found Okay Hound!"<<std::endl;
#endif /* HOUNDHOUSEDEBUG */
        return 0;
      }
      return byte_count;
    }
};

#endif /* OKHOUNDSINK_H */
