cmake_minimum_required(VERSION 3.10.0)
project(logger VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
  logger.cpp
  main.cpp
)

set(HEADERS
    logger.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})