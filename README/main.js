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
      "Resource & settings management"
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
        "value": "CMake \u2265 3.28",
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
        "Untitled Adventure Game is my C++ game featuring a custom window system with a draggable titlebar, fullscreen support, and an intuitive menu system. It's been built for my CS 135 class under Prof. Damien Ennis using a cumulation of documents from the web from sources such as StackOverflow, the SFML documentation, and various C++ programming tutorials. (I have done my best to link these docs where applicable in my source code.)"
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
        }
      ],
      "chips": [
        "Borderless window",
        "Draggable titlebar",
        "Fullscreen toggle",
        "Volume sliders",
        "Texture & sound caching"
      ]
    },
    {
      "id": "building",
      "navLabel": "Building",
      "title": "Building",
      "type": "bullets",
      "items": [
        "Install CMake Tools extension on VS Code",
        "Press the build button in the toolbar .-.",
        "(If this doesn't work then uh.... \"It worked fine on my PC\" xD)"
      ]
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
        "A burning love for massochism",
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
    }
  ],
  "fileMap": {
    "introParagraphs": [
      "Welcome to a tour of the project\u2019s file system. The whole thing is organized into four main folders, each with its own job:"
    ],
    "folderOverview": [
      {
        "name": "include",
        "description": "All the header files. Every .h that defines the structure for its matching .cpp."
      },
      {
        "name": "src/core",
        "description": "The \u201cengine room.\u201d These are the core .cpp files that keep the game running: the Game Engine, Scene Manager, Resource Manager, Script Parser, and other foundational systems."
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
    "afterOverviewText": "That\u2019s a high-level map. Below is the full breakdown of every file.",
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
            "name": "DialogBox.cpp",
            "href": "src/ui/DialogBox.cpp",
            "copyPath": "src/ui/DialogBox.cpp"
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
            "description": "Main game loop and state management"
          },
          {
            "name": "CustomWindow",
            "description": "Custom window implementation with titlebar"
          },
          {
            "name": "ResourceManager",
            "description": "Asset loading and caching system"
          },
          {
            "name": "ScriptParser",
            "description": "JSON script parsing for game scenes"
          },
          {
            "name": "SceneManager",
            "description": "Scene loading and management"
          }
        ]
      },
      {
        "title": "UI Components",
        "items": [
          {
            "name": "Button",
            "description": "Interactive button widget"
          },
          {
            "name": "DialogBox",
            "description": "Text display with speaker names"
          },
          {
            "name": "LayoutManager",
            "description": "Responsive layout calculations"
          }
        ]
      },
      {
        "title": "Game States",
        "items": [
          {
            "name": "MainMenuState",
            "description": "Main menu screen"
          },
          {
            "name": "StartState",
            "description": "Game start placeholder"
          },
          {
            "name": "SettingsState",
            "description": "Volume and settings control"
          },
          {
            "name": "PlayingState",
            "description": "Active gameplay screen"
          }
        ]
      },
      {
        "title": "Data Structures",
        "items": [
          {
            "name": "GameState",
            "description": "Abstract base class for all game states"
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
      case "features":
        renderFeaturesSection(section, container);
        break;
      case "bullets":
        renderBulletSection(section, container);
        break;
      case "fileMap":
        renderDocMapSection(section, container, data.fileMap);
        break;
      case "fileDescriptions":
        renderFileDescriptionsSection(
          section,
          container,
          data.fileDescriptions
        );
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
        const br = document.createElement("br");
        li.appendChild(br);
        li.appendChild(
          document.createTextNode(folder.description)
        );
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

      let nameInner;
      if (item.href) {
        const link = document.createElement("a");
        link.href = item.href;
        const code = document.createElement("code");
        code.textContent = item.name || "";
        link.appendChild(code);
        nameInner = link;
      } else {
        const code = document.createElement("code");
        code.textContent = item.name || "";
        nameInner = code;
      }

      nameDiv.appendChild(nameInner);

      if (item.note) {
        const noteSpan = document.createElement("span");
        noteSpan.className = "file-note";
        noteSpan.textContent = item.note;
        nameDiv.appendChild(noteSpan);
      }

      mainDiv.appendChild(prefixSpan);
      mainDiv.appendChild(nameDiv);
      li.appendChild(mainDiv);

      if (item.copyPath) {
        const btn = document.createElement("button");
        btn.className = "copy-btn";
        btn.type = "button";
        btn.dataset.path = item.copyPath;
        btn.dataset.label = "Copy";

        const icon = document.createElement("span");
        icon.className = "copy-btn-icon";
        icon.textContent = "📋";

        const label = document.createElement("span");
        label.className = "copy-btn-label";
        label.textContent = "Copy";

        btn.appendChild(icon);
        btn.appendChild(label);
        li.appendChild(btn);
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
        li.appendChild(
          document.createTextNode(` – ${item.description}`)
        );
      }
      ul.appendChild(li);
    });
    container.appendChild(ul);
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
      if (section.offsetTop <= fromTop) {
        currentId = section.id;
      }
    });

    navLinks.forEach((link) => {
      const id = link.getAttribute("href").slice(1);
      if (id === currentId) {
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
      const text =
        item.dataset.file ||
        (item.textContent || "").toLowerCase();
      if (!query || text.indexOf(query) !== -1) {
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

      navigator.clipboard
        .writeText(path)
        .then(() => {
          const labelSpan = btn.querySelector(
            ".copy-btn-label"
          );
          const originalLabel =
            btn.dataset.label || "Copy";
          if (!labelSpan) return;

          labelSpan.textContent = "Copied!";
          setTimeout(() => {
            labelSpan.textContent = originalLabel;
          }, COPY_RESET_MS);
        })
        .catch(() => {
          // Silently fail; no UI change
        });
    });
  });
}
