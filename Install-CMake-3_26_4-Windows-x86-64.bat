@echo off

set CMakeInstallationPath=%cd%\cmake-3.26.4-windows-x86_64.msi

powershell -Command "Invoke-WebRequest -Uri 'https://github.com/Kitware/CMake/releases/download/v3.26.4/cmake-3.26.4-windows-x86_64.msi' -OutFile '%CMakeInstallationPath%'"

start "CMake Installer" "cmake-3.26.4-windows-x86_64.msi"