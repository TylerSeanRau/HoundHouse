/* file "SimpleHoundCloudRequesterConfig.h" */

#ifndef SIMPLEHOUNDCLOUDREQUESTERCONFIG_H
#define SIMPLEHOUNDCLOUDREQUESTERCONFIG_H

struct SimpleHoundCloudRequesterConfig
{
  const char * const clientId;
  const char * const clientKey;
  const char * const userId;
};

extern const SimpleHoundCloudRequesterConfig simple_config;

#endif /* SIMPLEHOUNDCLOUDREQUESTERCONFIG_H */
