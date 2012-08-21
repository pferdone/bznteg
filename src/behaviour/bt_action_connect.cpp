/*
 * bt_action_connect.cpp
 *
 *  Created on: Aug 21, 2012
 *      Author: pferdone
 */

#include "bt_action_connect.h"

//--------------------------------------------------------------------------------
BTActionConnect::BTActionConnect()
  : _isConnecting(false)
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

  // first check if we are connected
  if (nntp_mgr.isConnected()) {
    if (nntp_mgr.poll()) {
      Logger &logger = Logger::getInstance();
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
      nntp_mgr.connect();
      _isConnecting = true;
    }
  }

  return _state;
}
