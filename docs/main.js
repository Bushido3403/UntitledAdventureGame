// ===== CONFIG: Data & UX behavior =====
// All content lives in PAGE_DATA below. To reuse this template,
// replace the PAGE_DATA object with your own data (same shape).

// How far down the page (in px) before the back-to-top button appears
const BACK_TO_TOP_THRESHOLD = 260;

// Scroll offset used when detecting the "active" section for the side nav
const SCROLL_OFFSET_PX = 120;

// How long (ms) the "Copied!" label stays before reverting
const COPY_RESET_MS = 900;

// ===== DATA: Page content (inline JSON-style object) =====

const PAGE_DATA = {
  "project": {
    "title": "Untitled Adventure Game",
    "subtitle": "2D text-oriented | C++ · SFML 3.x",
    "pill": "Norse-inspired story",
    "topChip": "Single-page project overview"
  },
  "hero": {
    "heading": "Untitled Adventure Game",
    "tagline": "A 2D text-oriented adventure game built with C++ and SFML 3.x. Storyline heavily based on Norse mythology.",
    "metaTags": [
      "Language: C++17",
      "Framework: SFML 3.x",
      "Class: CS 135 – Prof. Damien Ennis"
    ],
    "badges": [
      "Custom window system",
      "State-based architecture",
      "Resource & settings management",
      "Inventory & save system"
    ],
    "snapshotLabel": "Build snapshot",
    "snapshotBadge": "CMake · Git · SFML",
    "grid": [
      {
        "label": "Core tech",
        "value": "C++17 · SFML 3.x",
        "note": "Windowing, input, audio, and rendering"
      },
      {
        "label": "Architecture",
        "value": "State-driven",
        "note": "Multiple screens & game states"
      },
      {
        "label": "Build system",
        "value": "CMake ≥ 3.28",
        "note": "VS Code friendly"
      },
      {
        "label": "Project flavor",
        "value": "Norse mythology",
        "note": "Text-oriented adventure vibe"
      }
    ]
  },
  "navigationTitle": "On this page",
  "sections": [
    {
      "id": "about",
      "navLabel": "About",
      "title": "About",
      "type": "paragraphs",
      "body": [
        "Untitled Adventure Game is my C++ game featuring a custom window system with a draggable titlebar, fullscreen support, and an intuitive menu system. It's been built for my CS 135 class under Prof. Damien Ennis using a cumulation of documents from the web from sources such as StackOverflow, the SFML documentation, and various C++ programming tutorials."
      ]
    },
    {
      "id": "helpful-links",
      "navLabel": "Helpful Links",
      "title": "Helpful Links",
      "type": "helpfulLinks"
    },
    {
      "id": "design-approach",
      "navLabel": "Design Approach",
      "title": "Design Approach",
      "type": "designApproach",
      "body": [
        "This game was built with a **state-driven architecture** at its core. Every screen, main menu, settings, gameplay, is its own isolated state that can be pushed onto or popped from a stack. This makes transitions clean and keeps concerns separated.",
        "The **resource management** system uses lazy loading and caching. When a texture or sound is requested, it's loaded once and stored in a map for reuse. This avoids duplicate loads and keeps memory usage predictable.",
        "For the **UI layer**, I avoided a heavyweight framework. Instead, I built lightweight components (buttons, dialog boxes, confirmation modals) that own their own rendering and input handling. Each widget knows how to draw itself and respond to mouse events, which makes the codebase modular and easy to extend.",
        "The **scene system** is entirely data-driven. All narrative content, choices, and branching logic live in JSON files. The `ScriptParser` reads these scripts, and the `SceneManager` handles transitions. This separation means I can write new story content without touching C++ code.",
        "**Game state persistence** is handled through a single JSON save file. Player stats, inventory, story flags, and current position are serialized and deserialized on demand. The `GameStateManager` acts as the single source of truth, and all systems query or modify state through it.",
        "The **custom window system** was a deliberate choice. I wanted full control over the titlebar, fullscreen behavior, and cursor rendering. By creating a borderless SFML window and drawing my own UI chrome, I got pixel-perfect control over the player experience.",
        "Throughout development, I prioritized **readability over cleverness**. Class responsibilities are narrow, dependencies are explicit, and there's minimal inheritance. This made debugging easier and kept the codebase approachable for someone coming back to it weeks later."
      ]
    },
    {
      "id": "features",
      "navLabel": "Features I'm Proud Of",
      "title": "Features I'm Proud Of",
      "type": "features",
      "items": [
        {
          "strong": "Custom Window System",
          "text": "Borderless window with custom titlebar, drag support, and fullscreen toggle"
        },
        {
          "strong": "State Management",
          "text": "Clean state-based architecture supporting multiple game screens"
        },
        {
          "strong": "Settings System",
          "text": "Adjustable music volume with a visual slider interface"
        },
        {
          "strong": "Resource Management",
          "text": "Centralized loading and caching of textures, fonts, sounds, and music through SFML"
        },
        {
          "strong": "Inventory System",
          "text": "Grid-based inventory with tooltips and item management"
        },
        {
          "strong": "Save System",
          "text": "JSON-based game state persistence with flag tracking"
        }
      ],
      "chips": [
        "Borderless window",
        "Draggable titlebar",
        "Fullscreen toggle",
        "Volume sliders",
        "Texture & sound caching",
        "Grid inventory",
        "JSON save system"
      ]
    },
    {
      "id": "building",
      "navLabel": "Building",
      "title": "Building",
      "type": "building"
    },
    {
      "id": "gallery",
      "navLabel": "Gallery",
      "title": "Gallery",
      "type": "gallery"
    },
    {
      "id": "prereqs",
      "navLabel": "Prerequisites",
      "title": "Prerequisites for development",
      "type": "bullets",
      "items": [
        "C++17 compatible compiler",
        "CMake 3.28 or higher",
        "Git/GitHub",
        "A burning love for masochism",
        "Significantly higher qualifications than a CS-135 class"
      ]
    },
    {
      "id": "docmap",
      "navLabel": "Document Map",
      "title": "Document Map",
      "type": "fileMap"
    },
    {
      "id": "file-descriptions",
      "navLabel": "File Descriptions",
      "title": "File Descriptions",
      "type": "fileDescriptions"
    },
    {
      "id": "fun-fact",
      "navLabel": "Fun Fact",
      "title": "🎮 Fun Fact",
      "type": "funFact",
      "body": [
        "It IS in fact possible to lose the game. There are 3 different endings in total.",
        "Hint: right click to drop items!"
      ]
    }
  ],
  "fileMap": {
    "introParagraphs": [
      "Welcome to a tour of the project's file system. The whole thing is organized into four main folders, each with its own job:"
    ],
    "folderOverview": [
      {
        "name": "include",
        "description": "All the header files. Every .h that defines the structure for its matching .cpp."
      },
      {
        "name": "src/core",
        "description": "The \"engine room.\" These are the core .cpp files that keep the game running: the Game Engine, Scene Manager, Resource Manager, Script Parser, and other foundational systems."
      },
      {
        "name": "src/ui",
        "description": "Everything related to the user interface lives here: buttons, dialog boxes, layout logic, menus, settings screens, all the stuff the player actually clicks on."
      },
      {
        "name": "src/assets",
        "description": "Fonts, images, sound effects, and scene scripts. Each category has its own subfolder so things stay neat instead of turning into a junk drawer."
      }
    ],
    "afterOverviewText": "That's a high-level map. Below is the full breakdown of every file.",
    "groups": [
      {
        "id": "include",
        "title": "include/",
        "tag": "Header interfaces",
        "items": [
          {
            "pathPrefix": "include/",
            "name": "Button.h",
            "href": "include/Button.h",
            "copyPath": "include/Button.h"
          },
          {
            "pathPrefix": "include/",
            "name": "ConfirmationDialog.h",
            "href": "include/ConfirmationDialog.h",
            "copyPath": "include/ConfirmationDialog.h"
          },
          {
            "pathPrefix": "include/",
            "name": "CustomWindow.h",
            "href": "include/CustomWindow.h",
            "copyPath": "include/CustomWindow.h"
          },
          {
            "pathPrefix": "include/",
            "name": "DialogBox.h",
            "href": "include/DialogBox.h",
            "copyPath": "include/DialogBox.h"
          },
          {
            "pathPrefix": "include/",
            "name": "GameEngine.h",
            "href": "include/GameEngine.h",
            "copyPath": "include/GameEngine.h"
          },
          {
            "pathPrefix": "include/",
            "name": "GameState.h",
            "href": "include/GameState.h",
            "copyPath": "include/GameState.h"
          },
          {
            "pathPrefix": "include/",
            "name": "GameStateManager.h",
            "href": "include/GameStateManager.h",
            "copyPath": "include/GameStateManager.h"
          },
          {
            "pathPrefix": "include/",
            "name": "InventorySystem.h",
            "href": "include/InventorySystem.h",
            "copyPath": "include/InventorySystem.h"
          },
          {
            "pathPrefix": "include/",
            "name": "InventoryUI.h",
            "href": "include/InventoryUI.h",
            "copyPath": "include/InventoryUI.h"
          },
          {
            "pathPrefix": "include/",
            "name": "LayoutManager.h",
            "href": "include/LayoutManager.h",
            "copyPath": "include/LayoutManager.h"
          },
          {
            "pathPrefix": "include/",
            "name": "MainMenuState.h",
            "href": "include/MainMenuState.h",
            "copyPath": "include/MainMenuState.h"
          },
          {
            "pathPrefix": "include/",
            "name": "PlayingState.h",
            "href": "include/PlayingState.h",
            "copyPath": "include/PlayingState.h"
          },
          {
            "pathPrefix": "include/",
            "name": "PlayingStateUI.h",
            "href": "include/PlayingStateUI.h",
            "copyPath": "include/PlayingStateUI.h"
          },
          {
            "pathPrefix": "include/",
            "name": "ResourceManager.h",
            "href": "include/ResourceManager.h",
            "copyPath": "include/ResourceManager.h"
          },
          {
            "pathPrefix": "include/",
            "name": "SceneManager.h",
            "href": "include/SceneManager.h",
            "copyPath": "include/SceneManager.h"
          },
          {
            "pathPrefix": "include/",
            "name": "ScriptParser.h",
            "href": "include/ScriptParser.h",
            "copyPath": "include/ScriptParser.h"
          },
          {
            "pathPrefix": "include/",
            "name": "SettingsState.h",
            "href": "include/SettingsState.h",
            "copyPath": "include/SettingsState.h"
          },
          {
            "pathPrefix": "include/",
            "name": "StartState.h",
            "href": "include/StartState.h",
            "copyPath": "include/StartState.h"
          }
        ]
      },
      {
        "id": "src-root",
        "title": "src/",
        "tag": "Entry point",
        "items": [
          {
            "pathPrefix": "src/",
            "name": "main.cpp",
            "href": "src/main.cpp",
            "copyPath": "src/main.cpp"
          }
        ]
      },
      {
        "id": "src-core",
        "title": "src/core/",
        "tag": "Engine & systems",
        "items": [
          {
            "pathPrefix": "src/core/",
            "name": "CustomWindow.cpp",
            "href": "src/core/CustomWindow.cpp",
            "copyPath": "src/core/CustomWindow.cpp"
          },
          {
            "pathPrefix": "src/core/",
            "name": "GameEngine.cpp",
            "href": "src/core/GameEngine.cpp",
            "copyPath": "src/core/GameEngine.cpp"
          },
          {
            "pathPrefix": "src/core/",
            "name": "GameStateManager.cpp",
            "href": "src/core/GameStateManager.cpp",
            "copyPath": "src/core/GameStateManager.cpp"
          },
          {
            "pathPrefix": "src/core/",
            "name": "InventorySystem.cpp",
            "href": "src/core/InventorySystem.cpp",
            "copyPath": "src/core/InventorySystem.cpp"
          },
          {
            "pathPrefix": "src/core/",
            "name": "PlayingState.cpp",
            "href": "src/core/PlayingState.cpp",
            "copyPath": "src/core/PlayingState.cpp"
          },
          {
            "pathPrefix": "src/core/",
            "name": "ResourceManager.cpp",
            "href": "src/core/ResourceManager.cpp",
            "copyPath": "src/core/ResourceManager.cpp"
          },
          {
            "pathPrefix": "src/core/",
            "name": "SceneManager.cpp",
            "href": "src/core/SceneManager.cpp",
            "copyPath": "src/core/SceneManager.cpp"
          },
          {
            "pathPrefix": "src/core/",
            "name": "ScriptParser.cpp",
            "href": "src/core/ScriptParser.cpp",
            "copyPath": "src/core/ScriptParser.cpp"
          },
          {
            "pathPrefix": "src/core/",
            "name": "save_data.json",
            "href": "src/core/save_data.json",
            "copyPath": "src/core/save_data.json"
          }
        ]
      },
      {
        "id": "src-ui",
        "title": "src/ui/",
        "tag": "User interface",
        "items": [
          {
            "pathPrefix": "src/ui/",
            "name": "Button.cpp",
            "href": "src/ui/Button.cpp",
            "copyPath": "src/ui/Button.cpp"
          },
          {
            "pathPrefix": "src/ui/",
            "name": "ConfirmationDialog.cpp",
            "href": "src/ui/ConfirmationDialog.cpp",
            "copyPath": "src/ui/ConfirmationDialog.cpp"
          },
          {
            "pathPrefix": "src/ui/",
            "name": "DialogBox.cpp",
            "href": "src/ui/DialogBox.cpp",
            "copyPath": "src/ui/DialogBox.cpp"
          },
          {
            "pathPrefix": "src/ui/",
            "name": "InventoryUI.cpp",
            "href": "src/ui/InventoryUI.cpp",
            "copyPath": "src/ui/InventoryUI.cpp"
          },
          {
            "pathPrefix": "src/ui/",
            "name": "LayoutManager.cpp",
            "href": "src/ui/LayoutManager.cpp",
            "copyPath": "src/ui/LayoutManager.cpp"
          },
          {
            "pathPrefix": "src/ui/",
            "name": "MainMenuState.cpp",
            "href": "src/ui/MainMenuState.cpp",
            "copyPath": "src/ui/MainMenuState.cpp"
          },
          {
            "pathPrefix": "src/ui/",
            "name": "PlayingStateUI.cpp",
            "href": "src/ui/PlayingStateUI.cpp",
            "copyPath": "src/ui/PlayingStateUI.cpp"
          },
          {
            "pathPrefix": "src/ui/",
            "name": "SettingsState.cpp",
            "href": "src/ui/SettingsState.cpp",
            "copyPath": "src/ui/SettingsState.cpp"
          },
          {
            "pathPrefix": "src/ui/",
            "name": "StartState.cpp",
            "href": "src/ui/StartState.cpp",
            "copyPath": "src/ui/StartState.cpp"
          }
        ]
      },
      {
        "id": "src-assets",
        "title": "src/assets/",
        "tag": "Game content",
        "items": [
          {
            "pathPrefix": "src/assets/",
            "name": "fonts/",
            "note": "font files"
          },
          {
            "pathPrefix": "src/assets/",
            "name": "images/",
            "note": "image files including logo.ico"
          },
          {
            "pathPrefix": "src/assets/items/",
            "name": "items.json",
            "href": "src/assets/items/items.json",
            "copyPath": "src/assets/items/items.json",
            "note": "Item definitions"
          },
          {
            "pathPrefix": "src/assets/scripts/",
            "name": "intro.json",
            "href": "src/assets/scripts/intro.json",
            "copyPath": "src/assets/scripts/intro.json"
          },
          {
            "pathPrefix": "src/assets/",
            "name": "sfx/",
            "note": "sound effect files"
          }
        ]
      },
      {
        "id": "root",
        "title": "Root directory",
        "tag": "Project configuration",
        "items": [
          {
            "pathPrefix": "./",
            "name": "CMakeLists.txt",
            "href": "CMakeLists.txt",
            "copyPath": "CMakeLists.txt",
            "note": "Build configuration"
          },
          {
            "pathPrefix": "./",
            "name": "README.md",
            "href": "README.md",
            "copyPath": "README.md",
            "note": "Project documentation"
          },
          {
            "pathPrefix": "./",
            "name": "install.md",
            "href": "install.md",
            "copyPath": "install.md",
            "note": "For building from source"
          },
          {
            "pathPrefix": "./",
            "name": "LICENSE.md",
            "href": "LICENSE.md",
            "copyPath": "LICENSE.md",
            "note": "License information"
          },
          {
            "pathPrefix": "./",
            "name": "DOCMAP.md",
            "href": "DOCMAP.md",
            "copyPath": "DOCMAP.md",
            "note": "You are here!"
          },
          {
            "pathPrefix": "./",
            "name": ".gitignore",
            "href": ".gitignore",
            "copyPath": ".gitignore",
            "note": "Git ignore rules"
          },
          {
            "pathPrefix": "./",
            "name": "app.rc",
            "href": "app.rc",
            "copyPath": "app.rc",
            "note": "Windows resource file (icon and version info)"
          },
          {
            "pathPrefix": "./",
            "name": "Untitled Adventure Game.lnk",
            "href": "Untitled Adventure Game.lnk",
            "copyPath": "Untitled Adventure Game.lnk",
            "note": "Shortcut file to .exe once built"
          }
        ]
      },
      {
        "id": "build-dir",
        "title": "Build directory",
        "tag": "Generated output",
        "items": [
          {
            "pathPrefix": "./",
            "name": "build/",
            "note": "CMake build output (excluded from git)"
          }
        ]
      },
      {
        "id": "config",
        "title": "Configuration",
        "tag": "Editor & CI",
        "items": [
          {
            "pathPrefix": "./",
            "name": ".vscode/settings.json",
            "href": ".vscode/settings.json",
            "copyPath": ".vscode/settings.json",
            "note": "VS Code settings"
          },
          {
            "pathPrefix": "./",
            "name": ".github/workflows/",
            "href": ".github/workflows/",
            "copyPath": ".github/workflows/",
            "note": "GitHub Actions workflows"
          }
        ]
      }
    ]
  },
  "fileDescriptions": {
    "categories": [
      {
        "title": "Core System Files",
        "items": [
          {
            "name": "GameEngine",
            "description": "Main game loop and state management. Owns the custom window and state stack (main menu, settings, gameplay, etc.). Routes SFML events to the active state and handles fullscreen/resize updates. Centralizes resource loading (fonts, textures, sounds, music) and music playback."
          },
          {
            "name": "CustomWindow",
            "description": "Custom window implementation with titlebar. Replaces the OS border with a draggable titlebar and custom close/fullscreen buttons. Manages borderless fullscreen toggling while preserving previous windowed size/position. Hides the system cursor and renders a textured in‑game cursor every frame."
          },
          {
            "name": "ResourceManager",
            "description": "Asset loading and caching system. Loads textures, fonts, sound buffers, and streaming music on demand by string ID. Stores all resources in maps to avoid duplicate loads and share them across states. Provides simple get* accessors, logging errors when assets fail to load."
          },
          {
            "name": "ScriptParser",
            "description": "JSON script parsing for game scenes. Reads narrative scripts (scenes, choices, metadata) from JSON via nlohmann::json. Supports conditional choices, stat/flag effects, and item rewards from script. Exposes helpers to find scenes by ID for the SceneManager."
          },
          {
            "name": "SceneManager",
            "description": "Scene loading and management. Owns the currently loaded script and active scene pointer. Loads per‑scene background graphics, with fallback attempts for JPEG/PNG. Handles \"END\" sentinel scenes and notifies listeners when a script completes."
          },
          {
            "name": "GameStateManager",
            "description": "Game state persistence and flag management. Tracks story flags, player stats, current script, and current scene in memory. Applies script‑driven effects (set/clear flags, modify stats, grant items). Saves/loads full game state (including inventory) to/from assets/save_data.json."
          },
          {
            "name": "InventorySystem",
            "description": "Item management and inventory logic. Loads item definitions from assets/items/items.json and preloads their textures. Handles stackable items, max stack sizes, adds/removes items by index. Serializes and deserializes the player's inventory into the save file."
          }
        ]
      },
      {
        "title": "UI Components",
        "items": [
          {
            "name": "Button",
            "description": "Interactive button widget. Handles hover and click states with visual feedback (color changes). Supports both texture-based and text-only buttons. Plays a shared click sound effect when activated."
          },
          {
            "name": "DialogBox",
            "description": "Text display with speaker names. Supports hex color parsing for speaker name styling. Automatically wraps dialog text to fit a configurable width. Provides access to text bounds for layout-aware positioning."
          },
          {
            "name": "LayoutManager",
            "description": "Responsive layout calculations. Computes positions/sizes for dialog, graphics, and stats regions based on window size. Maintains minimum dialog height and 16:9 aspect ratio for graphics area. Provides scaled character sizes for consistent typography across resolutions."
          },
          {
            "name": "ConfirmationDialog",
            "description": "Modal confirmation dialog widget. Draws a dimmed fullscreen overlay to block background interaction. Wraps long confirmation messages and centers them within the dialog box. Renders inline colored key hints (\"Y\" green, \"N\" red) for clarity."
          },
          {
            "name": "InventoryUI",
            "description": "Visual inventory grid with tooltips and interaction. Builds a scrollable grid of item slots with hover highlighting. Shows item tooltips with name, description, and smart edge-avoidance. Renders item quantity overlays and scales icons to fit each cell."
          },
          {
            "name": "PlayingStateUI",
            "description": "Layout and rendering for the playing state screen. Manages dialog area, graphics box, stats area, and inventory panel positioning. Dynamically lays out choice buttons in one or two columns depending on count. Auto-resizes/wraps dialog text to avoid overlapping the choice buttons."
          }
        ]
      },
      {
        "title": "Game States",
        "items": [
          {
            "name": "MainMenuState",
            "description": "Main menu screen. Displays background, logo, and title textures sized to the current window. Hosts \"Start\" and \"Settings\" buttons wired into the GameEngine callbacks. Plays a fade‑to‑black transition when starting a new game."
          },
          {
            "name": "StartState",
            "description": "Game start placeholder. Shows a simple \"Game Starting...\" message centered in the window. Listens for ESC to return to the main menu via a callback. Re-centers UI text whenever the window is resized."
          },
          {
            "name": "SettingsState",
            "description": "Volume and settings control. Renders a title, volume label, and a horizontal slider for music volume. Supports clicking and dragging the slider handle to adjust SFML music volume. Updates the numeric volume text and slider handle position in real time."
          },
          {
            "name": "PlayingState",
            "description": "Active gameplay screen. Owns SceneManager, GameStateManager, InventorySystem, and PlayingStateUI. Handles scene transitions with fade in/out and script completion callbacks. Builds and updates choice buttons, inventory actions, and confirmation dialogs."
          }
        ]
      },
      {
        "title": "Data Structures",
        "items": [
          {
            "name": "GameState",
            "description": "Abstract base class for all game states. Provides a common interface: handleEvent, update, draw, updatePositions. Exposes a getType() enum so GameEngine can route callbacks by state. Enables stacking/changing states through std::unique_ptr<GameState>."
          },
          {
            "name": "GameScript / Scene / Choice / Effects / Condition",
            "description": "Represent parsed JSON script data: scenes, choices, metadata, and effects. Condition encodes flag requirements for unlocking specific choices. Effects describe mutations to flags, stats, and inventory when a scene resolves."
          },
          {
            "name": "InventoryItem / ItemDefinition",
            "description": "InventoryItem tracks an item id and current quantity in the player's inventory. ItemDefinition stores per‑item stats: name, description, stackable, max stack size, etc. Loaded once from assets/items/items.json and reused across the game."
          }
        ]
      }
    ]
  }
};

