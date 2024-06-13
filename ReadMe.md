[![License](https://img.shields.io/badge/License-boost-blue.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-x86_64-white.svg)](PLATFORM)

# Frogman-Engine
Copyright © 2023 by UNKNOWN STRYKER. All rights reserved. 
This project, Frogman Engine,' is licensed under the Boost Software License - Version 1.0. 
Users who use, modify, or redistribute the original source code cannot claim authority or ownership over Frogman Engine, which remains the sole property of its original author, "UNKNOWN STRYKER / Hojin Lee / 이호진."

This project is under development and may contain some bugs and issues.

# Dev Team Discord Link: https://discord.gg/jhu4vAU3Mm

# Frogman Engine Coding Conventions and Rules.
https://savory-moth-a00.notion.site/5cef12dd2c9b43588f22045405e80cff?v=86ea5413ff4f40de9204c4aa22907ffc&pvs=4


# Prerequisite: CMake 3.27.0 or latest, and LLVM Clang 10 or latest.

# C++ standard version: C++ 17 or latest.

# Visual Studio 2022 C++ Runtime Library. 
(NOTE: This project will drop msvc compiler support and use LLVM clang as its main compiler in later updates)
The default settings use /MTd (Static C++ Standard Library Debug Build) for debug configuration and /MT (Static C++ Standard Library Release Build) for release.

All project settings can be adjusted by modifying CMakeLists.txt.

| Platform     | Architecture  | Platform Support | 
|--------------|---------------|------------------|
| Windows      | X86-64        | Discontinued     |
| Linux        | X86-64        | In Development   |


# This project uses:
- Boost Libraries
https://github.com/boostorg/boost/releases/tag/boost-1.85.0

- Google Test
https://github.com/google/googletest/releases/tag/v1.14.0

- Google Benchmark
https://github.com/google/benchmark/releases/tag/v1.8.3