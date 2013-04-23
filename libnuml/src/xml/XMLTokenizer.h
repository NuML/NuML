/**
* Begin svn Header
* $Rev::		$:	Revision of last commit
* $Author::		$:	Author of last commit
* $Date::		$:	Date of last commit
* $HeadURL::	$
* $Id::			$
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
/**
 *
 * @class XMLTokenizer
 * @brief Class implementing methods for turning XML into tokens.
 *
 * @if java @deprecated libNUML internal @endif
 */

#ifndef XMLTokenizer_h
#define XMLTokenizer_h

#ifdef __cplusplus

#include <deque>

#include <numl/xml/XMLExtern.h>
#include <numl/xml/XMLHandler.h>

LIBNUML_CPP_NAMESPACE_BEGIN

/** @cond doxygen-libnuml-internal */

class LIBLAX_EXTERN XMLToken;

class XMLTokenizer : public XMLHandler
{
public:

  /**
   * Creates a new XMLTokenizer.
   */
  XMLTokenizer ();


  /**
   * Destroys this XMLTokenizer.
   */
  ~XMLTokenizer ();


  /**
   * @return the encoding of the underlying XML document.
   */
  const std::string& getEncoding ();


  /**
   * @return the xml version of the underlying XML document.
   */
  const std::string& getVersion ();


  /**
   * @return true if this XMLTokenizer has at least one XMLToken ready to
   * deliver, false otherwise.
   *
   * Note that hasNext() == false does not imply isEOF() == true.  The
   * XMLTokenizer may simply be waiting for the XMLParser to parse more of
   * the document.
   */
  bool hasNext () const;


  /**
   * @return true if the end of the XML file (document) has been reached
   * and there are no more tokens to consume, false otherwise.
   */
  bool isEOF () const;


  /**
   * Consume the next XMLToken and return it.
   *
   * @return the next XMLToken.
   */
  XMLToken next ();


  /**
   * Returns the next XMLToken without consuming it.  A subsequent call to
   * either peek() or next() will return the same token.
   *
   * @return the next XMLToken.
   */
  const XMLToken& peek ();


  /**
   * Prints a string representation of the underlying token stream, for
   * debugging purposes.
   */
  std::string toString ();


  /**
   * Receive notification of the XML declaration, i.e.
   * <?xml version="1.0" encoding="UTF-8"?>
   */
  virtual void XML (const std::string& version, const std::string& encoding);


  /**
   * Receive notification of the start of an element.
   */
  virtual void startElement (const XMLToken& element);


  /**
   * Receive notification of the end of the document.
   */
  virtual void endDocument ();


  /**
   * Receive notification of the end of an element.
   */
  virtual void endElement (const XMLToken& element);


  /**
   * Receive notification of character data inside an element.
   */
  virtual void characters (const XMLToken& data);


protected:

  bool mInChars;
  bool mInStart;
  bool mEOFSeen;

  std::string mEncoding;
  std::string mVersion;

  XMLToken             mCurrent;
  std::deque<XMLToken> mTokens;
};


/** @endcond doxygen-libnuml-internal */

LIBNUML_CPP_NAMESPACE_END

#endif  /* __cplusplus */

#endif  /* XMLTokenizer_h */
