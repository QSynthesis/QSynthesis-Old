cmake_minimum_required(VERSION 3.17)
project(QSynthesis)

set(CMAKE_CXX_STANDARD 11)

FILE (GLOB ALL_SOURCES "*.cpp")
FILE (GLOB ALL_INCLUDES "*.hpp" "*.h")
SET (ALL_SRCS ${ALL_SOURCES} ${ALL_INCLUDES})

add_executable(QSynthesis ${ALL_SRCS} resources/res.rc resources/app.manifest)