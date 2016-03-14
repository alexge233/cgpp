TODO [branch development]:

    0 - ASAP: fix Jaccard Coefficient Weights, by using the Ratio of each Set (Concepts,Relations,Edges)
            : fix Sorensen Coefficeint Weights, instead of using 50%-50%
            @see branch `tested` for more info.

    1 - Remove rapidjson and use boost
	    - Serialise using Boost (instead of manual JSON creation)
        - Deserialise using Boost (load JSON with Boost)

    2 - Node utilites and operations:
        - Add (Concatenate) Concepts or Relations into a new entity (operator+)
        - Subtract (Difference) Concepts or Relations into a new subentity (operator-)

    3 - Group/Cluster Heuristic Utilities:
        - Cluster of Nodes: find for current node, what other nodes it has common edges with.
        - Fully connected: are two groups (vectors, arrays, lists) of Nodes (R,C || C,R) fully connected by edges?

    4 - Implement Conversion of a Conceptual Graph to CGIF (string), or FOL (string).

