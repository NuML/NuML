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
* Contributors:
* Joseph O. Dada, The University of Manchester - initial API and implementation
* ****************************************************************************
**/

#ifndef NUMLError_h
#define NUMLError_h

#include <numl/common/extern.h>
#include <numl/xml/XMLError.h>
#include <numl/NUMLNamespaces.h>


LIBNUML_CPP_NAMESPACE_BEGIN
BEGIN_C_DECLS

/**
 * Codes for all NUML-level errors and warnings.
 *
 * These are distinguished from the XML layer (LIBLAX) error codes by being
 * numbered > 10000, while the XML layer's codes are < 9999.  Calling
 * programs may wish to check whether a given NUMLError object's error
 * identifier is actually from NUMLErrorCode_t or XMLError::XMLErrorCode_t.
 * This distinction corresponds to whether a given error represents a
 * low-level XML problem or an NUML problem.
 */
typedef enum
{
   UnknownError                          = 10000 /*!< Unknown internal libNUML error */
 , NotUTF8                               = 10101 /*!< Not UTF8 */
 , UnrecognizedElement                   = 10102 /*!< Unrecognized element */
 , NotSchemaConformant                   = 10103 /*!< Not conformant to NUML XML schema */
 , InvalidMathElement                    = 10201 /*!< Invalid MathML */
 , MultipleAssignmentOrRateRules         = 10304 /*!< Multiple rules for the same variable */
 , MultipleEventAssignmentsForId         = 10305 /*!< Multiple event assignments for the same variable */
 , EventAndAssignmentRuleForId           = 10306 /*!< <code>variable</code> value used in both event assignments and assignment rules */
 , DuplicateMetaId                       = 10307 /*!< Duplicate <code>metaid</code> identifier */
 , InvalidSBOTermSyntax                  = 10308 /*!< Invalid <code>sboTerm</code> value syntax */
 , InvalidMetaidSyntax                   = 10309 /*!< Invalid <code>metaid</code> value syntax */
 , InvalidIdSyntax                       = 10310 /*!< Invalid identifier syntax */
 , InvalidUnitIdSyntax                   = 10311 /*!< Invalid unit identifier syntax */
 , MissingAnnotationNamespace            = 10401 /*!< Missing declaration of XML namespace for annotation */
 , DuplicateAnnotationNamespaces         = 10402 /*!< Multiple annotations using same XML namespace */
 , NUMLNamespaceInAnnotation             = 10403 /*!< Invalid use of NUML XML namespace in annotation */
 , MissingOntologyTerms					 = 10502 /*!<Missing OntologyTerms*/
 , MissingResultComponents				 = 10503 /*!<Missing ResultComponents*/
 , InconsistentArgUnits                  = 10501 /*!< Units of arguments to function call do not match function's definition */
 , AssignRuleCompartmentMismatch         = 10511 /*!< Mismatched units in assignment rule for compartment */
 , AssignRuleSpeciesMismatch             = 10512 /*!< Mismatched units in assignment rule for species */
 , AssignRuleParameterMismatch           = 10513 /*!< Mismatched units in assignment rule for parameter */
 , InitAssignCompartmenMismatch          = 10521 /*!< Mismatched units in initial assignment to compartment */
 , InitAssignSpeciesMismatch             = 10522 /*!< Mismatched units in initial assignment to species */
 , InitAssignParameterMismatch           = 10523 /*!< Mismatched units in initial assignment to parameter */
 , RateRuleCompartmentMismatch           = 10531 /*!< Mismatched units in rate rule for compartment */
 , RateRuleSpeciesMismatch               = 10532 /*!< Mismatched units in rate rule for species */
 , RateRuleParameterMismatch             = 10533 /*!< Mismatched units in rate rule for parameter */
 , KineticLawNotSubstancePerTime         = 10541 /*!< Kinetic law units are not <code>substance</code>/<code>time</code> */
 , DelayUnitsNotTime                     = 10551 /*!< Units of delay are not units of time */
 , EventAssignCompartmentMismatch        = 10561 /*!< Mismatched units in event assignment for compartment */
 , EventAssignSpeciesMismatch            = 10562 /*!< Mismatched units in event assignment for species */
 , EventAssignParameterMismatch          = 10563 /*!< Mismatched units in event assignment for parameter */
 , OverdeterminedSystem                  = 10601 /*!< Model is overdetermined */
 , InvalidModelSBOTerm                   = 10701 /*!< Invalid <code>sboTerm</code> value for model */
 , InvalidFunctionDefSBOTerm             = 10702 /*!< Invalid <code>sboTerm</code> value for function definition */
 , InvalidParameterSBOTerm               = 10703 /*!< Invalid <code>sboTerm</code> value for parameter */
 , InvalidInitAssignSBOTerm              = 10704 /*!< Invalid <code>sboTerm</code> value for initial assignment */
 , InvalidRuleSBOTerm                    = 10705 /*!< Invalid <code>sboTerm</code> value for rule */
 , InvalidConstraintSBOTerm              = 10706 /*!< Invalid <code>sboTerm</code> value for constraint */
 , InvalidReactionSBOTerm                = 10707 /*!< Invalid <code>sboTerm</code> value for reaction */
 , InvalidSpeciesReferenceSBOTerm        = 10708 /*!< Invalid <code>sboTerm</code> value for species reference */
 , InvalidKineticLawSBOTerm              = 10709 /*!< Invalid <code>sboTerm</code> value for kinetic law */
 , InvalidEventSBOTerm                   = 10710 /*!< Invalid <code>sboTerm</code> value for event */
 , InvalidEventAssignmentSBOTerm         = 10711 /*!< Invalid <code>sboTerm</code> value for event assignment */
 , InvalidCompartmentSBOTerm             = 10712 /*!< Invalid <code>sboTerm</code> value for compartment */
 , InvalidSpeciesSBOTerm                 = 10713 /*!< Invalid <code>sboTerm</code> value for species */
 , InvalidCompartmentTypeSBOTerm         = 10714 /*!< Invalid <code>sboTerm</code> value for compartment type */
 , InvalidSpeciesTypeSBOTerm             = 10715 /*!< Invalid <code>sboTerm</code> value for species type */
 , InvalidTriggerSBOTerm                 = 10716 /*!< Invalid <code>sboTerm</code> value for event trigger */
 , InvalidDelaySBOTerm                   = 10717 /*!< Invalid <code>sboTerm</code> value for event delay */
 , NotesNotInXHTMLNamespace              = 10801 /*!< Notes not placed in XHTML namespace */
 , NotesContainsXMLDecl                  = 10802 /*!< XML declarations not permitted in notes */
 , NotesContainsDOCTYPE                  = 10803 /*!< XML <code>DOCTYPE</code> not permitted in notes */
 , InvalidNotesContent                   = 10804 /*!< Invalid notes content */
 , InvalidNamespaceOnNUML               = 20101 /*!< Invalid XML namespace for NUML container */
 , MissingOrInconsistentLevel            = 20102 /*!< Missing or inconsistent value for <code>level</code> attribute */
 , MissingOrInconsistentVersion          = 20103 /*!< Missing or inconsistent value for <code>version</code> attribute */
 , AnnotationNotesNotAllowedLevel1       = 20104 /*!< Annotation on <code>&lt;numl&gt;</code> not permitted in NUML Level&nbsp;1 */
 , MissingModel                          = 20201 /*!< Missing model */
 , IncorrectOrderInModel                 = 20202 /*!< Incorrect ordering of components in model definition */
 , EmptyListElement                      = 20203 /*!< A given <code>listOf___</code>, if present, cannot be empty */
 , NeedCompartmentIfHaveSpecies          = 20204 /*!< Missing compartment in species definition */
 , FunctionDefMathNotLambda              = 20301 /*!< Invalid expression in function definition */
 , InvalidApplyCiInLambda                = 20302 /*!< Invalid forward reference in <code>&lt;apply&gt;</code><code>&lt;ci&gt;</code>...<code>&lt;/ci&gt;</code><code>&lt;/apply&gt;</code> value */
 , ConstraintNotInXHTMLNamespace         = 21003 /*!< Constraint message is not in XHTML XML namespace */
 , ConstraintContainsXMLDecl             = 21004 /*!< XML declarations not permitted in constraint messages */
 , ConstraintContainsDOCTYPE             = 21005 /*!< XML <code>DOCTYPE</code> not permitted in constraint messages */
 , InvalidConstraintContent              = 21006 /*!< Invalid content for constraint message */

 , EventAssignmentForConstantEntity      = 21212 /*!< Cannot assign to a constant component in an event assignment */

 , GeneralWarningNotSpecified            = 29999 /*!< Unknown error */

  /* Lower bound for additional error codes returned by libNUML but not
   * defined in NUML specifications. */

 , LibNUMLAdditionalCodesLowerBound      = 90000 /*!< Lower bound of libNUML-specific codes */

 , CannotConvertToL1V1                   = 90001 /*!< Cannot convert to NUML Level&nbsp;1 Version&nbsp;1 */

  /* L1Compatability */

 , NoEventsInL1                          = 91001 /*!< NUML Level&nbsp;1 does not support events */
 , StrictUnitsRequiredInL1               = 91014 /*!< NUML Level&nbsp;1 requires strict unit consistency */

  /* L2v1 compatability */

 , NoConstraintsInL2v1                   = 92001 /*!< NUML Level&nbsp;2 Version&nbsp;1 does not support constraints */
, StrictUnitsRequiredInL2v1             = 92008 /*!< NUML Level&nbsp;2 Version&nbsp;1 requires strict unit consistency */

  /* These are errors checked by libNUML that were never
   * published in a spec. */

 , InvalidNUMLLevelVersion              = 99101 /*!< Invalid NUML Level and Version */
 , InvalidRuleOrdering                   = 99106 /*!< Invalid ordering of rules */
 , NoTimeSymbolInFunctionDef             = 99301 /*!< <code>&lt;csymbol&gt;</code> for <code>time</code> used within the <code>&lt;math&gt;</code> of a function definition */


  /* These are internal errors that reverts to 10501. */

  /** @cond doxygen-libnuml-internal */
 , InconsistentArgUnitsWarnings          = 99502 /*!< NUML L2v3 validation rule #10501 */
 , InconsistentPowerUnitsWarnings        = 99503 /*!< NUML L2v3 validation rule #10501 */
 , InconsistentExponUnitsWarnings        = 99504 /*!< NUML L2v3 validation rule #10501 */
  /** @endcond doxygen-libnuml-internal */

 , UndeclaredUnits                       = 99505 /*!< Undeclared units */
 , UnrecognisedSBOTerm                   = 99701 /*!< Unrecognized <code>sboTerm</code> value */
 , ObseleteSBOTerm                       = 99702 /*!< Obsolete <code>sboTerm</code> value */

  /* Internal consistency checks */

 , IncorrectCompartmentSpatialDimensions = 99901 /*!< in NUML Level&nbsp;1, only three-dimensional compartments are permitted */
 , CompartmentTypeNotValidAttribute      = 99902 /*!< Compartment types not supported in this Level+Version of NUML */
 , OffsetNotValidAttribute               = 99925 /*!< Attribute <code>offset</code> on units only available in NUML Level&nbsp;2 Version&nbsp;1 */

  /* Bounds */

  , NUMLCodesUpperBound                  = 99999 /*!< 99999, the upper bound of
						  * all libNUML codes.
                                                  * Application-specific codes
                                                  * should begin at 100000. */
} NUMLErrorCode_t;


