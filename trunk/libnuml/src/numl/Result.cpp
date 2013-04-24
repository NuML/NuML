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

#include <limits>

#include <numl/xml/XMLNode.h>
#include <numl/xml/XMLAttributes.h>
#include <numl/xml/XMLInputStream.h>
#include <numl/xml/XMLOutputStream.h>


#include <numl/NUMLDocument.h>

#include <numl/NUMLVisitor.h>

#include <numl/Result.h>


using namespace std;

LIBNUML_CPP_NAMESPACE_BEGIN

Result::Result (unsigned int level, unsigned int version) :
   NUMLList ( level, version )
{
  if (!hasValidLevelVersionNamespaceCombination())
    throw NUMLConstructorException();
}


Result::Result (NUMLNamespaces *numlns) :
    NUMLList                   ( numlns )
{
  if (!hasValidLevelVersionNamespaceCombination())
    throw NUMLConstructorException();
}

/** @cond doxygen-libnuml-internal */

/* constructor for validators */
Result::Result() :
  NUMLList()
{
}

/** @endcond doxygen-libnuml-internal */

/** @endcond doxygen-libnuml-internal */

/*
 * Destroys this Operation.
 */
Result::~Result ()
{
}

/*
 * @return a (deep) copy of this Result.
 */
Result*
Result::clone () const
{
	return new Result(*this);
}


/*
 * @return the NUMLTypeCode_t of NUML objects contained in this Result or
 * NUML_UNKNOWN (default)./*
 * @return the annotation of this NUML object by string.
 */
/* TODO std::string
NMBase::getAnnotationString ()
{
  return XMLNode::convertXMLNodeToString(getAnnotation());
}*/

NUMLTypeCode_t
Result::getItemTypeCode () const
{
	return NUML_RESULT;
}


/*
 * @return the name of this element ie "Result".
 */
const string&
Result::getElementName () const
{
	static const string name = "result";
	return name;
}


/* return nth item in list */
ResultComponent *
Result::get(unsigned int n)
{
	return static_cast<ResultComponent*>(NUMLList::get(n));
}


/* return nth item in list */
const ResultComponent *
Result::get(unsigned int n) const
{
	return static_cast<const ResultComponent*>(NUMLList::get(n));
}


/**
* Used by Result::get() to lookup an NMBase based by its id.
*/
struct IdEqS : public unary_function<NMBase*, bool>
{
	const string& id;

	IdEqS (const string& id) : id(id) { }
	bool operator() (NMBase* sb)
    		   { return static_cast <ResultComponent *> (sb)->getId() == id; }
};


/* return all the items */
/*Result*
Result::getResult()
{
  //return &mResult;
   return static_cast<Result*>(this);
//	return this;
}*/

/* return item by id */
ResultComponent*
Result::get (const std::string& sid)
{
	return const_cast<ResultComponent*>(
			static_cast<const Result&>(*this).get(sid) );
}


/* return item by id */
const ResultComponent*
Result::get (const std::string& sid) const
{
	vector<NMBase*>::const_iterator result;

	result = find_if( mItems.begin(), mItems.end(), IdEqS(sid) );
	return (result == mItems.end()) ? 0 : static_cast <ResultComponent*> (*result);
}


/* Removes the nth item from this list */
ResultComponent*
Result::remove (unsigned int n)
{
	return static_cast<ResultComponent*>(NUMLList::remove(n));
}


/* Removes item in this list by id */
ResultComponent*
Result::remove (const std::string& sid)
{
	NMBase* item = 0;
	vector<NMBase*>::iterator result;

	result = find_if( mItems.begin(), mItems.end(), IdEqS(sid) );

	if (result != mItems.end())
	{
		item = *result;
		mItems.erase(result);
	}

	return static_cast <ResultComponent*> (item);
}


/** @cond doxygen-libnuml-internal */
/*
 * @return the ordinal position of the element with respect to its siblings
 * or -1 (default) to indicate the position is not significant.
 */
int
Result::getElementPosition () const
{
	return 0;
}
/** @endcond doxygen-libnuml-internal */


/** @cond doxygen-libnuml-internal */
/*
 * @return the NUML object corresponding to next XMLToken in the
 * XMLInputStream or NULL if the token was not recognized.
 */
NMBase*
Result::createObject (XMLInputStream& stream)
{
	const string& name   = stream.peek().getName();
	NMBase*        object = 0;


	if (name == "resultComponent")
	{
		try
		{
			object = new ResultComponent(getNUMLNamespaces());
		}
		catch (NUMLConstructorException*)
		{
			object = new ResultComponent(NUMLDocument::getDefaultLevel(), NUMLDocument::getDefaultVersion());
		}
		catch ( ... )
		{
			object = new ResultComponent(NUMLDocument::getDefaultLevel(), NUMLDocument::getDefaultVersion());
		}

		if (object) mItems.push_back(object);
	}

	return object;
}
/** @endcond doxygen-libnuml-internal */

LIBNUML_CPP_NAMESPACE_END
