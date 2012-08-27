/*
 * main.cpp
 *
 *  Created on: Aug 20, 2012
 *  Author: pferdone
 */

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/XMLPScanToken.hpp>
#include <iostream>
#include <string>
#include <regex>

#include "common/nzb_common.h"
#include "nntp_manager.h"
#include "behaviour/bt_action_connect.h"
#include "behaviour/bt_action_authorize.h"
#include "behaviour/bt_action_downloadfile.h"
#include "behaviour/bt_sequence.h"
#include "xml/tinyxml2.h"

using namespace tinyxml2;


bool parseNzb(const char *fn, FileList_t &file_list);

/** Main program entry point. */
int main(int argc, char **argv)
{
  FileList_t file_list;
  if (!parseNzb("test.nzb", file_list)) return -1;


  // initialize nntp manager
  NNTPManager &nntp_mgr = NNTPManager::getInstance();

  BTSequence seq;
  seq.addAction(new BTActionConnect("reader.xsusenet.com", "119"));
  seq.addAction(new BTActionAuthorize("user", "pass"));
  seq.addAction(new BTActionDownloadFile(file_list.front()));

  uint8_t result = IN_PROGRESS;
  while((result=seq.execute())==IN_PROGRESS) {}

  std::cout << "result: " << (int)result << std::endl;

  nntp_mgr.destroy();

	return 0;
}

//--------------------------------------------------------------------------------
bool parseNzb(const char *fn, FileList_t &file_list)
{
  XMLDocument doc;
  if (doc.LoadFile(fn)!=XML_SUCCESS) return false;

  XMLElement *root_element = doc.RootElement();
  if (std::strcmp(root_element->Value(), "nzb")!=0) {
    std::cout << "no valid nzb, wrong root element" << std::endl;
    return false;
  }

  for (const XMLNode *file_node = root_element->FirstChild();
       file_node!=0;
       file_node=file_node->NextSibling()) {
    // create nzb file object
    NzbFile_s *nzb_file = new NzbFile_s();

    const XMLElement *file_element = file_node->ToElement();
    nzb_file->poster = file_element->Attribute("poster");
    nzb_file->date = file_element->IntAttribute("date");
    nzb_file->subject = file_element->Attribute("subject");

    // traverse groups for this node
    const XMLNode *groups_node = file_node->FirstChild();
    for (const XMLNode *group_node=groups_node->FirstChild();
         group_node!=0;
         group_node=group_node->NextSibling()) {
      const XMLElement *group_element = group_node->ToElement();
      nzb_file->groups.push_back(group_element->GetText());
    }

    const XMLNode *segments_node = groups_node->NextSibling();
    for (const XMLNode *segment_node=segments_node->FirstChild();
         segment_node!=0;
         segment_node=segment_node->NextSibling()) {
      const XMLElement *segment_element = segment_node->ToElement();
      Segment_s *segment = new Segment_s();
      segment->number = segment_element->IntAttribute("number");
      segment->bytes = segment_element->IntAttribute("bytes");
      segment->article = segment_element->GetText();
      nzb_file->segments.push_back(segment);
    }

    std::cout << nzb_file->subject << std::endl;
    file_list.push_back(nzb_file);
  }

  return true;
}
