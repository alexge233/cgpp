# CMake generated Testfile for 
# Source directory: /home/alex/projects/cgpp-master
# Build directory: /home/alex/projects/cgpp-master/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
ADD_TEST(ConstructGraph "creategraph")
ADD_TEST(JSON_Serialise "jsontest")
ADD_TEST(JSON_Deserialise "deserialise")
SUBDIRS(includes/Concept)
SUBDIRS(includes/ConceptualGraph)
SUBDIRS(includes/Node)
SUBDIRS(includes/Relation)
SUBDIRS(includes/Token)
SUBDIRS(includes/Edge)
SUBDIRS(includes/Utilities)
