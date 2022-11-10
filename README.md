# castle_maker
This package elaborates and executes the plan to build a mini-castle, made of wooden bricks, with an UR5e Robot.
### PREREQUISITES:
* `ROS2 foxy`
* `PlanSys2 package`
* `Popf`
* `Motion module` (or simulate the message flow)
* `Vision module`  (or simulate the message flow)
* `Communication bridge between ros1 and ros2` (needed if you are using motion module and vision module)
 
### INSTRUCTIONS:

To launch this package write on one terminal window:
```
$ ros2 launch castle_maker castle_maker_launch.py
```
On another terminal window write:
```
$ ros2 run castle_maker action_controller_node
```
After having chosen the layout of the building, the program reads messages from the vision module. 

**If that module is not available on your machine, simulate it on a new terminal window:**

* To add one parallelepiped:
```
$ ros2 topic pub /visionModuleid std_msgs/String '{data: 0}'
```
* To add one red cube:
```
$ ros2 topic pub /visionModuleid std_msgs/String '{data: 1}'
```
* To add one blue cube:
```
$ ros2 topic pub /visionModuleid std_msgs/String '{data: 2}'
```
* To add one yellow cube:
```
$ ros2 topic pub /visionModuleid std_msgs/String '{data: 3}'
```
* To finish the adding blocks procedure:
```
$ ros2 topic pub /visionModuleid std_msgs/String '{data: 4}'
```

Then, the package calculates the plan and executes it, sending the position messages, one after the other, to the motion module.

After each action the package waits for a response from the motion module, **to simulate it**:
```
$ ros2 topic pub /confirmation_topic std_msgs/String '{data: NOT BUSY }'
```
After all actions have been performed correctly, the program ends.
