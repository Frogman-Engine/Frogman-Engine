[![License](https://img.shields.io/badge/License-boost-blue.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-x86_64-white.svg)](PLATFORM)

# Frogman-Engine
Copyright © 2023 by UNKNOWN STRYKER. All rights reserved. 
This project, Frogman Engine,' is licensed under the Boost Software License - Version 1.0. 
Users who use, modify, or redistribute the original source code cannot claim authority or ownership over Frogman Engine, which remains the sole property of its original author, "UNKNOWN STRYKER / Hojin Lee / 이호진."

This project is under development and may contain some bugs and issues.

# Dev Team Discord Link: https://discord.gg/jhu4vAU3Mm
<<<<<<< HEAD
Currently, Unknown Stryker(Hojin Lee) is the only active developer for this project.
=======
>>>>>>> 19ea598051b1a13a8ae6b12b0447f686f156f948

# Frogman Engine Coding Conventions and Rules.
https://savory-moth-a00.notion.site/5cef12dd2c9b43588f22045405e80cff?v=86ea5413ff4f40de9204c4aa22907ffc&pvs=4

# Prerequisite: CMake 3.27.0 or latest, and LLVM Clang 10 or latest [ includes LLVM (clangcl) ].

# C++ standard version: C++ 17 or latest.
<<<<<<< HEAD
C++ 20 is highly recommended unless it is unavailable.
=======
>>>>>>> 19ea598051b1a13a8ae6b12b0447f686f156f948

All project settings can be adjusted by modifying CMakeLists.txt.

# The current development status.
| Platform     | Architecture  | Platform Support |
|--------------|---------------|------------------|
| Windows 11   | X86-64        | Suspended        |
| Ubuntu-Linux | X86-64        | In Development   |

# Frogman Engine wants to support these platforms in the future.
| Platform     | Architecture  |   CPU Brand   |
|--------------|---------------|---------------|
| Windows      | X86-64        | Intel and AMD |
|              | ARM64         |               |
https://www.nvidia.com/en-us/autonomous-machines/embedded-systems/

# This project uses:
- Boost Libraries
https://github.com/boostorg/boost/releases/tag/boost-1.85.0

- Google Test
https://github.com/google/googletest/releases/tag/v1.14.0

- Google Benchmark
https://github.com/google/benchmark/releases/tag/v1.8.4

# Help:
The default settings use /MTd (Static C++ Standard Library Debug Build) for debug configuration and /MT (Static C++ Standard Library Release Build) for release.

LINK_LIBRARIES(advapi32.lib shlwapi.lib) to use Google Benchmark on Windows.

In order to build boost libraries using Microsoft Visual Studio 2022 Clang CL:
1. Download the LLVM Clang CL from Visual Studio Installer.
2. Download Boost libraries from https://www.boost.org/
3. Build b2.exe by running bootstrap.bat(.sh)
4. Run the commands: 

./b2 toolset=clang-win architecture=x86 address-model=64 link=static runtime-link=static threading=multi variant=debug 

<<<<<<< HEAD
./b2 toolset=clang-win architecture=x86 address-model=64 link=static runtime-link=static threading=multi variant=release 


# Goorm IDE GPU Reference
https://www.techpowerup.com/gpu-specs/tesla-t4.c3316
https://docs.nvidia.com/datacenter/tesla/pdf/tesla-release-notes-410-72.pdf
=======
./b2 toolset=clang-win architecture=x86 address-model=64 link=static runtime-link=static threading=multi variant=release 
>>>>>>> 19ea598051b1a13a8ae6b12b0447f686f156f948
