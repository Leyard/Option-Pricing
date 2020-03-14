cmake_minimum_required(VERSION 3.1)

project(Option-Pricing
        VERSION 0.1
        DESCRIPTION "Option pricing models implemented in C++"
        LANGUAGES CXX)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(options main.cc)
