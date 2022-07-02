@ECHO OFF
PUSHD "%~dp0"

call "JamEd\ThirdParty\premake\Binaries\Win64\premake5.exe" --file="JamEd/Build/DevWorkspace.lua" vs2022

POPD
PAUSE