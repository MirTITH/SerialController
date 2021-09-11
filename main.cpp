// main.cpp : Defines the entry point for the console application.  
//  

//#include "stdafx.h"  
#include "SerialPort.h"  
#include <iostream>  
#include "conio.h"
#include "keyboard.h"

using namespace std;

stringstream SerialBuff;

CSerialPort mySerialPort;

KeyInputSpeed inputSpeed;
KeyInputTurnRatio inputTurnRatio;
KeyInputEmergency inputEmergency;

const double deltaTurnRatio = 0.05;
const double deltaSpeed = 3;

const double MAX_turnRatio = 0.2;
const double MAX_speed = 50;

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
    cout << "Please input serial port number." << endl;
    cout << "The default value is " << portNum << endl;
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

    mySerialPort.WriteData("m\n", 2); // �л����ֶ�����

    do
    {
        Sleep(100);

        inputSpeed.Update();
        inputTurnRatio.Update();
        inputEmergency.Update();

        // �ٶȿ���
        switch (inputSpeed.GetDir())
        {
        case Direct::up:
            speed += deltaSpeed;
            //cout << "up" << endl;
            break;
        case Direct::down:
            speed -= deltaSpeed;
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

        
        // ת�����
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

        // ��������
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
            break;
        case Direct::stop:
            cout << "stop" << endl;
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