// ===== Entry point =====

document.addEventListener("DOMContentLoaded", () => {
  initPage(PAGE_DATA);
});

function initPage(data) {
  if (!data) return;

  setProjectHeader(data.project);
  buildHero(data.hero);
  buildSections(data.sections, data);
  buildSideNav(data.sections, data.navigationTitle);
  setupBackToTop();
  setupScrollSpy(data.sections);
  setupFileSearch();
  setupCopyButtons();
}

// ===== Header + hero =====

function setProjectHeader(project) {
  if (!project) return;

  const titleEl = document.getElementById("projectTitle");
  const subtitleEl = document.getElementById("projectSubtitle");
  const pillTextEl = document.getElementById("projectPillText");
  const pillEl = document.getElementById("projectPill");
  const topChipEl = document.getElementById("topChip");

  if (titleEl && project.title) {
    titleEl.textContent = project.title;
    document.title = `${project.title} – Doc Map`;
  }

  if (subtitleEl && project.subtitle) {
    subtitleEl.textContent = project.subtitle;
  }

  if (pillTextEl && project.pill) {
    pillTextEl.textContent = project.pill;
  } else if (pillEl) {
    pillEl.style.display = "none";
  }

  if (topChipEl && project.topChip) {
    topChipEl.textContent = project.topChip;
  }
}

