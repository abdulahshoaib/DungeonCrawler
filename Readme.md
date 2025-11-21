# Game

## Build Instructions (Windows — PowerShell)

- **Prerequisites:** Install Raylib and MinGW (w64devkit). Ensure `C:/raylib/w64devkit/bin` is available on your PATH or use full paths below.

### Build (release)
```
mingw32-make
```

### Build (debug)
```
mingw32-make BUILD_MODE=DEBUG
```

If `mingw32-make` is not on your PATH, run with the full path:
```
C:/raylib/w64devkit/bin/mingw32-make.exe BUILD_MODE=DEBUG
```

To specify `RAYLIB_PATH` or other Makefile variables explicitly:
```
C:/raylib/w64devkit/bin/mingw32-make.exe RAYLIB_PATH=C:/raylib/raylib PROJECT_NAME=game OBJS=*.cpp BUILD_MODE=DEBUG
```

### VS Code
- Use `Tasks: Run Task` → choose `build debug` or `build release` (these tasks call mingw32-make with appropriate args).

### Notes
- The produced executable will be `game.exe` in the project root.
- Ensure `RAYLIB_PATH` in the Makefile or command line points to your raylib installation.
- If you prefer convenience, add `C:/raylib/w64devkit/bin` to your PATH so `mingw32-make` and `g++` are available globally.


