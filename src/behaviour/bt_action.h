/*
 * bt_action.h
 *
 *  Created on: Aug 21, 2012
 *      Author: pferdone
 */

#ifndef BT_ACTION_H_
#define BT_ACTION_H_

#include "bt_base.h"

/** States that can be returned by the execute() function. **/
enum BT_STATE
{
  IN_PROGRESS = 0x0,
  FAILED      = 0x1,
  SUCCEEDED   = 0x2,
};

/** BTAction is the base class for all single actions in a behaviour
 *  tree. You need to override the execute() function in your action
 *  implementation. **/
class BTAction : public BTBase
{
  public:
    /** Constructor. **/
    BTAction();
    /** Destructor. **/
    virtual ~BTAction();

    /** This function is repeatedly called until it returns true.
     *  So make sure that state handling is done inside here. **/
    virtual uint8_t execute() = 0;

  protected:
    uint8_t _state;
};


#endif /* BT_ACTION_H_ */