function buildHero(hero) {
  if (!hero) return;
  const heroEl = document.getElementById("hero");
  if (!heroEl) return;

  const gridItems = (hero.grid || [])
    .map(
      (item) => `
      <div class="hero-grid-item">
        <div class="hero-grid-label">${item.label || ""}</div>
        <div class="hero-grid-value">${item.value || ""}</div>
        ${
          item.note
            ? `<div class="hero-grid-note">${item.note}</div>`
            : ""
        }
      </div>
    `
    )
    .join("");

  const metaTags = (hero.metaTags || [])
    .map((tag) => `<span class="hero-meta-tag">${tag}</span>`)
    .join("");

  const badges = (hero.badges || [])
    .map(
      (badge) => `
      <div class="badge">
        <span class="badge-dot"></span>
        <span>${badge}</span>
      </div>
    `
    )
    .join("");

  heroEl.innerHTML = `
    <div class="hero-content">
      <div class="hero-left">
        <h1>${hero.heading || "Project Overview"}</h1>
        <p class="hero-tagline">${hero.tagline || ""}</p>
        <div class="hero-meta-row">
          ${metaTags}
        </div>
        <div class="hero-badges">
          ${badges}
        </div>
      </div>
      <aside class="hero-right">
        <div class="hero-right-header">
          <div class="hero-right-title">
            ${hero.snapshotLabel || "Build snapshot"}
          </div>
          <div class="hero-badge-small">
            ${hero.snapshotBadge || ""}
          </div>
        </div>
        <div class="hero-grid">
          ${gridItems}
        </div>
      </aside>
    </div>
  `;
}

