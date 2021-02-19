#include <ros.h>
#include <std_msgs/Empty.h>
#include <sensor_msgs/Joy.h>

ros::NodeHandle nh;
void forward() { digitalWrite(6,LOW); digitalWrite(7,HIGH); digitalWrite(8,HIGH); digitalWrite(9,LOW);}
void backward() { digitalWrite(6,HIGH); digitalWrite(7,LOW); digitalWrite(8,LOW); digitalWrite(9,HIGH);}
void turnLeft() { digitalWrite(6,LOW); digitalWrite(7,LOW); digitalWrite(8,HIGH); digitalWrite(9,LOW);}
void turnRight() { digitalWrite(6,LOW); digitalWrite(7,HIGH); digitalWrite(8,LOW); digitalWrite(9,LOW);}
void circle() { digitalWrite(6,HIGH); digitalWrite(7,LOW); digitalWrite(8,LOW); digitalWrite(9,HIGH);}
void vstop() { digitalWrite(6,LOW); digitalWrite(7,LOW); digitalWrite(8,LOW); digitalWrite(9,LOW);}

/*
void messageCb( const std_msgs::Empty& toggle_msg){
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
}
*/
void callbackFn( const sensor_msgs::Joy& joy_msg){
  
  //stop
  int movement=0;
  
  if((joy_msg.axes[1]==0)&&(joy_msg.axes[0]==0)){
    movement=0;//stop
  }
  else if(joy_msg.axes[1]>0.5){
    movement=1;//forward
  }
  else if(joy_msg.axes[1]<-0.5){
    movement=2;//backward
  }
  else if(joy_msg.axes[0]>0.5){
    movement=3;//turnleft
  }
  else if(joy_msg.axes[0]<-0.5){
    movement=4;//turnright
  }
  else{
    movement=0;
  }
  
  switch(movement){
    case 1:
      forward();
      delay(1);
      break;
    case 2:
      backward();
      delay(1);
      break;
    case 3:
      turnLeft();
      delay(1);
      break;
    case 4:
      turnRight();
      delay(1);
      break;
    case 0:
      vstop();
      delay(1);
      break;
    default:
      vstop();
      delay(1);
      break;
  }
  
  /*
  if(joy_msg.buttons[1]==1){
    digitalWrite(13, HIGH);
  }
  else{
    digitalWrite(13, LOW);
  }
  */
}

//ros::Subscriber<std_msgs::Empty> sub("toggle_led", &messageCb );
ros::Subscriber<sensor_msgs::Joy> joy("joy", &callbackFn );


void setup()
{
  pinMode(13, OUTPUT);
  pinMode(6, OUTPUT); 
  pinMode(7, OUTPUT); 
  pinMode(8, OUTPUT); 
  pinMode(9, OUTPUT);
  nh.initNode();
  //nh.subscribe(sub);
  //nh.subscribe(joy);
}

void loop()
{
  //nh.initNode();
  nh.subscribe(joy);
  nh.spinOnce();
  delay(1);
}
