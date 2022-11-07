/* file "SimpleDataSourceFromBase64EncodedString.h" */

#ifndef SIMPLEDATASOURCEFROMBASE64ENCODEDSTRING
#define SIMPLEDATASOURCEFROMBASE64ENCODEDSTRING

#include "ClientCapabilityRegistry.h"

#include <cstdint>

class SimpleDataSourceFromBase64EncodedString
  :
    public ClientCapabilityRegistry::DataSource
{
  private:
    const char * data;
    std::size_t data_length;
    std::uint8_t byte_buffer[3];
    std::size_t buffer_position;

  public:
    SimpleDataSourceFromBase64EncodedString(
      const char *data
    );

    ~SimpleDataSourceFromBase64EncodedString(void);

    std::size_t read_data(std::uint8_t *data, std::size_t byte_count);
};

#endif /* SIMPLEDATASOURCEFROMBASE64ENCODEDSTRING */
