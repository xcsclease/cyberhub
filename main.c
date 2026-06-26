<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>CyberHub – UI Preview</title>
<style>
  * { margin: 0; padding: 0; box-sizing: border-box; }

  body {
    background: #0a0a14;
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    min-height: 100vh;
    font-family: 'Courier New', monospace;
    color: #00ffff;
  }

  h1 {
    color: #555577;
    font-size: 12px;
    letter-spacing: 4px;
    margin-bottom: 20px;
    text-transform: uppercase;
  }

  /* ── 3DS Shell ─────────────────────────────────── */
  .ds-shell {
    background: #1a1a2e;
    border-radius: 18px 18px 0 0;
    padding: 14px 18px 10px;
    border: 2px solid #2a2a44;
    box-shadow: 0 0 40px rgba(0,0,0,0.8), inset 0 1px 0 rgba(255,255,255,0.05);
    position: relative;
  }
  .ds-shell-bottom {
    background: #161628;
    border-radius: 0 0 22px 22px;
    padding: 10px 18px 20px;
    border: 2px solid #2a2a44;
    border-top: none;
    display: flex;
    flex-direction: column;
    align-items: center;
    box-shadow: 0 10px 40px rgba(0,0,0,0.8);
    position: relative;
  }

  .hinge {
    height: 8px;
    background: #111122;
    border-top: 1px solid #2a2a44;
    border-bottom: 1px solid #2a2a44;
    margin: 0 -2px;
  }

  /* Camera dot */
  .camera {
    width: 6px; height: 6px;
    background: #222244;
    border-radius: 50%;
    margin: 0 auto 8px;
    border: 1px solid #333355;
  }

  /* ── Screen base styles ────────────────────────── */
  .screen {
    position: relative;
    overflow: hidden;
    border-radius: 4px;
    border: 2px solid #0d0d22;
    box-shadow: inset 0 0 12px rgba(0,0,0,0.6), 0 0 0 1px #333355;
  }
  .screen-top    { width: 400px; height: 240px; }
  .screen-bottom { width: 320px; height: 240px; margin-top: 4px; }

  /* Grid background */
  .screen-bg {
    position: absolute; inset: 0;
    background-color: #060612;
    background-image:
      linear-gradient(rgba(0,56,88,0.14) 1px, transparent 1px),
      linear-gradient(90deg, rgba(0,56,88,0.14) 1px, transparent 1px);
    background-size: 20px 20px;
  }

  /* Scanlines overlay */
  .scanlines {
    position: absolute; inset: 0; pointer-events: none; z-index: 100;
    background: repeating-linear-gradient(
      to bottom,
      transparent 0px, transparent 1px,
      rgba(0,0,0,0.18) 1px, rgba(0,0,0,0.18) 2px
    );
  }

  /* ── Neon utilities ────────────────────────────── */
  .neon-cyan   { color: #00ffff; text-shadow: 0 0 6px #00ffff, 0 0 14px #00ffff88; }
  .neon-pink   { color: #ff0088; text-shadow: 0 0 6px #ff0088, 0 0 14px #ff008888; }
  .neon-green  { color: #08ff44; text-shadow: 0 0 6px #08ff44, 0 0 14px #08ff4488; }
  .neon-red    { color: #ff0808; text-shadow: 0 0 6px #ff0808, 0 0 14px #ff080888; }
  .neon-yellow { color: #ffcc00; text-shadow: 0 0 6px #ffcc00; }
  .dim-cyan    { color: #009999; }
  .dim-pink    { color: #880044; }
  .dim-green   { color: #047720; }
  .gray        { color: #555577; }
  .white       { color: #e0e0ff; }

  /* Glow borders */
  .border-cyan {
    box-shadow:
      0 0 2px #00ffff22,
      0 0 5px #00ffff44,
      0 0 8px #00ffff66,
      inset 0 0 4px #00ffff11;
    border: 1px solid #00ffff;
  }
  .border-pink {
    box-shadow: 0 0 4px #ff008844, 0 0 8px #ff008866;
    border: 1px solid #ff008888;
  }

  /* ── Top screen layout ─────────────────────────── */
  .top-header {
    position: absolute; top: 0; left: 0; right: 0; height: 26px;
    background: rgba(4,14,32,0.95);
    display: flex; align-items: center; justify-content: space-between;
    padding: 0 8px;
    border-bottom: 1px solid rgba(0,255,255,0.2);
    z-index: 10;
  }
  .top-header::after {
    content: '';
    position: absolute; bottom: 0; left: 0; right: 0; height: 1px;
    background: linear-gradient(90deg, transparent, #00ffff44, #00ffff88, #00ffff44, transparent);
  }

  .header-title {
    font-size: 11px; letter-spacing: 2px; font-weight: bold;
    animation: blink-cyan 2s step-end infinite;
  }
  @keyframes blink-cyan {
    0%,49% { color:#00ffff; text-shadow: 0 0 8px #00ffff; }
    50%,100%{ color:#009999; text-shadow: none; }
  }

  .header-right {
    display: flex; gap: 10px; align-items: center;
  }
  .status-online { font-size: 9px; letter-spacing: 1px; }
  .frame-counter { font-size: 8px; color: #222233; }

  /* Entry list */
  .entry-list {
    position: absolute; top: 32px; left: 0; right: 0; bottom: 20px;
    z-index: 5;
  }

  .entry {
    height: 27px;
    display: flex; align-items: center;
    padding: 0 8px;
    position: relative;
    border-bottom: 1px solid #222233;
    font-size: 10px;
  }
  .entry.selected {
    background: rgba(0,40,72,0.8);
    border-bottom-color: transparent;
  }
  .entry.selected::before,
  .entry.selected::after {
    content: '';
    position: absolute; left: 4px; right: 4px;
    height: 1px;
  }
  .entry.selected::before { top: 0;    background: linear-gradient(90deg, transparent, #00ffff66, #00ffff, #00ffff66, transparent); }
  .entry.selected::after  { bottom: 0; background: linear-gradient(90deg, transparent, #00ffff44, #00ffff88, #00ffff44, transparent); }

  .entry-arrow { width: 14px; color: #00ffff; text-shadow: 0 0 6px #00ffff; }
  .entry-name  { flex: 1; overflow: hidden; white-space: nowrap; text-overflow: ellipsis; }
  .entry-badge { font-size: 9px; padding: 1px 3px; margin-left: 6px; }

  /* Top footer */
  .top-footer {
    position: absolute; bottom: 0; left: 0; right: 0; height: 20px;
    background: rgba(4,14,32,0.95);
    display: flex; align-items: center; justify-content: space-between;
    padding: 0 8px;
    border-top: 1px solid rgba(255,0,136,0.2);
    font-size: 9px; z-index: 10;
  }
  .top-footer::before {
    content: '';
    position: absolute; top: 0; left: 0; right: 0; height: 1px;
    background: linear-gradient(90deg, transparent, #ff008844, #ff008888, #ff008844, transparent);
  }

  /* Psy meter */
  .psy-value { animation: psy-color 4s ease-in-out infinite alternate; }
  @keyframes psy-color {
    0%   { color: #08ff44; text-shadow: 0 0 5px #08ff44; }
    60%  { color: #ffcc00; text-shadow: 0 0 5px #ffcc00; }
    100% { color: #ff0808; text-shadow: 0 0 8px #ff0808; }
  }

  /* Corner decorations */
  .corner {
    position: absolute; width: 10px; height: 10px;
    border-color: rgba(0,255,255,0.3);
    border-style: solid;
    z-index: 20;
  }
  .corner.tl { top: 27px;  left: 4px;  border-width: 1px 0 0 1px; }
  .corner.tr { top: 27px;  right: 4px; border-width: 1px 1px 0 0; }
  .corner.bl { bottom: 21px; left: 4px;  border-width: 0 0 1px 1px; }
  .corner.br { bottom: 21px; right: 4px; border-width: 0 1px 1px 0; }


  /* ── Bottom screen layout ──────────────────────── */
  .bot-logo-panel {
    position: absolute; top: 0; left: 0; right: 0; height: 42px;
    background: rgba(4,14,32,0.95);
    display: flex; flex-direction: column;
    align-items: center; justify-content: center; gap: 2px;
    border-bottom: 1px solid rgba(255,0,136,0.25);
    z-index: 10;
  }
  .bot-logo-panel::after {
    content: '';
    position: absolute; bottom: 0; left: 0; right: 0; height: 1px;
    background: linear-gradient(90deg, transparent, #ff008866, #ff0088bb, #ff008866, transparent);
  }

  .logo-text {
    font-size: 14px; font-weight: bold; letter-spacing: 6px;
    animation: logo-pulse 2s ease-in-out infinite;
  }
  @keyframes logo-pulse {
    0%,100% { color:#00cccc; text-shadow: 0 0 8px #00cccc88; }
    50%     { color:#00ffff; text-shadow: 0 0 12px #00ffff, 0 0 24px #00ffff66; }
  }
  .logo-sub { font-size: 8px; letter-spacing: 2px; color: #009999; }

  /* Info panel */
  .bot-info {
    position: absolute; top: 50px; left: 6px; right: 6px;
    height: 78px;
    background: rgba(4,14,32,0.9);
    padding: 6px 10px;
    z-index: 10;
  }
  .info-label { font-size: 8px; color: #009999; margin-bottom: 3px; }
  .info-name  { font-size: 11px; margin-bottom: 5px; }
  .info-type  { font-size: 8px; margin-bottom: 4px; }
  .info-path  { font-size: 7px; color: #555577; }

  /* Controls */
  .bot-controls {
    position: absolute; bottom: 0; left: 0; right: 0;
    height: 102px;
    background: rgba(4,14,32,0.95);
    border-top: 1px solid rgba(0,255,255,0.15);
    padding: 8px 10px 6px;
    z-index: 10;
  }
  .bot-controls::before {
    content: '';
    position: absolute; top: 0; left: 0; right: 0; height: 1px;
    background: linear-gradient(90deg, transparent, #00ffff44, #00ffff88, #00ffff44, transparent);
  }

  .controls-grid {
    display: grid; grid-template-columns: 1fr 1fr;
    gap: 6px 10px;
  }
  .ctrl-item { display: flex; flex-direction: column; gap: 2px; }
  .ctrl-btn  { font-size: 8px; font-weight: bold; }
  .ctrl-desc { font-size: 7px; color: #555577; }

  /* Hex ticker */
  .hex-ticker {
    position: absolute; bottom: 4px; left: 0; right: 0;
    overflow: hidden; height: 12px;
    z-index: 15;
  }
  .hex-text {
    font-size: 7px; color: #222233;
    white-space: nowrap;
    animation: ticker 8s linear infinite;
    display: inline-block;
  }
  @keyframes ticker {
    0%   { transform: translateX(320px); }
    100% { transform: translateX(-600px); }
  }

  /* Glitch animation on selected item */
  .glitch {
    animation: glitch 4s infinite;
  }
  @keyframes glitch {
    0%,90%,100% { transform: translateX(0); color: #e0e0ff; text-shadow: none; }
    92%         { transform: translateX(-3px); color: #ff0808; text-shadow: 0 0 4px #ff0808; }
    94%         { transform: translateX(3px);  color: #00ffff; }
    96%         { transform: translateX(-2px); color: #e0e0ff; }
  }

  /* Labels */
  .label {
    margin-top: 28px;
    font-size: 9px; letter-spacing: 3px;
    color: #333355;
    text-align: center;
  }
</style>
</head>
<body>

<h1>// CyberHub · UI Preview //</h1>

<!-- TOP SCREEN -->
<div class="ds-shell">
  <div class="camera"></div>
  <div class="screen screen-top">
    <div class="screen-bg"></div>

    <!-- Header -->
    <div class="top-header">
      <span class="header-title">[ CYBER HUB ]</span>
      <div class="header-right">
        <span class="status-online neon-green">// ONLINE //</span>
        <span class="frame-counter">004821</span>
      </div>
    </div>

    <!-- Corner ornaments -->
    <div class="corner tl"></div>
    <div class="corner tr"></div>
    <div class="corner bl"></div>
    <div class="corner br"></div>

    <!-- Entry list -->
    <div class="entry-list">
      <div style="position:absolute;top:50%;left:50%;transform:translate(-50%,-50%);text-align:center">
        <div style="font-size:13px;color:#555577;letter-spacing:2px;margin-bottom:8px">-- NO SIGNAL --</div>
        <div style="font-size:8px;color:#333355;letter-spacing:1px;line-height:2">
          PLACE .3DSX FILES IN /3DS/<br>
          PLACE ROM FILES IN /ROMS/<br>
          INSTALL CIA GAMES VIA FBI
        </div>
      </div>
    </div>

    <!-- Footer -->
    <div class="top-footer">
      <span class="neon-pink" style="font-size:9px">ENTRIES: 0</span>
      <span class="gray">PAGE 0/0</span>
      <span class="psy-value" style="font-size:9px">PSY: 12%</span>
    </div>

    <div class="scanlines"></div>
  </div>
</div>

<!-- HINGE -->
<div class="hinge" style="width:436px"></div>

<!-- BOTTOM SCREEN -->
<div class="ds-shell-bottom" style="width:436px">
  <div class="screen screen-bottom">
    <div class="screen-bg"></div>

    <!-- Logo panel -->
    <div class="bot-logo-panel">
      <span class="logo-text">C Y B E R H U B</span>
      <span class="logo-sub">v1.0 // NEURAL LINK ACTIVE</span>
    </div>

    <!-- Info panel -->
    <div class="bot-info border-cyan">
      <div class="info-label">> SELECTED:</div>
      <div class="info-name" style="color:#333355;font-size:10px;margin-top:6px">-- NOTHING SELECTED --</div>
      <div class="info-type" style="color:#222233;margin-top:6px">ADD GAMES TO GET STARTED</div>
    </div>

    <!-- Controls -->
    <div class="bot-controls">
      <div class="controls-grid">
        <div class="ctrl-item">
          <span class="ctrl-btn neon-green">[A]</span>
          <span class="ctrl-desc">LAUNCH</span>
        </div>
        <div class="ctrl-item">
          <span class="ctrl-btn neon-cyan">[R]</span>
          <span class="ctrl-desc">REFRESH</span>
        </div>
        <div class="ctrl-item">
          <span class="ctrl-btn neon-yellow">[↑/↓]</span>
          <span class="ctrl-desc">NAVIGATE</span>
        </div>
        <div class="ctrl-item">
          <span class="ctrl-btn neon-red">[START]</span>
          <span class="ctrl-desc">EXIT</span>
        </div>
      </div>

      <!-- Hex ticker -->
      <div class="hex-ticker">
        <span class="hex-text">DEAD4821 BEEF9C3F CAFE0012 FF3A8800 &nbsp;&nbsp; DEAD4822 BEEF9C40 CAFE0013 FF3A8801</span>
      </div>
    </div>

    <div class="scanlines"></div>
  </div>
</div>

<p class="label">TOP SCREEN 400×240 &nbsp;·&nbsp; BOTTOM SCREEN 320×240</p>

</body>
</html>
