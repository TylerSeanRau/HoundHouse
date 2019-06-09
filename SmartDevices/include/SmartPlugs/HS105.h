/* file "HS105.h" */

#ifndef HS105_H
#define HS105_H

#include <sys/socket.h>
#include <netinet/in.h>

class HS105
{
  private:
    const int socketfd;
    const struct sockaddr_in * const  addr;
    uint8_t recv_buff[2048];

    static const struct sockaddr_in * const
        CreateNeededAddr(
      const char * const address);

    static void
        encrypt(
      const char * const cmd_text,
      const unsigned int len,
      uint8_t * const raw_data);

  public:
    HS105(
      const char * const address
    );

    ~HS105(void);

    void On(void);
    void Off(void);
};

#endif /* HS105_H */
