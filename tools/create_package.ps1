Write-Host "Relocation to project root: $PSScriptRoot\.."
Set-Location $PSScriptRoot\..

conan create . -s build_type=Debug