cmake_minimum_required(VERSION 3.20)
project(HelloKittyAdventure)

set(CMAKE_CXX_STANDARD 17)

set(SFML_STATIC_LIBRARIES FALSE)
set(SFML_DIR "C:/Users/user/OneDrive/Desktop/SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.1/lib/cmake/SFML")

find_package(SFML 2 REQUIRED COMPONENTS graphics audio window system)

add_executable(HelloKittyAdventure main.cpp
)

target_link_libraries(HelloKittyAdventure sfml-graphics sfml-audio sfml-window sfml-system)