// ===== Sections =====

function buildSections(sections, data) {
  if (!Array.isArray(sections)) return;

  sections.forEach((section) => {
    const container = document.getElementById(section.id);
    if (!container) return;

    switch (section.type) {
      case "paragraphs":
        renderParagraphSection(section, container);
        break;
      case "helpfulLinks":
        renderHelpfulLinksSection(section, container);
        break;
      case "designApproach":
        renderDesignApproachSection(section, container);
        break;
      case "features":
        renderFeaturesSection(section, container);
        break;
      case "building":
        renderBuildingSection(section, container);
        break;
      case "bullets":
        renderBulletSection(section, container);
        break;
      case "fileMap":
        renderDocMapSection(section, container, data.fileMap);
        break;
      case "gallery":
        renderGallerySection(section, container);
        break;
      case "fileDescriptions":
        renderFileDescriptionsSection(section, container, data.fileDescriptions);
        break;
      case "funFact":
        renderFunFactSection(section, container);
        break;
      default:
        renderParagraphSection(section, container);
    }
  });
}

function renderParagraphSection(section, container) {
  container.innerHTML = "";
  const h2 = document.createElement("h2");
  h2.textContent = section.title || "";
  container.appendChild(h2);

  (section.body || []).forEach((text) => {
    const p = document.createElement("p");
    p.textContent = text;
    container.appendChild(p);
  });
}

