# For lots of helpful commentary on the commands used this file, look
# at the CMakeLists.txt it was based on:
# https://github.com/juce-framework/JUCE/blob/master/examples/CMake/ConsoleApp/CMakeLists.txt

cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(TRACKTION_HELLO_WORLD VERSION 0.0.1)

add_subdirectory(tracktion_engine/modules/juce)
add_subdirectory(tracktion_engine/modules)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

juce_add_console_app(TracktionHelloWorld
    PRODUCT_NAME "Tracktion Hello World")

target_sources(TracktionHelloWorld
    PRIVATE
        main.cc)

target_compile_definitions(TracktionHelloWorld
    PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0)

target_link_libraries(TracktionHelloWorld
    PRIVATE
        tracktion::tracktion_engine
        juce::juce_core
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags
        ${CURSES_LIBRARIES})

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_link_libraries(TracktionHelloWorld PRIVATE "-latomic")
endif()
