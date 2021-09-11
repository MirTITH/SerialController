// main.cpp : Defines the entry point for the console application.  
//  

//#include "stdafx.h"  
#include "SerialPort.h"  
#include <iostream>  
#include <sstream>
#include "conio.h"
#include "keyboard.h"

using namespace std;

stringstream SerialBuff;

CSerialPort mySerialPort;

KeyInputSpeed inputSpeed;
KeyInputTurnRatio inputTurnRatio;
KeyInputEmergency inputEmergency;

const double deltaTurnRatio = 0.02;
const double deltaSpeed = 1;

void SendSpeed(double _speed, double _turnRatio)
{
    string setSpeed = "s=";
    setSpeed += to_string(_speed);
    setSpeed += "\n";

    string setTurnRatio = "r=";
    setTurnRatio += to_string(_turnRatio);
    setTurnRatio += "\n";

    cout << setSpeed.data() << setTurnRatio.data() << endl;
    
    mySerialPort.WriteData(setSpeed.data(), setSpeed.length());
    mySerialPort.WriteData(setTurnRatio.data(), setTurnRatio.length());
}

int main(int argc, char* argv[])
{
    if (!mySerialPort.InitPort(3, CBR_115200))
    {
        std::cout << "initPort fail !" << std::endl;
        getchar();
    }
    else
    {
        std::cout << "initPort success !" << std::endl;
    }

    if (!mySerialPort.OpenListenThread())
    {
        std::cout << "OpenListenThread fail !" << std::endl;
        getchar();
    }
    else
    {
        std::cout << "OpenListenThread success !" << std::endl;
    }

    string powerOff = "s\n";

    double speed = 0;
    double turnRatio = 0;

    do
    {
        Sleep(100);

        inputSpeed.Update();
        inputTurnRatio.Update();
        inputEmergency.Update();

        // 速度控制
        switch (inputSpeed.GetDir())
        {
        case Direct::up:
            speed += deltaSpeed;
            cout << "up" << endl;
            //SendSpeed(speed, turnRatio);
            break;
        case Direct::down:
            speed -= deltaSpeed;
            cout << "down" << endl;
            //SendSpeed(speed, turnRatio);
            break;
        case Direct::unassign:
            if (speed > deltaSpeed / 2)
            {
                speed -= deltaSpeed / 2;
            }
            else if (speed < -deltaSpeed / 2)
            {
                speed += deltaSpeed / 2;
            }
            else
            {
                speed = 0;
            }

            break;
        default:
            cout << "inputSpeed default" << endl;
            break;
        }

        
        // 转向控制
        switch (inputTurnRatio.GetDir())
        {
        case Direct::left:
            cout << "left" << endl;
            if (turnRatio < 0) turnRatio = 0;
            turnRatio += deltaTurnRatio;
            break;
        case Direct::right:
            cout << "right" << endl;
            if (turnRatio > 0) turnRatio = 0;
            turnRatio -= deltaTurnRatio;
            break;
        case Direct::unassign:
            if (turnRatio > 4 * deltaTurnRatio)
            {
                turnRatio -= 4 * deltaTurnRatio;
            }
            else if (turnRatio < -4 * deltaTurnRatio)
            {
                turnRatio += 4 * deltaTurnRatio;
            }
            else
            {
                turnRatio = 0;
            }

            break;
        default:
            cout << "inputTurnRatio default" << endl;
            break;
        }

        // 紧急控制
        switch (inputEmergency.GetDir())
        {
        case Direct::brake:
            cout << "brake" << endl;
            speed = 0;
            turnRatio = 0;
            SendSpeed(0, 0);
            break;
        case Direct::stop:
            cout << "stop" << endl;
            mySerialPort.WriteData(powerOff.data(), powerOff.length());
            break;
        case Direct::unassign:
            if (turnRatio > 1) turnRatio = 1;
            if (turnRatio < -1) turnRatio = -1;
            cout << "s " << speed << "\tr " << turnRatio << endl;
            SendSpeed(speed, turnRatio);
            break;
        default:
            cout << "inputEmergency default" << endl;
            break;
        }

    } while (1);
    
    return 0;
}
