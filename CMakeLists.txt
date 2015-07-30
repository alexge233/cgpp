PROJECT(cgpp)

set (cgpp_VERSION_MAJOR 0)
set (cgpp_VERSION_MINOR 1)

cmake_minimum_required(VERSION 2.8)

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

find_package( Boost 1.49 COMPONENTS regex REQUIRED )
include_directories( ${Boost_INCLUDE_DIR} )

find_path(CerealIncludes cereal/details/helpers.hpp PATHS ${INCLUDE_DIRS})
if(NOT CerealIncludes)
  message(FATAL_ERROR "Can't find Header Dir containing cereal/details/helpers.hpp")
endif()

# Enable 'make test'
enable_testing()

add_executable ( creategraph 
                       tests/construct.cpp
			           includes/ConceptualGraph/ConceptualGraph.cpp
			           includes/ConceptualGraph/ConceptualGraphJSON.cpp
			           includes/Utilities/Utilities.cpp)
add_test ( ConstructGraph creategraph )

add_executable ( jsontest
                    tests/json.cpp
                    includes/ConceptualGraph/ConceptualGraph.cpp
                    includes/ConceptualGraph/ConceptualGraphJSON.cpp)
add_test( JSON_Serialise jsontest )

add_executable ( deserialise
                       tests/deserialise.cpp
			           includes/ConceptualGraph/ConceptualGraph.cpp
			           includes/ConceptualGraph/ConceptualGraphJSON.cpp)
add_test( JSON_Deserialise deserialise)

add_executable ( comparison
                       tests/comparison.cpp
                       includes/ConceptualGraph/ConceptualGraph.cpp
                       includes/ConceptualGraph/ConceptualGraphJSON.cpp
                       includes/ConceptualGraph/ConceptualGraphEXTRAS.cpp)
add_test( JSON_Comparison comparison)

add_executable ( extras
                       tests/extras.cpp
                       includes/ConceptualGraph/ConceptualGraph.cpp
                       includes/ConceptualGraph/ConceptualGraphJSON.cpp
		       includes/ConceptualGraph/ConceptualGraphEXTRAS.cpp)
add_test( test_extras extras)

# Build Libraries (both static and shared)
set (SOURCES ${SOURCES} includes/ConceptualGraph/ConceptualGraph.cpp
                        includes/ConceptualGraph/ConceptualGraphJSON.cpp
			includes/ConceptualGraph/ConceptualGraphEXTRAS.cpp
                        includes/Utilities/Utilities.cpp)

add_library (lcgpp OBJECT ${SOURCES})
add_library (cgpp.0.1-static STATIC $<TARGET_OBJECTS:lcgpp>)
add_library (cgpp.0.1 SHARED $<TARGET_OBJECTS:lcgpp>)

target_link_libraries(cgpp.0.1-static ${Boost_REGEX_LIBRARY} )
target_link_libraries(cgpp.0.1 ${Boost_REGEX_LIBRARY} )
target_link_libraries(creategraph ${Boost_REGEX_LIBRARY} )
target_link_libraries(jsontest ${Boost_REGEX_LIBRARY} )
target_link_libraries(deserialise ${Boost_REGEX_LIBRARY} )
target_link_libraries(comparison ${Boost_REGEX_LIBRARY} )
target_link_libraries(extras ${Boost_REGEX_LIBRARY} )

set(CMAKE_COLOR_MAKEFILE on)
#set(CMAKE_VERBOSE_MAKEFILE off)

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
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -mtune=native -march=native")
  set(BUILD_SHARED_LIBS OFF)
  message(STATUS "CXX Linker: " ${CMAKE_EXE_LINKER_FLAGS})

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # using GCC/Linux
  message (STATUS "GCC/Linux" )
  execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
  if (GCC_VERSION VERSION_GREATER 4.9 OR GCC_VERSION VERSION_EQUAL 4.9)
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

#set(MACOSX_RPATH ON)

# Install stuff
install (TARGETS cgpp.0.1-static  DESTINATION /usr/local/lib/)
install (TARGETS cgpp.0.1 DESTINATION /usr/local/lib/)
install (DIRECTORY includes/ DESTINATION /usr/local/include/${PROJECT_NAME} FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp" PATTERN "*.hxx")
install (FILES includes/cgpp DESTINATION /usr/local/include/${PROJECT_NAME})
