#!/usr/bin/env python
## 
## @file    createNUML.py
## @brief   cerates a NUML document.
## @author  Joseph O. Dada
## 
## <!--------------------------------------------------------------------------
## This file is part of libNUML.  Please visit http://sed-ml.org for more
## information about NUML, and the latest version of libNUML.
## 
## Copyright (c) 2013, University of Manchester
## All rights reserved.
## ------------------------------------------------------------------------ -.
## 

import sys
import os.path
import libnuml


def main (args):
  """Usage: create_numl output-filename
  """
  if (len(args) != 2):
    print(main.__doc__)
    sys.exit(1);

# create the document
  doc = libnuml.NUMLDocument(1, 1);  

# Header Information encoded in OntologyTerm objects
# 
# No.     Term    			Source Term Id 	Ontology URI
# 1       concentration   	SBO:0000196     http://www.ebi.ac.uk/sbo/
# 2       metabolite      	SBO:0000299     http://www.ebi.ac.uk/sbo/
# 3       Time    			SBO:0000345     http://www.ebi.ac.uk/sbo/
# 

#---------------------------------------------------------------------------
#
# Creates a OntologyTerm object inside OntologyTerms in NUMLDocument object.
#
#---------------------------------------------------------------------------

  oTerm = doc.createOntologyTerm();
  oTerm.setId("term1");
  oTerm.setTerm("Time");
  oTerm.setSourceTermId("SBO:0000345");
  oTerm.setOntologyURI("http://www.ebi.ac.uk/sbo/");

  oTerm = doc.createOntologyTerm();
  oTerm.setId("term2");
  oTerm.setTerm("metabolite");
  oTerm.setSourceTermId("SBO:0000299");
  oTerm.setOntologyURI("http://www.ebi.ac.uk/sbo/");

  oTerm = doc.createOntologyTerm();
  oTerm.setId("term3");
  oTerm.setTerm("concentration");
  oTerm.setSourceTermId("SBO:0000196");
  oTerm.setOntologyURI("http://www.ebi.ac.uk/sbo/");

#---------------------------------------------------------------------------
#
# Creates a ResultComponent object inside ResultComponents in NUMLDocument object.
#
#---------------------------------------------------------------------------

#The time course data
#
#   Time    BL      B       DLL
#   0       0       1.66058 0.0884913
#   20      0.23    1.76058 0.0984913
#

  rComp = doc.createResultComponent();
  rComp.setId("result_comp1");

#---------------------------------------------------------------------------
#
# Creates a CompositeDescription object inside DimesionDescription in the ResultComponent object.
#
#---------------------------------------------------------------------------
#TODO will added later

  # write the document
  libnuml.writeNUML(doc, args[1]);


if __name__ == '__main__':
  main(sys.argv)  