#!/bin/bash
PSScriptRoot=$(dirname "$SCRIPT")

echo "Relocation to project root: $PSScriptRoot\.."
cd $PSScriptRoot\..

conan install . --build=missing
cmake . -DCMAKE_TOOLCHAIN_FILE="build/Release/generators/conan_toolchain.cmake" -S . -B ./build