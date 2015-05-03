project(QBrowseButton)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#
# Enable C++11 for GCC builds
if(CMAKE_COMPILER_IS_GNUCXX)
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag("-std=c++11" GCC_stdcxx11)
    check_cxx_compiler_flag("-std=c++0x" GCC_stdcxx0x)

    if(GCC_stdcxx11)
        # Compiler supports -std=c++11
        message(STATUS "Using -std=c++11 to enable C++11 in GCC")
        add_definitions(-std=c++11)
    elseif(GCC_stdcxx0x)
        # Compiler doesn't support -std=c++11 but -std=c++0x
        message(STATUS "Using -std=c++0x to enable C++11 in GCC")
        add_definitions(-std=c++0x)
    else()
        # Neither -std=c++11 nor -std=c++0x are supported
        message(WARNING "Failed to determine C++11 flag for GCC :-(")
    endif()
endif(CMAKE_COMPILER_IS_GNUCXX)

include(CheckCXX11Features)
foreach(flag ${CXX11_FEATURE_LIST})
  add_definitions(-D${flag})
endforeach()

#
# User configurable build options
option(QBrowseButton_BUILD_AS_SUBMODULE "Build QBrowseButton as git submodule?" OFF)
option(QBrowseButton_BUILD_SHARED_LIBS "Build QBrowseButton as shared library?" ON)
option(QBrowseButton_WITH_EXAMPLE "Build demo executable for QBrowseButton?" ON)
option(QBrowseButton_WITH_DESIGNER_PLUGIN "Build QBrowseButton plugin for Qt Designer?" ON)
option(QBrowseButton_INSTALL_DESIGNER_PLUGIN "Install Qt Designer plugin to Qt plugin directory?" OFF)

if(NOT QBrowseButton_BUILD_AS_SUBMODULE)
    set(CPACK_PACKAGE_DESCRIPTION "QBrowseButton widget for Qt4")
    set(CPACK_PACKAGE_VERSION_MAJOR 1)
    set(CPACK_PACKAGE_VERSION_MINOR 1)
    set(CPACK_PACKAGE_VERSION_PATCH 1)
    if(WIN32)
        set(CPACK_GENERATOR "ZIP")
    endif(WIN32)
    include(CPack)
endif(NOT QBrowseButton_BUILD_AS_SUBMODULE)

#
# Look for Qt4
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#
# Setup target library type based on user choice
if(QBrowseButton_BUILD_SHARED_LIBS)
    set(LIB_TYPE SHARED)
else(QBrowseButton_BUILD_SHARED_LIBS)
    set(LIB_TYPE STATIC)
endif(QBrowseButton_BUILD_SHARED_LIBS)
include(GenerateExportHeader)

#
# libQBrowseButton: Library for applications using QBrowseButton
set(libQBrowseButton_MOC_HDRS QBrowseButton.h)
set(libQBrowseButton_SRCS QBrowseButton.cc)
set(libQBrowseButton_HDRS QBrowseButton.h)
QT4_WRAP_CPP(libQBrowseButton_MOC_SRCS ${libQBrowseButton_MOC_HDRS})
add_library(QBrowseButton ${LIB_TYPE} ${libQBrowseButton_MOC_SRCS} ${libQBrowseButton_SRCS} ${libQBrowseButton_HDRS})
target_link_libraries(QBrowseButton ${QT_LIBRARIES})
if(UNIX AND QBrowseButton_BUILD_SHARED_LIBS)
    target_set_properties(QBrowseButton PROPERTIES SONAME "QBrowseButton" SOVERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR})
endif(UNIX AND QBrowseButton_BUILD_SHARED_LIBS)
generate_export_header(QBrowseButton BASE_NAME QBrowseButton
                                     EXPORT_MACRO_NAME QBrowseButton_EXPORT
                                     EXPORT_FILE_NAME QBrowseButton_Export.h
                                     STATIC_DEFINE QBrowseButton_BUILT_AS_STATIC)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QBrowseButton_Export.h DESTINATION include/)
install(TARGETS QBrowseButton ARCHIVE DESTINATION lib
                              LIBRARY DESTINATION lib
                              RUNTIME DESTINATION bin)
install(FILES ${libQBrowseButton_HDRS} DESTINATION include/)

#
# QBrowseButton-test: Simple demo executable
if(QBrowseButton_WITH_EXAMPLE)
    add_executable(QBrowseButton-test test.cc)
    target_link_libraries(QBrowseButton-test QBrowseButton ${QT_LIBRARIES})
    install(TARGETS QBrowseButton-test RUNTIME DESTINATION bin)
endif(QBrowseButton_WITH_EXAMPLE)

#
# QBrowseButtonPlugin: Qt Designer plugin to use QBrowseButton in .ui files
if(QBrowseButton_WITH_DESIGNER_PLUGIN)
  add_definitions(${QT_DEFINITIONS})
  add_definitions(-DQT_PLUGIN)
  add_definitions(-DQT_SHARED)
  if(WIN32)
    add_definitions(-DQT_DLL)
  endif(WIN32)
  set(libQBrowseButtonPlugin_MOC_HDRS QBrowseButtonDesignerFactory.h)
  set(libQBrowseButtonPlugin_SRCS QBrowseButtonDesignerFactory.cc)
  QT4_WRAP_CPP(libQBrowseButtonPlugin_MOC_SRCS ${libQBrowseButtonPlugin_MOC_HDRS})
  add_library(QBrowseButtonPlugin SHARED ${libQBrowseButtonPlugin_MOC_SRCS} ${libQBrowseButtonPlugin_SRCS})
  target_link_libraries(QBrowseButtonPlugin QBrowseButton ${QT_LIBRARIES})
  if(QBrowseButton_INSTALL_DESIGNER_PLUGIN)
    install(TARGETS QBrowseButtonPlugin DESTINATION ${QT_PLUGINS_DIR}/designer)
  else(QBrowseButton_INSTALL_DESIGNER_PLUGIN)
    install(TARGETS QBrowseButtonPlugin ARCHIVE DESTINATION lib
                                        LIBRARY DESTINATION lib
                                        RUNTIME DESTINATION bin)
  endif(QBrowseButton_INSTALL_DESIGNER_PLUGIN)
endif(QBrowseButton_WITH_DESIGNER_PLUGIN)
