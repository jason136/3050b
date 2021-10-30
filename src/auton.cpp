#include "main.h"
#include "portdef.hpp"
#include "auton.hpp"
#include "chassis.hpp"
#include "lift.hpp"
#include "conveyor.hpp"
#include "file.hpp"
#include "opcontrol.hpp"

void runRecAuton() {
  int interations = getVectorSize();
  double recJoysticks[4];
  int recButtons[3];
  for (int x = 0; x < interations; x++) {
    updateIndex(&recJoysticks[0], &recButtons[0], x);
    processInput();
    pros::delay(20);
  }
}

/**
 * This is where all the various autonomous routines are located
 * and subsequently called by the autonomous() selector based on GUI input
 **/
void skillRun() {

  // Old code below use only for reference. ie delete
  //liftMove(100);
  pros::delay(100);
  //liftMove(-100);
  pros::delay(100);
  //liftMove(100);
  pros::delay(100);
  //liftMove(-100);
  pros::delay(100);
  //liftLock();

  setIndividualMotor(100, -100, -100, 100);
  pros::delay(2000);
  chassisStopDrive();
 }

void autoRedLeft() {

  // Code Here

}

void autoBlueLeft() {

  // Code Here

}

 void autoRedRight() {

  // Code Here

}


 void autoBlueRight() {

  // Code Here penis

}
