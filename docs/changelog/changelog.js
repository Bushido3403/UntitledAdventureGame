// ===== CONFIG: Markdown source =====

const CHANGELOG_URL = 'CHANGELOG.md';

// ===== Simple Markdown to HTML converter =====

function markdownToHtml(markdown) {
  let html = markdown;

  // Headers
  html = html.replace(/^### (.*$)/gim, '<h3>$1</h3>');
  html = html.replace(/^## (.*$)/gim, '<h2>$1</h2>');
  html = html.replace(/^# (.*$)/gim, '<h1>$1</h1>');

  // Bold
  html = html.replace(/\*\*(.*?)\*\*/g, '<strong>$1</strong>');

  // Inline code
  html = html.replace(/`([^`]+)`/g, '<code>$1</code>');

  // Links
  html = html.replace(/\[([^\]]+)\]\(([^)]+)\)/g, '<a href="$2">$1</a>');

  // Lists
  html = html.replace(/^\* (.*)$/gim, '<li>$1</li>');
  html = html.replace(/^- (.*)$/gim, '<li>$1</li>');

  // Wrap consecutive <li> in <ul>
  html = html.replace(/(<li>.*<\/li>\n?)+/g, (match) => {
    return '<ul>' + match + '</ul>';
  });

  // Paragraphs
  html = html.split('\n\n').map(para => {
    if (para.startsWith('<h') || para.startsWith('<ul') || para.trim() === '') {
      return para;
    }
    return '<p>' + para.replace(/\n/g, ' ') + '</p>';
  }).join('\n');

  return html;
}

// ===== Entry point =====

document.addEventListener('DOMContentLoaded', async () => {
  const root = document.getElementById('changelogRoot');
  
  try {
    const response = await fetch(CHANGELOG_URL);
    if (!response.ok) throw new Error(`HTTP ${response.status}`);
    
    const markdown = await response.text();
    const html = markdownToHtml(markdown);
    
    root.innerHTML = html;
  } catch (err) {
    console.error('Failed to load changelog:', err);
    root.innerHTML = `
      <div style="color: var(--color-text); padding: 2rem;">
        <h2>Error Loading Changelog</h2>
        <p>Could not load CHANGELOG.md. Please ensure the file exists in the root directory.</p>
        <p style="font-size: 0.85rem; color: var(--color-text-muted);">Error: ${err.message}</p>
      </div>
    `;
  }
});