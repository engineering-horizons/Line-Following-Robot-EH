# Team Collaboration Guideline

## 1. Git & Commit Protocol
To keep our repository history readable, **all commit messages must start with a tag in square brackets**

### Mandatory Tags:
* `[feat]` or `[feature]`: New code functionality (e.g., adding a new servo move).
* `[fix]`: Bug fixes in the logic or hardware integration.
* `[clean]`: Refactoring code or improving readability without changing logic.
* `[docs]`: Updates to the README, comments, or this guidelines file.
* `[hw]`: Specific changes related to hardware pinouts or wiring diagrams.

**Example:** `git commit -m "[feat] Added smooth stepping function to elbow joint"`

## 2. Workflow & Branching
1. **Never commit directly to `main`.** The `main` branch should always contain "production-ready" code that actually runs the arm.
2. **Feature Branches:** Create a new branch for every task (e.g., `feature/potentiometer-logic`).
3. **Pull Requests (PRs):** Once your feature works, open a PR. At least one other member must review your code before it is merged.

## 3. Code Standards
* **Comment Your Math:** If you are using a `map()` function or a specific delay, add a comment explaining *why* those numbers were chosen.
* **Variable Naming:** Use descriptive camelCase (e.g., `targetBaseAngle` instead of `x`).
* **Non-Blocking Logic:** Avoid using `delay()` inside the main loop if possible; use `millis()` so the "Stop" button always stays responsive.

## 4. Hardware Safety
Robotic arms are physically powerful and electrically sensitive.

1. **Verify Voltage:** Never plug the 7.4V LiPo directly into the ESP32. Always ensure the 5V regulator is between the battery and the MCU.
2. **The "Hand-Off" Rule:** Before uploading code that moves a servo, physically hold the arm or ensure it has "swing room." 
3. **Smooth Stepping:** Never command a servo to jump more than 5 degrees instantly. This can cause current spikes and mechanical stress.
4. **Power Cycle:** Always turn off the battery before changing any wiring on the breadboard or PCA9685.

## 5. Communication & Meetings
* **Weekly Sync:** We meet once a week to integrate our code modules.
* **Blockers:** If you are stuck for more than 2 hours, post in the slack. Don't wait until the meeting!