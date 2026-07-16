#include "main.h"
#include "lemlib/api.hpp"

pros::MotorGroup right_m({1, 2, 3});
pros::MotorGroup left_m({4, 5, 6});
pros::MotorGroup down_m({7, 8});
pros::MotorGroup middle_m({9, 10});
pros::MotorGroup up_m({11, 12});
pros::Controller mi_control(pros::E_CONTROLLER_MASTER); 

