cmake_minimum_required(VERSION 3.28)
project(Breakout)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(SFML_DIR C:/SFML/lib/cmake/SFML)
endif (WIN32)

find_package(SFML 2 COMPONENTS graphics audio REQUIRED)

add_executable(Breakout main.cpp
        main.cpp
)


target_link_libraries(Breakout sfml-graphics sfml-audio)