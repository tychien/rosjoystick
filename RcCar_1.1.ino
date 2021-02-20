#include <ros.h>
#include <std_msgs/Empty.h>
#include <sensor_msgs/Joy.h>

// L: in1 in2 , in1<in2 = counterclockwise  = forward 
// R: in3 in4 , in3>in4 = clockwise         = forward

#define in1 4
#define in2 5
#define in3 6 
#define in4 7
#define enA 9
#define enB 10


void forward()  { digitalWrite(in1,LOW);  digitalWrite(in2,HIGH); digitalWrite(in3,HIGH); digitalWrite(in4,LOW);  }
void backward() { digitalWrite(in1,HIGH); digitalWrite(in2,LOW);  digitalWrite(in3,LOW);  digitalWrite(in4,HIGH); }
void turnLeft() { digitalWrite(in1,LOW);  digitalWrite(in2,LOW);  digitalWrite(in3,HIGH); digitalWrite(in4,LOW);  }
void turnRight(){ digitalWrite(in1,LOW);  digitalWrite(in2,HIGH); digitalWrite(in3,LOW);  digitalWrite(in4,LOW);  }
void circle()   { digitalWrite(in1,HIGH); digitalWrite(in2,LOW);  digitalWrite(in3,LOW);  digitalWrite(in4,HIGH); }
void vstop()    { digitalWrite(in1,LOW);  digitalWrite(in2,LOW);  digitalWrite(in3,LOW);  digitalWrite(in4,LOW);  }

int motorSpeedA = 0;
int motorSpeedB = 0;

void callbackFn( const sensor_msgs::Joy& joy_msg){

  //joy_msg.axes[1] for Forward Backward from  1 to -1 
  //joy_msg.axes[0] for Left    Right    from  1 to -1
  int xAxis = (joy_msg.axes[3] +1)*512;
  int yAxis = (joy_msg.axes[4] +1)*512;

  //------------------------------------------------
  // Go Forward and Backward
  
  if(yAxis<470){
    backward();
    motorSpeedA = map(yAxis, 470, 0, 0, 255);
    motorSpeedB = map(yAxis, 470, 0, 0, 255);
  }else if(yAxis>550){
    forward();
    motorSpeedA = map(yAxis, 550, 1024, 0, 255);
    motorSpeedB = map(yAxis, 550, 1024, 0, 255);
  }else{
    motorSpeedA = 0;
    motorSpeedB = 0;
  }

  //-------------------------------------------------
  // Turn Left and Right
  
  if(xAxis <470){//turn right, A>B
    int xMapped = map(xAxis, 470, 0, 0, 255);
    motorSpeedA = motorSpeedA + xMapped;
    motorSpeedB = motorSpeedB - xMapped;
    if(motorSpeedB < 0){
      motorSpeedB = 0;
    }
    if(motorSpeedA > 255){
      motorSpeedA = 255;
    }
  }
  
  if(xAxis> 550){//turn left, B>A
    int xMapped = map(xAxis, 550, 1024, 0, 255);
    motorSpeedA = motorSpeedA - xMapped;
    motorSpeedB = motorSpeedB + xMapped;
    if(motorSpeedB > 255){
      motorSpeedB = 255;
    }
    if(motorSpeedA < 0){
      motorSpeedA = 0;
    }
  }

  //---------------------------------------------------

  if(motorSpeedA < 30){
    motorSpeedA = 0;
  }
  if(motorSpeedB < 30){
    motorSpeedB = 0;
  }
  analogWrite(9, motorSpeedA);
  analogWrite(10,motorSpeedB);
  
  Serial.print("  motorSpeedA = ");
  Serial.print(motorSpeedA);
  Serial.print("  motorSpeedB = ");
  Serial.println(motorSpeedB);
}

//------------------------------------------------------
//  ros::NodeHandle

ros::NodeHandle nh;

//------------------------------------------------------
//  ros::Subscriber

ros::Subscriber<sensor_msgs::Joy> joy("joy", &callbackFn );


void setup()
{
  Serial.begin(57600);
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);// enA
  pinMode(enB, OUTPUT);// enB
  nh.initNode();

}

void loop()
{
  nh.subscribe(joy);
  nh.spinOnce();
  delay(1);
}
