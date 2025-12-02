// ===== CONFIG: Data Sources & UX behavior =====

const README_URL = 'README.md';
const CHANGELOG_URL = 'CHANGELOG.md';

const BACK_TO_TOP_THRESHOLD = 260;
const SCROLL_OFFSET_PX = 120;
const COPY_RESET_MS = 900;

// ===== Entry point =====

document.addEventListener("DOMContentLoaded", async () => {
  try {
    const readmeText = await fetch(README_URL).then(r => r.text());
    const data = parseReadmeToPageData(readmeText);
    initPage(data);
  } catch (err) {
    console.error('Failed to load README.md:', err);
    document.getElementById('hero').innerHTML = `
      <div style="color: var(--color-text); padding: 2rem;">
        <h1>Error Loading Content</h1>
        <p>Could not load README.md. Please ensure the file exists in the root directory.</p>
      </div>
    `;
  }
});

// ===== Parse README.md into PAGE_DATA structure =====

function parseReadmeToPageData(markdown) {
  const lines = markdown.split('\n');
  const data = {
    project: {},
    hero: {},
    navigationTitle: "On this page",
    sections: [],
    fileMap: { groups: [] },
    fileDescriptions: { categories: [] }
  };

  let currentSection = null;
  let currentList = [];
  let inCodeBlock = false;

  for (let i = 0; i < lines.length; i++) {
    const line = lines[i];
    
    // Handle code blocks
    if (line.startsWith('```')) {
      inCodeBlock = !inCodeBlock;
      continue;
    }
    if (inCodeBlock) continue;

    // Extract project title (first H1)
    if (line.startsWith('# ') && !data.project.title) {
      data.project.title = line.slice(2).trim();
      data.hero.heading = data.project.title;
      continue;
    }

    // Extract sections based on H2 headers
    if (line.startsWith('## ')) {
      if (currentSection) {
        finalizeSection(currentSection, currentList, data);
      }
      
      const title = line.slice(3).trim();
      const id = title.toLowerCase().replace(/[^a-z0-9]+/g, '-');
      
      currentSection = {
        id,
        navLabel: title,
        title,
        type: 'paragraphs',
        body: []
      };
      currentList = [];
      continue;
    }

    // Handle list items
    if (line.match(/^[-*]\s+/) && currentSection) {
      const item = line.replace(/^[-*]\s+/, '').trim();
      currentList.push(item);
      currentSection.type = 'bullets';
      continue;
    }

    // Handle paragraphs
    if (line.trim() && !line.startsWith('#') && currentSection) {
      currentSection.body.push(line.trim());
    }
  }

  // Finalize last section
  if (currentSection) {
    finalizeSection(currentSection, currentList, data);
  }

  // Set defaults
  data.project.subtitle = "2D text-oriented | C++ · SFML 3.x";
  data.project.pill = "Norse-inspired story";
  data.project.topChip = "Single-page project overview";
  
  data.hero.tagline = "A 2D text-oriented adventure game built with C++ and SFML 3.x.";
  data.hero.metaTags = ["Language: C++17", "Framework: SFML 3.x"];
  data.hero.badges = ["Custom window system", "State-based architecture"];
  data.hero.snapshotLabel = "Build snapshot";
  data.hero.snapshotBadge = "CMake · Git · SFML";
  data.hero.grid = [
    { label: "Core tech", value: "C++17 · SFML 3.x", note: "Windowing, input, audio" },
    { label: "Architecture", value: "State-driven", note: "Multiple game states" }
  ];

  return data;
}

function finalizeSection(section, listItems, data) {
  if (section.type === 'bullets') {
    section.items = listItems;
    delete section.body;
  }
  
  // Special handling for known sections
  if (section.id.includes('gallery')) {
    section.type = 'gallery';
  } else if (section.id.includes('file') || section.id.includes('document')) {
    section.type = 'fileMap';
  } else if (section.id.includes('feature')) {
    section.type = 'features';
    section.items = listItems.map(item => {
      const match = item.match(/\*\*(.*?)\*\*:\s*(.*)/);
      if (match) {
        return { strong: match[1], text: match[2] };
      }
      return { strong: item.split(':')[0], text: item.split(':')[1] || '' };
    });
  }
  
  data.sections.push(section);
}

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

