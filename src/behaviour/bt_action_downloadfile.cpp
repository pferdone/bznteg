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
    _isDownloading(false),
    _outBytes(0)
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
            _buffer.insert(_buffer.end(), nntp_mgr.buffer().begin(), nntp_mgr.buffer().end());
          } else if (response_code == NO_SUCH_NEWSGROUP) {
            _grpIter++;
          }
        } else {
          _buffer.insert(_buffer.end(), nntp_mgr.buffer().begin(), nntp_mgr.buffer().end());

          static const Buffer8_t search = {'\n', '.'};
          Buffer8_t::const_iterator found = std::search(nntp_mgr.buffer().begin(),
              nntp_mgr.buffer().end(), search.begin(), search.end());

          if (found!=nntp_mgr.buffer().end()) {
            // RegEx: (?<=name=)[^\\s]+
            boost::regex rx("(?<=name=)[^\\s]+");
            boost::cmatch cm;
            if (boost::regex_search((char*)_buffer.data(), cm, rx)) {
              std::stringstream filename;
              filename << cm[0].str() << "_" << (*_segIter)->number;

              _outFile.open(filename.str().c_str(), std::fstream::binary);
              _outFile.write((char*)_buffer.data(), _buffer.size()-2);
              _outFile.close();

              std::size_t num_files = std::distance(_nzbFile->segments.begin(), _nzbFile->segments.end());
              std::size_t count = std::distance(_segIter, _nzbFile->segments.end());

              std::cout << "Downloaded: " << cm[0].str() << " " << count << "/" << num_files << std::endl;

              // reset
              _buffer.clear();
              _isGroupSelected = false;
              _isDownloading = false;
              _segIter++;
            }
          }

          if (_segIter == _nzbFile->segments.end()) {
            _state = SUCCEEDED;
          }
        }
      }
    }
  } else {
    _state = FAILED;
  }

  return _state;
}