function renderHelpfulLinksSection(section, container) {
  container.innerHTML = "";
  const h2 = document.createElement("h2");
  h2.textContent = section.title || "Helpful Links";
  container.appendChild(h2);

  const p = document.createElement("p");
  p.innerHTML = `👉 <strong>Full Documentation (Live Site):</strong> You are here!<br>`;
  container.appendChild(p);

  const linkP = document.createElement("p");
  linkP.innerHTML = `➡️ <strong><a href="https://github.com/Bushido3403/UntitledAdventureGame/releases/latest" target="_blank" rel="noopener noreferrer" style="color: var(--color-accent);">Latest Windows Build Download (Win11 x64)</a></strong><br>
<span style="color: var(--color-text-muted); font-size: 0.88rem;">Contains the compiled <code>.exe</code> and required files.</span>`;
  container.appendChild(linkP);
}

function renderFeaturesSection(section, container) {
  container.innerHTML = "";
  const h2 = document.createElement("h2");
  h2.textContent = section.title || "";
  container.appendChild(h2);

  const ul = document.createElement("ul");
  (section.items || []).forEach((item) => {
    const li = document.createElement("li");
    const strong = document.createElement("strong");
    strong.textContent = item.strong || "";
    li.appendChild(strong);
    li.appendChild(
      document.createTextNode(
        item.text ? `: ${item.text}` : ""
      )
    );
    ul.appendChild(li);
  });
  container.appendChild(ul);

  if (section.chips && section.chips.length) {
    const row = document.createElement("div");
    row.className = "pill-row";
    section.chips.forEach((chip) => {
      const pill = document.createElement("span");
      pill.className = "pill";
      pill.textContent = chip;
      row.appendChild(pill);
    });
    container.appendChild(row);
  }
}

