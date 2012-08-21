/*
 * bt_action_authorize.cpp
 *
 *  Created on: Aug 21, 2012
 *      Author: pferdone
 */

#include "bt_action_authorize.h"

//--------------------------------------------------------------------------------
BTActionAuthorize::BTActionAuthorize(const std::string &user, const std::string &pass)
  : _user(user),
    _pass(pass),
    _sendInformation(false)
{

}

//--------------------------------------------------------------------------------
BTActionAuthorize::~BTActionAuthorize()
{

}

//--------------------------------------------------------------------------------
uint8_t BTActionAuthorize::execute()
{
  NNTPManager &nntp_mgr = NNTPManager::getInstance();

  if (!_sendInformation) {
    std::stringstream ss;
    ss << "AUTHINFO USER " << _user << "\nAUTHINFO PASS " << _pass << "\n";
    nntp_mgr.send((const uint8_t*)ss.str().data(), ss.str().length()+3);
    _sendInformation = true;
  } else {
    if(nntp_mgr.poll()) {
      uint32_t response_code = nntp_mgr.getResponseCode();
      Logger &logger = Logger::getInstance();

      // check responses
      if (response_code==PASSWORD_REQUIRED) {
        logger.log("ignore password requirement", 255);
      } else if(response_code==AUTHENTICATION_ACCEPTED) {
        logger.log("authenticated", 0);
        _state = SUCCEEDED;
      } else {
        logger.log("authorization failed", 0);
        _state = FAILED;
      }
    }
  }

  return _state;
}
