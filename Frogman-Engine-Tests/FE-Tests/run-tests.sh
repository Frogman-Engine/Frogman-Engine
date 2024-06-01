#!/bin/bash

CURRENT_DIRECTORY=$(pwd)
BUILD_FILES_FOLDER_NAME=build
BUILD_TYPE=$1
SPECIFIED_TEST_NAME=$2

if [ -z "$BUILD_TYPE" ]; 
    then
    BUILD_TYPE=Debug
fi

chmod +x build-tests.sh
./build-tests.sh $BUILD_TYPE $SPECIFIED_TEST_NAME

if [ -z "$SPECIFIED_TEST_NAME" ]; 
    then

    TESTS=(
        "$CURRENT_DIRECTORY/$BUILD_FILES_FOLDER_NAME/FE.core.prerequisites/FE.core.prerequisites_test"
        "$CURRENT_DIRECTORY/$BUILD_FILES_FOLDER_NAME/FE.core.type_traits/FE.core.type_traits_test"
        "$CURRENT_DIRECTORY/$BUILD_FILES_FOLDER_NAME/FE.core.algorithm.utility/FE.core.algorithm.utility_test"
        "$CURRENT_DIRECTORY/$BUILD_FILES_FOLDER_NAME/FE.core.log/FE.core.log_test"
        "$CURRENT_DIRECTORY/$BUILD_FILES_FOLDER_NAME/FE.core.thread/FE.core.thread_test"
        "$CURRENT_DIRECTORY/$BUILD_FILES_FOLDER_NAME/FE.framework.predefined_main/FE.framework.predefined_main_test"
        "$CURRENT_DIRECTORY/$BUILD_FILES_FOLDER_NAME/FE.core.pool/FE.core.pool_test"
    )

    echo " "
    for TEST in "${TESTS[@]}"; do
        echo "Running a test named: $TEST"
        chmod +x "$TEST"
        "$TEST" &
    done

else
    TEST_NAME_SUFFIX="_test"
    TEST="$CURRENT_DIRECTORY/$BUILD_FILES_FOLDER_NAME/$SPECIFIED_TEST_NAME/$SPECIFIED_TEST_NAME$TEST_NAME_SUFFIX"

    echo "Running a test named: $SPECIFIED_TEST_NAME"
    chmod +x "$TEST"
    "$TEST" &
fi
wait