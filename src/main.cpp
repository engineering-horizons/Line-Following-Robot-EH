#include <Arduino.h>

/*
===========================================================
LINE FOLLOWING ROBOT - SOFTWARE SKELETON (SIMULATION)
===========================================================

PURPOSE OF THIS FILE:
This is the "brain model" of our robot.

We use it to:
- Understand how the robot makes decisions
- Test logic BEFORE hardware arrives
- Split work between team members clearly

We are building a system that will later run on an ESP32
with CNY70 IR sensors and motor drivers.

===========================================================
SYSTEM OVERVIEW (VERY IMPORTANT)
===========================================================

The robot follows this pipeline:

    [CNY70 SENSOR ARRAY]
              ↓
     line position (-1 to +1)
              ↓
          ERROR (center = 0)
              ↓
         PID CONTROLLER
              ↓
     LEFT / RIGHT MOTOR SPEEDS
              ↓
       MOTOR DRIVER (TB6612FNG)
              ↓
           ROBOT MOVEMENT

===========================================================
TEAM TASK BREAKDOWN
===========================================================
The following skeleton is currently a simulation. 
The following tasks will focus on replacing a certain section with real hardware code!

1. SENSOR INTERPRETATION (CNY70 MODULE)
   - Replace simulateSensor()
   - Read multiple CNY70 sensors
   - Convert readings → position (-1 to +1)

  1.1 Convert position to error (target is 0!) that way PID can use it as input! 
      This is already done in the main loop!

2. CONTROL FUNCTION (PID SYSTEM)
   - Improve computePID()
   - Tune Kp, Ki, Kd
   - Add stability improvements (optional later)

3. MOTOR TEAM (DRIVER LAYER)
   - Replace setMotors()
   - Use TB6612FNG motor driver
   - Convert correction → motor PWM signals

4. INTEGRATION (I WILL BE IN CHARGE OF INTEGRATION UNLESS SOMEONE IS PARTICULARLY INTERESTED IN LEADING THIS!)
   - Ensure all modules connect properly
   - Debug full system behavior
   - Tune final robot performance

===========================================================
GOAL:
Each module is independent so teams can work in parallel.
===========================================================
*/


// -------------------- CONFIG --------------------
float baseSpeed = 120;

// PID constants (starting point - we will tune these later)
float Kp = 80;
float Ki = 0;
float Kd = 20;

// PID memory
float integral = 0;
float lastError = 0;


// -------------------------------------------------
// 1. SENSOR LAYER (SIMULATED CNY70 ARRAY)
// -------------------------------------------------
/*
REAL HARDWARE (CNY70 SETUP):
We will use multiple CNY70 sensors arranged in a line - something like this:

   [S1] [S2] [S3] [S4] [S5]
    L    L    C    R    R

Each sensor measures reflected IR light from the ground.

BLACK LINE → low reflection
WHITE GROUND → high reflection

We convert sensor values into a single "position value".
*/

float simulateSensor() {
  static float t = 0;
  t += 0.1;

  // Simulated robot movement over a line
  // (-1 = far left, +1 = far right)
  float position = sin(t);

  return position;
}


// -------------------------------------------------
// 2. PID CONTROLLER (BRAIN OF ROBOT)
// -------------------------------------------------
/*
PID converts error into correction:

error = desired_position - actual_position

We want the robot centered → target = 0
*/

float computePID(float error) {
  integral += error;
  float derivative = error - lastError;
  lastError = error;

  float output = (Kp * error) + (Ki * integral) + (Kd * derivative);

  return output;
}


// -------------------------------------------------
// 3. MOTOR LAYER (SIMULATED OUTPUT)
// -------------------------------------------------
/*
REAL HARDWARE:
This will control TB6612FNG motor driver:

- Left motor speed
- Right motor speed
- Direction control pins

For now we simulate output only.
*/

void setMotors(float correction) {

  float leftMotor = baseSpeed - correction;
  float rightMotor = baseSpeed + correction;

  // Safety limits (real motors cannot exceed range)
  leftMotor = constrain(leftMotor, -255, 255);
  rightMotor = constrain(rightMotor, -255, 255);

  Serial.print("MOTORS -> L: ");
  Serial.print(leftMotor);
  Serial.print(" | R: ");
  Serial.println(rightMotor);

}

/**
 * Setup function - runs once at the beginning

// -------------------------------------------------
// 4. SETUP (RUNS ONCE)
// -------------------------------------------------
void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n====================================");
  Serial.println(" LINE FOLLOWING ROBOT SIMULATION ");
  Serial.println("====================================\n");
}
 */

// -------------------------------------------------
// 5. MAIN LOOP (REAL ROBOT LOGIC FLOW)
/**
 * Main loop of the robot
// -------------------------------------------------
void loop() {

  // STEP 1: SENSOR INPUT (CNY70 SIMULATION)
  float position = simulateSensor();

  // STEP 2: COMPUTE ERROR (center is 0)
  float target = 0;
  float error = target - position;

  // STEP 3: PID CONTROLLER
  float correction = computePID(error);

  // STEP 4: MOTOR OUTPUT
  Serial.print("POS: ");
  Serial.print(position, 3);
  Serial.print(" | ERROR: ");
  Serial.print(error, 3);
  Serial.print(" | ");

  setMotors(correction);

  delay(100);
}
*/

void setup(){
  Serial.begin(115200);
  delay(1000);
  Serial.println("Setup complete. Starting loop...");
}

void loop(){
  Serial.println("running...");
  delay(1000);
}