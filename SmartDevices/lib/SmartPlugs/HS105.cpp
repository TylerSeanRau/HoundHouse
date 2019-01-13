#include "HS105.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

HS105::HS105(
  const char * const address
)
  :
    socketfd(socket(AF_INET,SOCK_STREAM,0)),
    addr(CreateNeededAddr(address))
{
  std::memset(recv_buff,2048,0);
  connect(socketfd,reinterpret_cast<const sockaddr *>(addr),sizeof(sockaddr_in));
}

HS105::~HS105(void){
  delete addr;
  shutdown(socketfd,SHUT_RDWR);
}

const struct sockaddr_in * const
    HS105::CreateNeededAddr(
  const char * const address)
{
  struct sockaddr_in * to_return = new sockaddr_in;
  to_return->sin_family = AF_INET;
  to_return->sin_port = htons(9999);
  inet_aton(address, &(to_return->sin_addr));
  return to_return;
}

void
    HS105::encrypt(
  const char * const cmd_text,
  const unsigned int len,
  uint8_t * const raw_data)
{
  std::memset(raw_data, 0, 4+len);
  raw_data[3] = (len)&0xFF;
  raw_data[2] = (len>>8)&0xFF;
  raw_data[1] = (len>>16)&0xFF;
  raw_data[0] = (len>>24)&0xFF;
  uint8_t key = 171;
  for(int i = 0; i< len; key = raw_data[i+4], i++)
    raw_data[i+4] = key ^ cmd_text[i];
}


void
    HS105::On(
  void)
{
  static const char * const cmd_text =
    "{\"system\":{\"set_relay_state\":{\"state\":1}}}";

  static const unsigned int len = std::strlen(cmd_text);
  uint8_t raw_data[4+len];
  encrypt(cmd_text, len, raw_data);
  send(socketfd,raw_data,4+len,0);
  recv(socketfd,&recv_buff,2048,0);
}

void
    HS105::Off(
  void)
{
  static const char * const cmd_text =
    "{\"system\":{\"set_relay_state\":{\"state\":0}}}";

  static const unsigned int len = std::strlen(cmd_text);
  uint8_t raw_data[4+len];
  encrypt(cmd_text, len, raw_data);
  send(socketfd,raw_data,4+len,0);
  recv(socketfd,&recv_buff,2048,0);
}
