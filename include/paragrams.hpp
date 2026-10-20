#include "main.h"
#include "lemlib/api.hpp"

pros::MotorGroup left_m({4, 2, 11}, pros::MotorGearset::blue);
pros::MotorGroup right_m({1}, pros::MotorGearset::green);
pros::MotorGroup down_m({7, 8});
pros::MotorGroup middle_m({9, 10});
pros::MotorGroup up_m({11, 12});
pros::Controller mi_control(pros::E_CONTROLLER_MASTER); 
pros::Imu imu(10);
pros::Rotation horizontal(-13); //CHECK PORTT
pros::Rotation vertical(-17); //CHECK PORTT