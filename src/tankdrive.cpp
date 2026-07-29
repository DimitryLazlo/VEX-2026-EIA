#include "tankdrive.hpp"
#include "pros/misc.h"
#include "math.h"
using namespace std;

tankdrive::tankdrive(pros::MotorGroup *motorDer, pros::MotorGroup *motorIzq,
					pros::Controller *mi_control){
                        this->dermotor = motorDer;
                        this->izqmotor= motorIzq;
                        this->control = mi_control;
                    }

void tankdrive::mando(){
    pros::Task maneja{[this]{
        while (true)
        {
            float left = this->control->get_analog(ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
            float right = this->control->get_analog(ANALOG_RIGHT_Y);  
            if (abs(left)<3 && abs(right)< 3)
            {
                this ->dermotor->move_voltage(0);
                this ->izqmotor->move_voltage(0);

                

            }else{

                this->dermotor->move_voltage(adaptedR());
                this->izqmotor->move_voltage(adaptedL());

            }
            pros::delay(15);
        
        }
        
    }
};
}
float tankdrive::adaptedR(){
        static int cambio = 0;

        float right = this->control->get_analog(ANALOG_RIGHT_Y);  
        //bool on = this->control->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1);
        //bool off = this->control->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1);
        float escalarR = (right/127);
        if(this->control->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1) && cambio < 3){
            cambio += 1;
        }
        else if(this->control->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1) && cambio>0){
            cambio -=1;
        }
        this->rightVolt = ((right*12000)/127)*abs(pow(escalarR, abs(cambio)));
        return this->rightVolt;
        

        
    }
float tankdrive::adaptedL(){
        static int cambio = 0;

        float left = this->control->get_analog(ANALOG_LEFT_Y);  
        //bool on = this->control->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1);
        //bool off = this->control->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1);
        float escalarL = (left/127);
        if(this->control->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1) && cambio < 3){
            cambio += 1;
        }
        else if(this->control->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1) && cambio>0){
            cambio -=1;
        }
        this->leftVolt = ((left*12000)/127)*abs(pow(escalarL, abs(cambio)));
        return this->leftVolt;
        

        
    }

