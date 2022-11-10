# castle_maker
PREREQUISITES:
	-ROS2 foxy
	-PlanSys2 package
	-Popf
  -motion module (or simulating the message flow)
  -vision module  (or simulating the message flow)
  -bridge communication between ros1 and ros2 (if using motion module and vision module)
 
 INSTRUCTIONS:

To launch this package write on one terminal window:

$ ros2 launch castle_maker castle_maker_launch.py

On another terminal window write:

$ ros2 run castle_maker action_controller_node

Now, choose the layout of the building writing the colour of each column;

After that, the program reads the messages from the vision module.
If not available on your machine, simulate them on a new terminal window:

-To add one parallelepiped:
$ ros2 topic pub /visionModuleid std_msgs/String '{data: 0}'
-To add one red cube:
$ ros2 topic pub /visionModuleid std_msgs/String '{data: 1}'
-To add one blue cube:
$ ros2 topic pub /visionModuleid std_msgs/String '{data: 2}'
-To add one yellow cube:
$ ros2 topic pub /visionModuleid std_msgs/String '{data: 3}'
-To finish the adding procedure
$ ros2 topic pub /visionModuleid std_msgs/String '{data: 4}'

Then, the package calculates the plan and executes it sending the position messages, one after the other, to the motion module.
After each action the package waits for a response from the motion module, to simulate it:

$ ros2 topic pub /confirmation_topic std_msgs/String '{data: NOT BUSY }'

After all actions have been performed correctly, the program ends.