// ===== Keep all existing functions below unchanged =====

function setProjectHeader(project) {
  if (!project) return;

  const titleEl = document.getElementById("projectTitle");
  const subtitleEl = document.getElementById("projectSubtitle");
  const pillTextEl = document.getElementById("projectPillText");
  const pillEl = document.getElementById("projectPill");
  const topChipEl = document.getElementById("topChip");

  if (titleEl && project.title) titleEl.textContent = project.title;
  if (subtitleEl && project.subtitle) subtitleEl.textContent = project.subtitle;
  if (pillTextEl && project.pill) pillTextEl.textContent = project.pill;
  else if (pillEl) pillEl.style.display = 'none';
  if (topChipEl && project.topChip) topChipEl.textContent = project.topChip;
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
        ${item.note ? `<div class="hero-grid-note">${item.note}</div>` : ""}
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

function buildSections(sections, data) {
  if (!Array.isArray(sections)) return;

  sections.forEach((section) => {
    const container = document.getElementById(section.id);
    if (!container) return;

    switch (section.type) {
      case 'paragraphs':
        renderParagraphSection(section, container);
        break;
      case 'features':
        renderFeaturesSection(section, container);
        break;
      case 'bullets':
        renderBulletSection(section, container);
        break;
      case 'gallery':
        renderGallerySection(section, container);
        break;
      case 'fileMap':
        renderDocMapSection(section, container, data.fileMap);
        break;
      case 'fileDescriptions':
        renderFileDescriptionsSection(section, container, data.fileDescriptions);
        break;
      case 'funFact':
        renderFunFactSection(section, container);
        break;
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
    if (item.strong) {
      const strong = document.createElement("strong");
      strong.textContent = item.strong;
      li.appendChild(strong);
      li.appendChild(document.createTextNode(": " + (item.text || "")));
    } else {
      li.textContent = item;
    }
    ul.appendChild(li);
  });
  container.appendChild(ul);

  if (section.chips && section.chips.length) {
    const chipRow = document.createElement("div");
    chipRow.className = "pill-row";
    section.chips.forEach((chip) => {
      const span = document.createElement("span");
      span.className = "pill";
      span.textContent = chip;
      chipRow.appendChild(span);
    });
    container.appendChild(chipRow);
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
    item.innerHTML = `
      <img src="${img.src}" alt="${img.caption}" loading="lazy">
      <div class="gallery-item-caption">${img.caption}</div>
    `;
    item.addEventListener('click', () => openLightbox(index, images));
    grid.appendChild(item);
  });

  container.appendChild(grid);
}

function renderDocMapSection(section, container, fileMap) {
  container.innerHTML = "";
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

  search.appendChild(searchIcon);
  search.appendChild(searchInput);
  header.appendChild(h2);
  header.appendChild(search);
  container.appendChild(header);

  const intro = document.createElement("p");
  intro.textContent = "Below is the complete file structure of this project.";
  container.appendChild(intro);
}

function renderFileDescriptionsSection(section, container, fileDescriptions) {
  container.innerHTML = "";
  const h2 = document.createElement("h2");
  h2.textContent = section.title || "File Descriptions";
  container.appendChild(h2);
}

function renderFunFactSection(section, container) {
  container.innerHTML = "";
  const h2 = document.createElement("h2");
  h2.textContent = section.title || "Fun Fact";
  container.appendChild(h2);

  (section.body || []).forEach((text) => {
    const p = document.createElement("p");
    p.textContent = text;
    container.appendChild(p);
  });
}

function buildSideNav(sections, navTitle) {
  const nav = document.getElementById("sideNav");
  if (!nav) return;

  nav.innerHTML = `
    <div class="side-nav-title">${navTitle || "On this page"}</div>
    <ul>
      ${sections.map(s => `
        <li><a href="#${s.id}">${s.navLabel || s.title}</a></li>
      `).join('')}
    </ul>
  `;
}

function setupBackToTop() {
  const btn = document.getElementById("backToTop");
  if (!btn) return;

  window.addEventListener("scroll", () => {
    if (window.scrollY > BACK_TO_TOP_THRESHOLD) {
      btn.classList.add("visible");
    } else {
      btn.classList.remove("visible");
    }
  });

  btn.addEventListener("click", () => {
    window.scrollTo({ top: 0, behavior: "smooth" });
  });
}

function setupScrollSpy(sections) {
  const links = document.querySelectorAll(".side-nav a");
  if (!links.length) return;

  window.addEventListener("scroll", () => {
    let current = "";
    sections.forEach((section) => {
      const el = document.getElementById(section.id);
      if (el && el.getBoundingClientRect().top < SCROLL_OFFSET_PX) {
        current = section.id;
      }
    });

    links.forEach((link) => {
      link.classList.remove("active");
      if (link.getAttribute("href") === `#${current}`) {
        link.classList.add("active");
      }
    });
  });
}

function setupFileSearch() {
  const input = document.getElementById("fileSearchInput");
  if (!input) return;

  input.addEventListener("input", (e) => {
    const query = e.target.value.toLowerCase();
    document.querySelectorAll(".file-item").forEach((item) => {
      const text = item.textContent.toLowerCase();
      item.classList.toggle("hidden-by-filter", !text.includes(query));
    });
  });
}

function setupCopyButtons() {
  document.querySelectorAll(".copy-btn").forEach((btn) => {
    btn.addEventListener("click", async () => {
      const path = btn.dataset.path;
      try {
        await navigator.clipboard.writeText(path);
        const original = btn.innerHTML;
        btn.innerHTML = '<span class="copy-btn-icon">✓</span> Copied!';
        setTimeout(() => {
          btn.innerHTML = original;
        }, COPY_RESET_MS);
      } catch (err) {
        console.error("Copy failed:", err);
      }
    });
  });
}

let currentLightboxIndex = 0;
let lightboxImages = [];

function openLightbox(index, images) {
  currentLightboxIndex = index;
  lightboxImages = images;
  
  let lightbox = document.getElementById('lightbox');
  if (!lightbox) {
    lightbox = createLightbox();
  }
  
  updateLightboxContent();
  lightbox.classList.add('active');
  document.addEventListener('keydown', handleLightboxKeys);
}

function createLightbox() {
  const lightbox = document.createElement('div');
  lightbox.id = 'lightbox';
  lightbox.className = 'lightbox';
  lightbox.innerHTML = `
    <button class="lightbox-close" aria-label="Close lightbox">×</button>
    <button class="lightbox-nav prev" aria-label="Previous image">‹</button>
    <button class="lightbox-nav next" aria-label="Next image">›</button>
    <div class="lightbox-content">
      <div class="lightbox-image-wrapper">
        <img class="lightbox-image" src="" alt="">
      </div>
      <div class="lightbox-caption"></div>
    </div>
  `;
  
  document.body.appendChild(lightbox);
  
  lightbox.querySelector('.lightbox-close').addEventListener('click', closeLightbox);
  lightbox.querySelector('.prev').addEventListener('click', () => navigateLightbox(-1));
  lightbox.querySelector('.next').addEventListener('click', () => navigateLightbox(1));
  lightbox.addEventListener('click', (e) => {
    if (e.target === lightbox) closeLightbox();
  });
  
  return lightbox;
}

function updateLightboxContent() {
  const lightbox = document.getElementById('lightbox');
  const img = lightbox.querySelector('.lightbox-image');
  const caption = lightbox.querySelector('.lightbox-caption');
  const current = lightboxImages[currentLightboxIndex];
  
  img.src = current.src;
  img.alt = current.caption;
  caption.textContent = current.caption;
}

function closeLightbox() {
  const lightbox = document.getElementById('lightbox');
  lightbox.classList.remove('active');
  document.removeEventListener('keydown', handleLightboxKeys);
}

function navigateLightbox(direction) {
  currentLightboxIndex = (currentLightboxIndex + direction + lightboxImages.length) % lightboxImages.length;
  updateLightboxContent();
}

function handleLightboxKeys(e) {
  if (e.key === 'Escape') closeLightbox();
  else if (e.key === 'ArrowLeft') navigateLightbox(-1);
  else if (e.key === 'ArrowRight') navigateLightbox(1);
}