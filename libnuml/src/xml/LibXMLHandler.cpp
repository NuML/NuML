/**
 * @file    LibXMLHandler.cpp
 * @brief   Redirect LibXML events to an XMLHandler
* Begin svn Header
* $Rev$:	Revision of last commit
* $Author$:	Author of last commit
* $Date$:	Date of last commit
* $HeadURL$
* $Id$
* End svn Header
* ****************************************************************************
* This file is part of libNUML.  Please visit http://code.google.com/p/numl/for more
* information about NUML, and the latest version of libNUML.
* Copyright (c) 2013 The University of Manchester.
*
* This library is free software; you can redistribute it and/or modify it
* under the terms of the GNU Lesser General Public License as published
* by the Free Software Foundation.  A copy of the license agreement is
* provided in the file named "LICENSE.txt" included with this software
* distribution and also available online as http://www.gnu.org/licenses/lgpl.html
*
* The original code was initially developed by:
*
* 	SBML Team
* 	Control and Dynamical Systems, MC 107-81
* 	California Institute of Technology
* 	Pasadena, CA, 91125, USA
*
*  	http://www.sbml.org
* 	mailto:sbml-team@caltech.edu
*
* Adapted for NUML by:
*
* 	NUML Team
* 	Computational Systems Biology Group
* 	School of Computer Science
* 	The University of Manchester
* 	Manchester, M1 7DN UK
* 	mailto:josephodada@gmail.com
*
*   Contributor(s):
*   Ben Bornstein
*   Joseph O. Dada, The University of Manchester - initial LIBNUML API and implementation
* ****************************************************************************
**/

#include <numl/xml/XMLHandler.h>
#include <numl/xml/XMLTriple.h>
#include <numl/xml/XMLToken.h>

#include <numl/xml/LibXMLAttributes.h>
#include <numl/xml/LibXMLNamespaces.h>
#include <numl/xml/LibXMLTranscode.h>
#include <numl/xml/LibXMLHandler.h>

/** @cond doxygen-ignored */

using namespace std;

/** @endcond doxygen-ignored */

LIBNUML_CPP_NAMESPACE_BEGIN

/** @cond doxygen-libnuml-internal */

/**
 * The functions below are internal to this file.  They simply redirect to
 * the corresponding LibXMLHandler method (assuming user_data contains a
 * pointer to LibXMLHandler).  I first saw this redirect scheme used in
 * Stefan Hoops' ExpatParser class.
 */

static void
x_start_document (void* user_data)
{
  static_cast<LibXMLHandler*>(user_data)->startDocument();
}


static void
x_start_element (  void*           user_data
                 , const xmlChar*  localname
                 , const xmlChar*  prefix
                 , const xmlChar*  uri
                 , int             num_namespaces
                 , const xmlChar** namespaces
                 , int             num_attributes
                 , int             num_defaulted
                 , const xmlChar** attributes )
{
  const LibXMLAttributes attrs(attributes, localname,
			       num_attributes + num_defaulted);
  const LibXMLNamespaces xmlns(namespaces, num_namespaces);

  static_cast<LibXMLHandler*>(user_data)->
    startElement(localname, prefix, uri, attrs, xmlns);
}


static void
x_end_document (void* user_data)
{
  static_cast<LibXMLHandler*>(user_data)->endDocument();
}


static void
x_end_element (  void*           user_data
               , const xmlChar*  localname
               , const xmlChar*  prefix
               , const xmlChar*  uri )
{
  static_cast<LibXMLHandler*>(user_data)->endElement(localname, prefix, uri);
}


static void
x_characters (void* user_data, const xmlChar* chars, int length)
{
  static_cast<LibXMLHandler*>(user_data)->characters(chars, length);
}


static xmlEntityPtr
x_get_entity (void* user_data, const xmlChar* name)
{
  return xmlGetPredefinedEntity(name);
}


static void
x_set_locator (void* user_data, xmlSAXLocator* locator)
{
  static_cast<LibXMLHandler*>(user_data)->setDocumentLocator(locator);
}


static xmlSAXHandler SAXHandler =
{
 /* internalSubset        */   (internalSubsetSAXFunc)        0
 /* isStandalone          */ , (isStandaloneSAXFunc)          0
 /* hasInternalSubset     */ , (hasInternalSubsetSAXFunc)     0
 /* hasExternalSubset     */ , (hasExternalSubsetSAXFunc)     0
 /* resolveEntity         */ , (resolveEntitySAXFunc)         0
 /* getEntity             */ , (getEntitySAXFunc)             x_get_entity
 /* entityDecl            */ , (entityDeclSAXFunc)            0
 /* notationDecl          */ , (notationDeclSAXFunc)          0
 /* attributeDecl         */ , (attributeDeclSAXFunc)         0
 /* elementDecl           */ , (elementDeclSAXFunc)           0
 /* unparsedEntityDecl    */ , (unparsedEntityDeclSAXFunc)    0
 /* setDocumentLocator    */ , (setDocumentLocatorSAXFunc)    x_set_locator
 /* startDocument         */ , (startDocumentSAXFunc)         x_start_document
 /* endDocument           */ , (endDocumentSAXFunc)           x_end_document
 /* startElement          */ , (startElementSAXFunc)          0
 /* endElement            */ , (endElementSAXFunc)            0
 /* reference             */ , (referenceSAXFunc)             0
 /* characters            */ , (charactersSAXFunc)            x_characters
 /* ignorableWhitespace   */ , (ignorableWhitespaceSAXFunc)   0
 /* processingInstruction */ , (processingInstructionSAXFunc) 0
 /* comment               */ , (commentSAXFunc)               0
 /* warning               */ , (warningSAXFunc)               0
 /* error                 */ , (errorSAXFunc)                 0
 /* fatalError            */ , (fatalErrorSAXFunc)            0
 /* getParameterEntity    */ , (getParameterEntitySAXFunc)    0
 /* cdataBlock            */ , (cdataBlockSAXFunc)            0
 /* externalSubset        */ , (externalSubsetSAXFunc)        0
 /* initialized           */ , (unsigned int)                 XML_SAX2_MAGIC
 /* void* _private        */ , (void*)                        0
 /* startElementNs        */ , (startElementNsSAX2Func)       x_start_element
 /* endElementNs          */ , (endElementNsSAX2Func)         x_end_element
 /* xmlStructuredError    */ , (xmlStructuredErrorFunc)       0
};


