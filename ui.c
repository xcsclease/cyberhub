name: Build CyberHub

on:
  push:
    branches: [ main, master ]
  workflow_dispatch:  # lets you trigger a build manually from the GitHub website

jobs:
  build:
    runs-on: ubuntu-latest
    container:
      image: devkitpro/devkitarm:latest  # official devkitPro compiler image

    steps:
      - name: Checkout code
        uses: actions/checkout@v4

      - name: Install 3DS libraries
        run: |
          dkp-pacman -Sy --noconfirm \
            3ds-dev \
            3ds-citro2d \
            3ds-citro3d \
            3ds-libctru

      - name: Build CyberHub
        run: make
        env:
          DEVKITPRO: /opt/devkitpro
          DEVKITARM: /opt/devkitpro/devkitARM
          PATH: /opt/devkitpro/tools/bin:/opt/devkitpro/devkitARM/bin:$PATH

      - name: Upload .3dsx artifact
        uses: actions/upload-artifact@v4
        with:
          name: CyberHub
          path: CyberHub.3dsx
          if-no-files-found: error
