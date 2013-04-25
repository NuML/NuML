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

#ifdef USE_EXPAT
#include <numl/xml/ExpatParser.h>
#endif

#ifdef USE_LIBXML
#include <numl/xml/LibXMLParser.h>
#endif

#ifdef USE_XERCES
#include <numl/xml/XercesParser.h>
#endif

#include <numl/xml/XMLErrorLog.h>
#include <numl/xml/XMLParser.h>

/** @cond doxygen-ignored */

using namespace std;

/** @endcond doxygen-ignored */

LIBNUML_CPP_NAMESPACE_BEGIN

/*
 * Creates a new XMLParser.  The parser will notify the given XMLHandler
 * of parse events and errors.
 */
XMLParser::XMLParser () : mErrorLog(0)
{
}


/*
 * Destroys this XMLParser.
 */
XMLParser::~XMLParser ()
{
}


/*
 * Creates a new XMLParser.  The parser will notify the given XMLHandler
 * of parse events and errors.
 *
 * The library parameter indicates the underlying XML library to use if
 * the XML compatibility layer has been linked against multiple XML
 * libraries.  It may be one of: "expat" (default), "libxml", or
 * "xerces".
 *
 * If the XML compatibility layer has been linked against only a single
 * XML library, the library parameter is ignored.
 */
XMLParser*
XMLParser::create (XMLHandler& handler, const string library)
{
#ifdef USE_EXPAT
  if (library.empty() || library == "expat")  return new ExpatParser(handler);
#endif

#ifdef USE_LIBXML
  if (library.empty() || library == "libxml") return new LibXMLParser(handler);
#endif

#ifdef USE_XERCES
  if (library.empty() || library == "xerces") return new XercesParser(handler);
#endif

  return 0;
}


/*
 * @return an XMLErrorLog which can be used to log XML parse errors and
 * other validation errors (and messages).
 */
XMLErrorLog*
XMLParser::getErrorLog ()
{
  return mErrorLog;
}


/*
 * Sets the XMLErrorLog this parser will use to log errors.
 */
int
XMLParser::setErrorLog (XMLErrorLog* log)
{
  mErrorLog = log;
  if (mErrorLog) 
  {
    return mErrorLog->setParser(this);
  }
  else
  {
    return LIBNUML_OPERATION_FAILED;
  }
}

LIBNUML_CPP_NAMESPACE_END

