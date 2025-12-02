// ===== CONFIG: Markdown source =====
// Replace RAW_CHANGELOG_MD with your own markdown to reuse this page.
const RAW_CHANGELOG_MD = `# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/)

## [V0.1]

### Added
- Initial project scaffold, including CMake-based build system and SFML setup.
- Basic windowed SFML application (\`main.cpp\`) with event loop and render loop.
- CI workflow.
- \`.gitignore\` with standard build/cache/editor exclusions.
- Project documentation (\`README.md\`) and licensing (\`LICENSE.md\`).

## [V0.2]

### Added
- Asset folders under \`src/assets/\`, including fonts and images (\`MedievalSharp.ttf\`, \`menuBackground.jpg\`).  
- Window background rendering: \`main.cpp\` now loads and displays a background image.  
- Custom title bar UI inside the SFML window: title bar background, title text, and a close ("X") button.  
- Support for window dragging (click-and-drag on title bar to move window) and a custom window close control (via close button).  
- Handling of window resize events: enforces a 16:9 aspect ratio, adjusts view and rescales background accordingly.  
- Updated \`CMakeLists.txt\` to copy the \`src/assets/\` directory into the executable output directory after build.  

### Changed
- The initial bare-bones SFML window setup was replaced/improved with a full windowed UI featuring background, custom title bar, and event handling (resize, drag, close).  

### Removed
- Removal of the default window title bar (i.e. switching to a borderless / title-bar-less window).  

## [V1.0]

### Added
- Window now initially opens at 1280×720 instead of 1920×1080.  
- Window now starts at position (100, 100) on screen.  
- A fullscreen-toggle UI option: pressing the new "[ ]" button switches between windowed and fullscreen modes (with state tracking, and restoring previous windowed size/position when exiting fullscreen).  
- UI text/icon for the fullscreen toggle (rendered in cyan) alongside the close-button "X".  
- Improved title-bar UI layout updates on state changes (resizing, fullscreen toggling): background bar, title text, control buttons update their positions/size.  

### Changed
- Default window size/style updated: borderless / titleless style retained, but resolution lowered to 1280×720.  
- Event handling for close-button and fullscreen toggle added.  
- Rendering loop modified: title bar, title text, fullscreen toggle text, and close-button/text drawn appropriately alongside background.  

### Removed
- The explicit close-button rectangle previously drawn (with its own styling), replaced by a text-only "X" (and a new fullscreen toggle) for controls.  

### Fixed
- Window control logic refined for better consistency during fullscreen toggling and UI redraws (positions/size updating, framerate limit retention).  

## [V1.1]

### Added
- New asset files under \`src/assets/\`, images (\`logo.png\`, \`settings.png\`, \`start.png\`, \`title.png\`) and audio (\`Title.mp3\`).  
- In \`main.cpp\`, a simple menu-system framework:  
  - A \`GameState\` enum with at least \`MainMenu\`, \`Start\`, and \`Settings\`.  
  - Main-menu UI: sprites for logo, title, "Start" and "Settings" buttons, plus per-frame handling for hover and click (changing the game state accordingly).  
  - Window icon is set using \`logo.png\`.  
  - Background music (\`Title.mp3\`) loads and plays in loop.  
  - UI positioning/rescaling logic: when window size changes, background and menu elements adjust (scale/position) appropriately.  

- Build config in \`CMakeLists.txt\` updated to also link audio support (added \`SFML::Audio\`).  

### Changed
- The executable now links both \`Graphics\` **and** \`Audio\` libraries rather than just graphics, enabling music/sound support.  

## [V1.2]

### Added
- A full internal "state-machine" architecture: abstract \`GameState\` base class plus concrete states \`MainMenuState\`, \`StartState\`, \`SettingsState\`.  
- UI framework classes: \`Button\`, \`CustomWindow\`, and a \`ResourceManager\` for loading/holding textures, fonts, music, etc.  
- Subdirectories and separation of concerns: \`src/core/\`, \`src/ui/\`, \`include/\`, moving beyond a single \`main.cpp\`.  
- Updated build configuration (\`CMakeLists.txt\`) to compile all source files, include headers, and link \`SFML::Graphics\` and \`SFML::Audio\`.  
- \`CustomWindow\` implementation: borderless SFML window with custom title bar, controls (close, fullscreen), draggable window, and consistent handling of window events and view resizing.  

### Changed
- Project structure refactored, split logic into modules/states instead of flat \`main.cpp\`.  
- Switch from a monolithic main file to a modular design with dedicated UI and core modules.  

## [V1.3]

### Added
- In the settings menu: a music-volume slider UI (slider bar + handle) allowing adjustable background music volume.  
- In \`SettingsState\`: UI elements for "Music Volume" label and a dynamic volume-value display (e.g. "42%").  
- Logic to handle mouse interactions: dragging on the slider bar or handle adjusts volume, updates the display, and sets the volume of the \`title\` music resource.  
- Layout and resizing support: when the window size changes, the volume slider and related text reposition/scale correctly according to current window size.  

### Changed
- Modified \`SettingsState\` constructor (removed the old window parameter) and updated its interface to rely only on a shared \`ResourceManager\`.  
- Refactored settings-state drawing: replaced a placeholder "Settings Menu (Coming Soon)" text with full UI components (title, volume label + value, slider bar + handle, back text).   

### Removed
- Placeholder text UI from settings, the old "Coming Soon" placeholder is replaced by real settings UI.  

## [V1.4]

### Added  
- New sound effect asset: \`click.wav\`.  
- Click-sound support for UI buttons: updated \`Button\` class to include a static \`clickSound\`, play it on click.  
- Resource management extended: \`ResourceManager\` now supports loading and retrieving sound buffers in addition to textures/fonts/music.  
- In \`CustomWindow\` class: ability to set a custom window icon (via \`setIcon()\` and storing \`sf::Image icon\`).  
- General refactor: UI/state framework files (\`Button\`, \`CustomWindow\`, \`ResourceManager\`, state headers) updated to use the new resource- and sound-capable architecture.  

### Changed  
- UI code now integrates sound effects for UI interactions (clicks).  
- Window instantiation code updated so the custom icon from resources is applied to the window.  
- Resource loading subsystem expanded, sound buffers added alongside textures, fonts, music.   

## [V1.5]

### Added
- Centralized \`GameEngine\` class that owns the window, resource manager, and state stack.  
- New engine-driven main loop handling events, updates, drawing, and state transitions.  
- Expanded \`GameState\` interface with \`update\`, \`draw\`, and \`updatePositions\` methods.  
- New \`Playing\` state type added to the state-type enum.  
- \`CustomWindow\` now tracks whether it was resized and whether it's currently fullscreen.

### Changed
- Moved all run-loop and state-management logic out of \`main.cpp\` into \`GameEngine\`.  
- Project structure reorganized so core and UI logic are separated cleanly.

### Removed
- Old monolithic main loop that previously lived in \`main.cpp\`.

## [V1.6]

### Added
- Windows resource script \`app.rc\` defining the application icon and version metadata for the Windows build.
- Game icon asset \`src/assets/images/logo.ico\` used by the Windows executable.

### Changed
- CMake configuration:
  - Renamed the project to \`UntitledAdventureGame\` and switched the executable target to \`game\` with \`OUTPUT_NAME "UntitledAdventureGame"\`.
  - Updated source/header collection to use \`\${CMAKE_SOURCE_DIR}\` paths and added \`source_group\` for cleaner IDE organization.
  - Updated the Windows build to conditionally attach \`app.rc\` and to copy \`src/assets\` into an \`assets\` folder next to the built executable.
- LICENSE:
  - Replaced the template dual-license text with a single MIT license under "Untitled Adventure Game License" and added an SFML third-party license notice.
- README:
  - Rewrote from a generic CMake SFML project template into a game-specific README with description, feature list, simplified VS Code build steps, and development prerequisites.

## [V1.7]

### Added
- JSON-based narrative scripting system:
  - \`ScriptParser\` with \`GameScript\`, \`Scene\`, and \`Choice\` types for loading scripts from JSON.
  - Initial story script asset \`src/assets/scripts/intro.json\` with a short multi-scene intro and simple branching choices.
- New \`PlayingState\`:
  - Renders background, dialog text, speaker name, and choice options based on the loaded script.
  - Supports an \`onScriptComplete\` callback to notify the engine when the script finishes.
- \`GameEngine::createPlayingState(const std::string& scriptPath)\` factory for constructing a \`PlayingState\` tied to a specific script file.

### Changed
- Build configuration:
  - Added \`nlohmann/json\` as a dependency via \`FetchContent_Declare(json)\` and \`FetchContent_MakeAvailable(json)\`.
  - Linked the game target against \`nlohmann_json::nlohmann_json\`.
- Game flow / state wiring:
  - Main menu "Start" callback now pushes a \`PlayingState\` using \`assets/scripts/intro.json\` instead of the placeholder \`StartState\`.
  - \`GameEngine::setupStateCallbacks\` extended to recognize \`GameStateType::Playing\` and hook the \`PlayingState\`’s completion callback to \`popState()\`.

## [V1.8]

### Added
- Full rendering logic for PlayingState: background, dialog text, speaker name, and choice options.
- Keyboard and mouse input for selecting choices.
- Window-resize–aware layout using \`CustomWindow::getDrawableSize()\`.

### Changed
- PlayingState rewritten from placeholder logic to a complete, functional play-scene renderer.
- CustomWindow updated to support drawable-area queries for proper UI scaling.

### Removed
- Old placeholder rendering and event-handling code in PlayingState.

### Fixed
- Play screen no longer appears blank; scenes and choices now display correctly.

## [V2.0]

### Added
- Support for text-only buttons by allowing \`Button\` to be constructed with an optional \`sf::Texture*\` and internally managing \`sf::Sprite\` / \`sf::Text\` via \`std::optional\`.
- \`Button::setText\` API to configure button label (font, string, size, color) independent of a texture.
- \`PlayingState\` \`choiceButtons\` container and associated button-based choice system (creation, storage, and click callbacks tied to \`loadScene\`).
- Additional logging in \`ResourceManager::loadMusic\` and \`GameEngine\` to print music load success/failure, current working directory on failure, and runtime music status for the title track.

### Changed
- \`Button\` constructor now takes \`sf::Texture*\` and uses a \`hasTexture\` flag with optional sprite/text, updating \`setPosition\`, \`setScale\`, \`update\`, \`draw\`, and \`getBounds\` to work for both textured and text-only buttons.
- \`PlayingState\` choice handling refactored from manually managed \`sf::Text\` list / hit-tests to using \`Button\` objects for choices, including:
  - Clearing/owning \`choiceButtons\` alongside \`choiceNextScenes\`.
  - Creating a \`Button\` per choice with text label and \`onClick\` lambda that calls \`loadScene(nextScene)\`.
  - \`updateChoicePositions\` now iterating over \`choiceButtons\` and calling \`setPosition\` on each.
  - \`handleEvent\` delegating mouse events to each button while keeping keyboard shortcuts.
  - \`update\` delegating hover logic to \`Button::update\` and \`draw\` delegating rendering to \`Button::draw\`.
- \`MainMenuState\` updated to construct buttons with texture pointers (\`&resources.getTexture("...")\`) to match the new \`Button\` API.
- \`GameEngine\` now explicitly configures title music (set volume to 100, looping enabled, play call) and prints music status for debugging.
- \`StartState\` placeholder text copy tweaked from "Game Starting... (Placeholder)" to "Game Starting..." for a more polished message.

### Removed
- Old text-only choice hover and click detection logic in \`PlayingState\` that iterated \`choiceTexts\` and manually checked text bounds.
- Explicit "(Placeholder)" wording in the start screen message.

### Fixed
- Choice positioning now correctly operates on \`choiceButtons\` instead of \`choiceTexts\`, preventing mismatches between visual elements and their logical hit areas.
- Button hover/click detection unified through \`Button::getBounds\`, avoiding divergence between sprite/text bounds and interaction logic and properly handling buttons without textures.
- Safe handling of buttons created without a texture by guarding sprite usage with \`hasTexture\` and \`std::optional\`, preventing invalid access when using text-only buttons.

## [V2.1]

### Added
- Custom cursor sprite support to \`CustomWindow\`, storing a \`sf::Sprite cursorSprite\` initialized from a cursor texture.
- New cursor texture asset \`src/assets/images/cursor.png\` and corresponding \`resources.loadTexture("cursor", "src/assets/images/cursor.png");\` in \`GameEngine\`.
- Logic in \`CustomWindow::drawTitlebar()\` to position and draw the custom cursor each frame.

### Changed
- \`CustomWindow\` constructor updated to accept an additional \`const sf::Texture& cursorTexture\` parameter and use it to initialize \`cursorSprite\` with a scaled-down cursor graphic.
- \`CustomWindow\` now hides the default OS cursor (\`window.setMouseCursorVisible(false);\`) both on construction and after recreating the window in fullscreen toggle handling.
- \`GameEngine\` now passes the loaded cursor texture into \`CustomWindow\` when constructing the main window.
- Title music load path changed from \`Title.mp3\` to \`title.mp3\` to match the actual asset name and avoid case-sensitivity issues on some platforms.
- Comment in \`GameEngine\` adjusted to clarify that the existing \`window\` member is being constructed rather than a different variable.

### Removed
- Previous \`CustomWindow\` constructor overload that did not take a cursor texture (replaced by the new signature).

### Fixed
- Inconsistent cursor behavior during window recreation by re-hiding the system cursor after toggling fullscreen.

## [V2.2]

### Added
- Additional debug logging in \`PlayingState::loadScene\` to print the scene name and confirm flow during scene transitions.

### Changed
- \`PlayingState::loadScene\` updated to use \`sceneScript->loadSceneScript(sceneName)\` for loading script data, aligning with current script-loading architecture.
- Scene loading flow adjusted so that button creation and option generation occur immediately after calling \`loadSceneScript\`, ensuring UI reflects newly loaded scene data.

### Fixed
- Prevented stale or missing scene data by ensuring the correct script loader (\`loadSceneScript\`) is called instead of older or inconsistent loading paths.

## [V2.3]

### Added
- New text-handling helpers in \`PlayingState\`:  
  - \`updateTextSizes()\`  
  - \`wrapText(...)\`  
  - \`getScaledCharacterSize(...)\`
- New fields in \`PlayingState\`:  
  - \`baseWindowSize\`  
  - \`pendingSceneId\`  
  - \`onScriptChain\` callback
- \`Choice\` data structure now includes \`nextScript\`.
- \`GameScript\` now includes a new \`ScriptMetadata\` block to hold chapter/unlock-related metadata.
- JSON script files updated to include a \`"metadata"\` object matching the new parser model.

### Changed
- Script loading flow in \`PlayingState::loadScene\` updated to support multi-script chaining and the new metadata structure.
- JSON format refactored so choices can specify \`nextScript\` and top-level metadata is parsed into \`GameScript::metadata\`.

### Removed
- Old \`Choice\` format that lacked \`nextScript\` (implicitly replaced by the extended structure).

### Fixed
- Parser alignment issues by ensuring the in-code structures now match the updated JSON format.
- Scene-transition bugs caused by missing metadata or missing script-chain support.

## [V2.4]

### Added
- Functionality in \`PlayingState\` to dynamically scale text to window size: implemented use of \`baseWindowSize\` to scale character size and wrap text appropriately when window is resized.

### Changed
- Text rendering in \`PlayingState\` now responds to window resizing: character sizes and text wrapping are recalculated based on the new window dimensions rather than remaining fixed.
- Scene-display code adjusted so that UI layout (including text and choice buttons) adapts to variable window sizes, improving responsiveness.

### Removed
- Fixed-size text layout assumptions previously hard-coded in scene rendering and choice positioning logic.

### Fixed
- Resolved issues where text and choice buttons overlapped or appeared off-screen when window was resized, now layout and text scale correctly with window resizes.

## [V2.5]

### Added
- A new \`speakerColor\` field to \`Scene\` in the script parser, allowing per-speaker color specification.  
- In \`DialogBox\`, a new static helper \`parseHexColor(...)\` to convert hex-string color codes (e.g. \`"#FF0000"\`) into \`sf::Color\`.  
- The \`DialogBox::setText(...)\` overload now accepts an optional \`speakerColor\` parameter so dialogs can display with the specified color.  

### Changed
- When loading a scene, \`PlayingState\` now passes \`currentScene->speakerColor\` to \`DialogBox::setText\`, so the speaker’s text color reflects the JSON data.  
- Update in scene-loading and layout-update code ensures the dialog is re-rendered with proper speaker color when the window or layout changes.  
- In the JSON script (e.g. \`intro.json\`), speaker color value changed for the "Narrator" to a different hex code.  

### Removed
- The default usage of \`DialogBox::setText(...)\` without speaker color remains available, but the old fallback default color logic inside parser was replaced by explicit color parsing (default: white).  

### Fixed
- Dialog display now properly supports colored speaker names/text, preventing cases where all dialog appeared in the same default color regardless of intended speaker color.  

## [V2.6]

### Added
- CMake now fetches and makes available the \`cpr\` HTTP client library and links it into the game target.
- New OpenAI integration headers: \`ChatGPT.h\`, \`ChatGPTError.h\`, and \`Types.h\` defining \`OpenAI::ChatGPT\`, an \`OpenAI::Error\` exception, and \`OpenAI::ChatCompletion\`/parsing helpers.
- New source files \`ChatGPT.cpp\` and \`ChatGPTError.cpp\` implementing the OpenAI client and error handling.
- New story-related assets: \`intro.json\` script plus scene images (\`scene1.png\`, \`scene2.png\`, \`scene3accept.png\`, \`scene3moreinfo.png\`, \`scene3reject.png\`).

### Changed
- Updated \`CMakeLists.txt\` to link \`cpr::cpr\` alongside SFML and \`nlohmann_json\` for HTTP-based OpenAI calls.

## [V2.7]

### Added
- Added \`DOCMAP.md\` containing a structured overview of the project's directory layout and file purposes.
- Expanded \`README.md\` with updated project description and reorganized feature/build sections.

### Changed
- Updated \`CMakeLists.txt\` to disable GPT integration by removing \`cpr\` from link targets and commenting out its FetchContent block.

### Removed
- Build-time inclusion and linking of the \`cpr\` HTTP client library.

## [V2.8]

### Added
- Initial full changelog file (\`CHANGELOG.md\`) with past release history imported.  
- New \`changelog.css\`, \`changelog.js\`, and \`changelog.html\` under \`/changelog\` for auto-generated or styled changelog view (plus updates to \`index.html\`, \`styles.css\`, README to integrate/changelog link).  

### Changed
- Project documentation structure updated: README + project root layout now includes changelog directory and assets. 

## [V2.9]

### Added
- Script-flag system: added \`flags\` and \`stats\` storage to \`PlayingState\`, along with methods to check conditions and apply effects.  
- Extended scripting support: in \`ScriptParser\`, added \`Condition\`, \`Effects\`, flag-based branching, optional stat modifications, and speakerColor + effects support for scenes.  
- New save/load support for flags and stats (save_data.json now includes flags & stats).  
- Choice-button logic: skip choices whose condition fails; reindexed button labels properly after filtering invalid choices.  

### Changed
- Resource loading path for background image switched from \`.jpg\` to \`.jpeg\`.  
- Build configuration update: removed \`WIN32\` flag in \`add_executable(...)\` call in CMakeLists.  

### Removed
- Removal of the old \`menuBackground.jpg\` reference in favor of \`.jpeg\`.  

### Fixed
- Script-flag logic now correctly evaluates conditions and applies effects (flags/stats) when scenes change or choices are made.  
- Fixed save-game file path to use \`assets/save_data.json\`.  

## [V2.10]

### Added
- Scene-transition support: added \`TransitionState\`, \`transitionOverlay\`, \`startTransition(...)\`, and \`updateTransition(...)\` in \`PlayingState\`.  
- Fade-out / fade-in overlay effect to visually transition between scenes (using a semi-transparent overlay painted over the window).  
- Automatic scene switching: on load or when a choice triggers a new scene, transitions now handle switching via overlay rather than abrupt jumps.  
- Window-resize handling for overlay: transition overlay now resizes/repositions properly when window size changes.  

### Changed
- Refactored choice-button logic to route scene changes through transition system instead of direct \`loadScene(...)\` calls.  
- Updated \`update(...)\`, \`handleEvent(...)\`, and \`createChoiceButtons()\` logic to respect transition states (no choice input during transitions, deferred scene loading until after fade-out).  
- Adjusted layout update: \`updatePositions(...)\` now includes overlay resizing/ repositioning in response to window size changes.  

### Removed
- Removed direct immediate scene load on choice selection - replaced by transition-based loading.  
- Removed old logic that bypassed overlay and loaded scenes immediately (e.g. direct calls to \`loadScene(...)\` inside choice handlers).  

### Fixed
- Prevented user input / choice handling during transitions to avoid inconsistent state or crashes while fading.  
- Fixed scene-load timing: scenes now load only after fade-out, avoiding visual glitches or abrupt screen changes.  

## [V2.11]

### Added
- Long intro fade-in sequence: the game now begins with a full-black overlay that gradually fades into the first scene, improving presentation and atmosphere.
- Added \`resetTransition()\` in \`MainMenuState\` to properly reset fade state when returning to the menu.

### Changed
- Adjusted transition timing in \`PlayingState\`: fade duration reduced from 0.5s to 0.25s for smoother scene flow.
- Updated \`MainMenuState\` to route drawing, updates, and event handling through the transition system so menu elements behave correctly during fades.

### Fixed
- Fixed an issue where game content briefly appeared before the intro fade-in completed.
- Ensured returning from a play session to the main menu fully resets the fade overlay, preventing the menu from appearing dim or partially faded.

## [V3.0]

### Added
- \`GameStateManager\` class to centralize narrative state: flag checks, effect application, and save/load of flags and stats from \`assets/save_data.json\`.
- \`PlayingStateUI\` class to own dialog box, layout manager, background/box shapes, and choice-button positioning and drawing.
- CMake entries for \`GameStateManager\` and \`PlayingStateUI\` in \`CORE_SOURCES\`, \`UI_SOURCES\`, and \`HEADERS\`.

### Changed
- \`PlayingState\` refactored to delegate:
  - Script/scene loading to \`SceneManager\`.
  - UI layout, dialog rendering, and choice placement to \`PlayingStateUI\`.
  - Flag/stat logic and save/load behavior to \`GameStateManager\`.
- \`PlayingState\` header simplified: removed direct ownership of dialog/layout/box shapes in favor of higher-level collaborators (\`PlayingStateUI\`, \`GameStateManager\`).
- Transition data cleaned up in \`PlayingState\`: \`transitionDuration\` turned into a \`const\` and related members reorganized.

### Removed
- Inline save/load, flag, and stat-handling logic from \`PlayingState\`.
- Direct UI layout and rectangle-shape management from \`PlayingState\` (now handled inside \`PlayingStateUI\`).

### Fixed
- Clearer separation of concerns reduces the risk of inconsistent state between flags/stats, UI layout, and scene data during transitions and saves.

## [V3.1]

### Added
- Inventory system: introduced \`InventorySystem\` to manage item definitions and track player inventory (items, quantities, stackable items, etc.).  
- Inventory UI: added \`InventoryUI\` to present inventory items visually, allow item listing, display tooltips (item name/description), and handle inventory layout / scrolling / interaction.  
- Inventory logic hooks: updated \`GameStateManager\`, \`SceneManager\`, \`ScriptParser\`, and \`PlayingStateUI\` to support item-related effects (e.g. adding items through script effects).  
- CMake build updates: added \`InventorySystem.cpp\` and \`InventoryUI.cpp\` to \`CORE_SOURCES\` and \`UI_SOURCES\`, and \`InventorySystem.h\` / \`InventoryUI.h\` to \`HEADERS\`.  

### Changed
- Refactored \`PlayingState\` to include a unique pointer to \`InventorySystem\` (in addition to previous state/UI managers), and updated include directives accordingly.  
- Extended script effect definitions (\`Effects\`) in \`ScriptParser\` to support item addition (e.g. \`addItem\`, \`addItemQuantity\`) besides flags/stats modifications.  
- Updated UI layout logic so that inventory UI coexists with dialog/choice UI (inventory pane, tooltips, etc.) when inventory is open.  

### Fixed
- Basic inventory functionality working: adding/removing items, stacking, loading item definitions, and reflecting inventory changes in UI.  
- Save/load integration: inventory data persists in save files (alongside flags and stats), preventing loss of items on reload.

## [V3.2]

### Added
- Save/load support enhanced: inventory, flags, and stats are now correctly persisted to \`assets/save_data.json\` and reloaded on game start.  
- Stat-mod UI: implemented UI elements to display player stats and any modifications (e.g. after effects) within the game interface.  
- Item tooltips: when hovering or selecting items in inventory UI, detailed tooltips (item name, description, quantity, stats/effects if relevant) are shown.  

### Changed
- Modified \`SaveLoadManager\` (or equivalent save/load routines) to include inventory, flags, and stats in serialized game data.  
- Updated UI layout logic so inventory UI and stat-mod UI integrate cleanly without overlapping dialog/choice boxes - proper layering and layout adjustments done.  

### Fixed
- Fixed bugs in save/load that previously caused inventory or stat data to be lost between sessions.  
- Corrected tooltip logic: item tooltips now display correct data and update properly when inventory or stats change.  

## [V3.3]

### Added
- Intro screen artwork and scene: new visual assets and a dedicated intro scene before main menu.  
- Background / atmospheric music for main menu re-enabled - adds ambient/main-menu soundtrack when on menu screen.

### Changed
- Entry flow updated: game now starts with intro scene (with art), then transitions to main menu with music.  
- Adjusted main menu UI and background layout to accommodate new intro-to-menu transition and artwork.

### Fixed
- Resolved prior bug where main menu music did not trigger - music now reliably starts when reaching main menu.  
- Fixed potential mismatch between menu UI and background art (layout, scaling, or display issues) when using new intro artwork and scene.

## [V3.4]

### Added
- New art assets: multiple background images (forest edge, village backstreet, village square burning, void scenes, etc.) added under \`assets/images\`.  
- Expanded scene library: new scenes using the added background assets, enabling a broader variety of visuals and narrative paths.  

### Changed
- Updated asset loading logic to include the new background images and ensure proper path resolution in \`SceneManager\` / \`GameStateManager\`.  
- Adjusted UI layout and scaling to accommodate backgrounds with different aspect ratios/resolutions - dialog boxes, choice buttons, and overlays now dynamically scale/position based on background dimensions.  

### Removed
- Removed outdated placeholder or test images (if any) in favor of the new finalized background assets.  

### Fixed
- Corrected mismatches between background asset names/paths and code references - prevents missing-texture or crash-on-load issues when switching scenes.  
- Fixed save-load interplay to ensure that scene transitions referencing the new assets preserve flag/stat/inventory state correctly across sessions.  

## [V3.5]

### Added
- Scrollable inventory UI: added scrolling support to inventory view so large inventories can be navigated with mouse wheel or scroll offsets.  
- \`ConfirmationDialog\` added to \`PlayingStateUI\`, enabling confirm-type dialogs overlaid on the UI (e.g. when confirming item use or other choices).  

### Changed
- Modified \`InventoryUI\` internals: \`updateScroll(...)\`, \`getMaxScroll(...)\`, and grid-cell indexing logic updated to properly calculate item indices and scroll offsets (fixed incorrect indexing previously).  
- Updated \`PlayingStateUI\` initialization to include the new \`InventoryUI\` and \`ConfirmationDialog\` objects, integrating inventory display and confirmation dialog support into the main UI flow.  

### Fixed
- Fixed bug where inventory grid-cell indexing was wrong ( item selection / tooltip / click / draw mismatches resolved ).  
- Fixed scroll-limit and tooltip display logic so inventory UI behaves correctly for variable item counts without out-of-bounds or visual glitches.

## [V3.6]

### Added
- New Midgard forest and gate background images: \`bg_midgard_forest_crossroads\`, \`bg_midgard_forest_dirt1/2/3\`, \`bg_midgard_forest_gate\`, \`bg_midgard_forest_gate_open\`, and \`bg_midgard_village_square_ashes\`.
- New \`bronze_key.png\` item sprite and corresponding \`bronze_key\` item entry in \`items.json\`.
- Extended intro script branch:
  - Bull-fight failure and aftermath scenes (\`a1_s12_bull_failure\`, \`a1_s13_burned_village_wake\`).
  - Forest crossroads hub (\`a1_s20_forest_crossroads\` / \`a1_s29_forest_crossroads\`) with four path options.
  - Three puzzle-path chains (\`a1_s22/23\`, \`a1_s24/25\`, \`a1_s26–28\`) including a choice that rewards the bronze key.
  - Gate approach, locked gate, and unlock scenes (\`a1_s21\`, \`a1_s21b\`, \`a1_s30\`, \`a1_s31\`, \`a1_s32\`) that use the bronze key to open the way forward.

### Changed
- Updated existing choice text in the burning-village sequence (e.g. "Frolic away from the chaos.") and rerouted some choices to the new forest / failure branches instead of older placeholders (e.g. replacing \`BATTLE_BULL\` with \`a1_s12_bull_failure\`).
- Adjusted a "Keep moving into the forest" branch to lead into the new \`a1_s20_forest_crossroads\` scene.
- Refined \`items.json\` entry: renamed \`key_bronze\` → \`bronze_key\`, updated description to "Opens big gates.", and pointed the texture path at \`assets/items/bronze_key.png\`.
- Added script \`effects\` blocks to grant and later consume the bronze key (via \`addItem: "bronze_key"\` and \`addItemQuantity\` ±1) during the puzzle/gate sequence.

### Removed
- Old \`ancient_scroll\` and \`gold_coin\` item definitions from \`items.json\`.
- Previous health-potion reward \`effects\` on the bull-intro choice block (replaced by the new forest progression path).

### Fixed
- Aligned item IDs and textures between \`items.json\` and script effects so bronze-key acquisition/usage works consistently with the inventory system.
- Cleaned up punctuation and minor text inconsistencies in intro choices (e.g. ellipsis formatting).`;

