/*
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
*/

#ifndef RESULT_H_
#define RESULT_H_

#include <numl/common/extern.h>
#include <numl/common/numlfwd.h>
#include <numl/ResultComponent.h>

#ifdef __cplusplus

#include <numl/NMBase.h>
#include <string>

#include <numl/NUMLList.h>

LIBNUML_CPP_NAMESPACE_BEGIN

class ResultComponent;
class NUMLVisitor;
class XMLError;

/*
 *
 */

class LIBNUML_EXTERN Result : public NUMLList
{
public:

	Result();

	/**
	 * Creates an new Result using the given NUML @p level and @p version
	 * values.
	 *
	 * @param level an unsigned int, the NUML Level to assign to this Result
	 *
	 * @param version an unsigned int, the NUML Version to assign to this
	 *Result
	 *
	 * @note Once an Result has been added to an NUMLDocument, the @p level,
	 * @p version for the document @em override those used
	 * to create the Result.  Despite this, the ability to supply the values
	 * at creation time is an important aid to creating valid NUML.  Knowledge of
	 * the intented NUML Level and Version determine whether it is valid to
	 * assign a particular value to an attribute, or whether it is valid to add
	 * an object to an existing NUMLDocument.
	 */
	Result (unsigned int level, unsigned int version);

	/**
	 * Creates a new Result using the given NUMLNamespaces object
	 * @p numlns.
	 *
	 * The NUMLNamespaces object encapsulates NUML Level/Version/namespaces
	 * information.  It is used to communicate the NUML Level, Version, and
	 * (in Level&nbsp;3) packages used in addition to NUML Level&nbsp; Core.
	 * A common approach to using this class constructor is to create an
	 * NUMLNamespaces object somewhere in a program, once, then pass it to
	 * object constructors such as this one when needed.
	 *
	 * It is worth emphasizing that although this constructor does not take
	 * an identifier argument, in NUML Level&nbsp;2 and beyond, the "id"
	 * (identifier) attribute of an Result is required to have a value.
	 * Thus, callers are cautioned to assign a value after calling this
	 * constructor.  Setting the identifier can be accomplished using the
	 * method @if clike SBase::setId() @endif@if java SBase::setId(String id) @endif.
	 *
	 * @param numlns an NUMLNamespaces object.
	 *
	 * @note Once an Result has been added to an NUMLDocument, the @p level,
	 * @p version and @p xmlns namespaces for the document @em override those used
	 * to create the Result.  Despite this, the ability to supply the values
	 * at creation time is an important aid to creating valid NUML.  Knowledge of
	 * the intented NUML Level and Version determine whether it is valid to
	 * assign a particular value to an attribute, or whether it is valid to add
	 * an object to an existing NUMLDocument.
	 */
	Result (NUMLNamespaces* numlns);

	/**
	* Creates and returns a deep copy of this Result instance.
	*
	* @return a (deep) copy of this Result.
	*/
	virtual Result* clone () const;


	/**
	* Returns the libNUML type code for this %NUML object.
	*
	* @if clike LibNUML attaches an identifying code to every
	* kind of NUML object.  These are known as <em>NUML type codes</em>.
	* The set of possible type codes is defined in the enumeration
	* #NUMLTypeCode_t.  The names of the type codes all begin with the
	* characters @c NUML_. @endif@if java LibNUML attaches an
	* identifying code to every kind of NUML object.  These are known as
	* <em>NUML type codes</em>.  In other languages, the set of type codes
	* is stored in an enumeration; in the Java language interface for
	* libNUML, the type codes are defined as static integer constants in
	* interface class {@link libnumlConstants}.  The names of the type codes
	* all begin with the characters @c NUML_. @endif
	*
	* @return the NUML type code for this object, or @c NUML_UNKNOWN (default).
	*
	* @see getElementName()
	*/
	virtual NUMLTypeCode_t getTypeCode () const { return NUML_NUMLLIST; };


	/**
	* Returns the libNUML type code for the objects contained in this NUMLList
	* (i.e., ResultComponent objects, if the list is non-empty).
	*
	* @if clike LibNUML attaches an identifying code to every
	* kind of NUML object.  These are known as <em>NUML type codes</em>.
	* The set of possible type codes is defined in the enumeration
	* #NUMLTypeCode_t.  The names of the type codes all begin with the
	* characters @c NUML_. @endif@if java LibNUML attaches an
	* identifying code to every kind of NUML object.  These are known as
	* <em>NUML type codes</em>.  In other languages, the set of type codes
	* is stored in an enumeration; in the Java language interface for
	* libNUML, the type codes are defined as static integer constants in
	* interface class {@link libnumlConstants}.  The names of the type codes
	* all begin with the characters @c NUML_. @endif
	*
	* @return the NUML type code for the objects contained in this NUMLList
	* instance, or @c NUML_UNKNOWN (default).
	*
	* @see getElementName()
	*/
	virtual NUMLTypeCode_t getItemTypeCode () const;

