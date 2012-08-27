/*
 * nntp_common.h
 *
 *  Created on: Aug 20, 2012
 *      Author: pferdone
 */

#ifndef NNTP_COMMON_H_
#define NNTP_COMMON_H_

// codes used to identify responses are taken from here:
// http://tools.ietf.org/html/rfc3977#section-3.2
// applies to this return code pattern: ?xx
enum NNTP_RESPONSE {
  INVORMATIVE_RESPONE		= 0x31,
  COMMAND_COMPLETED_OK  = 0x32,
  COMMAND_OK_SEND_REST  = 0x33,
  COMMAND_OK_FAILED     = 0x34,
  COMMAND_ERROR         = 0x35,
};

// applies to this return code pattern: x?x
enum NNTP_CATEGORY {
  CONNECTION            = 0x30,
  NG_SELECTION          = 0x31,
  ARTICLE_SELECTION     = 0x32,
  POSTING               = 0x33,
  AUTHENTICATION        = 0x38,
  PRIVATE               = 0x39,
};

// applies to specific return codes (the 0x20 is just there to make it compare to an int)
enum NNTP_RESPONSE_CODES {
  HELP_TEXT_FOLLOWS             = 0x20303031,   // 100: help text follows
  SERVICE_AVAILABLE             = 0x20303032,   // 200: service available, posting allowed
  CLOSING_CONNECTION            = 0x20353032,   // 205: closing connection, goodbye
  GROUP_SUCCESSFULLY_SELECTED   = 0x20313132,   // 211: group successfully selected
  INFORMATION_FOLLOWS           = 0x20353132,   // 215: information follows
  ARTICLE_FOLLOWS               = 0x20303232,   // 220: article follows
  ARTICLE_POSTED_OK             = 0x20303432,   // 240: article posted ok
  AUTHENTICATION_ACCEPTED       = 0x20313832,   // 281: authentication accepted
  PASSWORD_REQUIRED             = 0x20313833,   // 381: password required
  NO_SUCH_NEWSGROUP             = 0x20313134,   // 411: no such newsgroup
  NO_NEWSGROUP_SELECTED         = 0x20323134,   // 412: no newsgroup has been selected
  POSTING_NOT_ALLOWED           = 0x20303434,   // 440: posting not allowed
  POSTING_FAILED                = 0x20303434,   // 441: posting failed
  AUTHENTICATION_FAILED         = 0x20313834,   // 481: authentication failed/rejected
  AUTHENTICATION_OOS            = 0x20323834,   // 482: authentication out of sequence
  CONNECTION_CLOSED             = 0x20303034,   // 400: connection has been closed
  CHANGE_CONNECTION_STATE       = 0x20313034,   // 401: client must change the state of the connection in some other manner
  INTERNAL_SERVER_ERROR         = 0x20333034,   // 403: internal error prevents server from executing such command
  AUTHENTICATION_NEEDED         = 0x20303834,   // 480: client need to authenticate before facility can be used with this connection
  TLS_REQUIRED                  = 0x20333834,   // 483: client must negotiate appropriate privacy protection on the connection over TLS
  COMMAND_NOT_IMPLEMENTED       = 0x20303035,   // 500: no such command is implemented
  COMMAND_SYNTAX_ERROR          = 0x20313035,   // 501: syntax error on existing command
  NEW_AUTH_CONNECTION_REQUIRED  = 0x20323035,   // 502: needs a new connection with authenticated user to execute command
  NO_SUCH_OPTIONAL_FEATURE      = 0x20333035,   // 503: command itself is correct, but has no such optional feature
  REQUIRES_BASE64_ENCODING      = 0x20343035,   // 504: requires base64 encoding
};

#endif /* NNTP_COMMON_H_ */
