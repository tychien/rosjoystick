# rosjoystick
something about rosarduino car and rosjoystick

# Studying Journal

## Feb 15 2020  
  1. make: warning: Clock skew detected. Your build may be incomplete. ->  
  ```bash 
  sudo apt install ntp
  touch *
  ```
  then it'll do the trick. 

  2. Cannot CMake -> just take a look at this tutorial: "http://wiki.ros.org/ROS/Tutorials/BuildingPackages" 
  3. Wrote JoyListener "https://github.com/tychien/rosjoystick/blob/main/joylistener.cpp".   
     great ref found :"https://github.com/iscumd/isc_joy/blob/master/src/joystick.cpp"
  
  Next step : transmmit the messages from joystick via rosmaster to arduino!!
  ref: "http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup"
