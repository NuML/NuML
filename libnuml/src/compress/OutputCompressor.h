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

#ifndef OutputCompressor_h
#define OutputCompressor_h

#include <iostream>
#include <numl/common/extern.h>
#include <numl/compress/CompressCommon.h>

LIBNUML_CPP_NAMESPACE_BEGIN

class LIBNUML_EXTERN OutputCompressor
{
public:

 /**
  * Opens the given gzip file as a gzofstream (subclass of std::ofstream class) object
  * for write access and returned the stream object.
  *
  * @param filename a string, the gzip file name to be written.
  *
  * @note ZlibNotLinked will be thrown if zlib is not linked with libNUML at compile time.
  *
  * @return a ostream* object bound to the given gzip file or NULL if the initialization
  * for the object failed.
  */
  static std::ostream* openGzipOStream(const std::string& filename);


 /**
  * Opens the given bzip2 file as a bzofstream (subclass of std::ofstream class) object
  * for write access and returned the stream object.
  *
  * @param filename a string, the bzip2 file name to be written.
  *
  * @note Bzip2NotLinked will be thrown if zlib is not linked with libNUML at compile time.
  *
  * @return a ostream* object bound to the given bzip2 file or NULL if the initialization
  * for the object failed.
  */
  static std::ostream* openBzip2OStream(const std::string& filename);


 /**
  * Opens the given zip file as a zipofstream (subclass of std::ofstream class) object
  * for write access and returned the stream object.
  *
  * @param filename a string, the zip archive file name to be written.
  * @param filenameinzip a string, the file name to be archived in the above zip archive file.
  * ('filenameinzip' will be extracted when the 'filename' is unzipped)
  *
  * @note ZlibNotLinked will be thrown if zlib is not linked with libNUML at compile time.
  *
  * @return a ostream* object bound to the given zip file or NULL if the initialization
  * for the object failed.
  */
  static std::ostream* openZipOStream(const std::string& filename, const std::string& filenameinzip);

};

LIBNUML_CPP_NAMESPACE_END

#endif // OutputCompressor_h

/** @endcond doxygen-libsbml-internal */
