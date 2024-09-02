Write-Host "Relocation to project root: $PSScriptRoot\.."
Set-Location $PSScriptRoot\..

conan profile detect
conan create . -s build_type=Debug --build missing