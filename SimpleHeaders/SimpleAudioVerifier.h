/* file "SimpleAudioVerifier.h" */

#ifndef SIMPLEAUDIOVERIFIER_H
#define SIMPLEAUDIOVERIFIER_H

#include "HoundAudioVerifier.h"

#include <iostream>

class SimpleAudioVerifier : public HoundAudioVerifier
{
  public:
    void report_error(const char *message){
      std::cerr<<"Warning: Input audio data"<<message<<std::endl;
    }
};

#endif /* SIMPLEAUDIOVERIFIER_H */
