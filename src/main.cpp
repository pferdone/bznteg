/*
 * main.cpp
 *
 *  Created on: Aug 20, 2012
 *  Author: pferdone
 */

#include "nntp_manager.h"
#include <stdio.h>

/**
 * Main program entry point.
 */
int main(int argc, char **argv)
{
  // initialize nntp manager
  NNTPManager &nntp_mgr = NNTPManager::getInstance("reader.xsusenet.com", "119");

  while(nntp_mgr.isConnected()) {
    if (nntp_mgr.poll()) {
      uint32_t response_code = nntp_mgr.getResponseCode();
      printf("response: %08x\n", response_code);
      switch(response_code) {
        case CLOSING_CONNECTION: {
          nntp_mgr.close();
        } break;
      }
    }
  }

  nntp_mgr.destroy();

	return 0;
}
