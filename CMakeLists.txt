project(QBrowseButton)
cmake_minimum_required(VERSION 3.1)

#
# User configurable build options
option(QBrowseButton_BUILD_AS_SUBMODULE "Build QBrowseButton as git submodule?" OFF)
option(QBrowseButton_BUILD_SHARED_LIBS "Build QBrowseButton as shared library?" ON)
option(QBrowseButton_WITH_EXAMPLE "Build demo executable for QBrowseButton?" ON)
option(QBrowseButton_WITH_DESIGNER_PLUGIN "Build QBrowseButton plugin for Qt Designer?" ON)
option(QBrowseButton_ENABLE_QT4 "Enable Qt4 version of widget?" ON)
option(QBrowseButton_ENABLE_QT5 "Enable Qt5 version of widget?" ON)

#
# Version number (for packages & Unix SOVERSION)
set(QBrowseButton_VERSION_MAJOR 1)
set(QBrowseButton_VERSION_MINOR 2)
set(QBrowseButton_VERSION_PATCH 2)

if(NOT QBrowseButton_BUILD_AS_SUBMODULE)
    set(CPACK_PACKAGE_DESCRIPTION "QBrowseButton widget for Qt")
    set(CPACK_PACKAGE_VERSION_MAJOR ${QBrowseButton_VERSION_MAJOR})
    set(CPACK_PACKAGE_VERSION_MINOR ${QBrowseButton_VERSION_MINOR})
    set(CPACK_PACKAGE_VERSION_PATCH ${QBrowseButton_VERSION_PATCH})
    if(WIN32)
        set(CPACK_GENERATOR "ZIP")
    endif(WIN32)
    include(CPack)
endif(NOT QBrowseButton_BUILD_AS_SUBMODULE)

#
# Automatically invoke moc for headers that need it
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#
# Include current directory for auto-generated files
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

#
# Setup target library type based on user choice
if(QBrowseButton_BUILD_SHARED_LIBS)
    set(LIB_TYPE SHARED)
else(QBrowseButton_BUILD_SHARED_LIBS)
    set(LIB_TYPE STATIC)
endif(QBrowseButton_BUILD_SHARED_LIBS)
include(GenerateExportHeader)

include(WriteCompilerDetectionHeader)
if(WIN32)
    set(supported_compilers GNU Clang MSVC)
else(WIN32)
    set(supported_compilers GNU Clang)
endif(WIN32)
write_compiler_detection_header(FILE ${CMAKE_CURRENT_BINARY_DIR}/include/QBrowseButton_compiler_features.h
                                PREFIX QBrowseButton
                                VERSION 3.1.0
                                COMPILERS ${supported_compilers}
                                FEATURES cxx_nullptr cxx_lambdas cxx_deleted_functions)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

configure_file(QBrowseButton_version.h.in ${CMAKE_CURRENT_BINARY_DIR}/include/QBrowseButton_version.h)

#
# Subdirectory builds for Qt4/5 versions of all libraries
if(NOT QBrowseButton_ENABLE_QT4 AND NOT QBrowseButton_ENABLE_QT5)
    message(ERROR "You need to enable at least one of Qt4/5!")
endif(NOT QBrowseButton_ENABLE_QT4 AND NOT QBrowseButton_ENABLE_QT5)

if(QBrowseButton_ENABLE_QT4)
    add_subdirectory(QBrowseButton4)
endif(QBrowseButton_ENABLE_QT4)

if(QBrowseButton_ENABLE_QT5)
    add_subdirectory(QBrowseButton5)
endif(QBrowseButton_ENABLE_QT5)


#
# Install header files
file(GLOB QBrowseButton_HDRS include/QBrowseButton.h)
install(FILES ${QBrowseButton_HDRS} DESTINATION include/)
