/**
 * @file    libnuml-version.h
 * @brief   Define libNUML version numbers for access from client software.
 * @author  Frank T. Bergmann
 *
 *<!---------------------------------------------------------------------------
 * This file is part of libNUML.  Please visit http://sbml.org for more
 * information about NUML, and the latest version of libNUML.
 *
 * Copyright (C) 2009-2013 jointly by the following organizations: 
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. EMBL European Bioinformatics Institute (EBML-EBI), Hinxton, UK
 *  
 * Copyright (C) 2006-2008 by the California Institute of Technology,
 *     Pasadena, CA, USA 
 *  
 * Copyright (C) 2002-2005 jointly by the following organizations: 
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. Japan Science and Technology Agency, Japan
 * 
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation.  A copy of the license agreement is provided
 * in the file named "LICENSE.txt" included with this software distribution and
 * also available online as http://sbml.org/software/libnuml/license.html
 *------------------------------------------------------------------------- -->
 */

#ifndef LIBNUML_VERSION_H
#define LIBNUML_VERSION_H 

#include "extern.h"


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
#define LIBNUML_VERSION		101


/**
 * LIBNUML_VERSION_STRING:
 *
 * The numeric version as a string: version 1.2.3 becomes "10203".
 */
#define LIBNUML_VERSION_STRING	"101"


LIBNUML_CPP_NAMESPACE_BEGIN
BEGIN_C_DECLS

/**
 * Returns the version number of this copy of libNUML as an integer.
 *
 * @return the libNUML version as an integer; version 1.2.3 becomes 10203.
 */
LIBNUML_EXTERN
int 
getLibNUMLVersion ();


/**
 * Returns the version number of this copy of libNUML as a string.
 *
 * @return the libNUML version as a string; version 1.2.3 becomes
 * "1.2.3".
 *
 * @see getLibNUMLVersionString()
 */
LIBNUML_EXTERN
const char* 
getLibNUMLDottedVersion ();


/**
 * Returns the version number of this copy of libNUML as a string without
 * periods.
 *
 * @return the libNUML version as a string: version 1.2.3 becomes "10203".
 *
 * @see getLibNUMLDottedVersion()
 */
LIBNUML_EXTERN
const char* 
getLibNUMLVersionString ();


END_C_DECLS
LIBNUML_CPP_NAMESPACE_END

#endif  /* LIBNUML_VERSION_H */
