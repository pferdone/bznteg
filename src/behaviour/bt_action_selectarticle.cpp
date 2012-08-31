/*
 * bt_action_selectarticle.cpp
 *
 *  Created on: Aug 31, 2012
 *      Author: pferdone
 */

#include "bt_action_selectarticle.h"

//--------------------------------------------------------------------------------
BTActionSelectArticle::BTActionSelectArticle(const std::string &article_id)
  : _articleId(article_id),
    _isArticleSelected(false)
{
}

//--------------------------------------------------------------------------------
BTActionSelectArticle::~BTActionSelectArticle()
{
}

//--------------------------------------------------------------------------------
uint8_t BTActionSelectArticle::execute()
{
  NNTPManager &nntp_mgr = NNTPManager::getInstance();
  Logger &logger = Logger::getInstance();

  if (nntp_mgr.isConnected()) {
    if (!_isArticleSelected) {
      std::stringstream ss;
      ss << "ARTICLE <" << _articleId << ">" << std::endl;
      nntp_mgr.send((const uint8_t*)ss.str().c_str(), ss.str().length());
      _isArticleSelected = true;
    } else {
      if (nntp_mgr.poll()) {
        uint32_t response_code = nntp_mgr.getResponseCode();
        _state = (response_code==GROUP_SUCCESSFULLY_SELECTED)?SUCCEEDED:FAILED;
      }
    }
  } else {
    _state = FAILED;
  }

  return _state;
}
