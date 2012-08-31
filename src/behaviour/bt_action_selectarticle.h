/*
 * bt_action_selectarticle.h
 *
 *  Created on: Aug 31, 2012
 *      Author: pferdone
 */

#ifndef BT_ACTION_SELECTARTICLE_H_
#define BT_ACTION_SELECTARTICLE_H_

#include <string>
#include <sstream>
#include "bt_action.h"
#include "../nntp_manager.h"
#include "../logger.h"

/** Select article. **/
class BTActionSelectArticle : public BTAction
{
  public:
    /** Constructor. **/
    BTActionSelectArticle(const std::string &article_id);
    /** Destructor. **/
    virtual ~BTActionSelectArticle();

    /** Select article and save it in a buffer. **/
    virtual uint8_t execute();

  private:
    /** Article ID. **/
    const std::string _articleId;
    /** Is article selected? **/
    bool _isArticleSelected;
    /** Article gets saved here. **/
    Buffer8_t _buffer;
};


#endif /* BT_ACTION_SELECTARTICLE_H_ */
