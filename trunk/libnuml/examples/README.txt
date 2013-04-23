
                            l i b N U M L

		     Example programs and numerical data

	    			Joseph O. Dada
        More information about libNUML is available online at
                 http://code.google.com/p/numl/

			    The NUML Team
			 http://code.google.com/p/numl/
		     mailto:josephodada@gmail.com

There are separate subdirectories for different programming languages:
"c" for example programs in the C language, "c++" for examples in C++,
"java" for examples in Java, etc.  You will first need to change your
working directory to one of these subdirectories.

The Makefile in each subdirectory is kept simple for illustrative
purposes.  For this reason, you may need to modify some of the values
assigned to variables in the Makefiles in order that they correspond
to your particular environment.

Once this is done, at the Unix command prompt, you should be able to
type the following command to compile the example programs in a given
language subdirectory:

  % make

Next, you may wish to try running the example programs on some NUML
files.  There are a number of sample NuML/numerical dada provided for this purpose
in the "example-data" subdirectory here.  So for example, you could
do try the following (if you were in the "c++" subdirectory):

  % printNUML     ../example-data/TwoDimensionNuMLData.xml
  % readNUML      ../example-data/TwoDimensionNuMLData.xml
  % createExampleNUMLDoc 
  % echoNUML  ../example-data/TwoDimensionNuMLData.xml twoDimensionData.xml
  %

More example data may be obtained from a number of other sources, including
the COPASI Web services (CopasiWS: http://www.comp-sys-bio.org/CopasiWS/).

The original code was initially developed by:

	SBML Team
	Control and Dynamical Systems, MC 107-81
	California Institute of Technology
	Pasadena, CA, 91125, USA

 	http://www.sbml.org
	mailto:sbml-team@caltech.edu

Adapted for NUML by:

	NUML Team
	Computational Systems Biology Group
	School of Computer Science
	The University of Manchester
	Manchester, M1 7DN UK
	mailto:josephodada@gmail.com

  Contributor(s):
  Joseph O. Dada, The University of Manchester - initial LIBNUML API and implementation
  
  $Rev::		$:	Revision of last commit
  $Author::	$:	Author of last commit
  $Date::		$:	Date of last commit
  $HeadURL::	$
  $Id::		$

# The following is for [X]Emacs users.  Please leave in place.
# Local Variables:
# fill-column: 70
# End:
