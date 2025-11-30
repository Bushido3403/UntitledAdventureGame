cmake_minimum_required(VERSION 3.28)

project(UntitledAdventureGame LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Force static linking
set(BUILD_SHARED_LIBS OFF)
set(SFML_STATIC_LIBRARIES TRUE)

# Add static linking flags for MinGW
if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
endif()

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
# FetchContent_Declare(cpr
#   GIT_REPOSITORY https://github.com/libcpr/cpr.git
#   GIT_TAG        1.10.5
#   GIT_SHALLOW    ON
#   EXCLUDE_FROM_ALL
#   SYSTEM
# )
FetchContent_MakeAvailable(SFML)
FetchContent_MakeAvailable(json)
# FetchContent_MakeAvailable(cpr)

# Sources
set(CORE_SOURCES
  "${CMAKE_SOURCE_DIR}/src/main.cpp"
  "${CMAKE_SOURCE_DIR}/src/core/GameEngine.cpp"
  "${CMAKE_SOURCE_DIR}/src/core/CustomWindow.cpp"
  "${CMAKE_SOURCE_DIR}/src/core/ResourceManager.cpp"
  "${CMAKE_SOURCE_DIR}/src/core/ScriptParser.cpp"
  "${CMAKE_SOURCE_DIR}/src/core/PlayingState.cpp"
  "${CMAKE_SOURCE_DIR}/src/core/SceneManager.cpp"
  "${CMAKE_SOURCE_DIR}/src/core/GameStateManager.cpp"
)

set(UI_SOURCES
  "${CMAKE_SOURCE_DIR}/src/ui/Button.cpp"
  "${CMAKE_SOURCE_DIR}/src/ui/MainMenuState.cpp"
  "${CMAKE_SOURCE_DIR}/src/ui/StartState.cpp"
  "${CMAKE_SOURCE_DIR}/src/ui/SettingsState.cpp"
  "${CMAKE_SOURCE_DIR}/src/ui/DialogBox.cpp"
  "${CMAKE_SOURCE_DIR}/src/ui/LayoutManager.cpp"
  "${CMAKE_SOURCE_DIR}/src/ui/PlayingStateUI.cpp"
)

set(HEADERS
  "${CMAKE_SOURCE_DIR}/include/GameEngine.h"
  "${CMAKE_SOURCE_DIR}/include/GameState.h"
  "${CMAKE_SOURCE_DIR}/include/CustomWindow.h"
  "${CMAKE_SOURCE_DIR}/include/ResourceManager.h"
  "${CMAKE_SOURCE_DIR}/include/ScriptParser.h"
  "${CMAKE_SOURCE_DIR}/include/PlayingState.h"
  "${CMAKE_SOURCE_DIR}/include/SceneManager.h"
  "${CMAKE_SOURCE_DIR}/include/GameStateManager.h"
  "${CMAKE_SOURCE_DIR}/include/PlayingStateUI.h"
  "${CMAKE_SOURCE_DIR}/include/Button.h"
  "${CMAKE_SOURCE_DIR}/include/MainMenuState.h"
  "${CMAKE_SOURCE_DIR}/include/StartState.h"
  "${CMAKE_SOURCE_DIR}/include/SettingsState.h"
  "${CMAKE_SOURCE_DIR}/include/DialogBox.h"
  "${CMAKE_SOURCE_DIR}/include/LayoutManager.h"
)

# ---- Executable ----
add_executable(game
  ${CORE_SOURCES}
  ${UI_SOURCES}
  ${HEADERS}
)

set_target_properties(game PROPERTIES OUTPUT_NAME "UntitledAdventureGame")

target_include_directories(game PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_features(game PRIVATE cxx_std_17)

# Link SFML modules
target_link_libraries(game PRIVATE SFML::Graphics SFML::Audio nlohmann_json::nlohmann_json)# cpr::cpr)

if (WIN32)
  target_compile_definitions(game PRIVATE SFML_STATIC)
endif()

# ---- Windows resources (icon + version info) ----
if (WIN32)
  set(APP_RC "${CMAKE_SOURCE_DIR}/app.rc")
  if (EXISTS "${APP_RC}")
    target_sources(game PRIVATE "${APP_RC}")
  else()
    message(WARNING "Windows resource file 'app.rc' not found.")
  endif()
endif()

# ---- Assets next to the exe ----
add_custom_target(copy_assets ALL
  COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:game>/assets"
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          "${CMAKE_SOURCE_DIR}/src/assets"
          "$<TARGET_FILE_DIR:game>/assets"
  COMMENT "Copying assets to build directory"
)
add_dependencies(game copy_assets)

# ---- Nice source groups for IDEs ----
source_group(TREE "${CMAKE_SOURCE_DIR}" FILES ${CORE_SOURCES} ${UI_SOURCES} ${HEADERS})
