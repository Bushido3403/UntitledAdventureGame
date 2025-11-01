cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Collect all source files
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/core/*.cpp"
    "src/ui/*.cpp"
)

# Collect all header files
file(GLOB_RECURSE HEADERS 
    "include/*.h"
    "src/core/*.h"
    "src/ui/*.h"
)

add_executable(main 
    src/main.cpp
    src/core/GameEngine.cpp
    src/core/ResourceManager.cpp
    src/core/CustomWindow.cpp
    src/ui/Button.cpp
    src/ui/MainMenuState.cpp
    src/ui/StartState.cpp
    src/ui/SettingsState.cpp
)
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics SFML::Audio)

if(WIN32)
    target_compile_definitions(main PRIVATE SFML_STATIC)
endif()

# Copy assets to build directory
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:main>/assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/src/assets
            $<TARGET_FILE_DIR:main>/assets
    COMMENT "Copying assets to build directory"
)
