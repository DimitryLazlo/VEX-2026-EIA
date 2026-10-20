#include "tankdrive.hpp"
#include <iostream>
#include "main.h"
#include "lemlib/api.hpp"
#include "autonomous.hpp"
#include "paragrams.hpp"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 * 
 */
tankdrive robot(&right_m, &left_m ,&mi_control);
Auto auton(
    &right_m,
    &left_m,
    &imu,
    &horizontal,
    &vertical,
    0.0,    // horizontalOffset: reemplazar por tu valor
    0.0,    // verticalOffset: reemplazar por tu valor
    1000.0,  // kP: 
    0.0,     // kI
    0.0,     // kD
    0.05     // dt: 50 ms, solo si tu controlador lo espera en segundos
);


void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize();
    pros::lcd::set_text(1, "Motor data:");

    pros::Task datos_motor([] {
        while (true) {
            pros::lcd::print(0, "Ang: %.1f deg",
                             right_m.get_position());

            pros::lcd::print(1, "Power: %.2f W",
                             right_m.get_power());

            pros::lcd::print(2, "Torque: %.3f Nm",
                             right_m.get_torque());

            pros::lcd::print(3, "Volt: %.2f V",
                             right_m.get_voltage() / 1000.0);

            pros::lcd::print(4, "Current: %.2f A",
                             right_m.get_current_draw() / 1000.0);

            pros::delay(100);
        }
    });

    pros::lcd::register_btn1_cb(on_center_button);
    
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
    auton.pruebas();
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via lol
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
    auton.calibrate_sensors();

    auton.move_to_pose(0, 24, 0);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *ccc
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	//robot.mando();
    
}