cmake_minimum_required(VERSION 3.2)
project(ECS)

set(CMAKE_CXX_VERSION 20)

add_library(ECS
  src/Entity.cpp
  src/Manager.cpp
)

target_include_directories(ECS PUBLIC include/)
