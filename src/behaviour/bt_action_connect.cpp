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
  if (!_isConnecting) {
    nntp_mgr.connect();
    _isConnecting = true;
  }

  if (nntp_mgr.isConnected()) {
    _state = SUCCEEDED;
  }

  return _state;
}
