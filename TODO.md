#TODO ASAP!!!:

1. IMPORTANT:
    * Add Class Unit Tests for `ConceptualGraph` (construct, operators)
    * Add Graph Logic Tests for `ConceptualGraph` (add nodes, add edges, similarity, metrics)

**DEADLINE 29th MARCH 2016**

#TODO: 0.4.0

1. Remove rapidjson and use boost
    * deserialise using Boost (load from json)
    * rapidjson is used in class `ConceptualGraph` only
    * serialise using Boost (save to json) instead of manually creating them

2. Implement Conversion of a Conceptual Graph to CGIF (string), or FOL.
	* Consider other FOL,HOL or Ontology Schemas (RDF?OWL?) to which we can translate Conceptual Graphs
	* Conversion may be semi-heuristic, e.g.,: infer edges and detect/predict entities
