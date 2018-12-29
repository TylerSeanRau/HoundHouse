/* file "SimplePartialHandler.h" */

#ifndef SIMPLEPARTIALHANDLER_H
#define SIMPLEPARTIALHANDLER_H

#include "HoundRequester.h"
#include "HoundPartialTranscriptJSON.h"

#include <iostream>

class SimplePartialHandler : public HoundRequester::PartialTranscriptHandler
{
  private:
    bool server_says_stop;

  public:
    SimplePartialHandler(void) :
      server_says_stop(false)
    {
    }

    ~SimplePartialHandler(void)
    {
    }

    void beginQuery(void){
      server_says_stop = false;
    }

    void finishQuery(void){
      std::cout<<std::endl;
    }

    void handle(HoundPartialTranscriptJSON *partial){
      assert(partial != NULL);

      server_says_stop =
        partial->hasSafeToStopAudio()
        && partial->getSafeToStopAudio();

#ifdef HOUNDHOUSEDEBUG
      std::cout<<partial->getPartialTranscript()<<std::endl;
#else
      std::cout<<'\r'<<"Transcript: "<<partial->getPartialTranscript()<<std::flush;
#endif /* HOUNDHOUSEDEBUG */
    }

    bool getServerSaysStop(void){
      return server_says_stop;
    }
};

#endif /* SIMPLEPARTIALHANDLER_H */
