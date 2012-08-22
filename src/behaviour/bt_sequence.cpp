/*
 * bt_sequence.cpp
 *
 *  Created on: Aug 22, 2012
 *      Author: pferdone
 */

#include "bt_sequence.h"

//--------------------------------------------------------------------------------
BTSequence::BTSequence()
{

}

//--------------------------------------------------------------------------------
BTSequence::~BTSequence()
{
  // clean up action list
  for (ActionList_t::iterator iter = _actionList.begin();
       iter != _actionList.end();
       ++iter) {
    (*iter)->setParent(0);
    delete (*iter);
  }
}

//--------------------------------------------------------------------------------
uint8_t BTSequence::execute()
{
  uint8_t state = _state;
  for (ActionList_t::iterator iter = _actionList.begin();
       iter != _actionList.end();
       ++iter) {

    while((state=(*iter)->execute())==IN_PROGRESS) {}
    // if state is FAILED at any point in time, set _state and return
    if (state==FAILED) {
      _state = state;
      return _state;
    }
  }

  _state = SUCCEEDED;
  return _state;
}

//--------------------------------------------------------------------------------
void BTSequence::addAction(BTAction *action)
{
  action->setParent(this);
  _actionList.push_back(action);
}
