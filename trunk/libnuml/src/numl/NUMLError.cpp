/**
* Begin svn Header
* $Rev::			$:	Revision of last commit
* $Author::			$:	Author of last commit
* $Date::			$:	Date of last commit
* $HeadURL::		$
* $Id::				$
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
* Contributors:
* Joseph O. Dada, The University of Manchester - initial API and implementation
* ****************************************************************************
**/

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

#include <numl/xml/XMLError.h>
#include <numl/NUMLError.h>
#include <numl/NUMLErrorTable.h>


/** @cond doxygen-ignored */

using namespace std;

/** @endcond doxygen-ignored */

LIBNUML_CPP_NAMESPACE_BEGIN

/** @cond doxygen-libnuml-internal **/
/**
 * Helper function for NUMLError().  Takes an index, NUML level and version,
 * and returns the appropriate field for the severity code out of the
   errorTable entry.
 */
static const unsigned int
getSeverityForEntry(unsigned int index,
                    unsigned int level,
                    unsigned int version)
{
  if ( level == 1 )
  {
    switch (version)
    {
    case 1:
      return errorTable[index].l1v1_severity;

    default:
      return errorTable[index].l1v1_severity;
    }
  }
}


/*
 * @return the severity as a string for the given @n code.
 */
std::string NUMLError::stringForSeverity(unsigned int code) const
{
  /* it should never happen that an error ends up with a severity
   * that is not in the XMLSeverity_t enumeration
   * but just in case:
   */
  if (code < LIBNUML_SEV_SCHEMA_ERROR)
  {
    return XMLError::stringForSeverity(code);
  }
  else
  {
    switch (code)
    {
      case LIBNUML_SEV_SCHEMA_ERROR:
        return "Schema error";
        break;
      case LIBNUML_SEV_GENERAL_WARNING:
        return "General warning";
        break;
      case LIBNUML_SEV_NOT_APPLICABLE:
        return "Not applicable";
        break;
      default:
        return "";
        break;
    }
  }
}

/*
 * Table of strings corresponding to the values from NUMLErrorCategory_t.
 * The enumeration starts at a number higher than 0, so each entry is keyed
 * by its enum value.
 *
 * A similar table for severity strings is currently unnecessary because
 * libNUML never returns anything more than the XMLSeverityCode_t values.
 */
static struct numlCategoryString {
  unsigned int catCode;
  const char * catString;
} numlCategoryStringTable[] = {
  { LIBNUML_CAT_NUML,                   "General NUML conformance"    },
  { LIBNUML_CAT_NUML_L1_COMPAT,         "Translation to NUML L1V1"    },
  { LIBNUML_CAT_NUML_L1V1_COMPAT,		"Translation to NUML L1V1"    },
  { LIBNUML_CAT_GENERAL_CONSISTENCY,	"NUML component consistency"  },
  { LIBNUML_CAT_IDENTIFIER_CONSISTENCY,	"NUML identifier consistency" },
  { LIBNUML_CAT_SBO_CONSISTENCY,        "SBO term consistency"        },
  { LIBNUML_CAT_INTERNAL_CONSISTENCY,   "Internal consistency"        }
};

static unsigned int numlCategoryStringTableSize
  = sizeof(numlCategoryStringTable)/sizeof(numlCategoryStringTable[0]);

/*
 * @return the category as a string for the given @n code.
 */
std::string NUMLError::stringForCategory(unsigned int code) const
{
  if ( code >= LIBNUML_CAT_NUML )
  {
    for ( unsigned int i = 0; i < numlCategoryStringTableSize; i++ )
      if ( numlCategoryStringTable[i].catCode == code )
        return numlCategoryStringTable[i].catString;
  }

  return XMLError::stringForCategory(code);
}

/** @endcond doxygen-libnuml-internal **/


