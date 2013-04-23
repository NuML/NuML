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

#include <numl/common/libnuml-version.h>
#include <numl/common/operationReturnValues.h>

#include <numl/common/numlfwd.h>

#include <numl/NMBase.h>
#include <numl/NUMLList.h>

#include <numl/NUMLDocument.h>
#include <numl/xml/XMLError.h>

#include <numl/OntologyTerm.h>

#include <numl/Result.h>

#include <numl/ResultComponent.h>
#include <numl/Dimension.h>

#include <numl/DimensionDescription.h>

#include <numl/CompositeValue.h>
#include <numl/Tuple.h>
#include <numl/AtomicValue.h>

#include <numl/CompositeDescription.h>
#include <numl/TupleDescription.h>
#include <numl/AtomicDescription.h>

#include <numl/NUMLReader.h>
#include <numl/NUMLWriter.h>

#include <numl/xml/XMLAttributes.h>
#include <numl/xml/XMLNamespaces.h>
#include <numl/xml/XMLToken.h>
#include <numl/xml/XMLNode.h>
#include <numl/xml/XMLTriple.h>
#include <numl/xml/XMLInputStream.h>
#include <numl/xml/XMLOutputStream.h>
#include <numl/xml/XMLError.h>
#include <numl/xml/XMLErrorLog.h>
#include <numl/xml/XMLParser.h>
#include <numl/xml/XMLHandler.h>
#include <numl/xml/XMLTokenizer.h>

//#include <numl/annotation/CVTerm.h>
//#include <numl/annotation/ModelHistory.h>
//#include <numl/annotation/RDFAnnotation.h>

#include "ListWrapper.h"