function renderDesignApproachSection(section, container) {
  container.innerHTML = "";
  const h2 = document.createElement("h2");
  h2.textContent = section.title || "Design Approach";
  container.appendChild(h2);

  (section.body || []).forEach((text) => {
    const p = document.createElement("p");
    p.innerHTML = text
      .replace(/\*\*(.*?)\*\*/g, '<strong>$1</strong>')
      .replace(/`(.*?)`/g, '<code>$1</code>');
    container.appendChild(p);
  });
}

function renderBuildingSection(section, container) {
  container.innerHTML = "";
  const h2 = document.createElement("h2");
  h2.textContent = section.title || "Building";
  container.appendChild(h2);

  const ul = document.createElement("ul");
  const li = document.createElement("li");
  li.innerHTML = `See <a href="install.md" style="color: var(--color-accent);">install.md</a> for building from source`;
  li.innerHTML = `See <a href="https://github.com/Bushido3403/UntitledAdventureGame/blob/master/install.md" target="_blank" rel="noopener noreferrer" style="color: var(--color-accent);">install.md</a> in source code for building from source`;
  ul.appendChild(li);
  container.appendChild(ul);
}

function renderBulletSection(section, container) {
  container.innerHTML = "";
  const h2 = document.createElement("h2");
  h2.textContent = section.title || "";
  container.appendChild(h2);

  const ul = document.createElement("ul");
  (section.items || []).forEach((text) => {
    const li = document.createElement("li");
    li.textContent = text;
    ul.appendChild(li);
  });
  container.appendChild(ul);
}

function renderGallerySection(section, container) {
  container.innerHTML = "";
  const h2 = document.createElement("h2");
  h2.textContent = section.title || "Gallery";
  container.appendChild(h2);

  const p = document.createElement("p");
  p.textContent = "Click any image to view it in full size.";
  container.appendChild(p);

  const grid = document.createElement("div");
  grid.className = "gallery-grid";

  const images = [
    { src: "gallery/1.png", caption: "Main Menu" },
    { src: "gallery/2.png", caption: "Settings Screen" },
    { src: "gallery/3.png", caption: "Game Introduction" },
    { src: "gallery/4.png", caption: "Gameplay Screen" },
    { src: "gallery/6.png", caption: "Inventory System" },
    { src: "gallery/7.png", caption: "Item Tooltips" }
  ];

  images.forEach((img, index) => {
    const item = document.createElement("div");
    item.className = "gallery-item";
    item.dataset.index = index;

    const picture = document.createElement("img");
    picture.src = img.src;
    picture.alt = img.caption;
    picture.loading = "lazy";

    const caption = document.createElement("div");
    caption.className = "gallery-item-caption";
    caption.textContent = img.caption;

    item.appendChild(picture);
    item.appendChild(caption);
    grid.appendChild(item);

    item.addEventListener("click", () => {
      openLightbox(index, images);
    });
  });

  container.appendChild(grid);
}

