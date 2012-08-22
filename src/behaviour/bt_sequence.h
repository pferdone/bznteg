/*
 * bt_sequence.h
 *
 *  Created on: Aug 22, 2012
 *      Author: pferdone
 */

#ifndef BT_SEQUENCE_H_
#define BT_SEQUENCE_H_

#include "bt_action.h"
#include <list>

typedef std::list<BTAction*> ActionList_t;

/** Sequence needs all actions to return SUCCEEDED. **/
class BTSequence : public BTAction
{
  public:
    /** Constructor. **/
    BTSequence();
    /** Destructor. **/
    virtual ~BTSequence();

    /** Execute all actions in the list. **/
    virtual uint8_t execute();
    /** Add action to sequence. **/
    virtual void addAction(BTAction *action);

  private:
    ActionList_t _actionList;
};

#endif /* BT_SEQUENCE_H_ */
