cmake_minimum_required(VERSION 3.1)
include(WriteBasicConfigVersionFile)
set(TARGET_NAME accneat)

# Project Name
PROJECT(${TARGET_NAME})
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/user.cmake")
	include(${CMAKE_CURRENT_SOURCE_DIR}/user.cmake)
	MESSAGE("include user.cmake")
	else()
	MESSAGE("didnt include user.cmake")
endif()

# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")
  
if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR CMake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/cmake/accneat)
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")
 
# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

#########################################################
# Include Files
#########################################################

FILE(GLOB_RECURSE HEADERS include/*.h)
FILE(GLOB_RECURSE SOURCES src/*.cpp)

add_library(${TARGET_NAME} ${SOURCES} ${HEADERS})
set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 11)
SET_SOURCE_FILES_PROPERTIES( ${SOURCES} PROPERTIES LANGUAGE CXX )
set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE CXX)

SET_PROPERTY(TARGET ${TARGET_NAME} APPEND PROPERTY PUBLIC_HEADER ${HEADERS})
target_include_directories(${TARGET_NAME}
	PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>" "$<INSTALL_INTERFACE:include>"
)

# header must be installed manually
#install(FILES "${HEADERS}" DESTINATION "${INSTALL_INCLUDE_DIR}" COMPONENT developer)

install(
  TARGETS ${TARGET_NAME}
  EXPORT ${TARGET_NAME}
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR}" COMPONENT developer
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT runtime
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}" COMPONENT developer
)

#WRITE_BASIC_CONFIG_VERSION_FILE("${VERSION_FILENAME}" VERSION ${VERSION} COMPATIBILITY ExactVersion)

configure_file("${TARGET_NAME}-config.in" "${CMAKE_BINARY_DIR}/${TARGET_NAME}-config.cmake" @ONLY)
install(
	FILES
		"${CMAKE_BINARY_DIR}/${TARGET_NAME}-config.cmake"
	DESTINATION cmake
	COMPONENT developer
)


# export target to binary tree
export(
	EXPORT ${TARGET_NAME}
	FILE "${TARGET_NAME}-targets.cmake"
)
# install target to install tree
install(
	EXPORT ${TARGET_NAME}
	DESTINATION "cmake"
	COMPONENT developer
	FILE "${TARGET_NAME}-targets.cmake"
)
