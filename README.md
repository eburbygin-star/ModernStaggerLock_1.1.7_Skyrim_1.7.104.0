# Modern Stagger Lock (Skyrim 1.7.104.0 Port)

A modernized and updated native SKSE plugin port of **Modern Stagger Lock** by [max-su-2019](https://github.com/max-su-2019/ModernStaggerLock), updated for **The Elder Scrolls V: Skyrim Special Edition / Anniversary Edition Runtime 1.7.104.0** and **SKSE 2.3.1**.

---

## Overview

Modern Stagger Lock overhauls Skyrim's stagger mechanics into a responsive, directional, and magnitude-based system:
- **Directional Stagger Reactions:** Seamless transitions between forward (hit from behind) and backward (hit from front) stagger animations.
- **Magnitude-Based Stagger Levels:** 4 stagger tiers (Small, Medium, Large, Largest) configured via INI thresholds.
- **Dynamic Recovery Windows:** Allows fluid counter-attacks or recovery animations during designated recovery windows.
- **Anti-Exploit Controls:** Option to disable player jumping during stagger state.
- **Framework Compatibility:** Full integration with OpenAnimationReplacer (OAR), Precision API, and modern dodge mods (DMCO, TK Dodge, TUDM).

---

## Target Runtime

- **Game Version:** The Elder Scrolls V: Skyrim SE/AE **1.7.104.0**
- **Script Extender:** SKSE64 **2.3.1**
- **Address Library:** Required (version independent)

---

## Porting & Technical Details

1. **SKSE Plugin Metadata:**
   - Updated `PluginVersionData` with `UsesAddressLibrary()` and `UsesUpdatedStructs()`.
   - Implemented standard SKSE query and load lifecycle for runtime 1.7.104.0.

2. **Trampoline Allocation:**
   - Increased trampoline allocation to 512 bytes (`1 << 9`) to prevent memory pool exhaustion during hook initialization.

3. **Runtime Hook & Offset Updates for 1.7.104.0:**
   - `PerformLandActionHook_NPC`: Address Library ID `37507`, call offset `0x9BB`.
   - `PerformLandActionHook_PC`: Address Library ID `42350`, call offset `0x22E`.
   - `StaggeredStateCheckPatch`: Address Library ID `37710`, NOP patch offset `0x54`.
   - `AnimEventHook`: Address Library ID `207890` (Vtable index `0x1`).
   - `ActorUpdateHook`: Character / PlayerCharacter Vtable index `0x0AD`.
   - `NotifyAnimationGraphHook`: Character / PlayerCharacter Vtable[3] index `0x1`.
   - `DisableStaggerJumpHook`: JumpHandler Vtable index `0x1`.

4. **Animation Assets:**
   - 64-bit binary Havok animation files for all 8 directional and tiered stagger states.
   - Preserves OAR (Open Animation Replacer) player and NPC variation packs.

---

## Build Dependencies & Toolchain

- **CommonLibSSE-NG:**
  - **Fork:** [alandtse/CommonLibSSE-NG](https://github.com/alandtse/CommonLibSSE-NG)
  - **Tag / Release:** `v8.0.0`
  - **Commit:** `1504349dddfc622d4d25704bba19e2ade669dc5a`
  - **License:** Apache-2.0 / MIT

- **DKUtil:**
  - **Commit:** `9ffa84252269e0f41b16715b5b9a7a9686c8fc40`
  - **License:** MIT

- **Package Manager:** `vcpkg` (dependencies: `spdlog`)
- **Compiler:** Microsoft Visual C++ (MSVC) 2022 (C++23 standard)
- **CMake:** 3.21 or newer

---

## How to Build

1. Clone or download this repository.
2. Ensure `VCPKG_ROOT` environment variable is set to your vcpkg installation.
3. Install vcpkg dependencies:
   ```cmd
   vcpkg install spdlog:x64-windows-static-md
   ```
4. Set environment variables (paths to CommonLibSSE-NG, DKUtil, and headless mode):
   ```cmd
   set CommonLibSSEPath=C:/path/to/CommonLibSSE-NG
   set DKUtilPath=C:/path/to/DKUtil
   set HEADLESS=1
   ```
5. Configure and build:
   ```cmd
   cmake -B build -S . -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release
   cmake --build build --config Release
   ```
6. The resulting binary `ModernStaggerLock.dll` and its debug symbol file `ModernStaggerLock.pdb` will be located in `build/Release/`.

---

## Credits & Licensing

- **Original Mod & Author:** [max-su-2019](https://github.com/max-su-2019) ([ModernStaggerLock](https://github.com/max-su-2019/ModernStaggerLock))
- **CommonLibSSE-NG:** [alandtse](https://github.com/alandtse) and contributors
- **DKUtil:** [GotobedSkyrim](https://github.com/GotobedSkyrim) / [Karuro](https://github.com/Karuro) / [doodlum](https://github.com/doodlum)
- **Port to 1.7.104.0:** Maintained for Skyrim AE 1.7.104.0 compatibility
- **License:** [MIT License](LICENSE) (c) 2023 max-su-2019
