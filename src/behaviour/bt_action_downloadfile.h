/*
 * bt_action_downloadfile.h
 *
 *  Created on: Aug 27, 2012
 *      Author: pferdone
 */

#ifndef BT_ACTION_DOWNLOADFILE_H_
#define BT_ACTION_DOWNLOADFILE_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <boost/regex.hpp>
#include "bt_action.h"
#include "../nntp_manager.h"
#include "../logger.h"
#include "../common/nzb_common.h"

/** Action to download a file. **/
class BTActionDownloadFile : public BTAction
{
  public:
    BTActionDownloadFile(NzbFile_s *nzb_file);
    ~BTActionDownloadFile();

    /** Tries to connect to the server. **/
    virtual uint8_t execute();

  private:
    NzbFile_s *_nzbFile;
    Groups_t::iterator _grpIter;
    Segments_t::iterator _segIter;
    bool _isGroupSelected;
    bool _isDownloading;
    std::ofstream _outFile;
    std::size_t _outBytes;
    Buffer8_t _buffer;
};


#endif /* BT_ACTION_DOWNLOADFILE_H_ */