function renderDocMapSection(section, container, fileMap) {
  if (!fileMap) return;
  container.innerHTML = "";

  // Header with search
  const header = document.createElement("div");
  header.className = "file-map-header";

  const h2 = document.createElement("h2");
  h2.textContent = section.title || "Document Map";

  const search = document.createElement("div");
  search.className = "file-search";

  const searchIcon = document.createElement("span");
  searchIcon.className = "file-search-icon";
  searchIcon.textContent = "🔍";

  const searchInput = document.createElement("input");
  searchInput.id = "fileSearchInput";
  searchInput.type = "search";
  searchInput.placeholder = "Filter files by name or folder...";
  searchInput.setAttribute("aria-label", "Filter file map");

  search.appendChild(searchIcon);
  search.appendChild(searchInput);

  header.appendChild(h2);
  header.appendChild(search);
  container.appendChild(header);

  // Intro paragraphs
  (fileMap.introParagraphs || []).forEach((text) => {
    const p = document.createElement("p");
    p.textContent = text;
    container.appendChild(p);
  });

  // Folder overview
  if (fileMap.folderOverview && fileMap.folderOverview.length) {
    const ul = document.createElement("ul");
    fileMap.folderOverview.forEach((folder) => {
      const li = document.createElement("li");
      const strong = document.createElement("strong");
      strong.textContent = folder.name;
      li.appendChild(strong);
      if (folder.description) {
        li.appendChild(document.createTextNode(` - ${folder.description}`));
      }
      ul.appendChild(li);
    });
    container.appendChild(ul);
  }

  if (fileMap.afterOverviewText) {
    const p = document.createElement("p");
    p.textContent = fileMap.afterOverviewText;
    container.appendChild(p);
  }

  // File groups
  (fileMap.groups || []).forEach((group) => {
    const sectionDiv = document.createElement("div");
    sectionDiv.className = "file-section";

    const headerDiv = document.createElement("div");
    headerDiv.className = "file-section-header";

    const titleDiv = document.createElement("div");
    titleDiv.className = "file-section-title";
    titleDiv.textContent = group.title || "";

    const tagDiv = document.createElement("div");
    tagDiv.className = "file-section-tag";
    tagDiv.textContent = group.tag || "";

    headerDiv.appendChild(titleDiv);
    headerDiv.appendChild(tagDiv);
    sectionDiv.appendChild(headerDiv);

    const list = document.createElement("ul");
    list.className = "file-list";

    (group.items || []).forEach((item) => {
      const li = document.createElement("li");
      li.className = "file-item";
      const fullPath = (item.pathPrefix || "") + (item.name || "");
      li.dataset.file = fullPath.toLowerCase();

      const mainDiv = document.createElement("div");
      mainDiv.className = "file-main";

      const prefixSpan = document.createElement("span");
      prefixSpan.className = "file-path-prefix";
      prefixSpan.textContent = item.pathPrefix || "";

      const nameDiv = document.createElement("div");
      nameDiv.className = "file-name";

      if (item.href) {
        const link = document.createElement("a");
        link.href = item.href;
        link.textContent = item.name || "";
        nameDiv.appendChild(link);
      } else {
        nameDiv.textContent = item.name || "";
      }

      if (item.note) {
        const noteSpan = document.createElement("span");
        noteSpan.className = "file-note";
        noteSpan.textContent = `– ${item.note}`;
        nameDiv.appendChild(noteSpan);
      }

      mainDiv.appendChild(prefixSpan);
      mainDiv.appendChild(nameDiv);
      li.appendChild(mainDiv);

      if (item.copyPath) {
        const copyBtn = document.createElement("button");
        copyBtn.className = "copy-btn";
        copyBtn.type = "button";
        copyBtn.dataset.path = item.copyPath;
        copyBtn.innerHTML = `<span class="copy-btn-icon">📋</span> Copy`;
        li.appendChild(copyBtn);
      }

      list.appendChild(li);
    });

    sectionDiv.appendChild(list);
    container.appendChild(sectionDiv);
  });
}

function renderFileDescriptionsSection(section, container, fileDescriptions) {
  if (!fileDescriptions) return;
  container.innerHTML = "";

  const h2 = document.createElement("h2");
  h2.textContent = section.title || "File Descriptions";
  container.appendChild(h2);

  (fileDescriptions.categories || []).forEach((category) => {
    const h3 = document.createElement("h3");
    h3.textContent = category.title || "";
    container.appendChild(h3);

    const ul = document.createElement("ul");
    (category.items || []).forEach((item) => {
      const li = document.createElement("li");
      const strong = document.createElement("strong");
      strong.textContent = item.name || "";
      li.appendChild(strong);
      if (item.description) {
        li.appendChild(document.createTextNode(` - ${item.description}`));
      }
      ul.appendChild(li);
    });
    container.appendChild(ul);
  });
}

function renderFunFactSection(section, container) {
  container.innerHTML = "";
  const h2 = document.createElement("h2");
  h2.textContent = section.title || "";
  container.appendChild(h2);

  (section.body || []).forEach((text) => {
    const p = document.createElement("p");
    p.textContent = text;
    container.appendChild(p);
  });
}

// ===== Side nav =====

function buildSideNav(sections, navTitle) {
  const navEl = document.getElementById("sideNav");
  if (!navEl || !Array.isArray(sections)) return;

  const navSections = sections.filter(
    (s) => s.includeInNav !== false
  );
  if (!navSections.length) {
    navEl.style.display = "none";
    return;
  }

  navEl.innerHTML = "";

  const titleDiv = document.createElement("div");
  titleDiv.className = "side-nav-title";
  titleDiv.textContent = navTitle || "On this page";
  navEl.appendChild(titleDiv);

  const list = document.createElement("ul");
  navSections.forEach((sec) => {
    const li = document.createElement("li");
    const a = document.createElement("a");
    a.href = `#${sec.id}`;
    a.textContent = sec.navLabel || sec.title || sec.id;
    li.appendChild(a);
    list.appendChild(li);
  });

  navEl.appendChild(list);
}

// ===== Back-to-top =====

function setupBackToTop() {
  const button = document.getElementById("backToTop");
  if (!button) return;

  window.addEventListener("scroll", () => {
    if (window.scrollY > BACK_TO_TOP_THRESHOLD) {
      button.classList.add("visible");
    } else {
      button.classList.remove("visible");
    }
  });

  button.addEventListener("click", () => {
    window.scrollTo({ top: 0, behavior: "smooth" });
  });
}

// ===== Scroll spy for side nav =====

