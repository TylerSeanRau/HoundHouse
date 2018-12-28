/* file "SimpleDynamicResponseHandlers.h" */

#ifndef SIMPLEDYNAMICRESPONSEHANDLERS_H
#define SIMPLEDYNAMICRESPONSEHANDLERS_H

#include "DynamicResponseHandler.h"
#include "DynamicResponseJSON.h"
#include "SimplePartialHandler.h"

#include <iostream>

class SimpleDynamicResponseHandlerWithNoAudioOutput : public DynamicResponseHandler
{
  private:
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

    void handle(DynamicResponseJSON *dynamic_response){
      partial_handler->finishQuery();
      assert(dynamic_response != NULL);
      std::cout<<"Response: "<<dynamic_response->getWrittenResponseLong()<<std::endl;
      saw_output = true;
    }
};

#endif /* SIMPLEDYNAMICRESPONSEHANDLERS_H */
