cmake_minimum_required(VERSION 3.10)
project(main)
add_executable(main)
file(GLOB sources CONFIGURE_DEPENDS *.cpp *.h)
target_sources(main PUBLIC ${sources})
add_definitions("-Wall -g") #带警告信息和调试信息的