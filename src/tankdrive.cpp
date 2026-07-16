#include "tankdrive.hpp"
using namespace std;

tankdrive::tankdrive(pros::MotorGroup *motorDer, pros::MotorGroup *motorIzq,
					pros::Controller *mi_control){
                        this->dermotor = motorDer;
                        this->izqmotor= motorIzq;
                        this->control = mi_control;
                    }

void tankdrive::controlar(){
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

                float escalarR = (right/127)*(right/127);
                float escalarL = (left/127)*(left/127);

                this->rightVolt = ((right*12000)/127)*escalarR;
                this->leftVolt = ((left*12000)/127)*escalarL;

                this->dermotor->move_voltage(this->rightVolt);
                this->izqmotor->move_voltage(this->leftVolt);

            }
            pros::delay(15);
        
        }
        
    }
};
}