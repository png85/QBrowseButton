project(QBrowseButton)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

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
# Look for Qt4
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
include_directories(${CMAKE_CURRENT_BINARY_DIR})


#
# libQBrowseButton: Library for applications using QBrowseButton
set(libQBrowseButton_MOC_HDRS QBrowseButton.h)
set(libQBrowseButton_SRCS QBrowseButton.cc)
set(libQBrowseButton_HDRS QBrowseButton.h)
QT4_WRAP_CPP(libQBrowseButton_MOC_SRCS ${libQBrowseButton_MOC_HDRS})
add_library(QBrowseButton STATIC ${libQBrowseButton_MOC_SRCS} ${libQBrowseButton_SRCS} ${libQBrowseButton_HDRS})
install(TARGETS QBrowseButton DESTINATION lib/)
install(FILES ${libQBrowseButton_HDRS} DESTINATION include/)

add_executable(QBrowseButton-test test.cc)
target_link_libraries(QBrowseButton-test QBrowseButton ${QT_LIBRARIES})

#
# QBrowseButtonPlugin: Qt Designer plugin to use QBrowseButton in .ui files
option(QBROWSEBUTTON_WITH_DESIGNER_PLUGIN "Build plugin to use widget in Qt Designer" ON)
if(QBROWSEBUTTON_WITH_DESIGNER_PLUGIN)
  add_definitions(${QT_DEFINITIONS})
  add_definitions(-DQT_PLUGIN)
  add_definitions(-DQT_SHARED)
  if(WIN32)
    add_definitions(-DQT_DLL)
  endif(WIN32)
  set(libQBrowseButtonPlugin_MOC_HDRS QBrowseButtonDesignerFactory.h)
  set(libQBrowseButtonPlugin_SRCS QBrowseButtonDesignerFactory.cc)
  QT4_WRAP_CPP(libQBrowseButtonPlugin_MOC_SRCS ${libQBrowseButtonPlugin_MOC_HDRS})
  add_library(QBrowseButtonPlugin SHARED ${libQBrowseButtonPlugin_MOC_SRCS} ${libQBrowseButtonPlugin_SRCS}
                                         ${libQBrowseButton_MOC_SRCS} ${libQBrowseButton_SRCS})
  target_link_libraries(QBrowseButtonPlugin ${QT_LIBRARIES})
  install(TARGETS QBrowseButtonPlugin DESTINATION ${QT_PLUGINS_DIR}/designer)
endif(QBROWSEBUTTON_WITH_DESIGNER_PLUGIN)
