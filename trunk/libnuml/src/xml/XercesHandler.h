/**
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
*      SBML Team
*      Control and Dynamical Systems, MC 107-81
*      California Institute of Technology
*      Pasadena, CA, 91125, USA
*
*      http://www.sbml.org
*      mailto:sbml-team@caltech.edu
*
* Adapted for NUML by:
*
*   NUML Team
*   Computational Systems Biology Group
*   School of Computer Science
*   The University of Manchester
*   Manchester, UK
*
*   Contributor(s):
*   Joseph O. Dada, The University of Manchester - initial LIBNUML API and implementation
* ****************************************************************************
**/

#ifndef XercesHandler_h
#define XercesHandler_h

#ifdef __cplusplus

#include <string>

#include <numl/xml/XercesTranscode.h>
#include <xercesc/sax2/DefaultHandler.hpp>

LIBNUML_CPP_NAMESPACE_BEGIN

/** @cond doxygen-libnuml-internal */

class XMLHandler;


class XercesHandler : public xercesc::DefaultHandler
{
public:

  /**
   * Creates a new XercesHandler.  Xerces-C++ SAX2 events will be
   * redirected to the given XMLHandler.
   */
  XercesHandler (XMLHandler& handler);


  /**
   * Destroys this XercesHandler.
   */
  virtual ~XercesHandler ();


  /**
   * Receive notification of the beginning of the document.
   */
  void startDocument ();


  /**
   * Receive notification of the start of an element.
   *
   * @param  uri        The URI of the associated namespace for this element
   * @param  localname  The local part of the element name
   * @param  qname      The qualified name of this element
   * @param  attrs      The specified or defaulted attributes
   */
  virtual void startElement
  (
     const XMLCh* const  uri
   , const XMLCh* const  localname
   , const XMLCh* const  qname
   , const xercesc::Attributes& attrs
  );


  /**
   * Receive notification of the end of the document.
   */
  void endDocument ();


  /**
   * Receive notification of the end of an element.
   *
   * @param  uri        The URI of the associated namespace for this element
   * @param  localname  The local part of the element name
   * @param  qname      The qualified name of this element
   */
  void endElement
  (
     const XMLCh* const  uri
   , const XMLCh* const  localname
   , const XMLCh* const  qname
  );


  /**
   * Receive notification of character data inside an element.
   *
   * @param  chars   The characters
   * @param  length  The number of characters to use from the character array
   */
  void characters (const XMLCh* const chars, const XercesSize_t length);


  /**
   * @return the column number of the current XML event.
   */
  unsigned int getColumn () const;


  /**
   * @return the line number of the current XML event.
   */
  unsigned int getLine () const;


  /**
   * Receive a Locator object for document events.
   */
  void setDocumentLocator (const xercesc::Locator* const locator);


protected:

  XMLHandler&              mHandler;
  const xercesc::Locator*  mLocator;
};

/** @endcond doxygen-libnuml-internal */

LIBNUML_CPP_NAMESPACE_END

#endif  /* __cplusplus */
#endif  /* XercesHandler_h */
