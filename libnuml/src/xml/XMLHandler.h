/**
* Begin svn Header
* $Rev::		$:	Revision of last commit
* $Author::		$:	Author of last commit
* $Date::		$:	Date of last commit
* $HeadURL::	$
* $Id::			$
* End svn Header
* ***************************************************************************
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
*   Joseph O. Dada, The University of Manchester - initial LIBNUML API and implementation
* ***************************************************************************
**/

/**
 *
 * @class XMLHandler
 * @brief Class providing a unified interface to different XML parsers.
 *
 * @if java @deprecated libNUML internal @endif
 */

#ifndef XMLHandler_h
#define XMLHandler_h

#ifdef __cplusplus

#include <string>
#include <numl/xml/XMLExtern.h>

LIBNUML_CPP_NAMESPACE_BEGIN

/** @cond doxygen-libnuml-internal */

class XMLToken;


class LIBLAX_EXTERN XMLHandler
{
public:

  /**
   * Creates a new XMLHandler.
   */
  XMLHandler ();


  /**
   * Destroys this XMLHandler.
   */
  virtual ~XMLHandler ();


  /**
   * Receive notification of the beginning of the document.
   *
   * By default, do nothing. Application writers may override this method
   * in a subclass to take specific actions at the start of the document.
   */
  virtual void startDocument ();


  /**
   * Receive notification of the XML declaration, i.e.
   * <?xml version="1.0" encoding="UTF-8"?>
   *
   * By default, do nothing. Application writers may override this method
   * in a subclass to take specific actions at the declaration.
   */
  virtual void XML (const std::string& version, const std::string& encoding);


  /**
   * Receive notification of the start of an element.
   *
   * By default, do nothing. Application writers may override this method
   * in a subclass to take specific actions at the start of each element.
   */
  virtual void startElement (const XMLToken& element);


  /**
   * Receive notification of the end of the document.
   *
   * By default, do nothing. Application writers may override this method
   * in a subclass to take specific actions at the end of the document.
   */
  virtual void endDocument ();


  /**
   * Receive notification of the end of an element.
   *
   * By default, do nothing. Application writers may override this method
   * in a subclass to take specific actions at the end of each element.
   */
  virtual void endElement (const XMLToken& element);


  /**
   * Receive notification of character data inside an element.
   *
   * By default, do nothing. Application writers may override this method
   * to take specific actions for each chunk of character data.
   */
  virtual void characters (const XMLToken& data);
};


/** @endcond doxygen-libnuml-internal */

LIBNUML_CPP_NAMESPACE_END

#endif  /* __cplusplus */
#endif  /* XMLHandler_h */
