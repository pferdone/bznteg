/*
 * nzb_common.h
 *
 *  Created on: Aug 27, 2012
 *      Author: pferdone
 */

#ifndef NZB_COMMON_H_
#define NZB_COMMON_H_

#include <list>
#include <string>
#include <stdint.h>

/** Segment structure. **/
struct Segment_s
{
  uint32_t number;
  std::size_t bytes;
  std::string article;
};

typedef std::list<std::string> Groups_t;
typedef std::list<Segment_s*> Segments_t;

/** NZB file structure. **/
struct NzbFile_s {
  std::string poster;
  std::string subject;
  int32_t date;
  Groups_t groups;
  Segments_t segments;
};

typedef std::list<NzbFile_s*> FileList_t;


#endif /* NZB_COMMON_H_ */
