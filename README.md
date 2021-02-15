# rosjoystick
something about rosarduino car and rosjoystick

ref:"https://www.programmersought.com/article/23474882018/"

using Logitech F710 gamepad

# installing

```bash
sudo apt-get install ros-indigo-joy(ROS related items, Jetson TK1 only installs this one)
sudo apt-get install ros-indigo-joystick-drivers
sudo apt-get install joystick
rosdep install joy
rosmake joy
```

#change user group 

```bash
ls -l /dev/input/js0
sudo chgrp dialout /dev/input/js0
```

you'll get 
```bash
crw-rw-r--+ 1 root dialout 13, 0 10Month 5 09:03 /dev/input/js0
```

plug in the usb receiver then

```bash
sudo jstest /dev/input/js0
```
# Run the controller mode

```bash
roscore
rosrun joy joy_node
rostopic echo joy
```
then you'll get 

```bash
header: 
  seq: 1
  stamp: 
    secs: 1525826012
    nsecs: 692879198
  frame_id: ''
axes: [0.0, -0.0, 0.0, 0.0]
buttons: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
---
header: 
  seq: 2
  stamp: 
    secs: 1525826012
    nsecs: 696846275
  frame_id: ''
axes: [0.0, -0.0, 0.0, 0.0]
buttons: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
---
header: 
  seq: 3
  stamp: 
    secs: 1525826012
    nsecs: 700968664
  frame_id: ''
axes: [0.0, -0.0, 0.0, 0.0]
buttons: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
---

```

