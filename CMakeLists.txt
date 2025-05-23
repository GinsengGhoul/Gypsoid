cmake_minimum_required(VERSION 3.29.0)
project(Gypsoid VERSION 0.0.01)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define option to use Clang
option(USE_CLANG "Use Clang compiler instead of the default system compiler" ON)

# Check if the compiler variables are already set in the cache
if(NOT DEFINED CMAKE_C_COMPILER AND NOT DEFINED CMAKE_CXX_COMPILER)
    # Set initial compiler flags
    set(INITIAL_C_COMPILER ${CMAKE_C_COMPILER})
    set(INITIAL_CXX_COMPILER ${CMAKE_CXX_COMPILER})

    # Check if the user wants to use Clang
    if(USE_CLANG)
        # Find Clang compiler
        find_program(CLANG_EXECUTABLE NAMES clang)

        if(CLANG_EXECUTABLE)
            message(STATUS "Clang compiler found: ${CLANG_EXECUTABLE}")
            # Set C and C++ compilers to Clang
            set(CMAKE_C_COMPILER ${CLANG_EXECUTABLE} CACHE FILEPATH "C Compiler" FORCE)
            set(CMAKE_CXX_COMPILER ${CLANG_EXECUTABLE} CACHE FILEPATH "C++ Compiler" FORCE)
        else()
            message(FATAL_ERROR "Clang compiler not found. Please make sure Clang is installed.")
        endif()
    endif()
endif()

#options
#-march
#-march=native
#i386 i486 i586 i686
#x86-64 x86-64-v2 x86-64-v3 x86-64-v4
option(OPTIMIZE_FOR_GENERIC "Build with -march=generic" OFF)
option(OPTIMIZE_FOR_NATIVE "Build with -march=native" OFF)
option(OPTIMIZE_FOR_I486 "Build with -march=i486" OFF)
option(OPTIMIZE_FOR_I586 "Build with -march=i586" OFF)
option(OPTIMIZE_FOR_I686 "Build with -march=i686" OFF)
option(OPTIMIZE_FOR_X86-64 "Build with -march=x86_64" OFF)
option(OPTIMIZE_FOR_X86-64-V2 "Build with -march=x86_64-v2" OFF)
option(OPTIMIZE_FOR_X86-64-V3 "Build with -march=x86_64-v3" OFF)
option(OPTIMIZE_FOR_X86-64-V4 "Build with -march=x86_64-v4" OFF)

# Append build settings
if(OPTIMIZE_FOR_NATIVE)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native")
elseif(OPTIMIZE_FOR_I486)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32 -march=i486")
elseif(OPTIMIZE_FOR_I586)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32 -march=i586")
elseif(OPTIMIZE_FOR_I686)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32 -march=i686")
elseif(OPTIMIZE_FOR_X86_64)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=x86-64")
elseif(OPTIMIZE_FOR_X86_64_V2)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=x86-64-v2")
elseif(OPTIMIZE_FOR_X86_64_V3)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=x86-64-v3")
elseif(OPTIMIZE_FOR_X86_64_V4)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=x86-64-v4")
else()
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=x86-64 -mtune=generic")
endif()

# set CFLAGS=CXXFLAGS
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}")

# append Warnings
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-incompatible-pointer-types")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-unused-variable -Wno-unused-parameter")

# Enable threading explicitly
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Add Threads to link libraries
list(APPEND EXTRA_LIBS Threads::Threads)

find_package(OpenGL REQUIRED)

# include SDL
add_subdirectory(SDL
                 GLES2
)

include_directories(Gypsoid
                    "SDL/include"
                    GLES2
                    ${OPENGL_INCLUDE_DIR}
                    )
add_definitions(-D_REENTRANT)

# source files
# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

file(GLOB SOURCES "src/*.cxx")

# Debug build
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
  message(STATUS "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")
  message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
  add_executable(Gypsoid_Debug ${SOURCES})
  target_compile_definitions(Gypsoid_Debug PRIVATE)
  target_link_libraries(Gypsoid_Debug SDL3::SDL3 OpenGL::GL)
  # Allow access to files inside the BinaryDIR
  target_include_directories(Gypsoid_Debug PRIVATE "${PROJECT_BINARY_DIR}")
endif()

# Release build
if(CMAKE_BUILD_TYPE STREQUAL Release)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
  message(STATUS "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")
  message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
  add_executable(Gypsoid ${SOURCES})
  target_compile_definitions(Gypsoid PRIVATE RELEASE)
  target_link_libraries(Gypsoid SDL3::SDL3 OpenGL::GL)
  # Allow access to files inside the BinaryDIR
  target_include_directories(Gypsoid PRIVATE "${PROJECT_BINARY_DIR}")
endif()
