# CMake build script for the git2 project
#
# Building (out of source build):
# > mkdir build && cd build
# > cmake .. [-DSETTINGS=VALUE]
# > cmake --build .
#
# Install:
# > cmake --build . --target install

PROJECT(git2app C)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")

# Collect sourcefiles
FILE(GLOB SRC *.c)
FILE(GLOB SRC_H *.h)

IF (WIN32 AND NOT CYGWIN)
    ADD_DEFINITIONS(-DWIN32 -D_DEBUG -D_LIB)
	IF (MINGW)
		SET(PTHREAD_LIBRARY pthread)
	ENDIF ()
ENDIF ()	

# Find required dependencies
FIND_PACKAGE(Libgit2 REQUIRED)

# Specify target
ADD_EXECUTABLE(git2 ${SRC})

INCLUDE_DIRECTORIES(${Libgit2_INCLUDE_DIR} ${Libgit2_INCLUDE_DIR}/../deps/zlib)
TARGET_LINK_LIBRARIES(git2 ${Libgit2_LIBRARY})
