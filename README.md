# SoC-VaccineRefrigerator
[![SHIELDS](https://img.shields.io/badge/development-completed-green)](https://shields.io/)

Authors: Coralie Allioux, Gabriel Ganzer.

Vaccination is a safe and effective way to prevent disease and save lives. Due to their composition, many vaccines must be stored at stable low temperatures after manufacture to avoid degradation. This can be a particular challenge in developing countries with rudimentary health care systems. For this reason, we present VARE, a low-cost vaccine refrigeration system that can be used to adapt a domestic fridge into a specialized medical one.

VARE is composed of the followings components:
- *UART2* for displaying messages to the user;
- *DMA* to manage data transfers;
- *TIMER2* to count the amount of time the door is open;
- *I2C1* serial communication with temperature sensors;
- *GPIO* for digital I/O signals.

## Versions for MacOS and Windows10

The `main` branch is the version for MacOS. You can find the version for Windows10 on the branch `winVersion`.

The difference between the two is in the file *platformio.ini*. MacOS doesn't call directly the command `renode`, it uses `mono` instead.

## Needed tools

To support our project, you will need:
- *Platformio*: you can download it via the official website;
- *Renode*: you must use the version providing by the link below, which is the source code of renode. Choose the appropriate OS for the prerequisites, depending on yours.

https://renode.readthedocs.io/en/latest/advanced/building_from_sources.html

## How to use

### Updating configuration files

You need to change some paths in the configuration files: *platformio.ini* and *stm32f4_discovery_modified.resc*.

#### platformio.ini file

The *platformio.ini* file is located on the root of the project. You must change the path of:
- `upload_command` value: path to *renode*;
- `upload_flags` value: path to the configuration file *stm32f4_discovery_modified.resc*;
- `debug_server` value: path to *renode* and the configuration file *stm32f4_discovery_modified.resc*.

#### stm32f4_discovery_modified.resc file

Th *stm32f4_discovery_modified.resc* file is located on the root of the project. You must change the path of:
- `machine LoadPlatformDescription` value: path to the file *sensors.repl*, located at the root;
- `$bin` value: path to the file *firmware.elf* located at *.pio/build/disco_f407vg/*.

### Starting VARE project

Build and upload the project via platformio, in order to launch renode. Once renode is open, you can include the configuration file by the following command (changing the part *YOUR_PATH*):

```include @YOUR_PATH/soc_arch_vare/stm32f4_discovery_modified.resc```

Then, start the project:

```start```

The UART is now open and your are able to interact with it via the *renode console*.

### Interacting with the system

To interact with the system, you will use directly the *renode console* to control the behavior of the different components. The results of those commands are visible on the UART and *console log*.

#### Buttons for setting the threashold

For setting up the threashold of the refrigerator, you have access on three buttons bia the *renode console*, all connected on *gpioPortC*:
- *buttonDown*: decreases the threashold of 1°C;

```gpioPortC.buttonDown PressAndRelease```

- *buttonUp*: increases the threashold of 1°C;

```gpioPortC.buttonUp PressAndRelease```

- *buttonOK*: validates the threashold.

```gpioPortC.buttonOK PressAndRelease```

#### Temperature sensors

The chamber is equipped of two temperature sensors, connected on *i2c1*. The supported temperature of the sensors is from -40°C to 125°C, otherwise, you will gate an error from *renode*. Chose the value of *YOUR_TEMPERATURE* according to this rule.
You can set the value of the measured temperature on each temperature sensor via the *renode console*, according to the following:
- *tempA*: control the measured temperature of the first sensor, called A;

```i2c1.tempA Temperature *YOUR_TEMPERATURE*```

- *tempB*: control the measured temperature of the first sensor, called B.

```i2c1.tempB Temperature *YOUR_TEMPERATURE*```

#### Door sensor

The door sensor is connected on *gpioPortA*, and is able to detect if the refrigrerator door is open or closed. The same command is used to open the door (when it is closed) and vice versa, which is the following:

```gpioPortA.sensorOC Toggle```
