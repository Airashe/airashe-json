Write-Host "Relocation to project root: $PSScriptRoot\.."
Set-Location $PSScriptRoot\..

conan install . --build=missing
cmake . -DCMAKE_TOOLCHAIN_FILE="build/generators/conan_toolchain.cmake" -S . -B ./build