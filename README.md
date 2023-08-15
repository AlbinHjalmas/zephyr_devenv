# 1. Introduction
Welcome to the ComMon RopeRobot repository. This repository contains the firmware source code for the robot as well as the build, development, and simulation environment source code.

# 2. RopeRobot Development Environment

This repository contains a Visual Studio Code (VS Code) DevContainer configuration that allows you to set up and start your development environment inside a Docker container for the RopeRobot project. This ensures a consistent development experience across different machines and operating systems.

## 2.1. Prerequisites

Before proceeding, make sure you have the following software installed on your machine:

1. [Docker Desktop](https://www.docker.com/products/docker-desktop) (Windows/Mac) or Docker Engine (Linux)
2. [Visual Studio Code](https://code.visualstudio.com/)
3. [Remote - Containers extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) for VS Code

## 2.2. Setup and Usage

Follow the steps below to set up and use the RopeRobot development environment with the DevContainer configuration:

1. Clone the RopeRobot repository to your local machine:
```git clone git@ssh.dev.azure.com:v3/DevPortDevop/Comrod/rope-robot-fw```
2. Open the cloned repository in VS Code:
```code rope-robot-fw```

3. After opening the project in VS Code, you should see a notification in the bottom-right corner suggesting to reopen the project in a container. Click on "Reopen in Container". If you don't see the notification, you can press `F1` (or `Cmd+Shift+P` on Mac) to open the Command Palette, search for "Remote-Containers: Reopen Folder in Container", and hit Enter.

4. VS Code will now build the Docker container based on the configuration in the `.devcontainer` folder. This may take a few minutes the first time, as it needs to download the base Docker image and set up the development environment.

5. Once the container is built and running, VS Code will attach to the container, and you'll see the "Dev Container: RopeRobot" indicator in the bottom-left corner. You are now working inside the Docker container with all the necessary tools and dependencies pre-installed.

6. You can now edit, build, and debug the RopeRobot project as you would in any other development environment. Any changes you make to the code will be automatically saved to your local machine, even though you're working inside the container.

7. When you're done with your development session, you can close VS Code, and the container will be stopped automatically. To resume your work, simply reopen the project in VS Code and follow step 3 to start the container again.

## 2.3. Debugging with Renode
This section explains how to run a debug session of the RopeRobot firmware using the Renode emulator within the VS Code DevContainer environment. By following the steps below, you can execute the firmware in an emulated hardware environment, allowing you to debug and test your code without the need for physical hardware.

### 2.3.1. Prerequisites
Make sure you have completed the steps outlined in the "RopeRobot Development Environment" section of the README.md file. This will ensure that you have the necessary tools and dependencies installed within the Docker container.

### 2.3.2. Debugging Steps
1. Build the RopeRobot firmware in VS Code by executing the appropriate build task or command.

2. In VS Code, open the Run and Debug panel by clicking on the "Run" icon in the Activity Bar on the side, or by pressing __Ctrl+Shift+D__ (or __Cmd+Shift+D__ on Mac).

3. From the debug configuration dropdown, select the "renode" debug configuration.

4. Press the "Start Debugging" button (or press __F5__). This will perform the following actions:

   - Run the __nrf52840.resc__ script, which loads the hardware platform, sets up a UART PTY terminal on the host, and loads the previously built firmware executable (.elf file).
   - Send a command to start a GDB server on port 3333 in the configured Renode emulation.
   - Start the Zephyr GDB client and connect it to the GDB server running on port 3333.
   - Use the Cortex-Debug extension to connect VS Code to the Zephyr GDB client.
  
5. You can now debug the RopeRobot firmware within the emulated environment provided by Renode. Set breakpoints, step through the code, and inspect variables as needed.

6. To stop the debug session, press the "Stop" button in the debug toolbar, or press Shift+F5. This will also stop the Renode emulation.

# 3. Building the RopeRobot source code using the docker image
The build and simulation environment dependencies for the RopeRobot are defined inside the [Dockerfile](./.devcontainer/Dockerfile.nordic_playground) located in the **.devcontainer** -folder in the root of this repository. To be able to build the code you first need to [install docker](https://docs.docker.com/get-docker/) on your host.
## 3.1. Building using CMake Presets
The following [CMake presets](./app/CMakePresets.json) are available for the RopeRobot code:

| Preset Name            | Desription                               |
| ---------------------- | ---------------------------------------- |
| build.debug.nrf52840DK | Debug build configuration for nrf52840dk |

To build the code using one of these presets, you first need to build the RopeRobot docker image by typing:

```
$ docker build --tag 'rope-robot-fw-env' - < ./.devcontainer/Dockerfile.nordic_playground
```
in your shell, when situated in the root of this repository. After the build has finished successfully you start the docker RopeRobot build environment by typing:

```
$ docker run --rm \
    -v ${PWD}:/workdir/project \
    -w /workdir/project/app \
    rope-robot-fw-env \
    west build -p -d <preset name> -- --preset <preset name>
```
And change the `<preset name>` to one from the list above, depending on what type of executable you want to build. For example, if we would want to build an executable for debugging the code on a nrf52840dk we could run:
```
$ docker run --rm \
    -v ${PWD}:/workdir/project \
    -w /workdir/project/app \
    rope-robot-fw-env \
    west build -p -d build.debug.nrf52840DK -- --preset build.debug.nrf52840DK
```
And the resulting executable will be located at `app/build.debug.nrf52840DK/zephyr/zephyr.elf` relative to the root of the repository.

# 4. Renode DevContainer Architecture

This section provides an overview of the Renode DevContainer architecture, helping you understand how it's set up and how to make changes if needed. The Renode DevContainer enables a consistent development experience and simplifies the process of debugging and testing the RopeRobot firmware in an emulated environment.

## 4.1. Overview
![](documentation/simulation_environment/RopeRobot_development_environment_architecture.png)  
The Renode DevContainer architecture consists of the following key components:

1. **Dockerfile**: This file defines the Docker image for the DevContainer. It specifies the base image, installs required dependencies, and configures the environment for Renode and other necessary tools.

2. **.devcontainer folder**: This folder contains the configuration files for the DevContainer, such as `devcontainer.json`, which specifies the Dockerfile to use, sets up VS Code extensions, and configures the container's environment.

3. **Renode installation**: Renode is installed within the DevContainer and configured to run as a telnet server. The installation includes all the necessary dependencies and tools for running and debugging RopeRobot firmware in an emulated environment.

4. **VS Code tasks**: These tasks automate common actions, such as building the firmware and interacting with the Renode telnet server. They can be found in the `.vscode/tasks.json` file.

5. **VS Code launch configurations**: The launch configurations define how to start and debug the RopeRobot firmware in Renode. They can be found in the `.vscode/launch.json` file.

6. **Renode scripts**: These scripts, such as `nrf52840.resc`, set up the emulated hardware platform and load the firmware executable. They are typically located in a dedicated folder within the repository.

## 4.2. Making Changes

To modify the Renode DevContainer architecture, follow these guidelines:

1. **RopeRobot Docker Container**: If you need to add or update dependencies, modify the Dockerfile in the `.devcontainer` folder. Rebuild the DevContainer afterward to apply the changes.

2. **.devcontainer folder**: Update the `devcontainer.json` file to modify the DevContainer configuration, such as adding new VS Code extensions or changing environment variables.

3. **VS Code tasks**: Edit the tasks in the `.vscode/tasks.json` file to modify existing tasks or add new ones. Be sure to update the launch configurations if necessary.

4. **VS Code launch configurations**: Modify the launch configurations in the `.vscode/launch.json` file to change the behavior of the Renode debugging process. Update the tasks and Renode scripts if needed.

5. **Renode scripts**: If you need to change the emulated hardware platform or its configuration, update the relevant Renode scripts (e.g., `nrf52840.resc`). Make sure to update the tasks and launch configurations accordingly.

# To Do
- [ ] Refactor this readme so that it is tailored for the velestim project
- [ ] Update `stm32f7.dtsi` To use the qdec bindings. example:  

Include:
```
#include <zephyr/dt-bindings/sensor/qdec_stm32.h>
```

And then add the node under the `timers` node:
```
timers5: timers@40000c00 {
			compatible = "st,stm32-timers";
			reg = <0x40000c00 0x400>;
			clocks = <&rcc STM32_CLOCK_BUS_APB1 0x00000008>;
			resets = <&rctl STM32_RESET(APB1, 3U)>;
			interrupts = <50 0>;
			interrupt-names = "global";
			st,prescaler = <0>;
			status = "disabled";

			pwm {
				compatible = "st,stm32-pwm";
				status = "disabled";
				#pwm-cells = <3>;
			};

			counter {
				compatible = "st,stm32-counter";
				status = "disabled";
			};

			qdec {
				compatible = "st,stm32-qdec";
				status = "disabled";
				st,input-filter-level = <NO_FILTER>;
			};
		};
```
