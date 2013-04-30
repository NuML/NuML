/**
* Begin svn Header
* $Rev$:	Revision of last commit
* $Author$:	Author of last commit
* $Date$:	Date of last commit
* $HeadURL$
* $Id$
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

#ifndef LIBNUML_VERSION_H
#define LIBNUML_VERSION_H 

#include <numl/common/extern.h>

/**
 * LIBNUML_DOTTED_VERSION:
 *
 * A version string of the form "1.2.3".
 */
#define LIBNUML_DOTTED_VERSION	"1.0.1"

/**
 * LIBNUML_VERSION:
 *
 * The version as an integer: version 1.2.3 becomes 10203.  Since the major
 * number comes first, the overall number will always increase when a new
 * libNUML is released, making it easy to use less-than and greater-than
 * comparisons when testing versions numbers.
 */
#define LIBNUML_VERSION		10001

/**
 * LIBNUML_VERSION_STRING:
 *
 * The numeric version as a string: version 1.2.3 becomes "10203".
 */
#define LIBNUML_VERSION_STRING	"10001"

LIBNUML_CPP_NAMESPACE_BEGIN
BEGIN_C_DECLS

/**
 * Returns the libNUML version as an integer: version 1.2.3 becomes 10203.
 *
 * @return the libNUML version as an integer: version 1.2.3 becomes 10203.
 */
LIBNUML_EXTERN
int 
getLibNUMLVersion () ;


/**
 * Returns the libNUML version as a string of the form "1.2.3".
 *
 * @return the libNUML version as a string of the form "1.2.3".
 */
LIBNUML_EXTERN
const char* 
getLibNUMLDottedVersion ();


/**
 * Returns the libNUML version as a string: version 1.2.3 becomes "10203".
 *
 * @return the libNUML version as a string: version 1.2.3 becomes "10203".
 */
LIBNUML_EXTERN
const char* 
getLibNUMLVersionString ();

END_C_DECLS
LIBNUML_CPP_NAMESPACE_END

#endif  /* LIBNUML_VERSION_H */