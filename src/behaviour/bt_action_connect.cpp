/*
 * bt_action_connect.cpp
 *
 *  Created on: Aug 21, 2012
 *      Author: pferdone
 */

#include "bt_action_connect.h"

//--------------------------------------------------------------------------------
BTActionConnect::BTActionConnect(const std::string &host, const std::string &port, double timeout)
  : _isConnecting(false),
    _host(host),
    _port(port),
    _timeout(timeout)
{

}

//--------------------------------------------------------------------------------
BTActionConnect::~BTActionConnect()
{

}

//--------------------------------------------------------------------------------
uint8_t BTActionConnect::execute()
{
  NNTPManager &nntp_mgr = NNTPManager::getInstance();
  Logger &logger = Logger::getInstance();

  // first check if we are connected
  if (nntp_mgr.isConnected()) {
    if (nntp_mgr.poll()) {
      uint32_t response_code = nntp_mgr.getResponseCode();
      if (response_code == SERVICE_AVAILABLE) {
        logger.log("connected to server");
        _state = SUCCEEDED;
      } else {
        logger.log("connection failed");
        _state = FAILED;
      }
    }
  } else {
    // we are not connected -> connect to server
    if (!_isConnecting) {
      if (nntp_mgr.connect(_host, _port)) {
        _isConnecting = true;
      } else {
        logger.log("invalid host, cannot connect");
        _state = FAILED;
      }
    }
  }

  // check if connection timed out
  if (_timer.elapsed()>=_timeout) {
    _state = FAILED;
    logger.log("connection timed out (maybe wrong port?)");
  }

  return _state;
}
