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

/**
 * @class XMLInputStream
 *
 * @if java @deprecated libNUML internal @endif
 */

#ifndef XMLInputStream_h
#define XMLInputStream_h

#include <numl/xml/XMLExtern.h>
#include <numl/xml/XMLToken.h>
#include <numl/common/numlfwd.h>
#include <numl/common/operationReturnValues.h>


#ifdef __cplusplus

#include <string>
#include <fstream>

#include <numl/xml/XMLTokenizer.h>

LIBNUML_CPP_NAMESPACE_BEGIN

/** @cond doxygen-libnuml-internal */

class XMLErrorLog;
class XMLParser;


class LIBLAX_EXTERN XMLInputStream
{
public:

  /**
   * Creates a new XMLInputStream.
   *
   * @docnote The native C++ implementation of this method defines a
   * default argument value.  In the documentation generated for different
   * libNUML language bindings, you may or may not see corresponding
   * arguments in the method declarations.  For example, in Java, a default
   * argument is handled by declaring two separate methods, with one of
   * them having the argument and the other one lacking the argument.
   * However, the libNUML documentation will be @em identical for both
   * methods.  Consequently, if you are reading this and do not see an
   * argument even though one is described, please look for descriptions of
   * other variants of this method near where this one appears in the
   * documentation.
   */
  XMLInputStream (  const char*        content
                  , bool               isFile   = true
                  , const std::string  library  = "" 
		  , XMLErrorLog*       errorLog = 0 );

  /**
   * Destroys this XMLInputStream.
   */
  virtual ~XMLInputStream ();


  /**
   * @return the encoding of the XML stream.
   */
  const std::string& getEncoding ();


  /**
   * @return the version of the XML stream.
   */
  const std::string& getVersion ();


  /**
   * @return an XMLErrorLog which can be used to log XML parse errors and
   * other validation errors (and messages).
   */
  XMLErrorLog* getErrorLog ();


  /**
   * @return true if end of file (stream) has been reached, false
   * otherwise.
   */
  bool isEOF () const;


  /**
   * @return true if a fatal error occurred while reading from this stream.
   */
  bool isError () const;


  /**
   * @return true if the stream is in a good state (i.e. isEOF() and
   * isError() are both false), false otherwise.
   */
  bool isGood () const;


  /**
   * Consumes the next XMLToken and return it.
   *
   * @return the next XMLToken or EOF (XMLToken.isEOF() == true).
   */
  XMLToken next ();


  /**
   * Returns the next XMLToken without consuming it.  A subsequent call to
   * either peek() or next() will return the same token.
   *
   * @return the next XMLToken or EOF (XMLToken.isEOF() == true).
   */
  const XMLToken& peek ();


  /**
   * Consume zero or more XMLTokens up to and including the corresponding
   * end XML element or EOF.
   */
  void skipPastEnd (const XMLToken& element);


  /**
   * Consume zero or more XMLTokens up to but not including the next XML
   * element or EOF.
   */
  void skipText ();


  /**
   * Sets the XMLErrorLog this stream will use to log errors.
   *
   * @return integer value indicating success/failure of the
   * function.  @if clike The value is drawn from the
   * enumeration #OperationReturnValues_t. @endif The possible values
   * returned by this function are:
   * @li LIBNUML_OPERATION_SUCCESS
   * @li LIBNUML_OPERATION_FAILED
   */
  int setErrorLog (XMLErrorLog* log);


  /**
   * Prints a string representation of the underlying token stream, for
   * debugging purposes.
   */
  std::string toString ();

  /**
  * @return the content processed by the XML stream.
  */
  std::string getContent ();


protected:

  /**
   * Unitialized XMLInputStreams may only be created by subclasses.
   */
  XMLInputStream ();


  /**
   * Runs mParser until mTokenizer is ready to deliver at least one
   * XMLToken or a fatal error occurs.
   */
  void queueToken ();


  bool mIsError;

  XMLToken     mEOF;
  XMLTokenizer mTokenizer;
  XMLParser*   mParser;
  std::string mContent;

};

/** @endcond doxygen-libnuml-internal */

LIBNUML_CPP_NAMESPACE_END

#endif  /* __cplusplus */



#ifndef SWIG

LIBNUML_CPP_NAMESPACE_BEGIN

/** @cond doxygen-libnuml-internal */

BEGIN_C_DECLS

/*-----------------------------------------------------------------------------
 * See the .cpp file for the documentation of the following functions.
 *---------------------------------------------------------------------------*/


LIBLAX_EXTERN
XMLInputStream_t *
XMLInputStream_create (const char* content, int isFile, const char *library);


LIBLAX_EXTERN
void
XMLInputStream_free (XMLInputStream_t *stream);


LIBLAX_EXTERN
const char *
XMLInputStream_getEncoding (XMLInputStream_t *stream);


LIBLAX_EXTERN
XMLErrorLog_t *
XMLInputStream_getErrorLog (XMLInputStream_t *stream);


LIBLAX_EXTERN
int
XMLInputStream_isEOF (XMLInputStream_t *stream);


LIBLAX_EXTERN
int
XMLInputStream_isError (XMLInputStream_t *stream);


LIBLAX_EXTERN
int
XMLInputStream_isGood (XMLInputStream_t *stream);


LIBLAX_EXTERN
XMLToken_t *
XMLInputStream_next (XMLInputStream_t *stream);


LIBLAX_EXTERN
const XMLToken_t *
XMLInputStream_peek (XMLInputStream_t *stream);


LIBLAX_EXTERN
void
XMLInputStream_skipPastEnd (XMLInputStream_t *stream,
			    const XMLToken_t *element);


LIBLAX_EXTERN
void
XMLInputStream_skipText (XMLInputStream_t *stream);


LIBLAX_EXTERN
int
XMLInputStream_setErrorLog (XMLInputStream_t *stream, XMLErrorLog_t *log);

END_C_DECLS

/** @endcond doxygen-libnuml-internal */

LIBNUML_CPP_NAMESPACE_END

#endif  /* !SWIG */
#endif  /* XMLInputStream_h */
