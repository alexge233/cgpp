# Conceptual Graph Library for C++11

This is a minimalistic library implementing John Sowa’s Conceptual Graphs [1].
It uses a much more lax JSON protocol to the one implemented in XML (CGXML, Cogitant, CGIF)
and at the moment, does not conform to the ISO Common Logic Project.
However, it is a very simple library, taking a graph-centric approach,
and should be very easy to use for simple Knowledge Representation.

## Directories

* json protocol is under `/includes/Proto`
* C++ headers and source code are in: `/includes`
( test apps are in : `/test`

## Tested with:

* Clang 5.1
* GNU g++ 4.8 and 4.9

## Dependencies:

* boost       >= 1.54     [http://www.boost.org]
* cereal      >= 1.0.0    [http://uscilab.github.io/cereal/] expected to be in /usr/local/include
* rapidjson   >= 0.1 (?)  [https://github.com/pah/rapidjson] included under /includes/rapidjson

## Building (Linux or OSX):

```
$ mkdir build
$ cd build
$ cmake ..
```

You can build both static and shared libraries with:

`cmake .. -DSTATIC=ON -DSHARED=ON`

You can disable shared with:

`cmake .. -DSTATIC=ON -DSHARED=ON`

By default only shared is built.

## Tests (Examples)

To build the tests:

`cmake .. -DBUILD_TESTS=ON`

and once built:

`$ make test`

## Installing 

By default the headers installed in `/usr/local/include`
and the library is installed in `/usr/local/libs`

If those directories don't exist in your distro or system,
you can edit the CMakeLists.txt.

`
$ su
$ make install
`

OR

`
$ sudo make install
`

## Contributor

- Alexander Gkiokas, **[a.gkiokas@warwick.co.uk]**

## References

[1] John F. Sowa, Knowledge Representation: Logical, Philosophical, and Computational Foundations, Brooks Cole Publishing Co., Pacific Grove, CA, ©2000. Actual publication date, 16 August 1999.
