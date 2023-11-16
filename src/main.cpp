#include "main.h"
#include "pros/misc.h"
#include "pros/motors.hpp"
#include <string>
#include <vector>
#include <math.h>




pros::Motor topRight(9, true); //port 13, clockwise
pros::Motor topLeft(3, false); 
pros::Motor botLeft(15, true);
pros::Motor botRight(20, false);
pros::Motor Catapult(3);
pros::Vision vision_sensor(7);  // Create a Vision sensor on port 1

int distRead;
pros::Distance dist(7); //distance censor 1

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
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
	pros::lcd::set_text(1, "Hello PROS User!");

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
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 * 
 * 
 * 
 */
void autonomous() {
pros::lcd::set_text(1, "AUTON!");

topLeft.tare_position(); // Swap negatives if you want the bot to drive in the other direction
topRight.tare_position();
botLeft.tare_position();
botRight.tare_position();

pros::lcd::set_text(2, std::to_string(topLeft.get_position()));
pros::lcd::set_text(3, std::to_string(topRight.get_position()));
pros::lcd::set_text(4, std::to_string(botLeft.get_position()));
pros::lcd::set_text(5, std::to_string(botRight.get_position()));

topLeft.move_absolute(1000,20); // Swap negatives if you want the bot to drive in the other direction
topRight.move_absolute(1000,20);
botLeft.move_absolute(-1000,20);
botRight.move_absolute(-1000,20);
pros::delay(5000);

pros::lcd::set_text(2, std::to_string(topLeft.get_position()));
pros::lcd::set_text(3, std::to_string(topRight.get_position()));
pros::lcd::set_text(4, std::to_string(botLeft.get_position()));
pros::lcd::set_text(5, std::to_string(botRight.get_position()));
pros::delay(2000);

topLeft.tare_position(); // Swap negatives if you want the bot to drive in the other direction
topRight.tare_position();
botLeft.tare_position();
botRight.tare_position();

pros::lcd::set_text(2, std::to_string(topLeft.get_position()));
pros::lcd::set_text(3, std::to_string(topRight.get_position()));
pros::lcd::set_text(4, std::to_string(botLeft.get_position()));
pros::lcd::set_text(5, std::to_string(botRight.get_position()));







}

/**VEX SIG FROM V5 
signature Vision16__GREEN_TRIBALL = signature (1, -7881, -3961, -5921, -5507, -2257, -3882, 2.2, 0);
vision Vision16 = vision (PORT16, 50, Vision16__GREEN_TRIBALL);\
**/
/** 

pros::vision_signature_s_t sig = pros::Vision::signature_from_utility(1, -6199, -3071, -4635, -6131, -3221, -4676, 2.100, 0);
vision.set_signature(1, &sig);  // Set the vision signature

	while (true) {
		dist.get(); //get distance
		distRead = dist.get();
		pros::delay(1);

		topRight.move_velocity(75); //forward
		topLeft.move_velocity(75);
		botLeft.move_velocity(-75);
		botRight.move_velocity(-75);
		pros::delay(1);

		while (distRead<=100) {
			topRight.move_velocity(-75); //backward
			topLeft.move_velocity(-75);
			botLeft.move_velocity(75);
			botRight.move_velocity(75);
			pros::delay(2000);
			
			topRight.move_velocity(0); //pause
			topLeft.move_velocity(0);
			botLeft.move_velocity(0);
			botRight.move_velocity(0);
			pros::delay(250);

			topRight.move_velocity(-75); //turn left
			topLeft.move_velocity(75);
			botLeft.move_velocity(-75);
			botRight.move_velocity(75);
			pros::delay(300);

			//velocity 15, delay .9 sec = 90 degrees

			dist.get(); //get distance
			distRead = dist.get();
			pros::delay(1);
		}	
	}

**/



/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 * 
 * 
*void opcontrol() {
*	 pros::vision_signature_s_t sig = pros::Vision::signature_from_utility(1, -6199, -3071, -4635, -6131, -3221, -4676, 2.100, 0);  //GreenTriball
*   vision_sensor.set_signature(1, &sig);  //Pointer is used to save signature to signature 1 
*   while (true) {
*        pros::vision_object_s_t obj = vision_sensor.get_by_sig(0, 1);
*        if (obj.signature == 1) {
*            pros::vision_signature_s_t sig = vision_sensor.get_signature(1);
*            pros::Vision::print_signature(sig);
*        }
*
*        pros::delay(20); // Don't hog CPU resources - delay between loops
*    }
*}
*/


void opcontrol() {
	int yMotion;
	int xMotion;

	while (true)
	{

		pros::lcd::set_text(1, std::to_string(topLeft.get_position()));
		pros::lcd::set_text(2, std::to_string(topRight.get_position()));
		pros::lcd::set_text(3, std::to_string(botLeft.get_position()));
		pros::lcd::set_text(4, std::to_string(botRight.get_position()));

		pros::Controller master(pros::E_CONTROLLER_MASTER);
		// driving control code

		yMotion = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X); // ik this looks wrong, but it works
		xMotion = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);


		int right = -xMotion + yMotion; //-power + turn
		int left = xMotion + yMotion;	// power + turn

		topLeft.move(left); // Swap negatives if you want the bot to drive in the other direction
		botLeft.move(-left);
		botRight.move(right);
		topRight.move(-right);


		if (master.get_digital(DIGITAL_R2))
		{ // runs flywheel while holding R2 down

			Catapult.move_velocity(40); // Changes flywheel velocity
			Catapult.move_velocity(40);
			pros::lcd::set_text(5, std::to_string(Catapult.get_actual_velocity()));
			pros::lcd::set_text(6, std::to_string(Catapult.get_actual_velocity()));
		}
		else
		{
			Catapult.move_velocity(0);
			Catapult.move_velocity(0);
		}

		
		//centerWheel.move(rotate);
		pros::delay(1);

		pros::delay(20);
	}


}