NUMLError::NUMLError (  const unsigned int errorId
                      , const unsigned int level
                      , const unsigned int version 
                      , const std::string& details
                      , const unsigned int line
                      , const unsigned int column
                      , const unsigned int severity
                      , const unsigned int category ) :
    XMLError(errorId, details, line, column, severity, category)
{
  // Check if the given id is one we have in our table of error codes.  If
  // it is, fill in the fields of the error object with the appropriate
  // content.  If it's not in the table, take the content as-is.

  if ( mErrorId >= 0 && mErrorId < XMLErrorCodesUpperBound )
  {
    // The error was caught during the XML read and the XMLError
    // constructor will have filled in all the right pieces.
    return;
  }
  else if ( mErrorId > XMLErrorCodesUpperBound
            && mErrorId < NUMLCodesUpperBound )
  {
    unsigned int tableSize = sizeof(errorTable)/sizeof(errorTable[0]);
    unsigned int index = 0;

    for ( unsigned int i = 0; i < tableSize; i++ )
    {
      if ( mErrorId == errorTable[i].code )
      {
        index = i;
        break;
      }
    }

    if ( index == 0 && mErrorId != UnknownError
         && ! (mErrorId > LibNUMLAdditionalCodesLowerBound
               && mErrorId < NUMLCodesUpperBound) )
    {
      // The id is in the range of error numbers that are supposed to be in
      // the NUML layer, but it's NOT in our table. This is an internal error.
      // Unfortunately, we don't have an error log or anywhere to report it
      // except the measure of last resort: the standard error output.
    
      cerr << "Internal error: unknown error code '" << mErrorId
           << "' encountered while processing error." << endl;
      return;
    }

    // The rest of this block massages the results to account for how some
    // internal bookkeeping is done in libNUML 3, and also to provide
    // additional info in the messages.

    mCategory     = errorTable[index].category;
    mShortMessage = errorTable[index].shortMessage;

    ostringstream newMsg;
    mSeverity = getSeverityForEntry(index, level, version);

    if (mSeverity == LIBNUML_SEV_SCHEMA_ERROR)
    {
      // Prior to L2v3, many possible errors were not listed separately as
      // validation rules because they were assumed to be caught by a
      // schema-aware XML parser.  In L2v3, we stopped relying on this and
      // listed schema errors separately.  This poses a problem for how
      // libNUML should errors for documents having levels/versions < L2v3.
      // LibNUML handles this internally by using the special severity code
      // SchemaError in NUMLErrorTable.h for those NUML level/version
      // combinations that didn't have separate validation rules, then
      // here, we translate the errors into the same basic error code and
      // add some elaboration to the error text message.

      mErrorId  = NotSchemaConformant;
      mSeverity = LIBNUML_SEV_ERROR;
      newMsg << errorTable[3].message << " "; // FIXME
    }
    else if (mSeverity == LIBNUML_SEV_GENERAL_WARNING)
    {
      // General warnings are our internal code for non-XML-schema issues
      // that were not defined as errors in prior levels/versions, but then
      // were defined as errors at some later time.  Like with SchemaError,
      // we use the GeneralWarning code for those cases in NUMLErrorTable.h
      // and then here we translate them into regular warnings.

      mSeverity = LIBNUML_SEV_WARNING;
      newMsg << "[Although NUML Level " << level
             << " Version " << version << " does not explicitly define the "
             << "following as an error, other Levels and/or Versions "
             << "of NUML do.] " << endl;
    }

    // Finish updating the (full) error message.

    newMsg << errorTable[index].message;
    if (!details.empty())
    {
      newMsg << " " << details;
    }      
    newMsg << endl;
    mMessage  = newMsg.str();

    // We mucked around with the severity code and (maybe) category code
    // after creating the XMLError object, so we may have to update the
    // corresponding strings.

    mSeverityString = stringForSeverity(mSeverity);
    mCategoryString = stringForCategory(mCategory);

    return;
  }

  // It's not an error code in the NUML layer, so assume the caller has
  // filled in all the relevant additional data.  (If they didn't, the
  // following merely assigns the defaults.)

  mMessage        = details;
  mSeverity       = severity;
  mCategory       = category;
  mSeverityString = stringForSeverity(mSeverity);
  mCategoryString = stringForCategory(mCategory);
}


/*
 * Copy Constructor
 */
NUMLError::NUMLError(const NUMLError& orig) :
 XMLError(orig)
{}


/** @cond doxygen-libnuml-internal **/
/*
 * clone function
 */
NUMLError*
NUMLError::clone() const
{
  return new NUMLError(*this);
}
/** @endcond doxygen-libnuml-internal **/


/** @cond doxygen-libnuml-internal **/
/*
 * Outputs this NUMLError to stream in the following format (and followed by
 * a newline):
 *
 *   line: (error_id [severity]) message
 */
void
NUMLError::print(ostream& s) const
{
  s << "line " << getLine() << ": ("
    << setfill('0') << setw(5) << getErrorId()
    << " [" << getSeverityAsString() << "]) "
    << getMessage() << endl;
}

/** @endcond doxygen-libnuml-internal **/
LIBNUML_CPP_NAMESPACE_END
