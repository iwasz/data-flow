# Wymagaj tej wersji - dopier w niej jest nowe makro FindPkgConfig
CMAKE_MINIMUM_REQUIRED (VERSION 2.8.0 FATAL_ERROR)

PROJECT (data-flow)
SET (CMAKE_EXPORT_COMPILE_COMMANDS ON)
INCLUDE (../tiliae/tiliae.cmake)
SET (CMAKE_VERBOSE_MAKEFILE OFF)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11" CACHE INTERNAL "cxx compiler flags")

SET(CMAKE_C_FLAGS_RELEASE "-DNDEBUG" CACHE INTERNAL "c release compiler flags")
SET(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG" CACHE INTERNAL "cxx release compiler flags")
SET (WITH_PARSER               ON CACHE BOOL "")
SET (WITH_CPPABI               ON CACHE BOOL "")

ADD_DEFINITIONS (-DBOOST_LOG_DYN_LINK)

find_package (Boost REQUIRED COMPONENTS log log_setup regex)
include_directories(${Boost_INCLUDE_DIRS})
link_directories (${Boost_LIBRARY_DIRS})

include (FindPkgConfig)

pkg_check_modules (TILIAE "tiliae")
if (NOT TILIAE_FOUND)
        MESSAGE (STATUS "Tiliae not installed, using local copy.")
        SET (TILIAE_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/../tiliae/src/")
        SET (TILIAE_LIBRARY_DIRS "${PROJECT_SOURCE_DIR}/../tiliae/build/src/")
        SET (TILIAE_LIBRARIES "tiliae")
        MESSAGE (STATUS ${TILIAE_INCLUDE_DIRS})
        MESSAGE (STATUS ${TILIAE_LIBRARY_DIRS})
endif ()
INCLUDE_DIRECTORIES (${TILIAE_INCLUDE_DIRS})
link_directories(${TILIAE_LIBRARY_DIRS})

# +-------------------------------+
# | Generate reflection database. |
# +-------------------------------+
IF (WITH_PARSER)
TILIAE_PARSE ("${PROJECT_SOURCE_DIR}/../tiliae/build/parser/tiliaeparser" "dataFlow" "src/Reflection_input.cc" "src/Reflection_output_data_flow.cc.h")
ENDIF ()
LIST (APPEND SOURCES "src/Reflection_input.cc")
LIST (APPEND SOURCES "src/Reflection_output_data_flow.cc.h")

# +-------------------------------+
# | Main target                   |
# +-------------------------------+

LIST (APPEND SOURCES
        "src/core/Core.h"
        "src/core/Arc.cc"
        "src/core/Arc.h"
        "src/core/Port.cc"
        "src/core/Port.h"
        "src/core/INode.h"
        "src/core/INode.cc"
        "src/core/IOPolicy.h"
        "src/core/AbstractNode.h"
        "src/core/Source.h"
        "src/core/Sink.h"
        "src/core/MathNodes.h"
        "src/core/CommonNodes.h"
        "src/core/CommonNodes.cc"
        "src/core/CommonSinks.h"
        "src/core/CommonSinks.cc"
        "src/core/CommonSources.h"
        "src/core/CommonSources.cc"
        "src/core/Exception.h"
        "src/core/Exception.cc"
        "src/Program.h"
        "src/Program.cc"
        "src/core/IFlowObserver.h"
)

# Local includes (inside project).
INCLUDE_DIRECTORIES (src)
INCLUDE_DIRECTORIES ("/usr/include/libcxxabi")

add_library (dataflow STATIC ${SOURCES})
IF (WITH_CPPABI)
TARGET_LINK_LIBRARIES (dataflow c++abi)
ENDIF ()

SET (SOURCES "src/main.cc")
add_executable (${CMAKE_PROJECT_NAME} ${SOURCES})
IF (WITH_CPPABI)
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} c++abi)
ENDIF ()
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} dataflow)
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} ${TILIAE_LIBRARIES})

