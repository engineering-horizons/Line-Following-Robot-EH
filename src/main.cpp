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

/*
-----------------------------------------------------------
getPosition()
-----------------------------------------------------------

PURPOSE:
This function determines where the black line is relative
to the center of the robot.

The output should be a SINGLE position value:

-1.0  = line is far LEFT
 0.0  = robot is centered on line
+1.0  = line is far RIGHT

This value becomes the input to the PID controller.

-----------------------------------------------------------
REAL HARDWARE VERSION (FUTURE)
-----------------------------------------------------------

Eventually this function will:

1. Read multiple CNY70 IR sensors
2. Detect which sensors see the black line
3. Convert those readings into ONE weighted position

Example sensor layout:

[S1] [S2] [S3] [S4] [S5]
 -1  -0.5  0  +0.5 +1

Example:
0 0 1 0 0  -> centered -> 0
1 1 0 0 0  -> left     -> -0.75
0 0 0 1 1  -> right    -> +0.75

-----------------------------------------------------------
WITHOUT HARDWARE (CURRENT TASK)
-----------------------------------------------------------

For now:
- simulate sensor behavior
- create fake sensor patterns
- test weighted averaging logic

IMPORTANT:
The goal is NOT realism yet.
The goal is to build the POSITION CALCULATION PIPELINE.

-----------------------------------------------------------
SUGGESTED IMPLEMENTATION STEPS
-----------------------------------------------------------

STEP 1:
Create a fake sensor array:
int sensors[5];

STEP 2:
Simulate different line positions
(example patterns)

STEP 3:
Assign weights to each sensor:
[-1, -0.5, 0, 0.5, 1]

STEP 4:
Compute weighted average position

STEP 5:
Return final normalized position value

-----------------------------------------------------------
EXPECTED OUTPUT:
-----------------------------------------------------------

float position

Range:
-1.0 to +1.0
*/

float getPosition() {

  // ======================================================
  // STEP 1: SIMULATED SENSOR INPUT (DO NOT MODIFY)
  // ======================================================

  int sensors[5];

  // Fake line movement (already working simulation)
  float t = millis() / 1000.0;

  sensors[0] = (sin(t) > 0.5) ? 1 : 0;
  sensors[1] = (sin(t + 0.5) > 0.5) ? 1 : 0;
  sensors[2] = (sin(t + 1.0) > 0.5) ? 1 : 0;
  sensors[3] = (sin(t + 1.5) > 0.5) ? 1 : 0;
  sensors[4] = (sin(t + 2.0) > 0.5) ? 1 : 0;

  // ======================================================
  // STEP 2: WEIGHTS (DO NOT CHANGE)
  // ======================================================

  float weights[5] = {-1.0, -0.5, 0.0, 0.5, 1.0};

  // ======================================================
  // STEP 3: YOUR TASK STARTS HERE
  // ======================================================
  // GOAL:
  // Convert sensors + weights → single position value
  //
  // RULES:
  // - Multiply sensor[i] * weights[i]
  // - Add results
  // - Divide by number of active sensors
  // - If no sensors active → return 0
  // ======================================================

  float sum = 0;
  int activeCount = 0;

  // TODO: implement weighted average here

  return 0; // <-- replace this
}
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

  // ======================================================
  // STEP 1 (START SIMPLE - REQUIRED FIRST)
  // ======================================================
  // GOAL:
  // Make correction proportional to error ONLY
  //
  // SEARCH:
  // "proportional control robot line following"
  // ======================================================

  float correction = 0;

  // TODO (STEP 1 ONLY):
  // correction = Kp * error;

  // ======================================================
  // STEP 2 (ONLY AFTER STEP 1 WORKS)
  // OPTIONAL IMPROVEMENTS:
  // Add stability using:
  // - integral (Ki)
  // - derivative (Kd)
  //
  // HINT:
  // integral += error;
  // derivative = error - lastError;
  // ======================================================

  return correction;
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

  // ======================================================
  // GOAL:
  // Convert "correction" into LEFT + RIGHT motor speeds
  // ======================================================

  float leftMotor = 0;
  float rightMotor = 0;

  // ======================================================
  // STEP 1 (REQUIRED)
  // BASE IDEA:
  // - baseSpeed = forward speed
  // - correction steers robot
  //
  // HINT:
  // if correction is positive → robot should turn right
  // ======================================================

  // TODO:
  // leftMotor = baseSpeed - correction;
  // rightMotor = baseSpeed + correction;

  // ======================================================
  // STEP 2 (SAFETY - DO NOT REMOVE)
  // ======================================================

  leftMotor = constrain(leftMotor, -255, 255);
  rightMotor = constrain(rightMotor, -255, 255);

  // ======================================================
  // DEBUG OUTPUT (KEEP THIS)
  // ======================================================

  Serial.print("LEFT: ");
  Serial.print(leftMotor);
  Serial.print(" | RIGHT: ");
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
float simulatedPosition = 0;  // fake robot state

/*
void loop() {

  // 1. SENSOR (what robot THINKS is happening)
  float sensorPosition = simulateSensor();

  // 2. ERROR
  float error = 0 - sensorPosition;

  // 3. PID OUTPUT
  float correction = computePID(error);

  // 4. MOTOR OUTPUT (this is what PID is controlling)
  setMotors(correction);

  // This simulates how motors affect robot position

  simulatedPosition += correction * 0.0005;

  // natural drift (like real robot imbalance)
  simulatedPosition *= 0.98;

  // feed simulated position back into sensor model
  Serial.print("SIM POS: ");
  Serial.print(simulatedPosition);
  Serial.print(" | CORR: ");
  Serial.println(correction);

  delay(100);
}
*/

<<<<<<< HEAD
void setup(){
  Serial.begin(115200);
  delay(1000);
  Serial.println("Setup complete. Starting loop...");
}

void loop(){
=======


//SETUP 

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("ESP32 setup successful ✔");
}

void loop() {
>>>>>>> 5ee8f98cbb05140c1814ec2ca1a0b6bac92ffefe
  Serial.println("running...");
  delay(1000);
}