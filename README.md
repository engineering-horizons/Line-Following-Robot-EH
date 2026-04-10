# Line Following Robot Engineering Horizons UW

## Overview

This project aims to design and build a **line-following robot from scratch** using an ESP32 microcontroller, IR sensors, and motor control systems.

The goal is not only to create a functioning robot, but also to help team members gain hands-on experience with:

* Embedded systems
* Sensor integration
* Motor control
* Control theory (PID)
* Hardware/software integration

---

## System Architecture

The robot operates using a simple control pipeline:

```
Sensors → Position → Error → PID → Motors
```

### Breakdown:

* **Sensors (CNY70 IR Array)**
  Detect the position of the line relative to the robot.

* **Position Calculation**
  Converts sensor readings into a normalized value from **-1 (left)** to **+1 (right)**.

* **Error Calculation**
  Computes how far the robot is from the center of the line:

  ```
  error = 0 - position
  ```

* **PID Controller**
  Converts error into a correction value for steering.

* **Motor Control (TB6612FNG)**
  Adjusts left and right motor speeds to follow the line.

---

## Project Structure

```
Line-Following-Robot-EH/
├── src/            # Main application code (main.cpp)
├── include/        # Header files
├── lib/            # External libraries (if needed)
├── test/           # Testing files
├── platformio.ini  # Project configuration (ESP32)
├── README.md       # Project documentation
```

---

## Getting Started

### 1. Prerequisites

* VS Code
* PlatformIO extension
* Git

### 2. Clone the Repository (the cloning link will change once I move the repository to Engineering Horizons

```bash
git clone https://github.com/Xander-Terry/Line-Following-Robot-EH.git 
cd Line-Following-Robot-EH
```

### 3. Open in VS Code

* Open the folder in VS Code
* PlatformIO should automatically detect the project

### 4. Build the Project

Click the Check mark in the bottom left (Build) button in the bottom toolbar. (May also be the checkmark button near the top right )

---

## Current Status

 **Simulation Phase**

We are currently:

* Developing software architecture
* Simulating sensor input and control logic
* Preparing for hardware integration

Hardware (ESP32, motors, sensors) will be integrated in future phases.

---

## Task Responsibilities

### 1. Sensor + Position System

* Read CNY70 IR sensors
* Convert readings into position (-1 to +1)

### 2. PID Control System

* Implement and tune PID controller
* Ensure stable and smooth line following

### 3. Motor Control System

* Interface with TB6612FNG motor driver
* Convert PID output into motor speeds

### 4. Integration (Software Lead)

* Combine all systems
* Debug full robot behavior
* Optimize performance

---

## Future Goals

* Integrate real hardware (ESP32 + sensors + motors)
* Tune PID for high-speed tracking
* Design custom PCB
* Potentially compete in robotics competitions

---

## Notes

* This project is structured to allow parallel development across multiple team members.
* Simulation code is used before hardware arrives to validate system logic.

---

## Contributors

* Software Lead: Xander Terry
* Team Members: (To be added)

---
