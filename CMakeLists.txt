cmake_minimum_required(VERSION 3.28)

# ---- Project ----
project(UntitledAdventureGame LANGUAGES CXX)

# Put built exe in build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Optional: build static libs by default (SFML will still be shared unless you build it static)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# ---- Dependencies: SFML 3 ----
include(FetchContent)
FetchContent_Declare(SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG        3.0.2
  GIT_SHALLOW    ON
  EXCLUDE_FROM_ALL
  SYSTEM
)
FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG        v3.11.3
  GIT_SHALLOW    ON
  EXCLUDE_FROM_ALL
  SYSTEM
)
FetchContent_MakeAvailable(SFML)
FetchContent_MakeAvailable(json)

# ---- Sources ----
# Collect .cpp files
file(GLOB_RECURSE SOURCES
  "${CMAKE_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_SOURCE_DIR}/src/core/*.cpp"
  "${CMAKE_SOURCE_DIR}/src/ui/*.cpp"
)

# Collect headers (not strictly required to build, but useful for IDEs)
file(GLOB_RECURSE HEADERS
  "${CMAKE_SOURCE_DIR}/include/*.h"
  "${CMAKE_SOURCE_DIR}/src/core/*.h"
  "${CMAKE_SOURCE_DIR}/src/ui/*.h"
)

# ---- Executable ----
# Use a simple target name; control the actual exe filename with OUTPUT_NAME below.
add_executable(game WIN32
  ${SOURCES}
  ${HEADERS}
)

# Name the produced .exe nicely (instead of game.exe)
set_target_properties(game PROPERTIES OUTPUT_NAME "UntitledAdventureGame")

target_include_directories(game PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_features(game PRIVATE cxx_std_17)

# Link SFML modules you use
target_link_libraries(game PRIVATE SFML::Graphics SFML::Audio nlohmann_json::nlohmann_json)

# If you’re building SFML statically, this define is commonly used.
if (WIN32)
  target_compile_definitions(game PRIVATE SFML_STATIC)
endif()

# ---- Windows resources (icon + version info) ----
# Put an app.rc next to this CMakeLists (root). It should contain the ICON and VS_VERSION_INFO blocks.
# The .rc should reference your icon at "src/assets/images/logo.ico".
if (WIN32)
  # Ensure the .rc file exists; add it to the target. Adjust path if you placed it elsewhere.
  set(APP_RC "${CMAKE_SOURCE_DIR}/app.rc")
  if (EXISTS "${APP_RC}")
    target_sources(game PRIVATE "${APP_RC}")
  else()
    message(WARNING "Windows resource file 'app.rc' not found. Task Manager will show the process name only.")
  endif()
endif()

# ---- Assets next to the exe ----
add_custom_command(TARGET game POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:game>/assets"
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          "${CMAKE_SOURCE_DIR}/src/assets"
          "$<TARGET_FILE_DIR:game>/assets"
  COMMENT "Copying assets to build directory"
)

# ---- Nice source groups for IDEs (optional) ----
source_group(TREE "${CMAKE_SOURCE_DIR}" FILES ${SOURCES} ${HEADERS})
