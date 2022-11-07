/* file "SimpleDataSourceFromBase64EncodedString.h" */

#include "SimpleDataSourceFromBase64EncodedString.h"

#include "ClientCapabilityRegistry.h"
#include "Fetch.h"

#include <cstdint>
#include <cstring>
#include <cassert>

SimpleDataSourceFromBase64EncodedString::
  SimpleDataSourceFromBase64EncodedString(
    const char *data
  )
    :
      data(data),
      buffer_position(0)
{
  assert(data != NULL);
  std::size_t length = strlen(data);
  data_length = (length / 4) * 3;

  /* Base64 must always use 4 bytes chunks, but this
   * meansthat some times garbage = characters might be
   * at the end of the string. These characters are used
   * only to fill the last one or two bytes at the
   * end. This is fine but we don't want to try to
   * play the = character as sound.
   */


  if(data_length > 0){
    if(data[length-1] == '='){
      --data_length;
      if(data[length-2] == '='){
        --data_length;
      }
    }
  }
}

SimpleDataSourceFromBase64EncodedString::
  ~SimpleDataSourceFromBase64EncodedString(void)
{
}

std::size_t SimpleDataSourceFromBase64EncodedString::
  read_data(
    std::uint8_t *input_data,
    std::size_t byte_count
  )
{
  assert(byte_count >= 0);

  assert(buffer_position >= 0);
  assert(buffer_position < 3);

  if (byte_count == 0)
      return 0;

  std::uint8_t * data_remaining = input_data;
  std::size_t byte_count_remaining = byte_count;
  if (buffer_position > 0){
    if (byte_count < 3 - buffer_position){
      std::memcpy(input_data, &(byte_buffer[buffer_position]), byte_count);
      buffer_position += byte_count;
      assert(buffer_position < 3);
      return byte_count;
    }
    std::memcpy(input_data, &(byte_buffer[buffer_position]), 3 - buffer_position);
    byte_count_remaining -= 3 - buffer_position;
    data_remaining += 3 - buffer_position;
    buffer_position = 0;
  }

  assert(buffer_position == 0);

  if (data_length >= 3 && byte_count_remaining >= 3){
    std::size_t bulk_byte_count =
      (data_length > byte_count_remaining) ?
      byte_count_remaining :
      data_length;
    std::size_t chunk_count = bulk_byte_count / 3;
    base64_decode(data, chunk_count * 4, data_remaining);
    data_length -= chunk_count * 3;
    data += chunk_count * 4;
    byte_count_remaining -= chunk_count * 3;
    data_remaining += chunk_count * 3;
  }

  if(data_length <= byte_count_remaining){
    assert(data_length < 3);
    if(data_length > 0){
      base64_decode(data, 4, &(byte_buffer[0]));
      std::memcpy(data_remaining, &(byte_buffer[0]), data_length);
      data_length = 0;
    }
    return (data_remaining - input_data) + data_length;
  }

  buffer_position = byte_count_remaining;
  assert(buffer_position < 3);
  if (buffer_position > 0){
    std::size_t to_decode =
      (data_length >= 4) ? 4 : data_length;
    base64_decode(data, 4, &(byte_buffer[0]));
    data_length -= to_decode;
    data += to_decode;
    std::memcpy(data_remaining, &(byte_buffer[0]), buffer_position);
    return byte_count;
  }

  return data_remaining - input_data;
}
