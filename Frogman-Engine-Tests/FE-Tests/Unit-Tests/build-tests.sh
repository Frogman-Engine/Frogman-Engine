#!/bin/bash
WORKING_DIRECTORY=$(dirname "$0")
if [ "$WORKING_DIRECTORY" = '.' ];
    then
    WORKING_DIRECTORY=$(pwd)
fi

BUILD_TYPE=$1
if [ -z "$BUILD_TYPE" ]; 
    then
    BUILD_TYPE=Debug
fi

CMAKE_DIRECTORY=$WORKING_DIRECTORY/../../../Third-Party-Tools/cmake-3.29.3-linux-x86_64/bin/cmake
BUILD_FILES_FOLDER_NAME=build

SPECIFIED_TEST_NAME=$2
if [ -z "$SPECIFIED_TEST_NAME" ]; 
    then

    if [ -d "$WORKING_DIRECTORY/$BUILD_FILES_FOLDER_NAME" ]; 
        then
        rm -r "$WORKING_DIRECTORY/$BUILD_FILES_FOLDER_NAME"
        echo "Frogman Engine Tests: re-building tests"
    fi
    mkdir "$WORKING_DIRECTORY/$BUILD_FILES_FOLDER_NAME"

else
    if [ -d "$WORKING_DIRECTORY/$BUILD_FILES_FOLDER_NAME/$SPECIFIED_TEST_NAME" ]; 
        then
        rm -r "$WORKING_DIRECTORY/$BUILD_FILES_FOLDER_NAME/$SPECIFIED_TEST_NAME"
        echo "Frogman Engine Tests: re-building '$SPECIFIED_TEST_NAME' test"
    fi
fi

sudo apt-get install ninja-build
PWD=$(pwd)
cd "$WORKING_DIRECTORY/$BUILD_FILES_FOLDER_NAME"
$CMAKE_DIRECTORY -DCMAKE_SYSTEM_NAME=Linux -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CXX_STANDARD=17 -DCMAKE_BUILD_TYPE=$BUILD_TYPE .. -G "Ninja"
ninja -j6
cd $PWD