	/**
	* Returns the XML element name of this object.
	*
	* For Result, the XML element name is @c "Result".
	*
	* @return the name of this element, i.e., @c "Result".
	*/
	virtual const std::string& getElementName () const;


	/**
	* Get a ResultComponent from the Result.
	*
	* @param n the index number of the ResultComponent to get.
	*
	* @return the nth ResultComponent in this Result.
	*
	* @see size()
	*/
	virtual ResultComponent * get(unsigned int n);


	/**
	* Get a ResultComponent from the Result.
	*
	* @param n the index number of the ResultComponent to get.
	*
	* @return the nth ResultComponent in this Result.
	*
	* @see size()
	*/
	virtual const ResultComponent * get(unsigned int n) const;

	/**
	* Get all the Result.
	*
	*
	* @return this Result.
	*
	* @see size()
	*/
	//virtual Result * getResultComponents();


	/**
	* Get a ResultComponent from the Result
	* based on its identifier.
	*
	* @param sid a string representing the identifier
	* of the ResultComponent to get.
	*
	* @return ResultComponent in this Result
	* with the given id or NULL if no such
	* ResultComponent exists.
	*
	* @see get(unsigned int n)
	* @see size()
	*/
	virtual ResultComponent* get (const std::string& sid);


	/**
	* Get a ResultComponent from the Result
	* based on its identifier.
	*
	* @param sid a string representing the identifier
	* of the ResultComponent to get.
	*
	* @return ResultComponent in this Result
	* with the given id or NULL if no such
	* ResultComponent exists.
	*
	* @see get(unsigned int n)
	* @see size()
	*/
	virtual const ResultComponent* get (const std::string& sid) const;


	/**
	* Removes the nth item from this Result items and returns a pointer to
	* it.
	*
	* The caller owns the returned item and is responsible for deleting it.
	*
	* @param n the index of the item to remove
	*
	* @see size()
	*/
	virtual ResultComponent* remove (unsigned int n);


	/**
	* Removes item in this Result items with the given identifier.
	*
	* The caller owns the returned item and is responsible for deleting it.
	* If none of the items in this list have the identifier @p sid, then @c
	* NULL is returned.
	*
	* @param sid the identifier of the item to remove
	*
	* @return the item removed.  As mentioned above, the caller owns the
	* returned item.
	*/
	virtual ResultComponent* remove (const std::string& sid);


	/** @cond doxygen-libnuml-internal */

	/**
	* Get the ordinal position of this element in the containing object
	* (which in this case is the Model object).
	*
	* The ordering of elements in the XML form of %NUML is generally fixed
	* for most components in %NUML.  So, for example, the Result in
	* a model is (in %NUML Level&nbsp;2 Version&nbsp;4) the sixth
	* NUMLList.  (However, it differs for different Levels and Versions of
	* NUML.)
	*
	* @return the ordinal position of the element with respect to its
	* siblings, or @c -1 (default) to indicate the position is not significant.
	*/
	virtual int getElementPosition () const;

	/** @endcond doxygen-libnuml-internal */

	/**
	 * Subclasses should override this method to write out their contained
	 * NUML objects as XML elements.  Be sure to call your parents
	 * implementation of this method as well.
	 */
//	virtual void writeElements(XMLOutputStream& stream) const;

	virtual ~Result();

protected:
	/** @cond doxygen-libnuml-internal */

	/**
	* @return the NUML object corresponding to next XMLToken in the
	* XMLInputStream or NULL if the token was not recognized.
	*/
	virtual NMBase* createObject (XMLInputStream& stream);

	/** @endcond doxygen-libnuml-internal */
};


LIBNUML_CPP_NAMESPACE_END

#endif  /* __cplusplus */

#ifndef SWIG

LIBNUML_CPP_NAMESPACE_BEGIN
BEGIN_C_DECLS

//TODO

END_C_DECLS
LIBNUML_CPP_NAMESPACE_END

#endif  /* !SWIG   */

#endif /* RESULT_H_ */