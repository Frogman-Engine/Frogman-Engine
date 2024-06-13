# Install script for directory: /workspace/Frogman-Engine-Lab/Frogman-Engine-Tests/FE-Tests/Unit-Tests

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/llvm-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workspace/Frogman-Engine-Lab/Frogman-Engine-Tests/FE-Tests/Unit-Tests/build/FE.core.prerequisites/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workspace/Frogman-Engine-Lab/Frogman-Engine-Tests/FE-Tests/Unit-Tests/build/FE.core.type_traits/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workspace/Frogman-Engine-Lab/Frogman-Engine-Tests/FE-Tests/Unit-Tests/build/FE.core.algorithm.utility/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workspace/Frogman-Engine-Lab/Frogman-Engine-Tests/FE-Tests/Unit-Tests/build/FE.core.hash/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workspace/Frogman-Engine-Lab/Frogman-Engine-Tests/FE-Tests/Unit-Tests/build/FE.core.log/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workspace/Frogman-Engine-Lab/Frogman-Engine-Tests/FE-Tests/Unit-Tests/build/FE.core.thread/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workspace/Frogman-Engine-Lab/Frogman-Engine-Tests/FE-Tests/Unit-Tests/build/FE.core.algorithm.math/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workspace/Frogman-Engine-Lab/Frogman-Engine-Tests/FE-Tests/Unit-Tests/build/FE.core.iterator/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workspace/Frogman-Engine-Lab/Frogman-Engine-Tests/FE-Tests/Unit-Tests/build/FE.core.memory/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workspace/Frogman-Engine-Lab/Frogman-Engine-Tests/FE-Tests/Unit-Tests/build/FE.core.algorithm.string/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workspace/Frogman-Engine-Lab/Frogman-Engine-Tests/FE-Tests/Unit-Tests/build/FE.core.fstring/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workspace/Frogman-Engine-Lab/Frogman-Engine-Tests/FE-Tests/Unit-Tests/build/FE.core.pool/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workspace/Frogman-Engine-Lab/Frogman-Engine-Tests/FE-Tests/Unit-Tests/build/FE.core.managed/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workspace/Frogman-Engine-Lab/Frogman-Engine-Tests/FE-Tests/Unit-Tests/build/FE.core.string/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workspace/Frogman-Engine-Lab/Frogman-Engine-Tests/FE-Tests/Unit-Tests/build/FE.core.string_view/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workspace/Frogman-Engine-Lab/Frogman-Engine-Tests/FE-Tests/Unit-Tests/build/FE.core.containers/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workspace/Frogman-Engine-Lab/Frogman-Engine-Tests/FE-Tests/Unit-Tests/build/FE.framework.reflection/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workspace/Frogman-Engine-Lab/Frogman-Engine-Tests/FE-Tests/Unit-Tests/build/FE.framework.predefined_main/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/workspace/Frogman-Engine-Lab/Frogman-Engine-Tests/FE-Tests/Unit-Tests/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
