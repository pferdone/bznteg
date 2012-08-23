/*
 * main.cpp
 *
 *  Created on: Aug 20, 2012
 *  Author: pferdone
 */

#include "nntp_manager.h"

#include "behaviour/bt_action_connect.h"
#include "behaviour/bt_action_authorize.h"
#include "behaviour/bt_sequence.h"

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/SAXParser.hpp>

using namespace xercesc;

/** Main program entry point. */
int main(int argc, char **argv)
{
  XMLPlatformUtils::Initialize();
  SAXParser *sax_parser = new SAXParser();



  // initialize nntp manager
  NNTPManager &nntp_mgr = NNTPManager::getInstance();

  BTSequence seq;
  seq.addAction(new BTActionConnect("reader.xsusenet.com", "119"));
  seq.addAction(new BTActionAuthorize("user", "pass"));

  uint8_t result = IN_PROGRESS;
  while((result=seq.execute())==IN_PROGRESS) {}

  std::cout << "result: " << (int)result << std::endl;

  nntp_mgr.destroy();

	return 0;
}