/**
 * Creates a new LibXMLHandler.  LibXML events will be redirected to the
 * given XMLHandler.
 */
LibXMLHandler::LibXMLHandler (XMLHandler& handler) :
   mHandler( handler )
 , mContext( 0       )
 , mLocator( 0       )
{
}


/**
 * Destroys this LibXMLHandler.
 */
LibXMLHandler::~LibXMLHandler ()
{
}


/**
 * Receive notification of the beginning of the document.
 */
void
LibXMLHandler::startDocument ()
{
  const string version  = LibXMLTranscode( mContext->version  );
  const string encoding = LibXMLTranscode( mContext->encoding );

  mHandler.startDocument();
  mHandler.XML(version, encoding);
}


/**
 * Receive notification of the start of an element.
 *
 * @param  localname   The local part of the element name
 * @param  prefix      The namespace prefix part of the element name.
 * @param  uri         The URI of the namespace for this element
 * @param  namespaces  The namespace definitions for this element
 * @param  attributes  The specified or defaulted attributes
 */
void
LibXMLHandler::startElement (  const xmlChar*           localname
                             , const xmlChar*           prefix
                             , const xmlChar*           uri
                             , const LibXMLAttributes&  attributes
                             , const LibXMLNamespaces&  namespaces )
{
  const string nsuri    = LibXMLTranscode( uri       );
  const string name     = LibXMLTranscode( localname );
  const string nsprefix = LibXMLTranscode( prefix    );

  const XMLTriple  triple ( name, nsuri, nsprefix );
  const XMLToken   element( triple, attributes, namespaces,
                            getLine(), getColumn() );

  mHandler.startElement(element);
}


/**
 * Receive notification of the end of an element.
 *
 * @param  localname  The local part of the element name
 * @param  prefix     The namespace prefix part of the element name.
 * @param  uri        The URI of the associated namespace for this element
 */
void
LibXMLHandler::endElement (  const xmlChar*   localname
                           , const xmlChar*   prefix
                           , const xmlChar*   uri )
{
  const string nsuri    = LibXMLTranscode( uri       );
  const string name     = LibXMLTranscode( localname );
  const string nsprefix = LibXMLTranscode( prefix    );

  const XMLTriple  triple ( name, nsuri, nsprefix );
  const XMLToken   element( triple, getLine(), getColumn() );

  mHandler.endElement(element);
}


/**
 * Receive notification of the end of the document.
 */
void
LibXMLHandler::endDocument ()
{
  mHandler.endDocument();
}


/**
 * Receive notification of character data inside an element.
 *
 * @param  chars   The characters
 * @param  length  The number of characters to use from the character array
 */
void
LibXMLHandler::characters (const xmlChar* chars, int length)
{
  XMLToken data( LibXMLTranscode(chars, length) );
  mHandler.characters(data);
}


/**
 * Sets the underlying parser context.  LibXML initialization is such
 * that the context cannot passed in when a LibXMLHandler is created.
 *
 * The context is needed by the DocumentLocator to query the current line
 * and column numbers.
 */
void
LibXMLHandler::setContext (xmlParserCtxt* context)
{
  mContext = context;
}


/**
 * Receive a Locator object for document events.
 */
void
LibXMLHandler::setDocumentLocator (const xmlSAXLocator* locator)
{
  mLocator = locator;
}


/**
 * @return the internal xmlSAXHandler that redirects libXML callbacks to
 * the method above.  Pass the return value along with "this" to one of the
 * libXML parse functions.  For example:
 *
 *   xmlSAXUserParseFile    (this->getInternalHandler(), this, filename);
 *   xmlSAXUserParseMemory  (this->getInternalHandler(), this, buffer, len);
 *   xmlCreatePushParserCtxt(this->getInternalHandler, this, ...);
 */
xmlSAXHandler*
LibXMLHandler::getInternalHandler ()
{
  return &SAXHandler;
}


/**
 * @return the column number of the current XML event.
 */
unsigned int
LibXMLHandler::getColumn () const
{
  if (mContext)
    return static_cast<unsigned int>( xmlSAX2GetColumnNumber(mContext) );
  else
    return 0;
}


/**
 * @return the line number of the current XML event.
 */
unsigned int
LibXMLHandler::getLine () const
{
  if (mContext)
    return static_cast<unsigned int>( xmlSAX2GetLineNumber(mContext) );
  else
    return 0;
}

/** @endcond doxygen-libnuml-internal */

LIBNUML_CPP_NAMESPACE_END