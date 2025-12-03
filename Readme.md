# Game
A lightweight 2D dungeon-crawler prototype built with Raylib and C++. This repository contains the game source, a small editor, and assets used during development.

---

## Table of Contents
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Build & Run (Windows)](#build--run-windows)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [Testing & Debugging Tips](#testing--debugging-tips)
- [License & Credits](#license--credits)

---

## Features
- Simple side-scroller dungeon crawler gameplay
- Multiple character/enemy types with animations
- Level maps and asset pipeline (images, audio, fonts)
- Basic UI system and in-game editor (in `editor/`)

## Prerequisites
- Windows (the included build tasks target MinGW / w64devkit)
- Raylib (compatible version installed; repository expects a local Raylib installation)
- MinGW-w64 or w64devkit (for `mingw32-make` and `g++`)
- Optional: Visual Studio Code for the included build tasks

Recommended locations used in tasks/examples: `C:/raylib` and `C:/raylib/w64devkit`.

## Build & Run (Windows)
Below are the most common commands used to build and run the game from PowerShell. Adjust paths to your local Raylib installation as needed.

1. Open PowerShell in the repository root (`c:\Users\Lenovo\Desktop\DungeonCrawler`).

2. Build (release):

```powershell
C:/raylib/w64devkit/bin/mingw32-make.exe
```

3. Build (debug):

```powershell
C:/raylib/w64devkit/bin/mingw32-make.exe BUILD_MODE=DEBUG
```

4. If you need to pass `RAYLIB_PATH` or change project name:

```powershell
C:/raylib/w64devkit/bin/mingw32-make.exe RAYLIB_PATH=C:/raylib/raylib PROJECT_NAME=DungeonCrawler OBJS=*.cpp BUILD_MODE=DEBUG
```

5. Run the produced executable (example):

```powershell
.\DungeonCrawler.exe
```

### VS Code Tasks
- The workspace contains tasks for building in Debug/Release. Open the Command Palette → `Tasks: Run Task` → choose `build debug` or `build release`.

## Project Structure (high level)
Key folders and files you will interact with:

- `src/` — Main game source code
	- `engine/` — Core engine, states, systems (audio, loader, progress)
	- `ui/` — UI elements and menus
	- `main.cpp` — Application entry point
- `assets/` — Images, audio, fonts, and maps used by the game
- `editor/` — Simple editor and associated build files
- `build/` — Generated build artifacts (ignored by git)
- `Makefile` — Build rules used by `mingw32-make`

## Contributing
- Fork the repo and open a pull request with a clear description of your changes.
- Keep changes isolated and small; include screenshots for UI changes.
- Use descriptive commit messages and run the build locally before opening PRs.

## Testing & Debugging Tips
- If the game crashes after incremental builds, remove object files and rebuild:

```powershell
Get-ChildItem -Recurse -Filter *.o | Remove-Item -Force
C:/raylib/w64devkit/bin/mingw32-make.exe BUILD_MODE=DEBUG
```

- If you see missing assets at runtime, ensure the `assets/` directory is next to the executable or that paths in `Loader` are configured correctly.
- For visual tweaks, adjust font sizes and positions in `src/engine/state/*.cpp` and rebuild.

## License & Credits
This project uses assets and code authored by the repository owner. Add a license file if you wish to make this project open-source. Example license choices: MIT, Apache-2.0.

Credits:
- Built with Raylib (https://www.raylib.com)
- Icons, sprites, and audio — see the `assets/` folder for attribution notes.

---

If you want, I can also:
- Add a `LICENSE` file (pick a license) and update the README accordingly.
- Add badges (build, license) and screenshots to the README.
- Create a short developer quickstart (set up Raylib on Windows) and include it in the README.

Would you like me to add any of those?


