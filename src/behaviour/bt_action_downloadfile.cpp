/*
 * bt_action_downloadfile.cpp
 *
 *  Created on: Aug 27, 2012
 *      Author: pferdone
 */

#include "bt_action_downloadfile.h"

//--------------------------------------------------------------------------------
BTActionDownloadFile::BTActionDownloadFile(NzbFile_s* nzb_file)
  : _nzbFile(nzb_file),
    _grpIter(nzb_file->groups.begin()),
    _segIter(nzb_file->segments.begin()),
    _isGroupSelected(false),
    _isDownloading(false)
{
}

//--------------------------------------------------------------------------------
BTActionDownloadFile::~BTActionDownloadFile()
{
}

//--------------------------------------------------------------------------------
uint8_t BTActionDownloadFile::execute()
{
  NNTPManager &nntp_mgr = NNTPManager::getInstance();
  Logger &logger = Logger::getInstance();

  if (nntp_mgr.isConnected()) {
    if (!_isGroupSelected) {
      _isGroupSelected = true;

      // construct command
      std::stringstream ss;
      ss << "GROUP " << _grpIter->c_str() << "\nARTICLE <" << (*_segIter)->article << ">\n";
      nntp_mgr.send((const uint8_t*)ss.str().c_str(), ss.str().length()+3);
    } else {
      if (nntp_mgr.poll()) {
        if (!_isDownloading) {
          uint32_t response_code = nntp_mgr.getResponseCode();
          if (response_code == GROUP_SUCCESSFULLY_SELECTED) {
            std::cout << "GROUP_SUCCESSFULLY_SELECTED" << std::endl;
          } else if (response_code == ARTICLE_FOLLOWS) {
            _isDownloading = true;
          } else if (response_code == NO_SUCH_NEWSGROUP) {
            std::cout << "NO_SUCH_NEWSGROUP" << std::endl;
            _grpIter++;
          }
        } else {
          std::cout << "Downloading buffer size: " << nntp_mgr.buffer().size() << std::endl;
        }
      }
    }
  } else {
    _state = FAILED;
  }

  return _state;
}
