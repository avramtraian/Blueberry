:: Copyright to Avram Traian. 2022 - 2022.
:: File created on June 13 2022.

@ECHO OFF
PUSHD "%~dp0"

call "JamEd\ThirdParty\premake\Binaries\Win64\premake5.exe" --file="JamEd/Build/DevWorkspace.lua" vs2022

POPD
PAUSE