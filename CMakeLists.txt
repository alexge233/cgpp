PROJECT(cgpp)
set (cgpp_VERSION_MAJOR 0)
set (cgpp_VERSION_MINOR 2)
cmake_minimum_required(VERSION 2.8)

# Command line arguments we're interested in:
# -DBUILD_SHARED_LIBS=ON -DBUILD_STATIC_LIBS=ON -DBUILD_TESTS=ON

set(LIBRARY_PATH ${LIBRARY_PATH}
		      /lib
		      /usr/lib
		      /usr/lib64
		      /usr/local/lib
		      /usr/local/lib64
		      /usr/lib/x86_64-linux-gnu)
set(INCLUDE_DIRS ${INCLUDE_DIRS} /usr/include)

include_directories(SYSTEM ${INCLUDE_DIRS})

add_subdirectory(includes/Concept)
add_subdirectory(includes/ConceptualGraph)
add_subdirectory(includes/Node)
add_subdirectory(includes/Relation)
add_subdirectory(includes/Token)
add_subdirectory(includes/Edge)
add_subdirectory(includes/Utilities)

find_package( Boost 1.55 COMPONENTS regex REQUIRED )
include_directories( ${Boost_INCLUDE_DIR} )

find_path(CerealIncludes cereal/details/helpers.hpp PATHS ${INCLUDE_DIRS})
if(NOT CerealIncludes)
  message(FATAL_ERROR "Can't find Header Dir containing cereal/details/helpers.hpp")
endif()

# Build Libraries (both static and shared)
set (SOURCES ${SOURCES} includes/ConceptualGraph/ConceptualGraph.cpp
                        includes/Utilities/Utilities.cpp)

add_library(lcgpp OBJECT ${SOURCES})

if (${STATIC})
    message(STATUS "Building static library")
    add_library(cgpp-${cgpp_VERSION_MAJOR}.${cgpp_VERSION_MINOR}-static STATIC $<TARGET_OBJECTS:lcgpp>)
    target_link_libraries(cgpp-${cgpp_VERSION_MAJOR}.${cgpp_VERSION_MINOR}-static ${Boost_REGEX_LIBRARY})
    set(LIBOBJ ${LIBOBJ} cgpp-${cgpp_VERSION_MAJOR}.${cgpp_VERSION_MINOR}-static)
endif()
if ( (${SHARED}) OR ( NOT (${STATIC}) ) )
    message(STATUS "Building shared library, you can enable static lib with \"-DSTATIC=ON\"")
    add_library(cgpp-${cgpp_VERSION_MAJOR}.${cgpp_VERSION_MINOR} SHARED $<TARGET_OBJECTS:lcgpp>)
    target_link_libraries(cgpp-${cgpp_VERSION_MAJOR}.${cgpp_VERSION_MINOR} ${Boost_REGEX_LIBRARY} )
    set(LIBOBJ ${LIBOBJ} cgpp-${cgpp_VERSION_MAJOR}.${cgpp_VERSION_MINOR})
endif()

# Enable 'make test'
if (${BUILD_TESTS})
    enable_testing()
    message(STATUS "building tests")
    add_executable(creategraph tests/construct.cpp)
    add_test(ConstructGraph creategraph)
    add_executable(jsontest tests/json.cpp)
    add_test(json_load jsontest)
    add_executable(deserialise tests/deserialise.cpp)
    add_test(binary_load deserialise)
    add_executable(comparison tests/comparison.cpp)
    add_test(Comparison comparison)
    #add_executable(extras tests/extras.cpp)
    #add_test(test_extras extras)

    target_link_libraries(comparison ${LIBOBJ})
    target_link_libraries(creategraph ${LIBOBJ})
    target_link_libraries(jsontest ${LIBOBJ})
    target_link_libraries(deserialise ${LIBOBJ})
    #target_link_libraries(extras ${Boost_REGEX_LIBRARY} )
else()
    message(STATUS "not building tests, you can make tests with: \"-DBUILD_TESTS=ON\"")
endif()

set(CMAKE_COLOR_MAKEFILE on)

#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug) #set only when coding/testing
message(STATUS "building ${CMAKE_BUILD_TYPE}")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  # using Clang
  message (STATUS "Clang/OSX" )
  execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
  if (CLANG_VERSION_MAJOR VERSION_GREATER 3 OR CLANG_VERSION_MAJOR VERSION_EQUAL 3)
    message(STATUS "Clang >= 3.0 using C++11")
  elseif ()
    message(FATAL_ERROR "Clang version >= 3.0 is required")
  endif()
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -Wall")
  message(STATUS "CXX Flags: " ${CMAKE_CXX_FLAGS})
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -mtune=native -march=native")
  set(BUILD_SHARED_LIBS OFF)
  message(STATUS "CXX Linker: " ${CMAKE_EXE_LINKER_FLAGS})
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # using GCC/Linux
  message (STATUS "GCC/Linux" )
  execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
  if (GCC_VERSION VERSION_GREATER 4.8 OR GCC_VERSION VERSION_EQUAL 4.8)
    message(STATUS "g++ version >= 4.8 using C++11")
  elseif ()
    message (FATAL_ERROR "g++ version >= 4.8 is required")
  endif()
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
#set(MACOSX_RPATH ON)
# Install stuff
install(TARGETS ${LIBOBJ}  DESTINATION /usr/local/lib/)
install(DIRECTORY includes/ DESTINATION /usr/local/include/${PROJECT_NAME} FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp" PATTERN "*.hxx")
install(FILES includes/cgpp DESTINATION /usr/local/include/${PROJECT_NAME})

