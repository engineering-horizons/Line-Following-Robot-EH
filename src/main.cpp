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
SYSTEM OVERVIEW 
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
const float baseSpeed = 120;

// -------------------- SENSOR --------------------
const int sensorThreshold = 2000;

// PID constants (starting point - we will tune these later)
const float Kp = 80;
const float Ki = 0;
const float Kd = 20;


// --------------- GLOBAL STATE ----------------
// PID memory
float integral = 0;
float lastError = 0;

int sensors[5];

//---------------- HARDWARE PINS ----------------

// TODO: Replace with actual PCB mappings
const int sensorPins[5] = {34, 35, 32, 33, 25};

// TB6612FNG
///A and B are out two motors
//PWM is the power amount we send 0 - 225
// IN1 and IN2 control direction
//Ex:
//Example:
/*
  AIN1	AIN2	Result
  HIGH	LOW	  forward
  LOW	  HIGH	reverse
  LOW	  LOW	  stop
*/
const int PWMA = 26;
const int AIN1 = 27;
const int AIN2 = 14;

const int PWMB = 13;
const int BIN1 = 12;
const int BIN2 = 15;



// -------------------------------------------------
// 1. SENSOR LAYER (READ/SIMULATE CN70 Array)
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

void readSensors() {

  // ======================================================
  // TEMP SIMULATION MODE
  // Replace with analogRead() when hardware is connected
  // ======================================================

  float t = millis() / 1000.0;

  sensors[0] = (sin(t) > 0.5) ? 1 : 0;
  sensors[1] = (sin(t + 0.5) > 0.5) ? 1 : 0;
  sensors[2] = (sin(t + 1.0) > 0.5) ? 1 : 0;
  sensors[3] = (sin(t + 1.5) > 0.5) ? 1 : 0;
  sensors[4] = (sin(t + 2.0) > 0.5) ? 1 : 0;

  // ======================================================
  // REAL ANALOG READ 
  // ======================================================
  // TODO: Determine experimentally using real sensor values
  /*

  int raw = analogRead(sensorPins[i]);

  if (raw < sensorThreshold)
      sensors[i] = 1;
  else
      sensors[i] = 0;

  */
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
  // STEP 1:WEIGHTS (DO NOT CHANGE)
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

  // Loop through all sensors
  for (int i = 0; i < 5; i++) {
    if (sensors[i] == 1) {
      sum += weights[i];
      activeCount++;
    }
  }
  if (activeCount == 0) {
    return 0;
  }

  // Weighted average
  float position = sum / activeCount;

  // Debug print
  Serial.print("POSITION: ");
  Serial.println(position);

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

  // PROPORTIONAL TERM
  //    - Bigger error = bigger steering correction

  float proportional = Kp * error;

  // DERIVATIVE TERM
  //    -Helps reduce oscillation/shaking

  float derivative = error - lastError;

  // INTEGRAL TERM
  //    - Helps correct long-term drift

  integral += error;

  // FINAL PID OUTPUT

  float correction =
      proportional +
      (Ki * integral) +
      (Kd * derivative);

  // Save for next loop
  lastError = error;

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

  float leftMotor = baseSpeed - correction;
  float rightMotor = baseSpeed + correction;

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

  // ---------------- LEFT MOTOR ----------------
  if (leftMotor >= 0) {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  } else {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
  }

  // ---------------- RIGHT MOTOR ----------------
  if (rightMotor >= 0) {
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  } else {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
  }

  // PWM POWER
  analogWrite(PWMA, abs(leftMotor));
  analogWrite(PWMB, abs(rightMotor));

  // DEBUG
  Serial.print("L:");
  Serial.print(leftMotor);

  Serial.print(" | R:");
  Serial.println(rightMotor);
}


// -------------------------------------------------
// 4. SETUP (RUNS ONCE)
// -------------------------------------------------
void setup() {
  Serial.begin(115200);
  delay(1000);

  // ---------------- SENSOR PINS ----------------
  for (int i = 0; i < 5; i++) {
    pinMode(sensorPins[i], INPUT);
  }

  // ---------------- MOTOR DRIVER PINS ----------------
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  Serial.println("\n====================================");
  Serial.println(" LINE FOLLOWING ROBOT SIMULATION ");
  Serial.println("====================================\n");
}


// -------------------------------------------------
// 5. MAIN LOOP (REAL ROBOT LOGIC FLOW)
// -------------------------------------------------
float simulatedPosition = 0;  // fake robot state

//for debugging
void printSensors() {

  Serial.print("SENSORS: ");

  for (int i = 0; i < 5; i++) {
    Serial.print(sensors[i]);
    Serial.print(" ");
  }

  Serial.println();
}


void loop() {

  readSensors();
  printSensors();
  // 1. SENSOR (what robot THINKS is happening)
  float sensorPosition = getPosition();

  // 2. ERROR
  float error = 0 - sensorPosition;

  // 3. PID OUTPUT
  float correction = computePID(error);

  // 4. MOTOR OUTPUT (this is what PID is controlling)
  setMotors(correction);


  Serial.print("POS: ");
  Serial.print(sensorPosition);

  Serial.print(" | ERR: ");
  Serial.print(error);

  Serial.print(" | CORR: ");
  Serial.print(correction);

  delay(100);
}



// ======================================================
// SENSOR READING TEST
// ======================================================
/*
void loop() {

  printRawSensorValues();

  delay(100);
}
*/
void printRawSensorValues() {

  Serial.print("RAW: ");

  for (int i = 0; i < 5; i++) {

    int raw = analogRead(sensorPins[i]);

    Serial.print(raw);
    Serial.print(" ");
  }

  Serial.println();
}




// ======================================================
// TEMP ESP32 CONNECTION TEST
// ======================================================
// This temporary setup/loop is ONLY for verifying:
// - ESP32 uploads correctly
// - Serial Monitor works
// - PlatformIO connection works
//
// Once hardware integration begins:
// - remove/comment this section
// - restore main robot simulation loop
// ======================================================
/*
void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("ESP32 setup successful ✔");
}

void loop() {
  Serial.println("running...");
  delay(1000);
}
*/