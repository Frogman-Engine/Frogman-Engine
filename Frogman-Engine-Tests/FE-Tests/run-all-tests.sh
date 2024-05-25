#!/bin/bash

CURRENT_DIRECTORY=$(pwd)
chmod +x build-tests.sh
./build-tests.sh


TESTS=(
    "$CURRENT_DIRECTORY/build/FE.core.prerequisites/FE.core.prerequisites_test"
    "$CURRENT_DIRECTORY/build/FE.core.type_traits/FE.core.type_traits_test"
    "$CURRENT_DIRECTORY/build/FE.core.algorithm.utility/FE.core.algorithm.utility_test"
    "$CURRENT_DIRECTORY/build/FE.core.log/FE.core.log_test"
    "$CURRENT_DIRECTORY/build/FE.framework.predefined_main/FE.framework.predefined_main_test"
    "$CURRENT_DIRECTORY/build/FE.core.pool/FE.core.pool_test"
)


echo " "
for TEST in "${TESTS[@]}"; do
    echo "Running a Test named: $TEST"
    chmod +x "$TEST"
    "$TEST" &
done

wait