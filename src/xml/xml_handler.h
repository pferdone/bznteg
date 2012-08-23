/*
 * xml_handler.h
 *
 *  Created on: Aug 23, 2012
 *      Author: pferdone
 */

#ifndef XML_HANDLER_H_
#define XML_HANDLER_H_

#include <xercesc/framework/XMLDocumentHandler.hpp>

using namespace xercesc;

class XMLHandler : public XMLDocumentHandler
{
  public:
    XMLHandler();
    virtual ~XMLHandler();

    virtual void docCharacters(const XMLCh* const chars, const XMLSize_t length,
        const bool cdataSection);
    virtual void docComment(const XMLCh* const comment);
    virtual void docPI(const XMLCh* const target, const XMLCh* const data);
    virtual void endDocument();
    virtual void endElement(const XMLElementDecl& elemDecl, const unsigned int uriId,
        const bool isRoot, const XMLCh* const prefixName = 0);
    virtual void endEntityReference(const XMLEntityDecl& entDecl);
    virtual void ignorableWhitespace(const XMLCh* const chars, const XMLSize_t length,
        const bool cdataSection);
    virtual void resetDocument();
    virtual void startDocument();
    virtual void startElement(const XMLElementDecl& elemDecl, const unsigned int uriId,
        const XMLCh* const prefixName, const RefVectorOf<XMLAttr>& attrList,
        const XMLSize_t attrCount, const bool isEmpty, const bool isRoot);
    virtual void startEntityReference(const XMLEntityDecl& entDecl);
    virtual void XMLDecl(const XMLCh* const versionStr, const XMLCh* const encodingStr,
        const XMLCh* const standaloneStr, const XMLCh* const autoEncodingStr);
};


#endif /* XML_HANDLER_H_ */
