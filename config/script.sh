#!/bin/bash

mkdir -p build && cd build

ls ../xpd/pd/
ls ../src/Properties/

echo "'cmake ..'"

if [ -n "$COVERAGE" ]
then
    cmake -DWITH_COVERAGE=On -DCMAKE_BUILD_TYPE=Debug ..
else
    cmake -DCMAKE_BUILD_TYPE=Debug ..
fi

echo "'build'"

cmake --build .

if [ $? -ne 0 ]; then
    error "Compile error!"
	# Terminate script and outputs 3
    exit 3
fi

export CTEST_OUTPUT_ON_FAILURE=1
make test

if [ -n "$COVERAGE" ]
then
    echo "Coverage...."
    bash <(curl -s https://codecov.io/bash) || echo "Codecov did not collect coverage reports"
fi
