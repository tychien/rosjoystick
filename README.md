# rosjoystick
something about rosarduino car and rosjoystick

# Studying Journal

## Feb 15 2021  
  1. make: warning: Clock skew detected. Your build may be incomplete. ->  `sudo apt install ntp; touch *`
  then it'll do the trick. 
  1. Cannot CMake -> just take a look at this tutorial: "http://wiki.ros.org/ROS/Tutorials/BuildingPackages" 
  1. Wrote JoyListener "https://github.com/tychien/rosjoystick/blob/main/joylistener.cpp".   
     great ref found :"https://github.com/iscumd/isc_joy/blob/master/src/joystick.cpp"
  1. Subscriber to Joy topic in ROS "https://stackoverflow.com/questions/62799181/subscriber-to-joy-topic-in-ros"
  
  
  Next step : transmmit the messages from joystick via rosmaster to arduino!!
  ref: "http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup"
  cool things about joysticks code : "https://github.com/iscumd/isc_joy/blob/master/src/joystick.cpp#L33"

## Feb 16 2021
  1. To install a new .tar.gz file, `tar -xzf archive-name.tar.gz; cd archive-name; ./configure; make; sudo make install`
  1. CMake error `CMake 3.7.2 or higher is required.  You are running version 3.5.1` The version is too old for compiling the "rosserial" -> follow those steps would help:"https://askubuntu.com/questions/829310/how-to-upgrade-cmake-in-ubuntu"
  1. `#error This file requires compiler and library support for the ISO C++ 2011 standard. This support must be enabled with the -std=c++11 or -std=gnu++11 compiler options.` -> add this line in CMakelist.txt `SET( CMAKE_CXX_FLAGS "-std=c++11 -O3")`
  1. Finished Installing Arduino IDE on board. 
  1. Next : Hello World for rosserial_arduino: "http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup"
  1. What is typedef & define in C++
  1. Video about rosserial_arduino "https://www.youtube.com/watch?v=MOBSb6cA7kY"
  
