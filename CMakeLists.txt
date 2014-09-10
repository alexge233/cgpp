PROJECT(cgpp)

cmake_minimum_required(VERSION 2.8)

set(LIBRARY_PATH ${LIBRARY_PATH}
		      /lib
		      /usr/lib
		      /usr/lib64
		      /usr/local/lib
		      /usr/local/lib64
		      /usr/lib/x86_64-linux-gnu)

set(INCLUDE_HEADERS ${INCLUDE_HEADERS} /usr/include/)

include_directories(SYSTEM ${INCLUDE_HEADERS})

find_package(Boost)

add_subdirectory(includes/Concept)
add_subdirectory(includes/ConceptualGraph)
add_subdirectory(includes/Node)
add_subdirectory(includes/Relation)
add_subdirectory(includes/Token)
add_subdirectory(includes/Edge)
add_subdirectory(includes/Utilities)

# Test executable "creategraph”
add_executable ( creategraph tests/construct.cpp
			     includes/ConceptualGraph/ConceptualGraph.cpp
			     includes/ConceptualGraph/ConceptualGraphJSON.cpp
			     includes/Utilities/Utilities.cpp)

# Test executable "jsontest"
add_executable ( jsontest tests/json.cpp
                          includes/ConceptualGraph/ConceptualGraph.cpp
                          includes/ConceptualGraph/ConceptualGraphJSON.cpp)

# Test executable "deserialise"
add_executable ( deserialise tests/deserialise.cpp
			     includes/ConceptualGraph/ConceptualGraph.cpp
			     includes/ConceptualGraph/ConceptualGraphJSON.cpp)

# Build Libraries (both static and shared)
set (SOURCES ${SOURCES} includes/ConceptualGraph/ConceptualGraph.cpp
                        includes/ConceptualGraph/ConceptualGraphJSON.cpp
                        includes/Utilities/Utilities.cpp)

add_library (lcgpp OBJECT ${SOURCES})
add_library (cgpp.0.1-static STATIC $<TARGET_OBJECTS:lcgpp>)
add_library (cgpp.0.1 SHARED $<TARGET_OBJECTS:lcgpp>)


set(CMAKE_COLOR_MAKEFILE on)
set(CMAKE_VERBOSE_MAKEFILE on)

#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug) #set only when coding/testing

# NOTE: C++14 is available as: -std=c++1y or -std=gnu++1y in GCC 4.9 - Don't know if Clang supports it yet.

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  # using Clang
  message (STATUS "Clang/OSX" )
  execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)

  if (CLANG_VERSION_MAJOR VERSION_GREATER 3 OR CLANG_VERSION_MAJOR VERSION_EQUAL 3)
    message(STATUS "Info: Clang >= 3.0 using C++11")
  elseif ()
    message(FATAL_ERROR "Clang version >= 3.0 is required")
  endif()
  
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -Wall")
  
  message(STATUS "CXX Flags: " ${CMAKE_CXX_FLAGS})
  
  #add_definitions(${CMAKE_CXX_FLAGS})
  
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
  
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG -O3 -s -mtune=native -march=native")
  
  set(BUILD_SHARED_LIBS OFF)
  
  message(STATUS "CXX Linker: " ${CMAKE_EXE_LINKER_FLAGS})

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

  message (STATUS "GCC/Linux" )
  execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
  
  if (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7)
    message(STATUS "Info: g++ version >= 4.9 using C++11")
  elseif ()
    message (FATAL_ERROR "g++ version >= 4.9 is required")
  endif()
  
  # NOTE: gnu++11 enables GNU's violating options, whereas c++11 is strictly only the new version
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=gnu++11 -Wall -fPIC")
  
  message(STATUS "CXX Flags: " ${CMAKE_CXX_FLAGS})
  
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
  
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -mtune=native -march=native") # -s ?
  
  set(BUILD_SHARED_LIBS OFF)
  
  message(STATUS "CXX Linker: " ${CMAKE_EXE_LINKER_FLAGS})

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    message (FATAL_ERROR "unsupported compiler")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message (FATAL_ERROR "unsupported compiler")
endif()

