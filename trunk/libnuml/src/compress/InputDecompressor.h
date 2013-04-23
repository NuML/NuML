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
#ifndef InputDecompressor_h
#define InputDecompressor_h

#include <iostream>
#include <numl/common/extern.h>
#include <numl/compress/CompressCommon.h>


LIBNUML_CPP_NAMESPACE_BEGIN

class LIBNUML_EXTERN InputDecompressor
{
public:

 /**
  * Opens the given gzip file as a gzifstream (subclass of std::ifstream class) object
  * for read access and returned the stream object.
  *
  * @param filename a string, the gzip file name to be read.
  *
  * @note ZlibNotLinked will be thrown if zlib is not linked with libNUML at compile time.
  *
  * @return a istream* object bound to the given gzip file or NULL if the initialization
  * for the object failed.
  */
  static std::istream* openGzipIStream (const std::string& filename);


 /**
  * Opens the given bzip2 file as a bzifstream (subclass of std::ifstream class) object
  * for read access and returned the stream object.
  *
  * @param filename a string, the bzip2 file name to be read.
  *
  * @note Bzip2NotLinked will be thrown if zlib is not linked with libNUML at compile time.
  *
  * @return a istream* object bound to the given bzip2 file or NULL if the initialization
  * for the object failed.
  */
  static std::istream* openBzip2IStream (const std::string& filename);


 /**
  * Opens the given zip file as a zipifstream (subclass of std::ifstream class) object
  * for read access and returned the stream object.
  *
  * @param filename a string, the zip file name to be read.
  *
  * @return a istream* object bound to the given zip file or NULL if the initialization
  * for the object failed.
  *
  * @note The first file in the given zip archive file will be opened if the zip archive
  * contains two or more files.
  */
  static std::istream* openZipIStream (const std::string& filename);


 /**
  * Opens the given gzip file and returned the string in the file.
  *
  * @param filename a string, the gzip file name to be read.
  *
  * @note ZlibNotLinked will be thrown if zlib is not linked with libNUML at compile time.
  *
  * @return a string, the string in the given file, or empty string if 
  * failed to open the file.
  */
  static char* getStringFromGzip (const std::string& filename);


 /**
  * Opens the given bzip2 file and returned the string in the file.
  *
  * @param filename a string, the bzip2 file name to be read.
  *
  * @note Bzip2NotLinked will be thrown if zlib is not linked with libNUML at compile time.
  *
  * @return a string, the string in the given file, or empty string if failed to open
  * the file.
  */
  static char* getStringFromBzip2 (const std::string& filename);


 /**
  * Opens the given zip file and returned the string in the file.
  *
  * @param filename a string, the zip file name to be read.
  *
  * @return a string, the string in the given file, or empty string if failed to open
  * the file.
  *
  * @note ZlibNotLinked will be thrown if zlib is not linked with libNUML at compile time.
  * The first file in the given zip archive file will be opened if the zip archive
  * contains two or more files.
  */
  static char* getStringFromZip (const std::string& filename);

};

LIBNUML_CPP_NAMESPACE_END

#endif // InputDecompressor_h

/** @endcond doxygen-libnuml-internal */
