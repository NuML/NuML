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

#include <numl/xml/XercesTranscode.h>
#include <numl/xml/XercesAttributes.h>

/** @cond doxygen-ignored */

using namespace std;
using namespace xercesc;

LIBNUML_CPP_NAMESPACE_BEGIN

/** @endcond doxygen-ignored */


/** @cond doxygen-libnuml-internal */

/**
 * Creates a new XMLAttributes set that wraps the given "raw" Xerces-C++
 * Attributes set.
 */
XercesAttributes::XercesAttributes (const Attributes& attrs,
				    const string elementName)
{
  unsigned int size = attrs.getLength();

  mNames .reserve(size);
  mValues.reserve(size);

  for (unsigned int n = 0; n < size; ++n)
  {
    const string            uri   = XercesTranscode( attrs.getURI      (n) );
    const string            name  = XercesTranscode( attrs.getLocalName(n) );
    const string            qname = XercesTranscode( attrs.getQName    (n) );
    const string            value = XercesTranscode( attrs.getValue    (n) );
    const string::size_type pos   = qname.find(":", 0);

    const string prefix = (pos != string::npos) ? qname.substr(0, pos) : "";

    //
    // Skip XML namespace declarations
    //
    if (prefix != "xmlns" && name != "xmlns")
    {
      mNames .push_back( XMLTriple(name, uri, prefix) );
      mValues.push_back( value );
    }
  }

  mElementName = elementName;
}


/**
 * Destroys this XercesAttributes set.
 */
XercesAttributes::~XercesAttributes ()
{
}

LIBNUML_CPP_NAMESPACE_END

/** @endcond doxygen-libnuml-internal */
