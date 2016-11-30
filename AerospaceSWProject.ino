
#include <PID_v1.h>

#include <SharpIR.h>

//#include <NewPing.h>

//#include <Servo.h>

//#include <Wire.h>



#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle  nh;

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);


//char hello[13] = "hello world!";
char hello[10];
char hello2[10];
char hello4[2] = ",";
char hello3[30];


//IR sesonr connection diagram

#define frontIr A4 //RX from front IR seonsor 

#define rightIr A5 //RX from right IR sensor

#define backIr A6 //RX from back IR sensor

#define leftIr A3 //RX from left IR sensor

#define model 20150 //IR sensor model number



//IR sensor and Maxsonar sensor variable declaration

double Setpoint, altSetpoint;

double frontIrInput, frontIrOutput;

double rightIrInput, rightIrOutput;

double backIrInput, backIrOutput;

double leftIrInput, leftIrOutput;

double altSonarInput, altSonarOutput,lastSonarInput;

double Kp = 2.9; //Kp variable must declare before IR sensor object declaration

double Ki = 0; //Ki variable must declare before IR sensor object declaration

double Kd = 0; //Kd variable must declare before IR sensor object declaration


//IR sensor and MaxSonar object declaration

SharpIR fIr(frontIr, 25, 70, model); //acquire 25 samples only 70% corrosiveness

SharpIR rIr(rightIr, 25, 70, model); //acquire 25 samples only 70% corrosiveness

SharpIR bIr(backIr, 25, 70, model); //acquire 25 samples only 70% corrosiveness

SharpIR lIr(leftIr, 25, 70, model); //acquire 25 samples only 70% corrosiveness



//IR sensor and MaxSonar PID object declaration

PID frontPID(&frontIrInput, &frontIrOutput, &Setpoint, Kp, Ki, Kd, DIRECT);

PID rightPID(&rightIrInput, &rightIrOutput, &Setpoint, Kp, Ki, Kd, DIRECT);

PID leftPID(&leftIrInput, &leftIrOutput, &Setpoint, Kp, Ki, Kd, DIRECT);

PID backPID(&backIrInput, &backIrOutput, &Setpoint, Kp, Ki, Kd, DIRECT);





void setup()

{





    Serial.begin(57600);



    //Setpoint setting

  Setpoint = 50;

  

  //SetOutputLimits setting

  frontPID.SetOutputLimits(30,100);

  rightPID.SetOutputLimits(30,100);

  backPID.SetOutputLimits(30,100);

  leftPID.SetOutputLimits(30,100);



  //SetMode setting

  frontPID.SetMode(AUTOMATIC);

  rightPID.SetMode(AUTOMATIC);

  backPID.SetMode(AUTOMATIC);

  leftPID.SetMode(AUTOMATIC);


   nh.initNode();
  nh.advertise(chatter);

}



void loop()

{



    

  static uint16_t unAleoIn;

  static uint16_t unEleoIn;

  

      Setpoint = 30;

  

      frontIrInput = fIr.cm();

      backIrInput = bIr.cm(); 

      rightIrInput = rIr.cm();

      leftIrInput = lIr.cm();

        

      frontPID.Compute();

      backPID.Compute();

      leftPID.Compute();

      rightPID.Compute();





//      Serial.println(rightIrOutput);



      

//      Serial.print("FRONTInput : ");

//      Serial.println(frontIrInput);

//      Serial.print("    backInput : ");

//      Serial.println(backIrInput);



//      Serial.print("front IR output : ");

//      Serial.println(frontIrOutput);

//      Serial.print("back IR output : ");

//      Serial.println(backIrOutput);

//





       unAleoIn = 1500-leftIrOutput+rightIrOutput;

//       Serial.print("roll : ");
//
//       Serial.print(unAleoIn);
//
//
//
//Serial.print("                            ");
//
//       



       unEleoIn = 1500+frontIrOutput-backIrOutput;

//       Serial.print("pitch : ");
//
//       Serial.println(unEleoIn);
//

//  itoa(unAleoIn, hello, 10);
//  itoa(unEleoIn, hello2, 10);
  
  String a = String(unAleoIn, DEC);
  String b = String(unEleoIn, DEC);
  
  String c = a+","+b;
  
  c.toCharArray(hello3, 30);
  
  str_msg.data = hello3;
  chatter.publish( &str_msg );
  nh.spinOnce();
  delay(1000);


}
