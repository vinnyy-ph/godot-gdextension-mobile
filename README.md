# 🎮 Godot 4 GDExtension Mobile Game

A collaborative mobile game built with **Godot 4** and **C++ via GDExtension**, targeting **Android & iOS**.

This guide walks you through setup from scratch — no prior C++ experience needed. Just follow each step in order.

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

### 1. Godot Engine 4
- **Download:** https://godotengine.org/download
- Choose **Godot Engine – Standard** (not .NET unless your team uses C#).
- Add the Godot executable to your system PATH, or note where you installed it.

### 2. Python 3.8+
- **Download:** https://www.python.org/downloads/
- ✅ **Windows:** Check **"Add Python to PATH"** during installation.
- ✅ **macOS:** Python 3 is not pre-installed on all Macs. The easiest way is via Homebrew (see below). Alternatively, download the macOS installer from the link above.
- Verify: `python3 --version`

#### macOS — Install Homebrew first (recommended)
Homebrew makes installing dev tools on a Mac much easier.
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
Then install Python and SCons in one go:
```bash
brew install python scons
```
- **Homebrew docs:** https://brew.sh

### 3. SCons (Build Tool)
- SCons is installed via Python's package manager.
- **Windows / Linux:** `pip install scons`
- **macOS (Homebrew):** `brew install scons` *(already covered above)*
- **Docs:** https://scons.org/doc/production/HTML/scons-user/
- Verify: `scons --version`

### 4. C++ Compiler

| Platform | Recommended Compiler | How to Get It |
|---|---|---|
| Windows | MSVC (Visual Studio Build Tools) | https://visualstudio.microsoft.com/visual-cpp-build-tools/ |
| Windows (alt) | LLVM/Clang + MinGW-w64 | https://www.mingw-w64.org/downloads/ |
| macOS | Xcode Command Line Tools | Run: `xcode-select --install` |
| Linux | GCC | `sudo apt install build-essential` |

> 💡 **Windows:** Install **Visual Studio Build Tools 2022** and select the **"Desktop development with C++"** workload.

> 🍎 **macOS:** Run `xcode-select --install` in Terminal. A popup will appear — click Install and wait for it to finish. That's all you need for desktop builds. For iOS builds, you'll also need the full Xcode app (see below).

### 5. Android SDK & NDK (Android builds only)
- **Android Studio (includes SDK):** https://developer.android.com/studio
- After installing Android Studio, open **SDK Manager** and install:
  - Android SDK Platform (API 33 or higher)
  - Android NDK (Side by Side) – version **r23c** or newer
  - CMake
- Set the `ANDROID_SDK_ROOT` environment variable to your SDK path:

```bash
# macOS — add this line to ~/.zshrc (default shell on modern Macs)
export ANDROID_SDK_ROOT="$HOME/Library/Android/sdk"
# Then reload your shell:
source ~/.zshrc
```

```bash
# Linux — add to ~/.bashrc
export ANDROID_SDK_ROOT="$HOME/Android/Sdk"
source ~/.bashrc
```

```powershell
# Windows — run PowerShell as Administrator
[System.Environment]::SetEnvironmentVariable("ANDROID_SDK_ROOT", "C:\Users\YourName\AppData\Local\Android\Sdk", "Machine")
```

- **NDK docs:** https://developer.android.com/ndk/guides

### 6. Xcode — macOS only, iOS builds only
- **Download:** https://developer.apple.com/xcode/ (also on the Mac App Store)
- After install, run:
  ```bash
  sudo xcode-select --switch /Applications/Xcode.app
  sudo xcodebuild -license accept
  ```
- You only need this if you're building for **iOS**. For Android or desktop testing on a Mac, `xcode-select --install` from Step 4 is enough.

### 7. Git
- **Download:** https://git-scm.com/downloads
- **macOS (Homebrew):** `brew install git`
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
> ⚠️ The `--recurse-submodules` flag is **required** — it downloads the `godot-cpp` bindings automatically. If you forget it, see Troubleshooting.

### Step 2 — Verify your tools
Run each command and confirm you get a version number back, not an error:
```bash
python3 --version
scons --version
git --version
```

### Step 3 — Build the C++ extension (Desktop / Debug)
This compiles the C++ code into a shared library that Godot will load.
```bash
scons platform=windows target=template_debug   # Windows
scons platform=macos   target=template_debug   # macOS
scons platform=linux   target=template_debug   # Linux
```
✅ When the build succeeds, compiled files will appear in `game/bin/`.

### Step 4 — Build for Android
```bash
scons platform=android target=template_debug arch=arm64
```
> Requires Android NDK installed and `ANDROID_SDK_ROOT` set (see Prerequisites § 5).

### Step 5 — Open the Godot project
1. Open the **Godot Engine** application.
2. Click **Import** and navigate to the `game/` folder.
3. Select `project.godot` and click **Open**.
4. Press **F5** or click ▶ to run.

---

## 💻 Platform-Specific Commands

### Windows (PowerShell or Command Prompt)
```powershell
git clone --recurse-submodules https://github.com/vinnyy-ph/godot-gdextension-mobile.git
cd godot-gdextension-mobile

scons platform=windows target=template_debug          # Desktop debug
scons platform=android target=template_debug arch=arm64  # Android
scons platform=windows target=template_release         # Release build
```

### macOS (Terminal)
```bash
git clone --recurse-submodules https://github.com/vinnyy-ph/godot-gdextension-mobile.git
cd godot-gdextension-mobile

scons platform=macos   target=template_debug           # Desktop debug
scons platform=android target=template_debug arch=arm64  # Android
scons platform=ios     target=template_debug arch=arm64  # iOS (needs Xcode)
```

> 🍎 **macOS tip:** If `scons` is not found after installing via Homebrew, run `brew link scons` or open a new terminal window.

### Linux (Bash)
```bash
# Install dependencies (Ubuntu/Debian)
sudo apt update && sudo apt install -y build-essential python3 python3-pip
pip3 install scons

git clone --recurse-submodules https://github.com/vinnyy-ph/godot-gdextension-mobile.git
cd godot-gdextension-mobile

scons platform=linux   target=template_debug           # Desktop debug
scons platform=android target=template_debug arch=arm64  # Android
```

---

## 🎮 Running the Game

After a successful build:
1. Open Godot Engine and import `game/project.godot`.
2. Press **F5** or click the ▶ Play button.
3. To test on a physical device, use **Remote Debug** over USB — see the Godot docs:
   - Android: https://docs.godotengine.org/en/stable/tutorials/export/exporting_for_android.html
   - iOS: https://docs.godotengine.org/en/stable/tutorials/export/exporting_for_ios.html

---

## 🔄 Daily Workflow (Pull & Recompile)

Whenever a teammate pushes new C++ code, pull and rebuild:

```bash
# 1. Commit any local changes
git add .
git commit -m "WIP: describe your change"

# 2. Pull latest from GitHub
git pull origin main

# 3. Update godot-cpp submodule if it changed
git submodule update --init --recursive

# 4. Rebuild
scons platform=<your_platform> target=template_debug

# 5. Open Godot — done!
```

> 💡 You only need to recompile when files inside `src/` changed. If only `.gd` or `.tscn` files changed, just pull and open Godot.

---

## 🔧 Troubleshooting

### ❌ `scons: command not found`
**Cause:** SCons is not installed or not in your PATH.
```bash
pip3 install scons          # Windows / Linux
brew install scons          # macOS
```
Close and reopen your terminal after installing.

---

### ❌ `cl.exe not found` or `MSVC not found` (Windows)
**Cause:** Visual Studio Build Tools are not installed.
**Fix:** Download from https://visualstudio.microsoft.com/visual-cpp-build-tools/ and install the **"Desktop development with C++"** workload, then restart.

---

### ❌ `xcrun: error` or `clang not found` (macOS)
**Cause:** Xcode Command Line Tools are missing.
**Fix:**
```bash
xcode-select --install
```
A system dialog will appear. Click Install and wait for it to complete.

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
**Fix:** Set `ANDROID_SDK_ROOT` for your platform — see Prerequisites § 5.

---

### ❌ Godot says "GDExtension failed to load"
**Cause:** The compiled binary is missing or was built for the wrong platform.
**Fix:** Re-run `scons` for your current platform and check that files appear in `game/bin/`.

---

### ❌ `python: command not found` (macOS)
**Cause:** macOS uses `python3`, not `python`.
**Fix:** Always use `python3` and `pip3` on a Mac, or install Python via Homebrew: `brew install python`.

---

## 🤝 Contributing

1. Fork this repo and create a branch: `git checkout -b feature/your-feature-name`
2. Make your changes in `src/` (C++) or `game/` (Godot scenes/scripts).
3. Build and test locally.
4. Push your branch and open a **Pull Request**.
5. A maintainer will review and merge.

Keep commits focused and descriptive. If you're unsure about a change, open an **Issue** first.

---

*Built with ❤️ in the Philippines 🇵🇭*
