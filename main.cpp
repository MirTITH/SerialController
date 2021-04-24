// main.cpp : Defines the entry point for the console application.  
//  

//#include "stdafx.h"  
#include "SerialPort.h"  
#include <iostream>  
#include <sstream>
#include "conio.h"

using namespace std;

stringstream SerialBuff;

int main(int argc, char* argv[])
{

    CSerialPort mySerialPort;

    if (!mySerialPort.InitPort(7, CBR_115200))
    {
        std::cout << "initPort fail !" << std::endl;
    }
    else
    {
        std::cout << "initPort success !" << std::endl;
    }

    //if (!mySerialPort.OpenListenThread())
    //{
    //    std::cout << "OpenListenThread fail !" << std::endl;
    //}
    //else
    //{
    //    std::cout << "OpenListenThread success !" << std::endl;
    //}

    string goForward = "s=90\n";
    string goForward1 = "s=50\n";
    string goBackward = "s=-50\n";
    string turnLeft = "tl=20\n";
    string turnRight = "tl=-20\n";
    string goStraight = "tl=0\n";
    string carStop = "s=0\n";
    string SharpTurnRight = "tl=-27\n";
    string SharpTurnLeft = "tl=27\n";
    string powerOff = "\'\n";
    string powerOn = "$\n";

    // bool isGoForward = true;
    //std::cin >> temp;

    //mySerialPort.WriteData(temp, 20);

    do
    {
        Sleep(10);
        //cout << SerialBuff.str();
        //SerialBuff.str("");
        if (_kbhit())
        {
            switch (_getch())
            {
            case 'w':
                //cout << "w" << endl;
                mySerialPort.WriteData(goForward.data(), goForward.length());
                Sleep(50);
                mySerialPort.WriteData(goStraight.data(), goStraight.length());
                break;
            case 's':
                //cout << "s" << endl;
                mySerialPort.WriteData(goBackward.data(), goBackward.length());
                Sleep(50);
                mySerialPort.WriteData(goStraight.data(), goStraight.length());
                break;
            case 'a':
                //cout << "a" << endl;
                mySerialPort.WriteData(turnLeft.data(), turnLeft.length());
                break;
            case 'd':
                //cout << "d" << endl;
                mySerialPort.WriteData(turnRight.data(), turnRight.length());
                break;
            case 'e':
                //mySerialPort.WriteData(goForward1.data(), goForward1.length());
                mySerialPort.WriteData(SharpTurnRight.data(), SharpTurnRight.length());
                break;
            case 'q':
                //mySerialPort.WriteData(goForward1.data(), goForward1.length());
                mySerialPort.WriteData(SharpTurnLeft.data(), SharpTurnLeft.length());
                break;
            case '\'':
                mySerialPort.WriteData(powerOff.data(), powerOff.length());
                break;
            case '\\':
                mySerialPort.WriteData(powerOn.data(), powerOn.length());
                break;
            case ' ':
                //cout << "break" << endl;
                mySerialPort.WriteData(carStop.data(), carStop.length());
                break;
            default:
                break;
            } 
        }
        //else
        //{
        //    //cout << "go straight" << endl;
        //    mySerialPort.WriteData(goStraight, 20);
        //}
        
    } while (1);
    
    return 0;
}
