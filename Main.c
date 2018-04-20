#pragma config(Sensor, dgtl9,  					pneumatics,    sensorDigitalOut)
#pragma config(Motor,  port2,           FL,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           FR,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           BL,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           BR,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           LLL1,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           LLL2,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           ULL1,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           ULL2,          tmotorVex393_MC29, openLoop)

//programmer definitions
#define X vexRT[Ch4]
#define Y vexRT[Ch3]
#define Z vexRT[Ch2]
#define ZZ vexRT[Ch1]

#define X2 vexRT[Ch4Xmtr2]
#define Y2 vexRT[Ch3Xmtr2]
#define Z2 vexRT[Ch2Xmtr2]
#define ZZ2 vexRT[Ch1Xmtr2]

#define liftFixL1 vexRT[Btn6UXmtr2]
#define liftFixL2 vexRT[Btn6DXmtr2]
#define liftFixU1 vexRT[Btn5UXmtr2]
#define liftFixU2 vexRT[Btn5DXmtr2]

#define pneumaticsButton vexRT[Btn8UXmtr2]

//pre-defined variables
int thresh = 15;
int liftSpeed = 50;
int timer = 0;

//base mechanim movement
task base(){
	motor[FR] = Y + ZZ - X;
	motor[BR] =  Y + ZZ + X;
	motor[FL] = Y - ZZ + X;
	motor[BL] =  Y - ZZ - X;
}

//lift/lower lift
task lift(){
	if (Y2 > thresh){
		motor[ULL1] = liftSpeed;
		motor[ULL2] = liftSpeed;
	}
	else if (Z2 > thresh){
		motor[LLL1] = liftSpeed*2;
		motor[LLL2] = liftSpeed*2;
	}
	else if(Y2 < -thresh){
		motor[ULL1] = -liftSpeed;
		motor[ULL2] = -liftSpeed;
	}
	else if(Z2 < -thresh){
		motor[LLL1] = -liftSpeed*2;
		motor[LLL2] = -liftSpeed*2;
	}
	else if(Z2 < thresh & Z2 > -thresh & Y2 < thresh & Y2 > -thresh){
		motor[ULL1] = 0;
		motor[ULL2] = 0;
		motor[LLL1] = 0;
		motor[LLL2] = 0;
	}
	if(liftFixL1){
		motor[LLL1] = -liftSpeed;
	}
	if(liftFixL2){
		motor[LLL2] = -liftSpeed;
	}
	if(liftFixU1){
		motor[ULL1] = -liftSpeed;
	}
	if(liftFixU2){
		motor[ULL2] = -liftSpeed;
	}
}

//open/close claw
task claw(){
	if(pneumaticsButton & timer > 1000){
		timer = 0;
		if(SensorValue[pneumatics] == 1){
			SensorValue[pneumatics] = 0;
		}
		else if(SensorValue[pneumatics] == 0){
			SensorValue[pneumatics] = 1;
		}
	}
}

//main loop
task main(){
	while(1==1){
		startTask(base);
		startTask(lift);
		startTask(claw);
		delay(1);
		timer += 1;
	}
}

/*
Vex Robotics Competition Code
Written By Ben Echard
In 2016
*/
