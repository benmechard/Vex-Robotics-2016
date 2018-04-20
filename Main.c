#pragma config(Sensor, dgtl9,  			       pneumatics, sensorDigitalOut)
#pragma config(Motor,  port2,           FrontLeft,           tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           FrontRight,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           BackLeft,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           BackRight,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           LowerLift1,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           LowerLift2,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           UpperLift1,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           UpperLift2,          tmotorVex393_MC29, openLoop)

//programmer definitions
#define X vexRT[Ch4]
#define Y vexRT[Ch3]
#define Z vexRT[Ch1]

#define Y2 vexRT[Ch3Xmtr2]
#define Z2 vexRT[Ch2Xmtr2]

#define liftFixL1 vexRT[Btn6UXmtr2]
#define liftFixL2 vexRT[Btn6DXmtr2]
#define liftFixU1 vexRT[Btn5UXmtr2]
#define liftFixU2 vexRT[Btn5DXmtr2]

#define pneumaticsButton vexRT[Btn8UXmtr2]

//pre-defined variables
int threshold = 15;
int liftSpeed = 50;
int timer = 0;

//base mechanim movement
task base(){
	motor[FrontRight] = Y + Z - X;
	motor[BackRight] =  Y + Z + X;
	motor[FrontLeft] = Y - Z + X;
	motor[BackLeft] =  Y - Z - X;
}

//lift movement
task lift(){
	if (Y2 > threshold){
		motor[UpperLift1] = liftSpeed;
		motor[UpperLift2] = liftSpeed;
	}
	else if (Z2 > threshold){
		motor[LowerLift1] = liftSpeed*2;
		motor[LowerLift2] = liftSpeed*2;
	}
	else if(Y2 < -threshold){
		motor[UpperLift1] = -liftSpeed;
		motor[UpperLift2] = -liftSpeed;
	}
	else if(Z2 < -threshold){
		motor[LowerLift1] = -liftSpeed*2;
		motor[LowerLift2] = -liftSpeed*2;
	}
	else if(Z2 < threshold & Z2 > -threshold & Y2 < threshold & Y2 > -threshold){
		motor[UpperLift1] = 0;
		motor[UpperLift2] = 0;
		motor[LowerLift1] = 0;
		motor[LowerLift2] = 0;
	}
	//to correct and missaligned lifts individually
	if(liftFixL1){ 
		motor[LowerLift1] = -liftSpeed;
	}
	if(liftFixL2){
		motor[LowerLift2] = -liftSpeed;
	}
	if(liftFixU1){
		motor[UpperLift1] = -liftSpeed;
	}
	if(liftFixU2){
		motor[UpperLift2] = -liftSpeed;
	}
}

//claw controls
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
2016
*/
