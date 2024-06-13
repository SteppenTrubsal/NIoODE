cmake_minimum_required(VERSION 3.28.0)
project(MishDZ VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB_RECURSE SOURCES "src/*.hpp")

add_executable(MishDZ ${SOURCES} "main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MishDZ PROPERTY CXX_STANDARD 20)
endif()