/**
 * Category codes for NUMLError diagnostics.
 *
 * Note that these are distinct from XMLError's category codes.  User
 * programs receiving an NUMLError object can use this distinction to
 * check whether the error represents a low-level XML problem or an
 * NUML problem.
 *
 * @see #XMLErrorCategory_t
 */
typedef enum 
{
    LIBNUML_CAT_NUML = (LIBNUML_CAT_XML + 1)
    /*!< General NUML error  not falling into another category below. */

  , LIBNUML_CAT_NUML_L1_COMPAT
    /*!< Category of errors that can only occur during attempted
     * translation from one Level/Version of NUML to another.  This
     * particular category applies to errors encountered while trying to
     * convert a numl objects from NUML Level&nbsp;2 to NUML Level&nbsp;1. */

  , LIBNUML_CAT_NUML_L1V1_COMPAT
    /*!< Category of errors that can only occur during attempted
     * translation from one Level/Version of NUML to another.  This
     * particular category applies to errors encountered while trying to
     * convert a numl objects to NUML Level&nbsp;1 Version&nbsp;1. */
  , LIBNUML_CAT_GENERAL_CONSISTENCY
    /*!< Category of errors that can occur while validating general NUML
     * constructs.  With respect to the NUML specification, these concern
     * failures in applying the validation rules numbered 2xxxx in the
     * Level&nbsp;2 Versions&nbsp;2 and&nbsp;3 specifications. */

  , LIBNUML_CAT_IDENTIFIER_CONSISTENCY
    /*!< Category of errors that can occur while validating symbol
     * identifiers in a numl objects.  With respect to the NUML specification,
     * these concern failures in applying the validation rules numbered
     * 103xx in the Level&nbsp;2 Versions&nbsp;2 and&nbsp;3 specifications. */
  , LIBNUML_CAT_SBO_CONSISTENCY
    /*!< Category of errors that can occur while validating SBO identifiers
     * in a numl objects.  With respect to the NUML specification, these concern
     * failures in applying the validation rules numbered 107xx in the
     * Level&nbsp;2 Versions&nbsp;2 and&nbsp;3 specifications. */
  , LIBNUML_CAT_INTERNAL_CONSISTENCY
    /*!< Category of errors that can occur while validating libNUML's
     * internal representation of NUML constructs. (These are tests
     * performed by libNUML and do not have equivalent NUML validation
     * rules.)  */

} NUMLErrorCategory_t;


