# Untitled Adventure Game

A 2D text-oriented adventure game built with C++ and SFML 3.x.
Storyline heavily based on Norse mythology.

## About

Untitled Adventure Game is my C++ game featuring a custom window system with a draggable titlebar, fullscreen support, and an intuitive menu system. It's been built for my CS 135 class under Prof. Damien Ennis using a cumulation of documents from the web from sources such as StackOverflow, the SFML documentation, and various C++ programming tutorials.

## Helpful Links

👉 **Full Documentation (Live Site):** [untitledgame.nodifyr.io](https://untitledgame.nodifyr.io)  
*Note: GitHub README links always open in the same tab by default — use Ctrl/Cmd-click or middle-click to open in a new tab.*

➡️ **[Latest Windows Build Download (Win11 x64)](https://github.com/Bushido3403/UntitledAdventureGame/releases/latest)**  
Contains the compiled `.exe` and required files.

## Features I'm Proud Of

- **Custom Window System**: Borderless window with custom titlebar, drag support, and fullscreen toggle
- **State Management**: Clean state-based architecture supporting multiple game screens
- **Settings System**: Adjustable music volume with a visual slider interface
- **Resource Management**: Centralized loading and caching of textures, fonts, sounds, and music through SFML
- **Inventory System**: Grid-based inventory with tooltips and item management
- **Save System**: JSON-based game state persistence with flag tracking

## Building

- Install CMake Tools extension on VS Code
- Press the build button in the toolbar .-.
- (If this doesn't work then uh.... "It worked fine on my PC" xD)

### Prerequisites for development

- C++17 compatible compiler
- CMake 3.28 or higher
- Git/Github
- A burning love for masochism
- Significantly higher qualifications than a CS-135 class

# ***Document Map***

### General Overview

Welcome to a tour of the project's file system.
The whole thing is organized into **four main folders**, each with its own job:

* **include**
  All the header files. Every `.h` that defines the structure for its matching `.cpp`.

* **src/core**
  The "engine room." These are the core `.cpp` files that keep the game running: the Game Engine, Scene Manager, Resource Manager, Script Parser, and other foundational systems.

* **src/ui**
  Everything related to the user interface lives here: buttons, dialog boxes, layout logic, menus, settings screens, all the stuff the player actually clicks on.

* **src/assets**
  Fonts, images, sound effects, and scene scripts. Each category has its own subfolder so things stay neat instead of turning into a junk drawer.

That's a high-level map. Below is the full breakdown of every file.

### File Map:

#### include/
- [`Button.h`](include/Button.h)
- [`ConfirmationDialog.h`](include/ConfirmationDialog.h)
- [`CustomWindow.h`](include/CustomWindow.h)
- [`DialogBox.h`](include/DialogBox.h)
- [`GameEngine.h`](include/GameEngine.h)
- [`GameState.h`](include/GameState.h)
- [`GameStateManager.h`](include/GameStateManager.h)
- [`InventorySystem.h`](include/InventorySystem.h)
- [`InventoryUI.h`](include/InventoryUI.h)
- [`LayoutManager.h`](include/LayoutManager.h)
- [`MainMenuState.h`](include/MainMenuState.h)
- [`PlayingState.h`](include/PlayingState.h)
- [`PlayingStateUI.h`](include/PlayingStateUI.h)
- [`ResourceManager.h`](include/ResourceManager.h)
- [`SceneManager.h`](include/SceneManager.h)
- [`ScriptParser.h`](include/ScriptParser.h)
- [`SettingsState.h`](include/SettingsState.h)
- [`StartState.h`](include/StartState.h)

#### src/
- [`main.cpp`](src/main.cpp)

#### src/core/
- [`CustomWindow.cpp`](src/core/CustomWindow.cpp)
- [`GameEngine.cpp`](src/core/GameEngine.cpp)
- [`GameStateManager.cpp`](src/core/GameStateManager.cpp)
- [`InventorySystem.cpp`](src/core/InventorySystem.cpp)
- [`PlayingState.cpp`](src/core/PlayingState.cpp)
- [`ResourceManager.cpp`](src/core/ResourceManager.cpp)
- [`SceneManager.cpp`](src/core/SceneManager.cpp)
- [`ScriptParser.cpp`](src/core/ScriptParser.cpp)
- [`save_data.json`](src/core/save_data.json)

#### src/ui/
- [`Button.cpp`](src/ui/Button.cpp)
- [`ConfirmationDialog.cpp`](src/ui/ConfirmationDialog.cpp)
- [`DialogBox.cpp`](src/ui/DialogBox.cpp)
- [`InventoryUI.cpp`](src/ui/InventoryUI.cpp)
- [`LayoutManager.cpp`](src/ui/LayoutManager.cpp)
- [`MainMenuState.cpp`](src/ui/MainMenuState.cpp)
- [`PlayingStateUI.cpp`](src/ui/PlayingStateUI.cpp)
- [`SettingsState.cpp`](src/ui/SettingsState.cpp)
- [`StartState.cpp`](src/ui/StartState.cpp)

#### src/assets/
- **fonts/**
  - (font files)
- **images/**
  - (image files including logo.ico)
- **items/**
  - [`items.json`](src/assets/items/items.json) - Item definitions
- **scripts/**
  - [`intro.json`](src/assets/scripts/intro.json)
- **sfx/**
  - (sound effect files)

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
  - Owns the custom window and state stack (main menu, settings, gameplay, etc.)
  - Routes SFML events to the active state and handles fullscreen/resize updates
  - Centralizes resource loading (fonts, textures, sounds, music) and music playback

- **CustomWindow** - Custom window implementation with titlebar
  - Replaces the OS border with a draggable titlebar and custom close/fullscreen buttons
  - Manages borderless fullscreen toggling while preserving previous windowed size/position
  - Hides the system cursor and renders a textured in‑game cursor every frame

- **ResourceManager** - Asset loading and caching system
  - Loads textures, fonts, sound buffers, and streaming music on demand by string ID
  - Stores all resources in maps to avoid duplicate loads and share them across states
  - Provides simple `get*` accessors, logging errors when assets fail to load

- **ScriptParser** - JSON script parsing for game scenes
  - Reads narrative scripts (scenes, choices, metadata) from JSON via nlohmann::json
  - Supports conditional choices, stat/flag effects, and item rewards from script
  - Exposes helpers to find scenes by ID for the SceneManager

- **SceneManager** - Scene loading and management
  - Owns the currently loaded script and active scene pointer
  - Loads per‑scene background graphics, with fallback attempts for JPEG/PNG
  - Handles "END" sentinel scenes and notifies listeners when a script completes

- **GameStateManager** - Game state persistence and flag management
  - Tracks story flags, player stats, current script, and current scene in memory
  - Applies script‑driven effects (set/clear flags, modify stats, grant items)
  - Saves/loads full game state (including inventory) to/from `assets/save_data.json`

- **InventorySystem** - Item management and inventory logic
  - Loads item definitions from `assets/items/items.json` and preloads their textures
  - Handles stackable items, max stack sizes, adds/removes items and by index
  - Serializes and deserializes the player’s inventory into the save file

#### UI Components:
- **Button** - Interactive button widget
  - Handles hover and click states with visual feedback (color changes)
  - Supports both texture-based and text-only buttons
  - Plays a shared click sound effect when activated

- **DialogBox** - Text display with speaker names
  - Supports hex color parsing for speaker name styling
  - Automatically wraps dialog text to fit a configurable width
  - Provides access to text bounds for layout-aware positioning

- **LayoutManager** - Responsive layout calculations
  - Computes positions/sizes for dialog, graphics, and stats regions based on window size
  - Maintains minimum dialog height and 16:9 aspect ratio for graphics area
  - Provides scaled character sizes for consistent typography across resolutions

- **ConfirmationDialog** - Modal confirmation dialog widget
  - Draws a dimmed fullscreen overlay to block background interaction
  - Wraps long confirmation messages and centers them within the dialog box
  - Renders inline colored key hints ("Y" green, "N" red) for clarity

- **InventoryUI** - Visual inventory grid with tooltips and interaction
  - Builds a scrollable grid of item slots with hover highlighting
  - Shows item tooltips with name, description, and smart edge-avoidance
  - Renders item quantity overlays and scales icons to fit each cell

- **PlayingStateUI** - Layout and rendering for the playing state screen
  - Manages dialog area, graphics box, stats area, and inventory panel positioning
  - Dynamically lays out choice buttons in one or two columns depending on count
  - Auto-resizes/wraps dialog text to avoid overlapping the choice buttons

#### Game States:
- **MainMenuState** - Main menu screen
  - Displays background, logo, and title textures sized to the current window
  - Hosts "Start" and "Settings" buttons wired into the GameEngine callbacks
  - Plays a fade‑to‑black transition when starting a new game

- **StartState** - Game start placeholder
  - Shows a simple "Game Starting..." message centered in the window
  - Listens for ESC to return to the main menu via a callback
  - Re-centers UI text whenever the window is resized

- **SettingsState** - Volume and settings control
  - Renders a title, volume label, and a horizontal slider for music volume
  - Supports clicking and dragging the slider handle to adjust SFML music volume
  - Updates the numeric volume text and slider handle position in real time

- **PlayingState** - Active gameplay screen
  - Owns SceneManager, GameStateManager, InventorySystem, and PlayingStateUI
  - Handles scene transitions with fade in/out and script completion callbacks
  - Builds and updates choice buttons, inventory actions, and confirmation dialogs

#### Data Structures:
- **GameState** - Abstract base class for all game states
  - Provides a common interface: `handleEvent`, `update`, `draw`, `updatePositions`
  - Exposes a `getType()` enum so GameEngine can route callbacks by state
  - Enables stacking/changing states through `std::unique_ptr<GameState>`

- **GameScript / Scene / Choice / Effects / Condition** (from ScriptParser.h)
  - Represent parsed JSON script data: scenes, choices, metadata, and effects
  - `Condition` encodes flag requirements for unlocking specific choices
  - `Effects` describe mutations to flags, stats, and inventory when a scene resolves

- **InventoryItem / ItemDefinition** (from InventorySystem.h)
  - `InventoryItem` tracks an item id and current quantity in the player’s inventory
  - `ItemDefinition` stores per‑item stats: name, description, stackable, max stack size, etc.
  - Loaded once from `assets/items/items.json` and reused across the game
