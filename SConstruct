# =============================================================
#  SConstruct — Godot 4 GDExtension Build Script
#  Compatible with: Windows, macOS, Linux, Android, iOS
# =============================================================

import os
import sys

# ── Load godot-cpp build system ───────────────────────────────
# godot-cpp must be present as a submodule in ./godot-cpp/
env = SConscript("godot-cpp/SConstruct")

# ── Extension name ────────────────────────────────────────────
# Change this to your extension's name (no spaces)
EXT_NAME = "mobile_ext"

# ── Source files ─────────────────────────────────────────────
# Add every .cpp file in src/ here, or use Glob to pick them up
sources = Glob("src/*.cpp")

# Recursively collect .cpp from subdirectories inside src/
for root, dirs, files in os.walk("src"):
    for f in files:
        if f.endswith(".cpp"):
            full = os.path.join(root, f)
            # Avoid duplicates from top-level Glob
            if full not in [str(s) for s in sources]:
                sources.append(full)

# ── Include paths ─────────────────────────────────────────────
env.Append(CPPPATH=[
    "src/",
    "godot-cpp/include/",
    "godot-cpp/gen/include/",
])

# ── Output path ───────────────────────────────────────────────
# Binaries land in game/bin/ so Godot can find them automatically
output_dir = "game/bin/"

# Determine the output file name based on platform
if env["platform"] == "windows":
    lib_name = "{}/{}.{}.{}.dll".format(
        output_dir, EXT_NAME, env["platform"], env["target"]
    )
elif env["platform"] in ["macos", "ios"]:
    lib_name = "{}/lib{}.{}.{}.dylib".format(
        output_dir, EXT_NAME, env["platform"], env["target"]
    )
else:  # linux, android
    lib_name = "{}/lib{}.{}.{}.so".format(
        output_dir, EXT_NAME, env["platform"], env["target"]
    )

# ── Build shared library ──────────────────────────────────────
library = env.SharedLibrary(
    lib_name,
    source=sources,
)

Default(library)
