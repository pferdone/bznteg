/*
 * main.cpp
 *
 *  Created on: Aug 20, 2012
 *  Author: pferdone
 */

#include "nntp_manager.h"
#include <stdio.h>

#include "behaviour/bt_action_connect.h"

/**
 * Main program entry point.
 */
int main(int argc, char **argv)
{
  // initialize nntp manager
  NNTPManager &nntp_mgr = NNTPManager::getInstance("reader.xsusenet.com", "119");

  BTActionConnect bt_conn;

  while(bt_conn.execute()==IN_PROGRESS) {

  }

  nntp_mgr.destroy();

	return 0;
}
