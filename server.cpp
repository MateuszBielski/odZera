#include "server.h"
#include <iostream>

Server::Server()
{
}

Server::~Server()
{
}

Server::type_signal_something Server::signal_something()
{
  return m_signal_something;
}

void Server::do_something()
{
  m_signal_something.emit(false, 5);
}