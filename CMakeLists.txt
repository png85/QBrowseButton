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


set(libQBrowseButton_MOC_HDRS QBrowseButton.h)
set(libQBrowseButton_SRCS QBrowseButton.cc)
QT4_WRAP_CPP(libQBrowseButton_MOC_SRCS ${libQBrowseButton_MOC_HDRS})
add_library(QBrowseButton ${libQBrowseButton_MOC_SRCS} ${libQBrowseButton_SRCS})
