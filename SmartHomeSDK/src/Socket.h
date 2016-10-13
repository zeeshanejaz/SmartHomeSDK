// Credit : The Linux Documentation Project (TLDP)
// Source : http://tldp.org/LDP/LG/issue74/misc/tougher/Socket.h.txt

#pragma once

#ifndef __SOCKETDEFINITION__

#define __SOCKETDEFINITION__

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>

#ifndef __CYGWIN32__
#include <netinet/tcp.h>
#endif

const int MAXHOSTNAME = 200;
const int MAXCONNECTIONS = 5;
const int MAXRECV = 500;

class Socket

{
 public:
  Socket();
  virtual ~Socket();

  // Server initialization
  bool create();
  bool bind ( const int port );
  bool listen() const;
  bool accept ( Socket& ) const;

  // Client initialization
  bool connect ( const std::string host, const int port );
  void closeSocket();
  
  // Data Transimission
  bool send ( const std::string ) const;
  int recv ( std::string& ) const;
  void set_non_blocking ( const bool );
  bool is_valid() const { return m_sock != -1; }
  
 private:
  int m_sock;
  sockaddr_in m_addr;
};

#endif
