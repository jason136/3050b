#ifndef _LIFT_H_
#define _LIFT_H_

#include "api.h"

// ----------- SETTINGS FOR AUTO LIFT CONTROL -------
#define LIFT_FULL_RETRACT 0
#define LIFT_MAX_HEIGHT 550
#define LIFT_LEVEL_LOW 100
#define LIFT_LEVEL_HIGH 400

void moveLift(int LTop, int LBottom, int RTop, int RBottom);

// lock the front lift where it is right now....
void liftLock(bool left, bool right);

// Get the current lift lock mode of the break
pros::motor_brake_mode_e_t getliftLockMode();

// Set pneumatics to extend or retract
void togglePneumaticState(int mode);

void moveClaw(int mode);

void moveGrabber(int mode);

// Control method for differential mechanism on lift
void liftComplex(int right, int left);

#endif
