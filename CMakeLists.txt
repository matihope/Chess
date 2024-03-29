cmake_minimum_required(VERSION 3.18.1)

project(chess VERSION 0.1.0)
add_compile_definitions("DEBUG=$<CONFIG:Debug>")

# SFML
find_package(SFML 2 REQUIRED COMPONENTS window audio graphics system network)
link_libraries(sfml-graphics sfml-window sfml-system sfml-audio)

# Nlohmann json
find_package(nlohmann_json 3.11.2 REQUIRED)
link_libraries(nlohmann_json::nlohmann_json)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else ()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Werror -Wextra -pedantic -Wno-unused-parameter)
endif ()
add_compile_options(-std=c++20)

# Link engine
add_subdirectory(Engine)
link_libraries(Engine)
link_directories(Engine)

# Link game's code
add_subdirectory(src)
link_libraries(Game)
link_directories(Game)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(${PROJECT_NAME} main.cpp)
