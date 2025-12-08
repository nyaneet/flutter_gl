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

target_link_libraries(${PLUGIN_NAME} PRIVATE
  GLEW
)

# List of absolute paths to libraries that should be bundled with the plugin.
# This list could contain prebuilt libraries, or libraries created by an
# external build triggered from this build file.
set(flutter_gl_linux_bundled_libraries
  ""
  # PARENT_SCOPE
)
