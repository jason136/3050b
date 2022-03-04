#include "main.h"
#include "portdef.hpp"
#include "lift.hpp"

// Setup the motor definition for the lift motor
pros::Motor rightTopLiftMotor(RIGHT_TOP_LIFT_MOTOR, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightBottomLiftMotor(RIGHT_BOTTOM_LIFT_MOTOR, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftTopLiftMotor(LEFT_TOP_LIFT_MOTOR, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftBottomLiftMotor(LEFT_BOTTOM_LIFT_MOTOR, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);

void moveLift(int LTop, int LBottom, int RTop, int RBottom) {
    if (LTop) leftTopLiftMotor.move(LTop);
    if (LBottom) leftBottomLiftMotor.move(LBottom);
    if (RTop) rightTopLiftMotor.move(RTop);
    if (RBottom) rightBottomLiftMotor.move(RBottom);
}

void liftLock(pros::motor_brake_mode_e_t brakeType, bool left=false, bool right=false) {
    if (!left) {
        leftTopLiftMotor.set_brake_mode(brakeType);
        leftBottomLiftMotor.set_brake_mode(brakeType);
        leftTopLiftMotor.move_velocity(0);
        leftBottomLiftMotor.move_velocity(0);
    }
    if (!right) {
        rightTopLiftMotor.set_brake_mode(brakeType);
        rightBottomLiftMotor.set_brake_mode(brakeType);
        rightTopLiftMotor.move_velocity(0);
        rightBottomLiftMotor.move_velocity(0);
    }
}

void resetLiftEncoders() {
    rightTopLiftMotor.tare_position();
    rightBottomLiftMotor.tare_position();
    leftTopLiftMotor.tare_position();
    leftBottomLiftMotor.tare_position();
}

pros::motor_brake_mode_e_t getliftBrakeMode() {
    return rightTopLiftMotor.get_brake_mode();
}

int speed;
bool decelerating;

void liftComplex(int left, int right) {
    if ((right || left) && speed < 127) speed += 10;
    else {
        if (speed > 0) {
            decelerating = true;
            speed -= 20;
        }
        else if (speed <= 0) {
            decelerating = false;
            speed = 0;
        }
    }
    
    if (decelerating) {
        liftLock(pros::E_MOTOR_BRAKE_COAST);
    }
    else if (right || left) {
        std::cout << "lift with speed called" << std::endl;
        if (right) {
            // moveLift(right * -1 * speed, right * -1 * speed, right * 1 * speed, right * 1 * speed);
            moveLift(0, 0, right * 1 * speed, right * -1 * speed);
            liftLock(pros::E_MOTOR_BRAKE_HOLD, false, true);
        }
        else if (left) {
            moveLift(left * -1 * speed, left * -1 * speed, left * 1 * speed, left * 1 * speed);
        }
    }
    else {
        liftLock(pros::E_MOTOR_BRAKE_HOLD); 
    }
}

void liftRaiseForEncoder(int encDegrees, int speed, bool wait) {
    resetLiftEncoders();

    leftTopLiftMotor.move_absolute(encDegrees, -speed);
    leftBottomLiftMotor.move_absolute(encDegrees, -speed);
    rightTopLiftMotor.move_absolute(encDegrees, speed);
    rightBottomLiftMotor.move_absolute(encDegrees, speed);

    if (wait) {
        while (!((leftTopLiftMotor.get_position() < encDegrees + 5) && (leftTopLiftMotor.get_position() > encDegrees - 5))) {
            pros::delay(2);
        }
    }
}

void spinRollerForEncoder(int encDegrees, int speed, bool wait) {
    liftLock(pros::E_MOTOR_BRAKE_HOLD, false, true);
    resetLiftEncoders();

    rightTopLiftMotor.move_absolute(encDegrees, speed);
    rightBottomLiftMotor.move_absolute(encDegrees, -speed);

    if (wait) {
        while (!((rightTopLiftMotor.get_position() < encDegrees + 5) && (rightTopLiftMotor.get_position() > encDegrees - 5))) {
            pros::delay(2);
        }
    }
}