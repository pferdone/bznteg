/*
 * bt_action_selectgroup.h
 *
 *  Created on: Aug 31, 2012
 *      Author: pferdone
 */

#ifndef BT_ACTION_SELECTGROUP_H_
#define BT_ACTION_SELECTGROUP_H_

#include <sstream>
#include <string>
#include "bt_action.h"
#include "../nntp_manager.h"
#include "../logger.h"

/** Action to select a group. **/
class BTActionSelectGroup : public BTAction
{
  public:
    /** Constructor. **/
    BTActionSelectGroup(const std::string &grp_name);
    /** Destructor. **/
    virtual ~BTActionSelectGroup();

    /** Select a group on a newsgroup. **/
    virtual uint8_t execute();

  private:
    /** Group name. **/
    const std::string _grpName;
    /** Is group selected? **/
    bool _isGroupSelected;
};


#endif /* BT_ACTION_SELECTGROUP_H_ */
