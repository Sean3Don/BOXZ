/*
BOXZ.h - Library for general robot control.
Created by Leo.Zhu, 21 July, 2013.
https://github.com/leolite/BOXZ

Wiki Chinese:
http://wiki.geek-workshop.com/doku.php?id=arduino:libraries:boxz

License: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
http://creativecommons.org/licenses/by-nc-sa/3.0/

Include following library
  Servo.h - Interrupt driven Servo library for Arduino using 16 bit timers- Version 2
  Copyright (c) 2009 Michael Margolis.  All right reserved.
*/

/*  Modified record:
	Updata: 20130816
	1. goRaw() renamed with motorRaw()
	2. goRaws() renamed with motorRaws()
	3. init() renamed with initMotor()
	
	Updata: 20130814
	1. add servoRaw()
	2. add servoRaws()
	3. Update servoCom()(Both servo action) and motorCom()(add Key Q and E)
	4. Update goRaw() and go Raws()
	
	Updata: 20130812
	1. add Servo function(SEEED drive board not support Servo, because of disable PWM of Pin 9 and 10)
	2. add servoCom()
	3. Update motorCom() (servo could action when motor is running)
	
	Updata: 20130810
	1. Support for Adafruit Motor Drive(not support RAW)
	2. add checkIO_AF()
	3. add initAFMotor()
	
	Updata: 20130809
	1. add motorCom()
	
	Update: 20130730
	1. add goRaws() for control by raw data(String HEX).
	
	Update: 20130729
	1. add goRaw() for control by raw data(Long int HEX).
	
	Update: 20130728
	1. add checkIO_ED() and checkIO_DF() for checking board type
	2. add init() for Automatic choose board type.
*/

#ifndef __BOXZ_H__
#define __BOXZ_H__

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <Servo.h> 


#define DEBUG			1
#define PREACCELERATION	1  //not ready yet
#define DEFAULT_SPEED	255

/******Pins definitions for DFROBOT L298N and A3906*************/
//_driverMode = 4
//2 control pin and 2 speed pin
#define DF_INA			4
#define DF_INB			7
#define DF_SPEEDA		5
#define DF_SPEEDB		6

/******Pins definitions for SEEED L298N and TB6612FNG*************/
//_driverMode = 6
//4 control pin and 2 speed pin
#define SD_IN1			8
#define SD_IN2			11
#define SD_IN3			12
#define SD_IN4			13
#define SD_SPEEDA		9
#define SD_SPEEDB		10

/******Pins definitions for Adafruit Motor shield*************/
//default active M1 and M2(AF_GROUP = 1); if want to choose M3 and M4, set AF_GROUP = 2
#define AF_GROUP 		1
//_driverMode = 8
//4 control pin and 4 speed pin, with 2 servo(PWM1A and PWM1B)
#define AF_DIR_LATCH	12
#define AF_DIR_CLK		4
#define AF_DIR_EN		7
#define AF_DIR_SER		8
#define AF_PWM0A 		6
#define AF_PWM0B 		5
#define AF_PWM1A 		9
#define AF_PWM1B 		10
#define AF_PWM2A 		11
#define AF_PWM2B 		3
//status for Adafruit Motor Driver 74HC595 data
#define AFM1F 		32;
#define AFM1B 		16;
#define AFM2F 		64;
#define AFM2B 		8;
#define AFM3F 		128;
#define AFM3B 		2;
#define AFM4F 		1;
#define AFM4B 		4;

/*------------------------------------------------------------------
 define servo
 D9  Left hand(servo 01)
 D10 Right hand(servo 02)
 ------------------------------------------------------------------*/
#define SERVO_PIN01			9;
#define SERVO_PIN02			10;
#define SERVO_POS01 		20; // middle position
#define SERVO_POS02 		20; // middle position
#define SERVO_POSMIN 		20; // min position is 0
#define SERVO_POSMAX 		160; // max position is 180
#define SERVO_DELAY 		1;  //[modifid]delay speed of hand
#define SERVO_FRAME 		20;  //[modifid]

/**Class for motor control**/
class BOXZ
{
public:
	//motor control
	boolean initMotor();  //Automatic check board
	boolean initMotor(int type);
	void initMotor(int inA, int inB, int pwmA, int pwmB);
	void initMotor(int in1, int in2, int in3, int in4, int pwmA, int pwmB);
	void initAFMotor(); //initialization for Adafruit Motor Driver
	void goForward(int speedA, int speedB);
	void goBackward(int speedA, int speedB);
	void goLeft(int speedA, int speedB);
	void goRight(int speedA, int speedB);
	void goForward();
	void goBackward();
	void goLeft();
	void goRight();
	void stop();
	void motorCom(int keyword); //Support for BOXZ Base
	void motorCom(int keyword, int speedA, int speedB); //Support for BOXZ Base with speed control
    void motorRaw(unsigned long data);
	void motorRaws(String datas);

	//servo control
	Servo servo01;  // create servo object to control a servo 
	Servo servo02;  // create servo object to control a servo

	void initServo();
	void initServo(int pin01,int pin02);
	void initServo(int pin01,int pin02, int posMin, int posMax);
	void servo01Up();
	void servo02Up();
	void servo01Down();
	void servo02Down();
	void servo01Up(int type);
	void servo02Up(int type);
	void servo01Down(int type);
	void servo02Down(int type);
	void servoCom(int keyword); //Support for BOXZ Pro
	void servoRaw(unsigned long data);
	void servoRaws(String datas);
	

		
private:
	//Motor
	boolean checkIO_ED(); //IO check for Seeed
	boolean checkIO_DF(); //IO check for DFROBOT
	boolean checkIO_AF(); //IO check for Adafruit
	//Pin define
	int _inA;
	int _inB;
	int _in1; 
	int _in2; 
	int _in3; 
	int _in4; 
	int _pwmA; 
	int _pwmB;
	int _driverMode;
	//Output value
	int _in1Status;
	int _in2Status;
	int _in3Status;
	int _in4Status;
	int _AFMstatus; //status for Adafruit Motor Driver 74HC595 data
	int _speedA;
	int _speedB;
	
	//servo
	int _servoPosMax;
	int _servoPosMin;
	int _servoPos01;
	int _servoPos02;
	int _servoTar01; //Target Positon
	int _servoTar02; //Target Positon
	int _servoAct01; //actived
	int _servoAct02; //actived
	int _servoDis01; //Distance
	int _servoDis02; //Distance
	int _servoFra01; //Frame Distance
	int _servoFra02; //Frame Distance
	int _servoDelay;
	int _servoFrame;
};

extern BOXZ boxz;
#endif
