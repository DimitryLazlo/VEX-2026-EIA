#include "main.h"
#include "pros/misc.hpp"
#include "pros/motor_group.hpp"
#include "pros/rtos.hpp"
#include "lemlib/api.hpp"

class tankdrive
{
private:
    /* data */
public:
    tankdrive(pros::MotorGroup *motorDer, pros::MotorGroup*motorIzq, pros::Controller*control);
    
    pros::MotorGroup *dermotor;
    pros::MotorGroup *izqmotor;
    pros::Controller *control;

    float adaptedR();
    void mando();
    float adaptedL();


    int cambio = 0; 

    float rightVolt {};
	float leftVolt {};
    
    
    

};

