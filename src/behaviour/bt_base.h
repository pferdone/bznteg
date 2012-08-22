/*
 * bt_base.h
 *
 *  Created on: Aug 21, 2012
 *      Author: pferdone
 */

#ifndef BT_BASE_H_
#define BT_BASE_H_

#include <stdint.h>

/** Base class for all behaviour tree elements. **/
class BTBase
{
  public:
    /** Constructor. **/
    BTBase();
    /** Destructor. **/
    virtual ~BTBase();

    /** Set parent for this object. **/
    void setParent(BTBase *parent);

  protected:
    /** Parent of this behaviour tree element. **/
    BTBase *_parent;
};


#endif /* BT_BASE_H_ */
