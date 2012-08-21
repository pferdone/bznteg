/*
 * bt_action_connect.h
 *
 *  Created on: Aug 21, 2012
 *      Author: pferdone
 */

#ifndef BT_ACTION_CONNECT_H_
#define BT_ACTION_CONNECT_H_

#include "bt_action.h"
#include "../nntp_manager.h"
#include "../logger.h"

class BTActionConnect : public BTAction
{
  public:
    /** Constructor. **/
    BTActionConnect();
    /** Destructor. **/
    virtual ~BTActionConnect();

    /** Tries to connect to the server. **/
    virtual uint8_t execute();

  private:
    bool _isConnecting;
};

#endif /* BT_ACTION_CONNECT_H_ */
