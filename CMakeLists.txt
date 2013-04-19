project(QBrowseButton)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(CheckCXX11Features)
foreach(flag ${CXX11_FEATURE_LIST})
  add_definitions(-D${flag})
endforeach()

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -std=c++0x")
  list(REMOVE_DUPLICATES CMAKE_CXX_FLAGS)

  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb")
  list(REMOVE_DUPLICATES CMAKE_CXX_FLAGS_DEBUG)
endif(CMAKE_COMPILER_IS_GNUCXX)

if(MSVC)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /W4")
  list(REMOVE_DUPLICATES CMAKE_CXX_FLAGS_DEBUG)
endif(MSVC)



#
# Look for Qt4
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
include_directories(${CMAKE_CURRENT_BINARY_DIR})


#
# libQBrowseButton: Library for applications using QBrowseButton
set(libQBrowseButton_MOC_HDRS QBrowseButton.h)
set(libQBrowseButton_SRCS QBrowseButton.cc)
QT4_WRAP_CPP(libQBrowseButton_MOC_SRCS ${libQBrowseButton_MOC_HDRS})
add_library(QBrowseButton ${libQBrowseButton_MOC_SRCS} ${libQBrowseButton_SRCS})
install(TARGETS QBrowseButton DESTINATION lib/)


#
# QBrowseButtonPlugin: Qt Designer plugin to use QBrowseButton in .ui files
add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_PLUGIN)
#add_definitions(-DQT_NO_DEBUG)
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