/**
 * Severity codes for NUMLError diagnostics.
 *
 * These are distinct from XMLError's severity codes.  
 *
 * @see XMLErrorSeverity_t
 */
typedef enum
{
  /** @cond doxygen-libnuml-internal **/

  /* The following are used internally in NUMLErrorTable, but publicly,
   * we only report one of the 4 XMLError_Severity values.  Translation
   * of the codes is done in NUMLError.cpp.
   */

    LIBNUML_SEV_SCHEMA_ERROR    = (LIBNUML_SEV_FATAL + 1)
    /*!< The XML content does not conform to
     * the relevant version of the NUML XML
     * Schema.  The content is not valid NUML. */

  , LIBNUML_SEV_GENERAL_WARNING
    /*!< The XML content is invalid for some
     * levels/versions of NUML, and while it
     * may be valid in others, it is something
     * that is best avoided anyway.  LibNUML
     * will issue warnings in those cases it
     * can recognize. */

  , LIBNUML_SEV_NOT_APPLICABLE
    /*!< This error code is only a placeholder
     * for errors that have relevance to some
     * versions of NUML but not others. */

  /** @endcond doxygen-libnuml-internal **/
} NUMLErrorSeverity_t;

END_C_DECLS
LIBNUML_CPP_NAMESPACE_END

