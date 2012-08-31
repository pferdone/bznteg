/*
 * bt_action_selectgroup.cpp
 *
 *  Created on: Aug 31, 2012
 *      Author: pferdone
 */

#include "bt_action_selectgroup.h"

//--------------------------------------------------------------------------------
BTActionSelectGroup::BTActionSelectGroup(const std::string &grp_name)
  : _grpName(grp_name),
    _isGroupSelected(false)
{

}

//--------------------------------------------------------------------------------
BTActionSelectGroup::~BTActionSelectGroup()
{
}

//--------------------------------------------------------------------------------
uint8_t BTActionSelectGroup::execute()
{
  NNTPManager &nntp_mgr = NNTPManager::getInstance();
  Logger &logger = Logger::getInstance();

  if (nntp_mgr.isConnected()) {
    if (!_isGroupSelected) {
      std::stringstream ss;
      ss << "GROUP " << _grpName << std::endl;
      nntp_mgr.send((const uint8_t*)ss.str().c_str(), ss.str().length());
      _isGroupSelected = true;
    } else {
      if (nntp_mgr.poll()) {
        uint32_t response_code = nntp_mgr.getResponseCode();
        _state = (response_code==GROUP_SUCCESSFULLY_SELECTED)?SUCCEEDED:FAILED;
      }
    }
  } else {
    _state = FAILED;
  }

  return _state;
}
