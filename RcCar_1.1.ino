#include <ros.h>
#include <std_msgs/Empty.h>
#include <sensor_msgs/Joy.h>

ros::NodeHandle nh;
void forward() { digitalWrite(4,LOW); digitalWrite(5,HIGH); digitalWrite(6,HIGH); digitalWrite(7,LOW);}
void backward() { digitalWrite(4,HIGH); digitalWrite(5,LOW); digitalWrite(6,LOW); digitalWrite(7,HIGH);}
void turnLeft() { digitalWrite(4,LOW); digitalWrite(5,LOW); digitalWrite(6,HIGH); digitalWrite(7,LOW);}
void turnRight() { digitalWrite(4,LOW); digitalWrite(5,HIGH); digitalWrite(6,LOW); digitalWrite(7,LOW);}
void circle() { digitalWrite(4,HIGH); digitalWrite(5,LOW); digitalWrite(6,LOW); digitalWrite(7,HIGH);}
void vstop() { digitalWrite(4,LOW); digitalWrite(5,LOW); digitalWrite(6,LOW); digitalWrite(7,LOW);}

int motorSpeedA = 0;
int motorSpeedB = 0;

void callbackFn( const sensor_msgs::Joy& joy_msg){

  //joy_msg.axes[1] for Forward Backward from  1 to -1 
  //joy_msg.axes[0] for Left    Right    from  1 to -1
  int xAxis = (joy_msg.axes[3] +1)*512;
  int yAxis = (joy_msg.axes[4] +1)*512;
  if(yAxis<470){
    backward();
    motorSpeedA = map(yAxis, 470, 0, 0, 255);
    motorSpeedB = map(yAxis, 470, 0, 0, 255);
  }
  else if(yAxis>550){
    forward();
    motorSpeedA = map(yAxis, 550, 1024, 0, 255);
    motorSpeedB = map(yAxis, 550, 1024, 0, 255);
  }
  else{
    motorSpeedA = 0;
    motorSpeedB = 0;
  }


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

ros::Subscriber<sensor_msgs::Joy> joy("joy", &callbackFn );


void setup()
{
  Serial.begin(57600);
  pinMode(4, OUTPUT); 
  pinMode(5, OUTPUT); 
  pinMode(6, OUTPUT); 
  pinMode(7, OUTPUT);
  pinMode(9, OUTPUT);// enA
  pinMode(10,OUTPUT);// enB
  nh.initNode();

}

void loop()
{
  nh.subscribe(joy);
  nh.spinOnce();
  delay(1);
}
