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
* ****************************************************************************
**/

#include <numl/xml/ExpatAttributes.h>

/** @cond doxygen-ignored */

using namespace std;

LIBNUML_CPP_NAMESPACE_BEGIN

/** @endcond doxygen-ignored */


/** @cond doxygen-libnuml-internal */

/**
 * Creates a new XMLAttributes set from the given "raw" Expat attributes.
 * The Expat attribute names are assumed to be in namespace triplet form
 * separated by sepchar.
 */
ExpatAttributes::ExpatAttributes (const XML_Char** attrs,
				  const XML_Char* elementName,
				  const XML_Char sep)
{
  unsigned int size = 0;
  while (attrs[2 * size]) ++size;

  mNames .reserve(size);
  mValues.reserve(size);

  for (unsigned int n = 0; n < size; ++n)
  {
    mNames .push_back( XMLTriple( attrs[2 * n], sep ) );
    mValues.push_back( string   ( attrs[2 * n + 1]  ) );
  }

  mElementName = elementName;
}


/**
 * Destroys this Attribute set.
 */
ExpatAttributes::~ExpatAttributes ()
{
}

LIBNUML_CPP_NAMESPACE_END

/** @endcond doxygen-libnuml-internal */
