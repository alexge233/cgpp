# JSON Prototype

This is the JSON prototype for version 0.1 of the Conceptual Graph.
Please always follow this format, anything else won't be parsed and will result in a runtime exception.

```json
{
    "version" : "1",
    "guid" : "00000000-0000-0000-0000-000000000000",
    "creator" : null,
    "relations" : [
     {
         "label" : "is",
         "postag" : "VBZ",
         "index" : "1",
         "id" : "2976782025758403374"
     }],
     "concepts" : [
     {
         "label" : "sky",
         "postag" : "NNZ",
         "index" : "0",
         "id" : "1577683746703680484"
     },
     {
         "label" : "blue",
         "postag" : "NNZ",
         "index" : "2",
         "id" : "15843861542616104093"
     }],
     "adjacencies": [
     {
         "nodeTo" : "1577683746703680484",
         "nodeFrom" : "2976782025758403374",
         "index" : "0",
         "order" : "cr"
     },
     {
         "nodeTo" : "15843861542616104093",
         "nodeFrom" : "2976782025758403374",
         "index" : "1",
         "order" : "rc"
     }]
}
```

* `version` defines the current protocol version.
* `guid` must be a valid UUID version 4, invalid ones will throw an exception.
* `creator` is optional.
* `relations` array must contain all graph relation nodes.
* `concepts` array must contain all graph concept nodes.
* `adjacencies` array must contain all edges.

A few important notes:

* `label` is the actual string value of a node, it is mandatory.
* `postag` is the part-of-speech tag of a node, it is optional.
* `index` is the position of the node in a text sentence and is mandatory. Conflicting `index` fields will throw an exception.
* `id` is a unique id for a specific node. If not unique the library *may* throw an exception. Its best to use Murmur or similar hash.

Adjacencies work by creating an *adjacency matrix* where each edge is described by members `nodeTo` and `nodeFrom`.
* `index` in an adjacency object defines the order of the edge list, and must be unique and is mandatory.
* `order` in an adjacency object defines the node class types, e.g., if [Concept→ Relation] use `cr` and `rc` for the opposite.
