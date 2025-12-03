# RC Syot

"RC Syot" (Remote Control DIY) is a project dedicated to building your own remote-controlled toys using Arduino microcontrollers and common RF433 communication modules. This project provides the basic framework for creating a remote control transmitter and a receiver unit for a toy, demonstrated through a simple remote-controlled tank.

The goal of this project is to offer a hands-on approach to understanding basic wireless communication, microcontroller programming, and motor control in the context of DIY remote-controlled vehicles.

## Project Architecture Overview

The project is divided into two main components:

1.  **Remote Control (Transmitter):** This unit is responsible for sending control signals based on user input (e.g., joystick movements, button presses). It reads inputs and transmits corresponding commands wirelessly via an RF433 module.
2.  **Client (Receiver - Tank):** This unit is mounted on the remote-controlled toy (e.g., a tank). It receives commands from the remote control via an RF433 module and translates them into actions, such as controlling motors to move the tank.

Communication between the remote and the client is handled using simple RF433 modules, which are inexpensive and widely available.

## Top-Level Diagram

```mermaid
C4Context
    title System Context Diagram for RC Syot

    Person(user, "RC Syot User", "Operates the remote control <br>to command the toy vehicle.")

    System(rc_syot_system, "RC Syot System", "A DIY remote control system <br>for toy vehicles using Arduino <br>and RF433 communication.")

    System_Boundary(rc_syot_system_boundary, "RC Syot System") {
        System(remote_control, "Remote Control", "Sends control commands <br>wirelessly via RF433.")
        System(client_tank, "Client (Tank)", "Receives commands and <br>controls the tank's movement.")
    }

    Rel(user, remote_control, "Operates")
    Rel(remote_control, client_tank, "Sends control <br>signals to", "RF433 Wireless")
```

## Remote Control

The remote control part of this project is implemented in the `RCSyot/src/remote` directory, with the primary sketch being `remote_rf433.ino`. It typically involves:

*   **Input Devices:** Joysticks, buttons, or potentiometers for user input.
*   **Microcontroller:** An Arduino board (e.g., Arduino Uno, Nano) to read inputs and process commands.
*   **RF433 Transmitter:** To send encoded control signals wirelessly.

## Client (Tank)

The client part, specifically for a tank, is located in the `RCSyot/src/client` directory, with `tank_rf433.ino` as its main sketch. This component usually comprises:

*   **RF433 Receiver:** To receive control signals from the remote.
*   **Microcontroller:** An Arduino board to decode received signals and control actuators.
*   **Motor Driver:** To control the speed and direction of DC motors for movement.
*   **Motors:** To provide propulsion for the tank.

## Circuit Diagrams for Image Generation

To help visualize the hardware connections, detailed descriptions of the circuits for both the Remote Control and the Client (Tank) are provided below. These descriptions can be used to manually create circuit diagrams using various tools (e.g., Fritzing, KiCad, or drawing software).

### Remote Control Circuit Description

The Remote Control unit typically uses an Arduino Nano/Uno, an RF433MHz Transmitter module, a PS2 Joystick, and a Buzzer.

*   **Arduino Nano/Uno**
    *   **RF433MHz Transmitter Module:**
        *   VCC pin to Arduino 5V.
        *   GND pin to Arduino GND.
        *   DATA pin to Arduino Digital Pin 9 (D9).
    *   **PS2 Joystick:**
        *   VCC pin to Arduino 5V.
        *   GND pin to Arduino GND.
        *   DAT pin to Arduino Digital Pin 12 (D12).
        *   CMD pin to Arduino Digital Pin 11 (D11).
        *   SEL pin to Arduino Digital Pin 10 (D10).
        *   CLK pin to Arduino Digital Pin 13 (D13).
    *   **Buzzer:**
        *   One terminal to Arduino Digital Pin 6 (D6).
        *   Other terminal to Arduino GND.

### Client (Tank) Circuit Description

The Client (Tank) unit typically uses an Arduino Nano/Uno, an RF433MHz Receiver module, an L298N Motor Driver, two DC Motors, and a Buzzer.

*   **Arduino Nano/Uno**
    *   **RF433MHz Receiver Module:**
        *   VCC pin to Arduino 5V.
        *   GND pin to Arduino GND.
        *   DATA pin to Arduino Digital Pin 4 (D4).
    *   **L298N Motor Driver Module:**
        *   VCC (or 12V) pin to a separate power source (e.g., battery, 7-12V), and connect its GND to Arduino GND.
        *   IN1 pin to Arduino Digital Pin 11 (D11).
        *   IN2 pin to Arduino Digital Pin 6 (D6).
        *   IN3 pin to Arduino Digital Pin 3 (D3).
        *   IN4 pin to Arduino Digital Pin 5 (D5).
    *   **DC Motors:**
        *   Motor 1 terminals to L298N OUT1 and OUT2.
        *   Motor 2 terminals to L298N OUT3 and OUT4.
    *   **Buzzer:**
        *   One terminal to Arduino Digital Pin 2 (D2).
        *   Other terminal to Arduino GND.


