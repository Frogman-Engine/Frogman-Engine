#!/bin/bash

CURRENT_DIRECTORY=$(pwd)
CMAKE_DIRECTORY=$CURRENT_DIRECTORY/../../Third-Party-Tools/cmake-3.29.3-linux-x86_64/bin/cmake

BUILD_FILES_FOLDER_NAME=build


if [ -d "$CURRENT_DIRECTORY/$BUILD_FILES_FOLDER_NAME" ]; 
    then
    rm -r "$CURRENT_DIRECTORY/$BUILD_FILES_FOLDER_NAME"
    echo "Frogman Engine Tests: re-building tests"
fi

mkdir $BUILD_FILES_FOLDER_NAME
cd $BUILD_FILES_FOLDER_NAME

$CMAKE_DIRECTORY -DCMAKE_SYSTEM_NAME=Linux -DCMAKE_CXX_COMPILER=clang++-12 -DCMAKE_CXX_STANDARD=17 -DCMAKE_BUILD_TYPE=Debug ..

sudo apt-get install make
make -j2
cd ..