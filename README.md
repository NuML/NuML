## NuML - Numerical Markup Language

### Project Information
The Numerical Markup Language (NuML) aims to standardize the exchange and archiving of numerical results. NuML originates from the numerical aspects of the [Systems Biology Results Markup Language (SBRML)][1] with the aim of re-using it in multiple other standardization efforts.

This project hosts the [schema][2], the [specification of NuML][4], as well as the [library for reading and writing NuML (libNUML)][3].

### Get involved:

Join our mailing list at: [http://groups.google.com/group/numl-discuss/](http://groups.google.com/group/numl-discuss/)

### NuML is being / planned to be used by:

* [SBRML](1)
* [SED-ML](http://sed-ml.org)

### Software supporting NuML:

* [SBRML.NET](http://sbrml.sourceforge.net/SBRML/Welcome.html)

 
### Example of a NuML Document
	<?xml version="1.0" encoding="UTF-8"?>
	<numl version="1" level="1" xmlns="http://www.numl.org/numl/level1/version1">   
	  <ontologyTerms>
	      <ontologyTerm id="term1" term="time" sourceTermId="SBO:0000345" ontologyURI="http://www.ebi.ac.uk/sbo/" />         
	      <ontologyTerm id="term2" term="concentration" sourceTermId="SBO:0000196" ontologyURI="http://www.ebi.ac.uk/sbo/" />
	  </ontologyTerms>
	  <resultComponent id="component1">
	      <dimensionDescription>
	        <compositeDescription name="Time" ontologyTerm="term1" indexType="double">
	            <compositeDescription name="Species" indexType="xpath">
	              <atomicDescription name="Concentration" ontologyTerm="term2" valueType="double" />
	            </compositeDescription>
	        </compositeDescription>
	      </dimensionDescription>
	      <dimension>
	        <compositeValue indexValue="0">
	            <compositeValue indexValue="/sbml:sbml/sbml:model/sbml:listOfSpecies/sbml:species[@id='x_CO2']">
	              <atomicValue>1</atomicValue>
	            </compositeValue>
	            <compositeValue indexValue="/sbml:sbml/sbml:model/sbml:listOfSpecies/sbml:species[@id='RuBP_ch']">
	              <atomicValue>0.33644</atomicValue>
	            </compositeValue>
	            <compositeValue indexValue="/sbml:sbml/sbml:model/sbml:listOfSpecies/sbml:species[@id='PGA_ch']">
	              <atomicValue>3.35479</atomicValue>
	            </compositeValue>
	        </compositeValue>
	        <compositeValue indexValue="1">
	            <compositeValue indexValue="/sbml:sbml/sbml:model/sbml:listOfSpecies/sbml:species[@id='x_CO2']">
	              <atomicValue>0.66356</atomicValue>
	            </compositeValue>
	            <compositeValue indexValue="/sbml:sbml/sbml:model/sbml:listOfSpecies/sbml:species[@id='RuBP_ch']">
	              <atomicValue>8.90632e-31</atomicValue>
	            </compositeValue>
	            <compositeValue indexValue="/sbml:sbml/sbml:model/sbml:listOfSpecies/sbml:species[@id='PGA_ch']">
	              <atomicValue>3.35479</atomicValue>
	            </compositeValue>
	        </compositeValue>
	        <resultComponent id="recomponet2"> ... </resultComponent>
	      </dimension>
	  </resultComponent>
	</numl>

[1]: http://www.comp-sys-bio.org/tiki-index.php?page=SBRML
[2]: https://raw.githubusercontent.com/NuML/NuML/master/NUMLSchema.xsd
[3]: https://github.com/NuML/NuML/tree/master/libnuml  
[4]: https://github.com/NuML/NuML/blob/master/numl-spec-l1v1.pdf