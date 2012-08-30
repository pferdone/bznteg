/*
 * connection_manager.cpp
 *
 *  Created on: Aug 20, 2012
 *      Author: pferdone
 */

#include "nntp_manager.h"

NNTPManager *NNTPManager::_instance = 0;

//--------------------------------------------------------------------------------
NNTPManager::NNTPManager()
  : _socket(_ioService)
{
}

//--------------------------------------------------------------------------------
NNTPManager::~NNTPManager()
{
  _socket.close();
}

//--------------------------------------------------------------------------------
NNTPManager& NNTPManager::getInstance()
{
  if (_instance==0) {
    _instance = new NNTPManager();
  }

  return *_instance;
}

//--------------------------------------------------------------------------------
void NNTPManager::destroy()
{
  delete _instance;
  _instance = 0;
}

//--------------------------------------------------------------------------------
bool NNTPManager::connect(const std::string &host, const std::string &port)
{
  tcp::resolver resolver(_ioService);
  tcp::resolver::query query(host, port);
  try {
    _resIter = resolver.resolve(query);
    _socket.async_connect(_resIter->endpoint(),
          boost::bind(&NNTPManager::handleConnection, this,
          boost::asio::placeholders::error));
    return true;
  } catch(boost::exception &e) { }
  return false;
}

//--------------------------------------------------------------------------------
void NNTPManager::close()
{
  _socket.close();
}

//--------------------------------------------------------------------------------
void NNTPManager::send(const Buffer8_t &buffer)
{
  send(_buffer.data(), _buffer.size());
}

//--------------------------------------------------------------------------------
void NNTPManager::send(const uint8_t *buffer, std::size_t size)
{
  _socket.send(boost::asio::buffer(buffer, size));
  /*_socket.async_send(boost::asio::buffer(buffer, size),
        boost::bind(&NNTPManager::handleRead, this,
        boost::asio::placeholders::error));*/
}

//--------------------------------------------------------------------------------
bool NNTPManager::isConnected() const
{
  return _socket.is_open();
}

//--------------------------------------------------------------------------------
bool NNTPManager::poll()
{
  std::size_t bytes_available = _socket.available();
  if (bytes_available>0) {
    _buffer.clear();
    _buffer.resize(bytes_available, 0);
    _socket.read_some(boost::asio::buffer(_buffer.data(), _buffer.size()));
  }

  return bytes_available > 0;
}

//--------------------------------------------------------------------------------
const Buffer8_t& NNTPManager::buffer() const
{
  return _buffer;
}

//--------------------------------------------------------------------------------
uint32_t NNTPManager::getResponseCode() const
{
  uint32_t response_code = -1;
  if (_buffer.size() >= 4) {
    response_code = *(const uint32_t*)_buffer.data();
  }
  return response_code;
}

//--------------------------------------------------------------------------------
void NNTPManager::handleConnection(const boost::system::error_code& error)
{
  std::cout << "connect error" << std::endl;
}

//--------------------------------------------------------------------------------
void NNTPManager::handleRead(const boost::system::error_code& error)
{
  std::cout << "read" << std::endl;
}

//--------------------------------------------------------------------------------
void NNTPManager::handleSend(const boost::system::error_code& error)
{
  std::cout << "send" << std::endl;
}
