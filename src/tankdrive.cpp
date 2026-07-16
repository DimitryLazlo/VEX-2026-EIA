#include "tankdrive.hpp"
#include "pros/misc.h"
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

 
                float escalarL = (left/127)*(left/127);

                this->leftVolt = ((left*12000)/127)*escalarL;

                this->dermotor->move_voltage(adaptedR());
                this->izqmotor->move_voltage(adaptedL());

            }
            pros::delay(15);
        
        }
        
    }
};
}
float tankdrive::adaptedR(){
    pros::Task maneja{[this]{
        while (true)
        {
            float right = this->control->get_analog(ANALOG_RIGHT_Y);  
            float on = this->control->get_digital(pros::E_CONTROLLER_DIGITAL_L1);
            float off = this->control->get_digital(pros::E_CONTROLLER_DIGITAL_R1);
            if(on){
                
                float escalarR = (right/127)*(right/127);
                this->rightVolt = ((right*12000)/127)*escalarR;

                return this->rightVolt;
            }else{
                this->rightVolt = ((right*12000)/127);              
            }
        }
        
    }
};
}
float tankdrive::adaptedL(){
    pros::Task maneja{[this]{
        while (true)
        {
            float left = this->control->get_analog(ANALOG_LEFT_Y);  
            float on = this->control->get_digital(pros::E_CONTROLLER_DIGITAL_L1);
            float off = this->control->get_digital(pros::E_CONTROLLER_DIGITAL_R1);
            if(on){
                
                float escalarL = (left/127)*(left/127);
                this->rightVolt = ((left*12000)/127)*escalarL;

                return this->rightVolt;
            }else{
                this->rightVolt = ((left*12000)/127);              
            }
        }
        
    }
};
}