// ===== Markdown rendering logic =====

document.addEventListener("DOMContentLoaded", () => {
  const root = document.getElementById("changelogRoot");
  if (!root) return;

  root.innerHTML = markdownToHtml(RAW_CHANGELOG_MD);
  document.title = "Changelog – Untitled Adventure Game";
});

function markdownToHtml(md) {
  const lines = md.split(/\r?\n/);
  let html = "";
  let inList = false;

  function closeList() {
    if (inList) {
      html += "</ul>";
      inList = false;
    }
  }

  for (let i = 0; i < lines.length; i++) {
    const rawLine = lines[i];
    const line = rawLine.trimEnd();

    if (!line.trim()) {
      closeList();
      continue;
    }

    // Headings
    let m;
    if ((m = line.match(/^###\s+(.*)/))) {
      closeList();
      html += `<h3>${inlineFormat(m[1])}</h3>`;
      continue;
    }
    if ((m = line.match(/^##\s+(.*)/))) {
      closeList();
      html += `<h2>${inlineFormat(m[1])}</h2>`;
      continue;
    }
    if ((m = line.match(/^#\s+(.*)/))) {
      closeList();
      html += `<h1>${inlineFormat(m[1])}</h1>`;
      continue;
    }

    // Unordered list item
    if ((m = line.match(/^[-*]\s+(.*)/))) {
      if (!inList) {
        html += "<ul>";
        inList = true;
      }
      html += `<li>${inlineFormat(m[1])}</li>`;
      continue;
    }

    // Paragraph
    closeList();
    html += `<p>${inlineFormat(line)}</p>`;
  }

  closeList();
  return html;
}

function inlineFormat(text) {
  // Escape HTML
  let out = text
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;");

  // Links: [text](url)
  out = out.replace(
    /\[([^\]]+)\]\(([^)]+)\)/g,
    '<a href="$2" target="_blank" rel="noreferrer">$1</a>'
  );

  // Inline code: `code`
  out = out.replace(/`([^`]+)`/g, "<code>$1</code>");

  // Bold: **text**
  out = out.replace(/\*\*(.+?)\*\*/g, "<strong>$1</strong>");

  // Italic: *text*
  out = out.replace(/\*(.+?)\*/g, "<em>$1</em>");

  return out;
}
