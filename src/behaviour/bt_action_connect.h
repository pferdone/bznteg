/*
 * bt_action_connect.h
 *
 *  Created on: Aug 21, 2012
 *      Author: pferdone
 */

#ifndef BT_ACTION_CONNECT_H_
#define BT_ACTION_CONNECT_H_

#include <boost/timer.hpp>
#include "bt_action.h"
#include "../nntp_manager.h"
#include "../logger.h"

/** BT action that's trying to connect to our server. **/
class BTActionConnect : public BTAction
{
  public:
    /** Constructor. **/
    BTActionConnect(const std::string &host, const std::string &port, double timeout=10);
    /** Destructor. **/
    virtual ~BTActionConnect();

    /** Tries to connect to the server. **/
    virtual uint8_t execute();

  private:
    bool _isConnecting;
    const std::string _host;
    const std::string _port;
    double _timeout;
    boost::timer _timer;
};

#endif /* BT_ACTION_CONNECT_H_ */
