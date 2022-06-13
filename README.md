# Blueberry Engine

Welcome to Blueberry Engine source code!

This is the main repository of Blueberry Technology. With the code from here, you can build Blueberry ***Runtime***, ***Editor*** & ***All Tools***. Modify the code in any way, so it can suit your needs.

## Branches

The source code is organized in multiple branches:
*    At the moment, the *latest-stable* release can be found in the [***release***](https://github.com/avramtraian/Blueberry/tree/release) branch. This is the branch that *most* users should clone.
*    Once per year, we release the [***LTS***](https://github.com/avramtraian/Blueberry/tree/LTS/2022) (*long-term support*) version of the engine. These can be found in the ***LTS/{year}*** branches.
*    If you want to use more experimental code and help test the engine, [***master***](https://github.com/avramtraian/Blueberry/tree/master) is the branch where all the features merge first. This is not meant for use in any comercial project.
*    Branches whose names start with ***dev/***, ***test/*** or ***feature/*** are only for internal development purposes and are not useful for other users. Some commits might not even compile.
 
## Downloading, Compiling and Running
 
 These steps take you through the process of downloading, compiling and running the editor yourself.
 
### Windows

1.   Install a Git client, such as [***Fork***](https://git-fork.com/) or [***Github for Windows***](https://desktop.github.com/), then ***fork and clone*** this repository. Or, you can use the the command-line instead, using the following command:
```
git clone --recursive -b release https://github.com/avramtraian/Blueberry.git {your installation path}
```
      Either one you choose, make sure to download all the submodules.
      
2.    Install **Visual Studio 2022**. Blueberry Engine *require* Visual Studio. All desktop editions of Visual Studio 2022 can build Blueberry Engine, including [*Visual Studio Community 2022*](https://visualstudio.microsoft.com/vs/community/), which is free to use.

      In the *Visual Studio Installer*, you need to install the following components:
      * **Desktop development with C++**
      * **Game development with C++**
      * **Windows 10 SDK**
      
3.    Open the engine folder, and execute **GenerateProjectFiles.bat**. This will create the Visual Studio project files. It shouldn't take more than a few seconds.

4.    Open **Blueberry.sln**. Set the **BlueberryJam** as the startup project and select the **Release** configuration, **Win64** platform. Right-click on the solution target and press **Build Solution** (*Ctrl+Shift+B*).

5.    After the compiling finishes, you can run the editor by pressing ***F5***.

### Mac

Currently, ***MacOS*** is not available as a build target.

### Linux

Currently, ***Linux*** is not available as a build target.