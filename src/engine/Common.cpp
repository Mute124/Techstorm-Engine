#include "Common.h"
#include <iostream>
#ifdef TS_ENABLE_HAPTICS
#ifdef WIN32

#include <windows.h>
#include <Xinput.h>
// Link the XInput library
#pragma comment(lib, "Xinput.lib")

#else 
// TODO : Linux support
#endif
#endif


#ifdef TS_ENABLE_HAPTICS

void Techstorm::InitHaptics()
{

}

void Techstorm::SetControllerRumble(int controllerIndex, int leftMotorSpeed, int rightMotorSpeed)
{
#ifdef WIN32
    XINPUT_VIBRATION vibration = {};
    vibration.wLeftMotorSpeed = leftMotorSpeed;  // Speed for left motor (0-65535)
    vibration.wRightMotorSpeed = rightMotorSpeed; // Speed for right motor (0-65535)
    XInputSetState(controllerIndex, &vibration);
#endif
}

void Techstorm::StartRumblingController(int controllerIndex, int leftMotorSpeed, int rightMotorSpeed)
{
    SetControllerRumble(controllerIndex, leftMotorSpeed, rightMotorSpeed);
}

void Techstorm::StopRumblingController(int controllerIndex)
{
    SetControllerRumble(controllerIndex, 0, 0);
}

#endif