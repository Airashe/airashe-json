#!/bin/bash
PSScriptRoot=$(dirname "$SCRIPT")

echo "Relocation to project root: $PSScriptRoot\.."
cd $PSScriptRoot\..

conan profile detect
conan create . -s build_type=Debug --build missing