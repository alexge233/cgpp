TODO [ASAP!!!]:

    1 - Implement Utilities: 
		- Cluster of Nodes: find for current node, what other nodes it has common edges with.
        - Cluster of Concepts (to Relations)
        - Cluster of Relations (to Concepts)

    2 - IMPORTANT: Add Unit Tests for basic classes: Token, Node, Concept, Relation, ConceptualGraph
        - constructor tests
        - operator tests
        - use Boost and verify there is no undefined behaviour

    3 - Remove rapidjson and use boost
	    - deserialise using Boost (load from json)
        - rapidjson is used in class `ConceptualGraph` only
        - serialise using Boost (save to json) instead of manually creating them

[DEADLINE 29th MARCH 2016]

TODO: [0.4.0]

    1 - Implement Conversion of a Conceptual Graph to CGIF (string), or FOL.
		- Consider other FOL,HOL or Ontology Schemas (RDF?OWL?) to which we can translate Conceptual Graphs
		- Conversion may be semi-heuristic, e.g.,: infer edges and detect/predict entities
