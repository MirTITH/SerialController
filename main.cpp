/**
* COPYRIGHT NOTICE 
* Copyright (c) 2021, MirTITH (https://github.com/MirTITH/)
* All rights reserved. 
*   
* @file    main.cpp 
* @brief   Defines the entry point for the console application. 
*   
* @author  谢阳
* @version See const string VERSION
* @email：200320620@stu.hit.edu.cn
* @date    2021/09/12
* #license GNU 2.0
*/ 

//#include "stdafx.h"  
#include "SerialPort.h"  
#include <iostream>  
#include "conio.h"
#include "keyboard.h"

using namespace std;

const string VERSION = "1.0";

stringstream SerialBuff;

CSerialPort mySerialPort;

KeyInputSpeed inputSpeed;
KeyInputTurnRatio inputTurnRatio;
KeyInputEmergency inputEmergency;

const double deltaTurnRatio = 0.07;
const double deltaSpeed = 3;

const double MAX_turnRatio = 0.25;
const double MAX_speed = 40;

void SendSpeed(double _speed, double _turnRatio)
{
    string setTurnRatio = "r ";
    setTurnRatio += to_string(_turnRatio);
    setTurnRatio += "\n";

    string setSpeed = "cs ";
    setSpeed += to_string(_speed);
    setSpeed += "\n";

    //cout << setSpeed.data() << setTurnRatio.data() << endl;
    
    mySerialPort.WriteData(setTurnRatio.data(), setTurnRatio.length());
    mySerialPort.WriteData(setSpeed.data(), setSpeed.length());
}

int main(int argc, char* argv[])
{
    int portNum = 6;
    cout << "Serial Controller \tVer. " << VERSION << endl;
    cout << "Copyright(C) 2021, MirTITH (https://github.com/MirTITH/)" << endl;
    cout << "All rights reserved." << endl;
    cout << endl;
    cout << "Author: 谢阳(Xie Yang)" << endl;
    cout << "E-mail: 200320620@stu.hit.edu.cn" << endl;
    cout << "github: https://github.com/MirTITH/" << endl;
    cout << "gitee: https://gitee.com/tithchan" << endl;
    cout << endl;

    cout << "Manual:" << endl;
    cout << "Use w,s,a,d to run the car." << endl;
    cout << "Use [space] to brake." << endl;
    cout << "Use [shift] to turn off the motor." << endl << endl;
    cout << "Please input serial port number." << endl;
    cout << ">";
    cin >> portNum;
    cout << endl << "Opening COM " << portNum << endl;
    if (!mySerialPort.InitPort(portNum, CBR_115200))
    {
        std::cout << "initPort fail !" << std::endl;
        system("pause");
        return -1;
    }
    else
    {
        std::cout << "initPort success !" << std::endl;
    }

    //if (!mySerialPort.OpenListenThread())
    //{
    //    std::cout << "OpenListenThread fail !" << std::endl;
    //    system("pause");
    //    return -1;
    //}
    //else
    //{
    //    std::cout << "OpenListenThread success !" << std::endl;
    //}

    string powerOff = "s\n";

    double speed = 0;
    double turnRatio = 0;

    mySerialPort.WriteData("m\n", 2); // 切换到手动控制

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
            if (speed >= 0)
            {
                speed += deltaSpeed;
            }
            else
            {
                speed += 2 * deltaSpeed;
            }
            //cout << "up" << endl;
            break;
        case Direct::down:
            if (speed <= 0)
            {
                speed -= deltaSpeed;
            }
            else
            {
                speed -= 2 * deltaSpeed;
            }
            //cout << "down" << endl;
            break;
        case Direct::unassign:
            if (speed > deltaSpeed)
            {
                speed -= deltaSpeed;
            }
            else if (speed < -deltaSpeed)
            {
                speed += deltaSpeed;
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
            //cout << "left" << endl;
            if (turnRatio < 0) turnRatio = 0;
            turnRatio += deltaTurnRatio;
            break;
        case Direct::right:
            //cout << "right" << endl;
            if (turnRatio > 0) turnRatio = 0;
            turnRatio -= deltaTurnRatio;
            break;
        case Direct::unassign:
            if (turnRatio > 3 * deltaTurnRatio)
            {
                turnRatio -= 3 * deltaTurnRatio;
            }
            else if (turnRatio < -3 * deltaTurnRatio)
            {
                turnRatio += 3 * deltaTurnRatio;
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
            if (speed > 7)
            {
                speed -= 6;
            }
            else if (speed < -7)
            {
                speed += 6;
            }
            else
            {
                speed = 0;
            }
            SendSpeed(speed, turnRatio);
            //cout << "stop" << endl;
            //mySerialPort.WriteData(powerOff.data(), powerOff.length());
            break;
        case Direct::stop:
            //cout << "brake" << endl;
            //if (speed > 7)
            //{
            //    speed -= 6;
            //}
            //else if (speed < -7)
            //{
            //    speed += 6;
            //}
            //else
            //{
            //    speed = 0;
            //}
            //SendSpeed(speed, turnRatio);
            cout << "s " << speed << "\tr " << turnRatio;
            cout << "\tstop" << endl;
            mySerialPort.WriteData(powerOff.data(), powerOff.length());
            break;
        case Direct::unassign:
            if (turnRatio > MAX_turnRatio) turnRatio = MAX_turnRatio;
            if (turnRatio < -MAX_turnRatio) turnRatio = -MAX_turnRatio;

            if (speed > MAX_speed) speed = MAX_speed;
            if (speed < -MAX_speed) speed = -MAX_speed;

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
