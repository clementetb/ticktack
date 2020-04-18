# Sets the minimum version of CMake required to build your native library.
# This ensures that a certain set of CMake features is available to
# your build.

cmake_minimum_required(VERSION 3.4.1)

# Specifies a library name, specifies whether the library is STATIC or
# SHARED, and provides relative paths to the source code. You can
# define multiple libraries by adding multiple add_library() commands,
# and CMake builds them for you. When you build your app, Gradle
# automatically packages shared libraries with your APK.

add_library( # Specifies the name of the library.
  ticktack_jni_lib
  # Sets the library as a shared library.
  SHARED
  # Provides a relative path to your source file(s).
  ticktack-jni.cpp)


# Sets lib_src_DIR to the path of the target CMake project.
set( ticktack_src_DIR ../../../../../ticktack-core/ )

# Sets lib_build_DIR to the path of the desired output directory.
set( ticktack_build_DIR ../../../../../ticktack-core/build/ )
file(MAKE_DIRECTORY ${ticktack_build_DIR})

# Adds the CMakeLists.txt file located in the specified directory
# as a build dependency.
add_subdirectory( # Specifies the directory of the CMakeLists.txt file.
  ${ticktack_src_DIR}
  # Specifies the directory for the build outputs.
  ${ticktack_build_DIR} )
# Adds the output of the additional CMake build as a prebuilt static
include_directories( ${ticktack_src_DIR}/include )

# Links the top-level CMake build output against lib_gmath.
target_link_libraries( ticktack_jni_lib ticktack_lib )
