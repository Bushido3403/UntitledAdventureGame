# ***Document Map***

### General Overview

Welcome to a tour of the project’s file system.
The whole thing is organized into **four main folders**, each with its own job:

* **include**
  All the header files. Every `.h` that defines the structure for its matching `.cpp`.

* **src/core**
  The “engine room.” These are the core `.cpp` files that keep the game running: the Game Engine, Scene Manager, Resource Manager, Script Parser, and other foundational systems.

* **src/ui**
  Everything related to the user interface lives here: buttons, dialog boxes, layout logic, menus, settings screens, all the stuff the player actually clicks on.

* **src/assets**
  Fonts, images, sound effects, and scene scripts. Each category has its own subfolder so things stay neat instead of turning into a junk drawer.

That’s a high-level map. Below is the full breakdown of every file.

### File Map:

#### include/
- [`Button.h`](include/Button.h)
- [`CustomWindow.h`](include/CustomWindow.h)
- [`DialogBox.h`](include/DialogBox.h)
- [`GameEngine.h`](include/GameEngine.h)
- [`GameState.h`](include/GameState.h)
- [`LayoutManager.h`](include/LayoutManager.h)
- [`MainMenuState.h`](include/MainMenuState.h)
- [`PlayingState.h`](include/PlayingState.h)
- [`ResourceManager.h`](include/ResourceManager.h)
- [`SceneManager.h`](include/SceneManager.h)
- [`ScriptParser.h`](include/ScriptParser.h)
- [`SettingsState.h`](include/SettingsState.h)
- [`StartState.h`](include/StartState.h)
- [`Types.h`](include/Types.h)

#### src/
- [`main.cpp`](src/main.cpp)

#### src/core/
- [`CustomWindow.cpp`](src/core/CustomWindow.cpp)
- [`GameEngine.cpp`](src/core/GameEngine.cpp)
- [`PlayingState.cpp`](src/core/PlayingState.cpp)
- [`ResourceManager.cpp`](src/core/ResourceManager.cpp)
- [`SceneManager.cpp`](src/core/SceneManager.cpp)
- [`ScriptParser.cpp`](src/core/ScriptParser.cpp)
- [`save_data.json`](src/core/save_data.json)

#### src/ui/
- [`Button.cpp`](src/ui/Button.cpp)
- [`DialogBox.cpp`](src/ui/DialogBox.cpp)
- [`LayoutManager.cpp`](src/ui/LayoutManager.cpp)
- [`MainMenuState.cpp`](src/ui/MainMenuState.cpp)
- [`SettingsState.cpp`](src/ui/SettingsState.cpp)
- [`StartState.cpp`](src/ui/StartState.cpp)

#### src/assets/
- **fonts/**
  - (font files)
- **images/**
  - (image files including logo.ico)
- **scripts/**
  - [`intro.json`](src/assets/scripts/intro.json)
- **sfx/**
  - (sound effect files)
- 

#### Additional Sections (outside the 4 main folders):

#### Root Directory Files:
- [`CMakeLists.txt`](CMakeLists.txt) - Build configuration
- [`README.md`](README.md) - Project documentation
- [`LICENSE.md`](LICENSE.md) - License information
- [`DOCMAP.md`](DOCMAP.md) - You are here!
- [`.gitignore`](.gitignore) - Git ignore rules
- [`app.rc`](app.rc) - Windows resource file (icon and version info)
- [`Untitled Adventure Game.lnk`](Untitled Adventure Game.lnk) - Shortcut file to .exe once the project has been built using CMake

#### Build Directory:
- [`build/`](build/) - CMake build output (excluded from git)

#### Configuration:
- [`.vscode/settings.json`](.vscode/settings.json) - VS Code settings
- [`.github/workflows/`](.github/workflows/) - GitHub Actions workflows

### File Descriptions:

#### Core System Files:
- **GameEngine** - Main game loop and state management
- **CustomWindow** - Custom window implementation with titlebar
- **ResourceManager** - Asset loading and caching system
- **ScriptParser** - JSON script parsing for game scenes
- **SceneManager** - Scene loading and management
- **ChatGPT** & **ChatGPTError** - OpenAI API integration (currently unused)

#### UI Components:
- **Button** - Interactive button widget
- **DialogBox** - Text display with speaker names
- **LayoutManager** - Responsive layout calculations

#### Game States:
- **MainMenuState** - Main menu screen
- **StartState** - Game start placeholder
- **SettingsState** - Volume and settings control
- **PlayingState** - Active gameplay screen

#### Data Structures:
- **Types** - OpenAI API type definitions
- **GameState** - Abstract base class for all game states