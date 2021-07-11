cmake_minimum_required(VERSION 3.5)

project(ReLearning LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set( project_sources
    main.cpp
    filescan.cpp
    helpers.cpp)

add_executable(ReLearning main.cpp
    filescan.cpp
    helpers.cpp)
