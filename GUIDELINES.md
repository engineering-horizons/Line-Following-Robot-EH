# Team Collaboration Guideline

## 1. Git & Commit Protocol

To keep our repository history readable, **all commit messages must start with a tag in square brackets**

### Mandatory Tags:

* `[feat]` or `[feature]`: New code functionality (e.g., adding PID logic or sensor processing).
* `[fix]`: Bug fixes in the logic or hardware integration.
* `[clean]`: Refactoring code or improving readability without changing logic.
* `[docs]`: Updates to the README, comments, or this guidelines file.
* `[hw]`: Specific changes related to hardware pinouts or wiring diagrams.

**Example:** `git commit -m "[feat] Implemented PID controller with initial tuning"`

## 2. Workflow & Branching

1. **Never commit directly to `main`.** The `main` branch should always contain "production-ready" code that actually runs the robot.
2. **Feature Branches:** Create a new branch for every task (e.g., `feature/pid-controller`, `feature/sensor-position`).
3. **Pull Requests (PRs):** Once your feature works, open a PR. At least one other member must review your code before it is merged.

## 3. Code Standards

* **Comment Your Math:** If you are using a position calculation, PID constants, or thresholds, add a comment explaining *why* those values were chosen.
* **Variable Naming:** Use descriptive camelCase (e.g., `linePosition`, `motorCorrection`, `leftMotorSpeed` instead of `x`).
* **Keep Modules Separate:** Do not combine sensor reading, PID logic, and motor control into a single function. Each layer should remain independent.
* **Non-Blocking Logic:** Avoid using `delay()` inside the main loop if possible; use `millis()` so the control loop remains responsive.

## 4. Hardware Safety

Line-following robots involve motors and power systems that must be handled carefully.

1. **Verify Voltage:** Never power motors directly from the ESP32. Ensure proper voltage regulation between the battery, motors, and microcontroller.
2. **Initial Testing:** Start with low motor speeds when testing new code to prevent unstable behavior.
3. **Sensor Setup:** Ensure IR sensors are positioned close to the ground and securely mounted for reliable readings.
4. **Power Cycle:** Always turn off the battery before changing any wiring on the breadboard or motor driver.

## 5. Communication & Meetings

* **Weekly Sync:** We meet once a week to integrate our code modules.
* **Blockers:** If you are stuck for more than 2 hours, post in the slack. Don't wait until the meeting!