#ifdef __cplusplus

LIBNUML_CPP_NAMESPACE_BEGIN

class LIBNUML_EXTERN NUMLError : public XMLError
{
public:

  /**
   * Creates a new NUMLError to report that something occurred during NUML
   * processing.
   *
   * When a libNUML operation on NUML content results in a warning, error
   * or other diagnostic, the issue is reported as an NUMLError object.
   * NUMLError objects have identification numbers to indicate the nature
   * of the exception.  @if clike These numbers are drawn from
   * the enumeration <a class="el"
   * href="#NUMLErrorCode_t">
   * NUMLErrorCode_t</a>.  @endif@if java These numbers are
   * defined as unsigned integer constants in the file
   * "libnumlConstants.html".  See the <a class="el"
   * href="#NUMLErrorCode_t">top of this documentation page</a> for a table
   * listing the possible values and their meanings. @endif The argument 
   * @p errorId to this constructor @em can be (but does not have to be) a
   * value from this @if clike enumeration. If it @em is a value
   * from <a class="el" href="#NUMLErrorCode_t">NUMLErrorCode_t</a>, the
   * NUMLError class assumes the error is a low-level system or NUML layer
   * error and <em>prepends</em> a built-in, predefined error message to
   * any string passed in the argument @p details to this constructor.  In
   * addition, all <a class="el"
   * href="#NUMLErrorCode_t">NUMLErrorCode_t</a> errors have associated
   * values for the @p severity and @p category codes, and these fields are
   * filled-in as well from the enumerations <a class="el"
   * href="#NUMLErrorSeverity_t">NUMLErrorSeverity_t</a> and <a class="el"
   * href="#NUMLErrorCategory_t">NUMLErrorCategory_t</a>,
   * respectively. @endif@if java set of constants.  If it @em
   * is one of the predefined error identifiers, the NUMLError class
   * assumes the error is a low-level system or NUML layer error and
   * <em>prepends</em> a built-in, predefined error message to any string
   * passed in the argument @p details to this constructor.  In addition,
   * all the predefined error identifiers have associated values for the 
   * @p severity and @p category codes, and these fields are filled-in using
   * the libNUML defaults for each different error identifier. @endif
   *
   * If the error identifier @p errorId is a number greater than 99999, the
   * NUMLError class assumes the error was generated from another part of
   * the software and does not do additional filling in of values beyond
   * the default in the constructor itself.  This allows NUMLError to serve
   * as a base class for other errors, such as for user-defined validation
   * rules (see Validator).  Callers should fill in all the parameters with
   * suitable values if generating errors with codes greater than 99999 to
   * make maximum use of the NUMLError facilities.
   *
   * @if clike As mentioned above, there are two other
   * enumerations, <a class="el"
   * href="#NUMLErrorSeverity_t">NUMLErrorSeverity_t</a> and <a class="el"
   * href="#NUMLErrorCategory_t">NUMLErrorCategory_t</a>, used for indicating
   * the severity and category of error for the predefined NUMLError codes.
   * The values passed in @p severity and @p category override the defaults
   * assigned based on the error code.  If the value of @p errorId is a
   * value from <a class="el" href="#NUMLErrorCode_t">NUMLErrorCode_t</a>,
   * callers do not need to fill in @p severity and @p category.
   * Conversely, if @p errorId is not a value from <a class="el"
   * href="#NUMLErrorCode_t">NUMLErrorCode_t</a>, callers can use other
   * values (not just those from <a class="el"
   * href="#NUMLErrorSeverity_t">NUMLErrorSeverity_t</a> and <a class="el"
   * href="#NUMLErrorCategory_t">NUMLErrorCategory_t</a>, but their own
   * special values) for @p severity and 
   * @p category. @endif@if java As mentioned above, 
   * there are additional constants defined for <a class="el"
   * href="#NUMLErrorSeverity_t">standard severity</a> and <a class="el"
   * href="#NUMLErrorCategory_t">standard category</a> codes, and every predefined
   * error in libNUML has an associated value for severity and category taken
   * from these predefined sets.  These constants have symbol names
   * prefixed with <code>LIBNUML_SEV_</code> and <code>LIBNUML_CAT_</code>,
   * respectively.  If the value of @p errorId is one of the standard error
   * codes, callers do not need to fill in @p severity and @p category in a
   * call to this constructor.  Conversely, if @p errorId is not an existing
   * NUML-level error code, callers can use other values for @p severity and
   * @p category. @endif
   *
   * Please see the top of the documentation for NUMLError for a longer
   * discussion of the possible error codes, their meanings, and their
   * applicability to different combinations of Level+Version of NUML.
   *
   * @param errorId an unsigned int, the identification number of the error.
   *
   * @param level the NUML Level of the NUML model
   *
   * @param version the NUML Version within the Level of the NUML model
   * 
   * @param details a string containing additional details about the error.
   * If the error code in @p errorId is one that is recognized by NUMLError,
   * the given message is @em appended to a predefined message associated
   * with the given code.  If the error code is not recognized, the message
   * is stored as-is as the text of the error.
   * 
   * @param line an unsigned int, the line number at which the error occured.
   * 
   * @param column an unsigned int, the column number at which the error occured.
   * 
   * @param severity an integer indicating severity of the error.
   * 
   * @param category an integer indicating the category to which the error
   * belongs.
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
  NUMLError
  (
     const unsigned int errorId  = 0
   , const unsigned int level    = NUML_DEFAULT_LEVEL
   , const unsigned int version  = NUML_DEFAULT_VERSION
   , const std::string& details  = ""
   , const unsigned int line     = 0
   , const unsigned int column   = 0
   , const unsigned int severity = LIBNUML_SEV_ERROR
   , const unsigned int category = LIBNUML_CAT_NUML
  );


  /**
   * Copy constructor; creates a copy of this NUMLError.
   */
  NUMLError(const NUMLError& orig);


#ifndef SWIG

  /** @cond doxygen-libnuml-internal **/

  /**
   * clone function
   */
  virtual NUMLError* clone() const;

  /**
   * Outputs this NUMLError to stream in the following format (and followed
   * by a newline):
   *
   *   line: (error id) message
   *
   * @param stream the output stream to write to.
   */
  virtual void print(std::ostream& stream) const;

  /** @endcond doxygen-libnuml-internal **/

#endif  /* !SWIG */

protected:
  /** @cond doxygen-libnuml-internal **/

  virtual std::string stringForSeverity(unsigned int code) const;
  virtual std::string stringForCategory(unsigned int code) const;

  /** @endcond doxygen-libnuml-internal **/
};

LIBNUML_CPP_NAMESPACE_END

#endif  /* __cplusplus */
#endif /* NUMLError_h */
