# 🚀 Building the Project (Windows 11 – Fresh Install Tested)

This guide walks through the exact steps required to get the project compiling from a clean Windows 11 install, including the MSYS2 + UCRT64 toolchain setup and the CMake configuration inside VS Code.

---

# 1. Install Prerequisites

## ✔️ Install Git (and add to PATH)
Download: [https://git-scm.com ](https://git-scm.com/install/windows) 
During installation: **Enable “Add Git to PATH.”**

Verify in a fresh terminal:
```bash
git -v
```

## ✔️ Install Visual Studio Code

Download: [https://code.visualstudio.com](https://code.visualstudio.com)
Enable: **“Add to PATH”**

Open VS Code once so PATH updates.

---

# 2. Clone the Repository

In VS Code:

* **Terminal → New Terminal**
* Navigate to a parent directory you trust.
* Then run:

```bash
git clone https://github.com/Bushido3403/UntitledAdventureGame.git
```

Then:

**File → Open Folder → UntitledAdventureGame**

(This ensures VS Code treats it as the workspace root.)

---

# 3. Install the Needed VS Code Extensions

Install these from the Extensions sidebar:

* **CMake Tools** (Microsoft)
* *(Optional but recommended)* C/C++ (Microsoft)

After installing, **restart VS Code**.

---

# 4. Install the Compiler Toolchain (MSYS2 UCRT64)

We use the UCRT64 variant because it matches the project’s static MinGW configuration.

### 4.1 Download & Install MSYS2

[https://www.msys2.org/](https://www.msys2.org/)

Open **MSYS2 UCRT64** (not MSYS, not MINGW64).

### 4.2 Fully Update MSYS2

```bash
pacman -Syu
# If it tells you to close the window, close it and reopen UCRT64
```

### 4.3 Install the UCRT64 compiler + tools

```bash
pacman -S --needed \
  mingw-w64-ucrt-x86_64-gcc \
  mingw-w64-ucrt-x86_64-cmake \
  mingw-w64-ucrt-x86_64-ninja \
  git
```

Verify CMake exists:

```bash
which cmake
cmake --version
```

Expected output: `/ucrt64/bin/cmake`

---

# 5. Configure CMake in VS Code

Since VS Code is a Windows app, it does **not** automatically see MSYS2’s executables. We must point it manually.

### 5.1 Open VS Code Settings

`Ctrl + Shift + P` → **Preferences: Open Settings (JSON)**

Add this entry:

```json
"cmake.cmakePath": "C:\\msys64\\ucrt64\\bin\\cmake.exe"
```

(Adjust if your MSYS2 is installed elsewhere.)

Save settings.

---

# 6. Select the Correct Build Kit

In VS Code:

`Ctrl + Shift + P` → **CMake: Select a Kit**

Choose the one that looks like:

```
GCC x.x.x (x86_64-w64-mingw32) - UCRT64
```

This ensures the MinGW-UCRT toolchain is used.

---

# 7. Configure and Build

Run:

* `Ctrl + Shift + P` → **CMake: Configure**
* `Ctrl + Shift + P` → **CMake: Build**

Assets will auto-copy; CMake will fetch SFML and JSON; the project should compile cleanly.

---

# ✅ Done

You now have:

* UCRT64 GCC toolchain
* MSYS2 providing static MinGW libraries
* CMake Tools correctly pointing at a valid `cmake.exe`
* VS Code building the project