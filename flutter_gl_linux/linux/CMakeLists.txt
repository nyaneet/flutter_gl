# The Flutter tooling requires that developers have CMake 3.10 or later
# installed. You should not increase this version, as doing so will cause
# the plugin to fail to compile for some customers of the plugin.
cmake_minimum_required(VERSION 3.10)

# Project-level configuration.
set(PROJECT_NAME "flutter_gl_linux")
project(${PROJECT_NAME} LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#list(APPEND FLUTTER_LIBRARY_HEADERS
#        "flutter_export.h"
#        "flutter_windows.h"
#        "flutter_messenger.h"
#        "flutter_plugin_registrar.h"
#        "flutter_texture_registrar.h"
#                "fl_texture_registrar.h"
#        "fl_pixel_buffer_texture.h"
#)


# This value is used when generating builds using this plugin, so it must
# not be changed.
set(PLUGIN_NAME "flutter_gl_linux_plugin")

# Define the plugin library target. Its name must not be changed (see comment
# on PLUGIN_NAME above).
#
# Any new source files that you add to the plugin should be added here.
add_library(
  ${PLUGIN_NAME} SHARED
  flutter_gl_linux_plugin.cc
  fl_my_texturep_gl.cc
  fl_my_texture_gl.cc
  customrender.cc
  renderworker.cc
  eglenv.cc
  OpenGLProgram.cpp
  #test.cpp

  #../src/common.h
  #../src/ffi.cpp
  #../src/Renderer.cpp
  #../src/Shader.cpp
  #../src/uniformQueue.cpp
  #../src/Sampler2D.cpp

  #../src/opencv_capture.cpp

)

# Apply a standard set of build settings that are configured in the
# application-level CMakeLists.txt. This can be removedfor plugins that want
# full control over build settings.
# apply_standard_settings(${PLUGIN_NAME})

# Symbols are hidden by default to reduce the chance of accidental conflicts
# between plugins. This should not be removed; any symbols that should be
# exported should be explicitly exported with the FLUTTER_PLUGIN_EXPORT macro.
set_target_properties(${PLUGIN_NAME} PROPERTIES
  CXX_VISIBILITY_PRESET hidden)
target_compile_definitions(${PLUGIN_NAME} PRIVATE FLUTTER_PLUGIN_IMPL)

# don't treat warnings as compile errors in this plugin. It will be removed
target_compile_options(${PLUGIN_NAME} PRIVATE -Wall -Wno-error -v -v)


# Source include directories and library dependencies. Add any plugin-specific
# dependencies here.
target_include_directories(${PLUGIN_NAME} INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
  #"${CMAKE_CURRENT_SOURCE_DIR}/../src"
  #"${CMAKE_CURRENT_SOURCE_DIR}/../src/shaders"
)
target_link_libraries(${PLUGIN_NAME} PRIVATE flutter)
target_link_libraries(${PLUGIN_NAME} PRIVATE PkgConfig::GTK)

#find_package(OpenGL REQUIRED COMPONENTS OpenGL EGL)
#find_package(OpenCV REQUIRED COMPONENTS
# core
# highgui
# imgproc 
# imgcodecs
#)
#include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries(${PLUGIN_NAME} PRIVATE
  # OpenGL::OpenGL
  EGL
  GLEW

  #opencv_core
  #opencv_highgui
  # opencv_imgproc
  # opencv_imgcodecs
  lapack
  cblas
)

# List of absolute paths to libraries that should be bundled with the plugin.
# This list could contain prebuilt libraries, or libraries created by an
# external build triggered from this build file.
set(flutter_gl_linux_bundled_libraries
  ""
  # PARENT_SCOPE
)

#message(STATUS "************* OpenCV_DIR = ${OpenCV_DIR}")
#message(STATUS "************* OpenCV_INCLUDE_DIRS = ${OpenCV_INCLUDE_DIRS}")
#message(STATUS "************* OpenCV_LIBS = ${OpenCV_LIBS}")

# target_compile_definitions(${PLUGIN_NAME} PRIVATE -DWITH_OPENCV=TRUE )

# set(CMAKE_EXE_LINKER_FLAGS "-Xlinker -v -v")
# target_compile_options(${PLUGIN_NAME} PRIVATE -v)




#Available <target>s are gles2, gles3, gles31, gles32, and gl. The default <target> is gles32
# add_compile_options(-DDEQP_TARGET=default -DGLCTS_GTF_TARGET=gles2)
# set(DEQP_GLES2_LIBRARIES   )
# set(DEQP_GLES3_LIBRARIES   )
# set(DEQP_GLES31_LIBRARIES  )
# set(DEQP_GLES32_LIBRARIES  )
# set(DEQP_EGL_LIBRARIES     )
# set(DEQP_OPENGL_LIBRARIES  )
