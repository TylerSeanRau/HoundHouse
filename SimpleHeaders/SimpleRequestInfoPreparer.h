/* file "SimpleRequestInfoPreparer.h" */

#ifndef SIMPLEREQUESTINFOPREPARER_H
#define SIMPLEREQUESTINFOPREPARER_H

#include "RequestInfoPreparer.h"
#include "RequestInfoJSON.h"

#ifdef HOUNDHOUSEDEBUG
#include <iostream>
#endif /* HOUNDHOUSEDEBUG */

class SimpleRequestInfoPreparer : public RequestInfoPreparer
{
  protected:
    const bool has_lat_to_use;
    const double lat_to_use;
    const bool has_lon_to_use;
    const double lon_to_use;

  public:
    SimpleRequestInfoPreparer(void)
      :
        has_lat_to_use(false),
        lat_to_use(0.0),
        has_lon_to_use(false),
        lon_to_use(0.0)
    {
    }

    SimpleRequestInfoPreparer(
      const double lat,
      const double lon
    )
      :
        has_lat_to_use(true),
        lat_to_use(lat),
        has_lon_to_use(true),
        lon_to_use(lon)
    {
    }

    SimpleRequestInfoPreparer(
      const bool lat_passed,
      const double lat,
      const bool lon_passed,
      const double lon
    )
      :
        has_lat_to_use(lat_passed),
        lat_to_use(lat),
        has_lon_to_use(lon_passed),
        lon_to_use(lon)
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

      if(has_lat_to_use){
        request_info->setLatitude(lat_to_use);
#ifdef HOUNDHOUSEDEBUG
        std::cout<<"lat: "<<lat_to_use<<std::endl;
#endif /* HOUNDHOUSEDEBUG */
      }

      if(has_lon_to_use){
        request_info->setLongitude(lon_to_use);
#ifdef HOUNDHOUSEDEBUG
        std::cout<<"lon: "<<lon_to_use<<std::endl;
#endif /* HOUNDHOUSEDEBUG */
      }

#ifdef HOUNDHOUSEDEBUG
      std::cout<<"Finished RequestInfoJSON preperations."<<std::endl;
#endif /* HOUNDHOUSEDEBUG */
    }
};

#endif /* SIMPLEREQUESTINFOPREPARER_H */
