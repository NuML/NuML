/**
 * @file    SyntaxChecker.cpp
 * @brief   Syntax checking functions
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
*   Sarah Keating
*   Joseph O. Dada, The University of Manchester - initial LIBNUML API and implementation
* ****************************************************************************
**/

/*
 * @class SyntaxChecker
 * @brief Methods for checking syntax of ids, metaids and units
 *
 */

#ifndef SyntaxChecker_h
#define SyntaxChecker_h


#include <numl/common/extern.h>
#include <numl/NMBase.h>
#include <numl/xml/XMLNode.h>
#include <numl/util/util.h>

#ifdef __cplusplus


#include <string>

LIBNUML_CPP_NAMESPACE_BEGIN

class LIBNUML_EXTERN SyntaxChecker
{
public:

  /**
   * Predicate returning @c true or @c false depending on whether the
   * argument string conforms to the NUML type SId.
   *
   * @param sid string to be checked for conformance
   *
   * @return @c true if the string conforms to type SId, @c false otherwise.
   *
   * @note The literal representation of NUML type SId consists of strings
   * of characters restricted to:
   *
   *  - letter ::= 'a'..'z','A'..'Z'
   *  - digit  ::= '0'..'9'
   *  - idChar ::= letter | digit | '_'
   *  - SId    ::= ( letter | '_' ) idChar*
   */  
  static bool isValidNUMLSId(std::string sid);

  
  /**
   * Predicate returning @c true or @c false depending on whether the
   * argument string conforms to the XML 1.0 type ID. 
   *
   * @param id string to be checked for conformance
   *
   * @return @c true if the string conforms to type ID, @c false otherwise.
   *
   * @note The literal representation of XML 1.0 type ID consists of strings 
   * of characters restricted to:
   *
   *  - NCNameChar ::= letter | digit | '.' | '-' | '_' | ':' | CombiningChar | Extender
   *  - ID ::= ( letter | '_' | ':' ) NCNameChar*
   */  
  static bool isValidXMLID(std::string id);


  /**
   * Predicate returning @c true or @c false depending on whether the
   * argument string conforms to the NUML type UnitSId.
   *
   * @param units string to be checked for conformance
   *
   * @return @c true if the string conforms to type UnitSId, 
   * @c false otherwise.
   *
   * @note The literal representation of NUML type UniySId consists of strings
   * of characters restricted to:
   *
   *  - letter ::= 'a'..'z','A'..'Z'
   *  - digit  ::= '0'..'9'
   *  - idChar ::= letter | digit | '_'
   *  - UnitSId    ::= ( letter | '_' ) idChar*
   */
   static bool isValidUnitSId(std::string units);


  /**
   * Predicate returning @c true or @c false depending on whether the
   * argument XMLNode represents XHTML that conforms to the 
   * requirements of the NUML specification.
   *
   * @param xhtml the XMLNode to be checked for conformance.
   * @param numlns the NUMLNamespaces associated with the object.
   *
   * @return @c true if the XMLNode conforms, @c false otherwise.
   *
   * @note the optional NUMLNamespaces artype filter textgument can be used to
   * check for the declaration of the XHTML namespace at the top-level
   * within an NUMLDocument.
   */
  static bool hasExpectedXHTMLSyntax(const XMLNode * xhtml, 
                                     NUMLNamespaces * numlns = NULL);


  /** @cond doxygen-libnuml-internal */

  /*
   * return true if element is an allowed xhtml element
   */
  static bool isAllowedElement(const XMLNode &node);

  /** @endcond doxygen-libnuml-internal */

  /** @cond doxygen-libnuml-internal */

  /*
   * return true has the xhtml ns correctly declared
   */
  static bool hasDeclaredNS(const XMLNode &node, const XMLNamespaces* toplevelNS);

  /** @endcond doxygen-libnuml-internal */

  /** @cond doxygen-libnuml-internal */

  /*
   * return true if the html tag contains both a title
   * and a body tag 
   */
  static bool isCorrectHTMLNode(const XMLNode &node);

  /** @endcond doxygen-libnuml-internal */

protected:  
  /** @cond doxygen-libnuml-internal */
  /**
   * Checks if a character is part of the Unicode Letter set.
   * @return true if the character is a part of the set, false otherwise.
   */
  static bool isUnicodeLetter(std::string::iterator, unsigned int);


  /**
   * Checks if a character is part of the Unicode Digit set.
   * @return true if the character is a part of the set, false otherwise.
   */
  static bool isUnicodeDigit(std::string::iterator, unsigned int);


  /**
   * Checks if a character is part of the Unicode CombiningChar set.
   * @return true if the character is a part of the set, false otherwise.
   */
  static bool isCombiningChar(std::string::iterator, unsigned int);


  /**
   * Checks if a character is part of the Unicode Extender set.
   * @return true if the character is a part of the set, false otherwise.
   */
  static bool isExtender(std::string::iterator, unsigned int);

  /** @endcond doxygen-libnuml-internal */
};

LIBNUML_CPP_NAMESPACE_END

#endif  /* __cplusplus */


#ifndef SWIG

LIBNUML_CPP_NAMESPACE_BEGIN
BEGIN_C_DECLS

/*-----------------------------------------------------------------------------
 * See the .cpp file for the documentation of the following functions.
 *---------------------------------------------------------------------------*/
LIBNUML_EXTERN
int
SyntaxChecker_isValidNUMLSId(const char * sid);


LIBNUML_EXTERN
int
SyntaxChecker_isValidXMLID(const char * id);


LIBNUML_EXTERN
int
SyntaxChecker_isValidUnitSId(const char * units);


LIBNUML_EXTERN
int
SyntaxChecker_hasExpectedXHTMLSyntax(XMLNode_t * node, 
                                     NUMLNamespaces_t * numlns);

END_C_DECLS
LIBNUML_CPP_NAMESPACE_END


#endif  /* !SWIG */
#endif  /* SyntaxChecker_h */
