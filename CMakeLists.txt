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

# Test executable "creategraph”
add_executable ( creategraph tests/construct.cpp
			     includes/ConceptualGraph/ConceptualGraph.cpp)

# Test executable "jsontest"
add_executable ( jsontest tests/json.cpp
                          includes/ConceptualGraph/ConceptualGraph.cpp)

# Build Libraries (both static and shared)
set (SOURCES ${SOURCES} includes/ConceptualGraph/ConceptualGraph.cpp)

add_library (cgpp OBJECT ${SOURCES})
add_library (static STATIC $<TARGET_OBJECTS:cgpp>)
add_library (shared SHARED $<TARGET_OBJECTS:cgpp>)


set(CMAKE_COLOR_MAKEFILE on)
set(CMAKE_VERBOSE_MAKEFILE on)

#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  # using Clang
  message (STATUS "Clang/OSX" )
  execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)

  if (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7)
    message(STATUS "Info: C++ version >= 4.7 using C++11")
  elseif ()
    message(FATAL_ERROR "C++ version >= 4.6 is required")
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
    message(STATUS "Info: C++ version >= 4.7 using C++11")
  elseif ()
    message (FATAL_ERROR "C++ version >= 4.6 is required")
  endif()
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=gnu++0x -Wall -fPIC")
  message(STATUS "CXX Flags: " ${CMAKE_CXX_FLAGS})
  #add_definitions(${CMAKE_CXX_FLAGS})
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG -O3 -s -mtune=native -march=native")
  set(BUILD_SHARED_LIBS OFF)
  message(STATUS "CXX Linker: " ${CMAKE_EXE_LINKER_FLAGS})

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    message (FATAL_ERROR "unsupported compiler")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message (FATAL_ERROR "unsupported compiler")
endif()


# TODO: Finally, after building, set the installation directory if needed as such:
#       install(DIRECTORY dirs... DESTINATION <dir> (http://www.cmake.org/pipermail/cmake/2011-December/047905.html)
