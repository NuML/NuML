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

#include <sstream>

#include <numl/xml/XMLToken.h>
#include <numl/xml/XMLTokenizer.h>

/** @cond doxygen-ignored */

using namespace std;

/** @endcond doxygen-ignored */

LIBNUML_CPP_NAMESPACE_BEGIN

/** @cond doxygen-libnuml-internal */

/*
 * Creates a new XMLTokenizer.
 */
XMLTokenizer::XMLTokenizer () :
   mInChars( false )
 , mInStart( false )
 , mEOFSeen( false )
{
}


/*
 * Destroys this XMLTokenizer.
 */
XMLTokenizer::~XMLTokenizer ()
{
}


/*
 * @return the encoding of the underlying XML document.
 */
const string&
XMLTokenizer::getEncoding ()
{
  return mEncoding;
}


/*
 * @return the version of the underlying XML document.
 */
const string&
XMLTokenizer::getVersion ()
{
  return mVersion;
}


/*
 * @return true if this XMLTokenizer has at least one XMLToken ready to
 * deliver, false otherwise.
 *
 * Note that hasNext() == false does not imply isEOF() == true.  The
 * XMLTokenizer may simply be waiting for the XMLParser to parse more of
 * the document.
 */
bool
XMLTokenizer::hasNext () const
{
  return (mTokens.size() > 0);
}


/*
 * @return true if the end of the XML file (document) has been reached
 * and there are no more tokens to consume, false otherwise.
 */
bool
XMLTokenizer::isEOF () const
{
  return mEOFSeen && !hasNext();
}


/*
 * Consume the next XMLToken and return it.
 *
 * @return the next XMLToken.
 */
XMLToken
XMLTokenizer::next ()
{
  XMLToken token( peek() );
  mTokens.pop_front();

  return token;
}


/*
 * Returns the next XMLToken without consuming it.  A subsequent call to
 * either peek() or next() will return the same token.
 *
 * @return the next XMLToken.
 */
const XMLToken&
XMLTokenizer::peek ()
{
  return mTokens.front();
}


/*
 * Prints a string representation of the underlying token stream, for
 * debugging purposes.
 */
string
XMLTokenizer::toString ()
{
  ostringstream stream;

  for (unsigned int n = 0; n < mTokens.size(); ++n)
  {
    stream << '[' << mTokens[n].toString() << ']' << endl;
  }

  return stream.str();
}


/*
 * Receive notification of the XML declaration, i.e.
 * <?xml version="1.0" encoding="UTF-8"?>
 */
void
XMLTokenizer::XML (const string& version, const string& encoding)
{
  mVersion = version;
  mEncoding = encoding;
}


/*
 * Receive notification of the start of an element.
 */
void
XMLTokenizer::startElement (const XMLToken& element)
{
  if (mInChars || mInStart)
  {
    mInChars = false;
    mTokens.push_back( mCurrent );
  }

  //
  // We delay pushing element onto mTokens until we see either an end
  // elment (in which case we can collapse start and end elements into a
  // single token) or the beginning of character data.
  //
  mInStart = true;
  mCurrent = element;
}


/*
 * Receive notification of the end of the document.
 */
void
XMLTokenizer::endDocument ()
{
  mEOFSeen = true;
}


/*
 * Receive notification of the end of an element.
 */
void
XMLTokenizer::endElement (const XMLToken& element)
{
  if (mInChars)
  {
    mInChars = false;
    mTokens.push_back( mCurrent );
  }

  if (mInStart)
  {
    mInStart = false;
    mCurrent.setEnd();
    mTokens.push_back( mCurrent );
  }
  else
  {
    mTokens.push_back(element);
  }
}


/*
 * Receive notification of character data inside an element.
 */
void
XMLTokenizer::characters (const XMLToken& data)
{
  if (mInStart)
  {
    mInStart = false;
    mTokens.push_back( mCurrent );
  }

  if (mInChars)
  {
    mCurrent.append( data.getCharacters() );
  }
  else
  {
    mInChars = true;
    mCurrent = data;
  }
}

/** @endcond doxygen-libnuml-internal */

LIBNUML_CPP_NAMESPACE_END
