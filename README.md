# 🎮 Godot 4 GDExtension Mobile Game

> A collaborative mobile game built with **Godot 4** and **C++ via GDExtension**, targeting **Android & iOS**.

Welcome, contributor! You don't need to be a C++ expert to work on this project — this guide will walk you through **every single step** from a fresh computer to a running build. Take it one step at a time. You've got this! 💪

---

## 📋 Table of Contents

1. [Prerequisites](#-prerequisites)
2. [Project Structure](#-project-structure)
3. [Clone & Build (Step-by-Step)](#-clone--build-step-by-step)
4. [Platform-Specific Commands](#-platform-specific-commands)
5. [Running the Game](#-running-the-game)
6. [Daily Workflow (Pull & Recompile)](#-daily-workflow-pull--recompile)
7. [Troubleshooting](#-troubleshooting)
8. [Contributing](#-contributing)

---

## 🛠 Prerequisites

Install **all** of the following tools before proceeding. Raw links are provided so you can copy-paste them directly into your browser.

### 1. Godot Engine 4 (with .NET / Mono — pick the standard version)
- **Download:** https://godotengine.org/download
- Choose **Godot Engine – Standard** (not .NET unless your team uses C#).
- Add the Godot executable to your system PATH, or note where you installed it.

### 2. Python 3.8+
- **Download:** https://www.python.org/downloads/
- ✅ During installation on Windows, check **"Add Python to PATH"**.
- Verify: `python --version` or `python3 --version`

### 3. SCons (Build Tool)
- SCons is installed via Python's package manager after Python is set up.
- Install command: `pip install scons`
- **Docs:** https://scons.org/doc/production/HTML/scons-user/
- Verify: `scons --version`

### 4. C++ Compiler

| Platform | Recommended Compiler | Download Link |
|---|---|---|
| Windows | MSVC (Visual Studio Build Tools) | https://visualstudio.microsoft.com/visual-cpp-build-tools/ |
| Windows (alt) | LLVM/Clang + MinGW-w64 | https://www.mingw-w64.org/downloads/ |
| macOS | Xcode Command Line Tools | Run: `xcode-select --install` |
| Linux | GCC (usually pre-installed) | `sudo apt install build-essential` |

> 💡 **Windows users:** Install **Visual Studio Build Tools 2022** and select the "Desktop development with C++" workload. This is the easiest option.

### 5. Android SDK & NDK (for Android builds only)
- **Android Studio (includes SDK):** https://developer.android.com/studio
- After installing Android Studio, open **SDK Manager** and install:
  - Android SDK Platform (API 33 or higher recommended)
  - Android NDK (Side by Side) – version **r23c** or newer
  - CMake
- Set these environment variables (replace paths with your actual install location):
  ```
  ANDROID_SDK_ROOT = C:\Users\YourName\AppData\Local\Android\Sdk   (Windows)
  ANDROID_SDK_ROOT = ~/Library/Android/sdk                          (macOS)
  ANDROID_SDK_ROOT = ~/Android/Sdk                                  (Linux)
  ```
- **NDK docs:** https://developer.android.com/ndk/guides

### 6. Xcode (for iOS builds — macOS only)
- **Download:** https://developer.apple.com/xcode/
- Available on the Mac App Store or from the Apple Developer portal.
- After install, run: `sudo xcode-select --switch /Applications/Xcode.app`

### 7. Git
- **Download:** https://git-scm.com/downloads
- Verify: `git --version`

---

## 📁 Project Structure

```
godot-gdextension-mobile/
│
├── game/                        # Godot project lives here
│   ├── project.godot            # Godot project file
│   ├── scenes/                  # .tscn scene files
│   ├── scripts/                 # GDScript (.gd) files
│   ├── assets/                  # Sprites, audio, fonts
│   │   ├── images/
│   │   ├── audio/
│   │   └── fonts/
│   ├── bin/                     # Compiled .gdextension binaries go here
│   │   └── mobile_ext.gdextension
│   └── export_presets.cfg       # Android/iOS export config (git-ignored)
│
├── src/                         # C++ GDExtension source code
│   ├── register_types.cpp       # Entry point: registers all custom classes
│   ├── register_types.h
│   └── example_node/            # One folder per custom class/module
│       ├── example_node.cpp
│       └── example_node.h
│
├── godot-cpp/                   # Godot C++ bindings (added as git submodule)
│
├── SConstruct                   # SCons build configuration
├── .gitignore
├── .gitmodules
└── README.md
```

---

## 🚀 Clone & Build (Step-by-Step)

Follow these steps **in order**. Each step must succeed before moving to the next.

### Step 1 — Clone the repository
```bash
git clone --recurse-submodules https://github.com/vinnyy-ph/godot-gdextension-mobile.git
cd godot-gdextension-mobile
```
> ⚠️ The `--recurse-submodules` flag is **required** — it downloads the `godot-cpp` bindings automatically.

### Step 2 — Verify your tools
Run each command and make sure you get a version number back, not an error:
```bash
python --version
scons --version
git --version
```

### Step 3 — Build the C++ extension (Desktop/Debug)
This compiles the C++ code into a shared library (`.dll` / `.so` / `.dylib`) that Godot will load.
```bash
scons platform=windows target=template_debug   # Windows
scons platform=macos   target=template_debug   # macOS
scons platform=linux   target=template_debug   # Linux
```
✅ When the build succeeds, you'll see compiled files appear in `game/bin/`.

### Step 4 — Build for Android
```bash
scons platform=android target=template_debug arch=arm64
```
> Requires Android NDK to be installed and `ANDROID_SDK_ROOT` set (see Prerequisites).

### Step 5 — Open the Godot project
1. Open the **Godot Engine** application.
2. Click **Import** and navigate to the `game/` folder.
3. Select `project.godot` and click **Open**.
4. Hit **Play (▶)** to run in the editor.

---

## 💻 Platform-Specific Commands

### Windows (PowerShell or Command Prompt)
```powershell
# Clone
git clone --recurse-submodules https://github.com/vinnyy-ph/godot-gdextension-mobile.git
cd godot-gdextension-mobile

# Build debug (desktop)
scons platform=windows target=template_debug

# Build Android
scons platform=android target=template_debug arch=arm64

# Build release (for export)
scons platform=windows target=template_release
```

### macOS (Terminal)
```bash
# Clone
git clone --recurse-submodules https://github.com/vinnyy-ph/godot-gdextension-mobile.git
cd godot-gdextension-mobile

# Build debug (desktop)
scons platform=macos target=template_debug

# Build iOS (requires Xcode)
scons platform=ios target=template_debug arch=arm64

# Build Android
scons platform=android target=template_debug arch=arm64
```

### Linux (Bash)
```bash
# Install dependencies first (Ubuntu/Debian)
sudo apt update && sudo apt install -y build-essential python3 python3-pip scons

# Clone
git clone --recurse-submodules https://github.com/vinnyy-ph/godot-gdextension-mobile.git
cd godot-gdextension-mobile

# Build debug (desktop)
scons platform=linux target=template_debug

# Build Android
scons platform=android target=template_debug arch=arm64
```

---

## 🎮 Running the Game

After a successful build:
1. Open Godot Engine and import `game/project.godot`.
2. In the Godot editor, press **F5** or click the ▶ Play button.
3. For a mobile device, use **Remote Debug** via USB (see Godot docs: https://docs.godotengine.org/en/stable/tutorials/export/exporting_for_android.html).

---

## 🔄 Daily Workflow (Pull & Recompile)

Whenever a teammate pushes new C++ code, you need to re-pull and rebuild. Here's the exact routine:

```bash
# 1. Save your work and commit any local changes first
git add .
git commit -m "WIP: describe your change"

# 2. Pull the latest changes from GitHub
git pull origin main

# 3. Update the godot-cpp submodule (if it changed)
git submodule update --init --recursive

# 4. Rebuild the C++ extension
scons platform=<your_platform> target=template_debug

# 5. Open Godot — the extension is now updated!
```

> 💡 **You only need to recompile** when files inside `src/` change. If only GDScript (`.gd`) or scene (`.tscn`) files changed, just pull and open Godot directly.

---

## 🔧 Troubleshooting

### ❌ `scons: command not found`
**Cause:** SCons is not installed or not in your PATH.
**Fix:**
```bash
pip install scons
# or on some systems:
pip3 install scons
```
Then close and reopen your terminal.

---

### ❌ `cl.exe not found` or `MSVC not found` (Windows)
**Cause:** Visual Studio Build Tools are not installed.
**Fix:** Download from https://visualstudio.microsoft.com/visual-cpp-build-tools/ and install the **"Desktop development with C++"** workload. Restart your computer after.

---

### ❌ `godot-cpp` folder is empty
**Cause:** You cloned without `--recurse-submodules`.
**Fix:**
```bash
git submodule update --init --recursive
```

---

### ❌ `NDK not found` or `ANDROID_NDK_ROOT not set`
**Cause:** Android NDK path is not configured.
**Fix:** Set the environment variable:
```bash
# macOS/Linux (add to ~/.bashrc or ~/.zshrc)
export ANDROID_SDK_ROOT="$HOME/Android/Sdk"

# Windows (PowerShell — run as Administrator)
[System.Environment]::SetEnvironmentVariable("ANDROID_SDK_ROOT", "C:\Users\YourName\AppData\Local\Android\Sdk", "Machine")
```

---

### ❌ Godot says "GDExtension failed to load"
**Cause:** The `.dll`/`.so`/`.dylib` binary is missing or was built for the wrong platform.
**Fix:** Re-run the `scons` build command for your current platform and check that files appear in `game/bin/`.

---

### ❌ Build errors: `Python not found`
**Cause:** Python is not installed or not in PATH.
**Fix:** Download from https://www.python.org/downloads/ and make sure you check **"Add to PATH"** during setup.

---

## 🤝 Contributing

1. **Fork** this repo and create a new branch: `git checkout -b feature/your-feature-name`
2. Make your changes in `src/` (C++) or `game/` (Godot scenes/scripts).
3. Build and test locally.
4. Push your branch and open a **Pull Request** on GitHub.
5. A maintainer will review and merge your work.

Please follow the existing code style and keep commits small and focused. If you're unsure about something, open an **Issue** first to discuss. No question is too small! 🙂

---

*Built with ❤️ in the Philippines 🇵🇭*
