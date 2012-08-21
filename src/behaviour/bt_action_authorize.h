/*
 * bt_action_authorize.h
 *
 *  Created on: Aug 21, 2012
 *      Author: pferdone
 */

#ifndef BT_ACTION_AUTHORIZE_H_
#define BT_ACTION_AUTHORIZE_H_

#include <string>
#include <sstream>
#include "bt_action.h"
#include "../nntp_manager.h"
#include "../logger.h"

/** BT action that's trying to authorize itself on the server. **/
class BTActionAuthorize : public BTAction
{
  public:
    /** Constructor. **/
    BTActionAuthorize(const std::string &user, const std::string &pass);
    /** Destructor. **/
    virtual ~BTActionAuthorize();

    /** Authorize itself. **/
    virtual uint8_t execute();

  private:
    std::string _user;
    std::string _pass;
    bool _sendInformation;
};


#endif /* BT_ACTION_AUTHORIZE_H_ */
