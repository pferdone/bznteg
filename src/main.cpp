/*
 * main.cpp
 *
 *  Created on: Aug 20, 2012
 *  Author: pferdone
 */

#include "nntp_manager.h"
#include <stdio.h>
#include <list>

#include "behaviour/bt_action_connect.h"
#include "behaviour/bt_action_authorize.h"

typedef std::list<BTAction*> BTActionList_t;

/**
 * Main program entry point.
 */
int main(int argc, char **argv)
{
  // initialize nntp manager
  NNTPManager &nntp_mgr = NNTPManager::getInstance("reader.xsusenet.com", "119");

  BTActionList_t bt_action_list;
  bt_action_list.push_back(new BTActionConnect());
  bt_action_list.push_back(new BTActionAuthorize("user", "pass"));

  for (BTActionList_t::iterator iter = bt_action_list.begin();
       iter != bt_action_list.end();
       ++iter) {
    while((*iter)->execute()==IN_PROGRESS) {}
  }

  nntp_mgr.destroy();

	return 0;
}
