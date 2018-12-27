/* file "SimpleRequestInfoPreparer.h" */

#include "RequestInfoPreparer.h"

#ifdef HOUNDHOUSEDEBUG
#include <iostream>
#endif /* HOUNDHOUSEDEBUG */

class SimpleRequestInfoPreparer : public RequestInfoPreparer
{
  private:
  public:
    SimpleRequestInfoPreparer(void)
    {
    }

    ~SimpleRequestInfoPreparer(void)
    {
    }

    void prepare(RequestInfoJSON *request_info){
      assert(request_info != NULL);
#ifdef HOUNDHOUSEDEBUG
      std::cout<<"Beginning RequestInfoJSON preperations."<<std::endl;
#endif /* HOUNDHOUSEDEBUG */

      request_info->setServerDeterminesEndOfAudio(true);

#ifdef HOUNDHOUSEDEBUG
      std::cout<<"Finished RequestInfoJSON preperations."<<std::endl;
#endif /* HOUNDHOUSEDEBUG */
    }
};

