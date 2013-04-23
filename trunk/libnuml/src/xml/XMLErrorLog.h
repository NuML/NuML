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
 *
 * @class XMLErrorLog
 * @brief Log of errors and other events encountered while processing an XML
 * file or data stream.
 *
 * @htmlinclude libnuml-not-numl-warning.html
 *
 * The error log is simply a list.  The XML layer of libNUML maintains an
 * error log associated with a given XML document or data stream.  When an
 * operation results in an error, or when there is something wrong with the
 * XML content, the problem is reported as an XMLError object stored in the
 * XMLErrorLog list.  Problems range from low-level issues (such as the
 * inability to open a file) to XML syntax errors (such as mismatched tags
 * or other problems).
 *
 * A typical approach for using this error log is to first use
 * XMLErrorLog::getNumErrors() to inquire how many XMLError object instances
 * it contains, and then to iterate over the list of objects one at a time
 * using XMLErrorLog::getError(unsigned int n).
 *
 * In normal circumstances, programs using libNUML will actually obtain an
 * NUMLErrorLog rather than an actual XMLErrorLog.  The former is
 * subclassed from XMLErrorLog and simply wraps commands for working with
 * NUMLError objects rather than the low-level XMLError objects.  Classes
 * such as NUMLDocument use the higher-level NUMLErrorLog.
 */

#ifndef XMLErrorLog_h
#define XMLErrorLog_h

#include <numl/xml/XMLExtern.h>
#include <numl/xml/XMLError.h>
#include <numl/common/numlfwd.h>


#ifdef __cplusplus

#include <string>
#include <vector>
#include <list>

LIBNUML_CPP_NAMESPACE_BEGIN

class XMLParser;


class LIBLAX_EXTERN XMLErrorLog
{
public:

  /**
   * Returns the number of errors that have been logged.
   *
   * To retrieve individual errors from the log, callers may use
   * XMLErrorLog::getError(unsigned int n).
   *
   * @return the number of errors that have been logged.
   */
  unsigned int getNumErrors () const;


  /**
   * Returns the nth XMLError in this log.
   *
   * Callers should first use XMLErrorLog::getNumErrors() to find out how
   * many errors are in the log.
   *
   * @param n the index number of the error to retrieve (with 0 being the
   * first error)
   *
   * @return the nth XMLError in this log, or NULL if @p n is greater than
   * or equal to XMLErrorLog::getNumErrors().
   */
  const XMLError* getError (unsigned int n) const;


  /**
   * Removes all errors from this log.
   */
  void clearLog();


  /** @cond doxygen-libnuml-internal */

  /**
   * Creates a new empty XMLErrorLog.
   */
  XMLErrorLog ();


  /**
   * Destroys this XMLErrorLog.
   */
  virtual ~XMLErrorLog ();


  /**
   * Logs the given XMLError.
   *
   * @param error XMLError, the error to be logged.
   */
  void add (const XMLError& error);


  /**
   * Logs (copies) the XMLErrors in the given XMLError list to this
   * XMLErrorLog.
   *
   * @param errors list, a list of XMLError to be added to the log.
   */
  void add (const std::list<XMLError>& errors);


  /**
   * Sets the XMLParser associated with this XMLErrorLog.
   *
   * The XMLParser will be used to obtain the current line and column
   * number for XMLError objects that lack line and column numbers when
   * they are logged.  This method is used by libNUML's internal XML
   * parsing code and probably has no useful reason to be called from
   * application programs.
   *
   * @param p XMLParser, the parser to use
   *
   * @return integer value indicating success/failure of the
   * function.  @if clike The value is drawn from the
   * enumeration #OperationReturnValues_t. @endif The possible values
   * returned by this function are:
   * @li LIBNUML_OPERATION_SUCCESS
   * @li LIBNUML_OPERATION_FAILED
   */
  int setParser (const XMLParser* p);

  /** @endcond doxygen-libnuml-internal */


protected:
  /** @cond doxygen-libnuml-internal */

  std::vector<XMLError*> mErrors;
  const XMLParser*       mParser;

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


LIBLAX_EXTERN
XMLErrorLog_t *
XMLErrorLog_create (void);


LIBLAX_EXTERN
void
XMLErrorLog_free (XMLErrorLog_t *log);


LIBLAX_EXTERN
void
XMLErrorLog_add (XMLErrorLog_t *log, const XMLError_t *error);


LIBLAX_EXTERN
const XMLError_t *
XMLErrorLog_getError (const XMLErrorLog_t *log, unsigned int n);


LIBLAX_EXTERN
unsigned int
XMLErrorLog_getNumErrors (const XMLErrorLog_t *log);


LIBLAX_EXTERN
void
XMLErrorLog_clearLog (XMLErrorLog_t *log);


END_C_DECLS
LIBNUML_CPP_NAMESPACE_END

#endif  /* !SWIG */
#endif  /* XMLErrorLog_h */