function setupScrollSpy(sections) {
  if (!Array.isArray(sections)) return;

  const navLinks = Array.from(
    document.querySelectorAll(".side-nav a[href^='#']")
  );
  if (!navLinks.length) return;

  const trackedSections = sections
    .filter((s) => s.includeInNav !== false)
    .map((s) => document.getElementById(s.id))
    .filter(Boolean);

  function updateActiveNav() {
    const fromTop = window.scrollY + SCROLL_OFFSET_PX;
    let currentId = null;

    trackedSections.forEach((section) => {
      const sectionTop = section.offsetTop;
      const sectionHeight = section.offsetHeight;
      if (fromTop >= sectionTop && fromTop < sectionTop + sectionHeight) {
        currentId = section.id;
      }
    });

    navLinks.forEach((link) => {
      const href = link.getAttribute("href");
      if (href === `#${currentId}`) {
        link.classList.add("active");
      } else {
        link.classList.remove("active");
      }
    });
  }

  updateActiveNav();
  window.addEventListener("scroll", updateActiveNav);
}

// ===== File search =====

function setupFileSearch() {
  const searchInput = document.getElementById("fileSearchInput");
  if (!searchInput) return;

  const items = Array.from(
    document.querySelectorAll(".file-item")
  );

  searchInput.addEventListener("input", () => {
    const query = searchInput.value.toLowerCase().trim();
    items.forEach((item) => {
      const filePath = item.dataset.file || "";
      if (!query || filePath.includes(query)) {
        item.classList.remove("hidden-by-filter");
      } else {
        item.classList.add("hidden-by-filter");
      }
    });
  });
}

// ===== Copy buttons =====

function setupCopyButtons() {
  const buttons = Array.from(
    document.querySelectorAll(".copy-btn")
  );
  if (!buttons.length || !navigator.clipboard) return;

  buttons.forEach((btn) => {
    btn.addEventListener("click", () => {
      const path = btn.dataset.path;
      if (!path) return;

      navigator.clipboard.writeText(path).then(() => {
        const original = btn.innerHTML;
        btn.innerHTML = `<span class="copy-btn-icon">✓</span> Copied!`;
        btn.style.color = "var(--color-accent)";

        setTimeout(() => {
          btn.innerHTML = original;
          btn.style.color = "";
        }, COPY_RESET_MS);
      });
    });
  });
}

// ===== Lightbox =====

let currentLightboxIndex = 0;
let lightboxImages = [];

function openLightbox(index, images) {
  currentLightboxIndex = index;
  lightboxImages = images;

  let lightbox = document.getElementById("lightbox");
  if (!lightbox) {
    lightbox = createLightbox();
  }

  updateLightboxContent();
  lightbox.classList.add("active");
  document.body.style.overflow = "hidden";
}

function createLightbox() {
  const lightbox = document.createElement("div");
  lightbox.id = "lightbox";
  lightbox.className = "lightbox";

  const content = document.createElement("div");
  content.className = "lightbox-content";

  const imageWrapper = document.createElement("div");
  imageWrapper.className = "lightbox-image-wrapper";

  const img = document.createElement("img");
  img.className = "lightbox-image";
  img.id = "lightboxImage";

  const caption = document.createElement("div");
  caption.className = "lightbox-caption";
  caption.id = "lightboxCaption";

  imageWrapper.appendChild(img);
  content.appendChild(imageWrapper);
  content.appendChild(caption);

  const closeBtn = document.createElement("button");
  closeBtn.className = "lightbox-close";
  closeBtn.innerHTML = "×";
  closeBtn.setAttribute("aria-label", "Close lightbox");
  closeBtn.addEventListener("click", closeLightbox);

  const prevBtn = document.createElement("button");
  prevBtn.className = "lightbox-nav prev";
  prevBtn.innerHTML = "‹";
  prevBtn.setAttribute("aria-label", "Previous image");
  prevBtn.addEventListener("click", () => navigateLightbox(-1));

  const nextBtn = document.createElement("button");
  nextBtn.className = "lightbox-nav next";
  nextBtn.innerHTML = "›";
  nextBtn.setAttribute("aria-label", "Next image");
  nextBtn.addEventListener("click", () => navigateLightbox(1));

  lightbox.appendChild(content);
  lightbox.appendChild(closeBtn);
  lightbox.appendChild(prevBtn);
  lightbox.appendChild(nextBtn);

  lightbox.addEventListener("click", (e) => {
    if (e.target === lightbox) {
      closeLightbox();
    }
  });

  document.addEventListener("keydown", handleLightboxKeys);

  document.body.appendChild(lightbox);
  return lightbox;
}

function updateLightboxContent() {
  const img = document.getElementById("lightboxImage");
  const caption = document.getElementById("lightboxCaption");

  if (img && caption && lightboxImages[currentLightboxIndex]) {
    const current = lightboxImages[currentLightboxIndex];
    img.src = current.src;
    img.alt = current.caption;
    caption.textContent = `${current.caption} (${currentLightboxIndex + 1}/${lightboxImages.length})`;
  }
}

function closeLightbox() {
  const lightbox = document.getElementById("lightbox");
  if (lightbox) {
    lightbox.classList.remove("active");
    document.body.style.overflow = "";
  }
}

function navigateLightbox(direction) {
  currentLightboxIndex = (currentLightboxIndex + direction + lightboxImages.length) % lightboxImages.length;
  updateLightboxContent();
}

function handleLightboxKeys(e) {
  const lightbox = document.getElementById("lightbox");
  if (!lightbox || !lightbox.classList.contains("active")) return;

  if (e.key === "Escape") {
    closeLightbox();
  } else if (e.key === "ArrowLeft") {
    navigateLightbox(-1);
  } else if (e.key === "ArrowRight") {
    navigateLightbox(1);
  }
}