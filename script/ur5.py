from hpp.corbaserver import * 
from hpp.corbaserver.ur5 import Robot
from hpp.corbaserver import ProblemSolver
from hpp.gepetto import Viewer
from hpp.gepetto import PathPlayer

# define colors for the roadmap
white=[1.0,1.0,1.0,1.0]
green=[0.23,0.75,0.2,0.5]
brown=[0.85,0.75,0.15,0.5]
blue = [0.0, 0.0, 0.8, 1.0]
grey = [0.7,0.7,0.7,1.0]
red = [0.8,0.0,0.0,1.0]

robot = Robot ('robot_ur5')
robot.setJointBounds ("base_joint_xyz", [-5,-2.5,-6,-3,0.75,0.75])
ps = ProblemSolver (robot)
v = Viewer (ps)

q_init = robot.getCurrentConfig ()
q_goal = q_init [::]
q_init [0:3] = [-2.971,-3.796,0.75]
rank = robot.rankInConfiguration ['shoulder_lift_joint']
q_init [rank] = -0.739
rank = robot.rankInConfiguration ['elbow_joint']
q_init [rank] = 1.635
rank = robot.rankInConfiguration ['wrist_1_joint']
q_init [rank] = 3.809
rank = robot.rankInConfiguration ['wrist_2_joint']
q_init [rank] = -1.65
rank = robot.rankInConfiguration ['wrist_3_joint']
q_init [rank] = 0.874
v (q_init)

q_goal [0:3] = [-4.515,-5.244,0.75]
rank = robot.rankInConfiguration ['shoulder_pan_joint']
q_goal [rank] = 3.456
rank = robot.rankInConfiguration ['shoulder_lift_joint']
q_goal [rank] = -0.776
rank = robot.rankInConfiguration ['elbow_joint']
q_goal [rank] = 0.66
rank = robot.rankInConfiguration ['wrist_1_joint']
q_goal [rank] = -2.963
rank = robot.rankInConfiguration ['wrist_2_joint']
q_goal [rank] = -0.266
rank = robot.rankInConfiguration ['wrist_3_joint']
q_goal [rank] =0
#r (q_goal)

v.loadObstacleModel ("iai_maps", "kitchen_area", "kitchen")
ps.setInitialConfig (q_init)
ps.addGoalConfig (q_goal)

#ps.selectPathPlanner("rrtConnect")

ps.solve ()

# display roadmap for the base of the robot (no specified joint)
v.displayRoadmap("rmB",white,0.02,1,brown)
# hide previous roadmap
v.client.gui.removeFromGroup("rmB",v.sceneName)

#display roadmap for the tools :
v.displayRoadmap("rmR",blue,0.02,1,green,'r_gripper_tool_joint')
v.displayRoadmap("rmL",red,0.02,1,grey,'l_gripper_tool_joint')


# alternative method : replace ps.solve() and v.displayRoadmap() with :
# v.solveAndDisplay("rmR",2,blue,0.02,1,green,'r_gripper_tool_joint')
# v.displayRoadmap("rmL",red,0.02,1,grey,'l_gripper_tool_joint')
################################################################

pp = PathPlayer (robot.client, v)
#display path
pp (0)
#display path with post-optimisation
pp (1)


# hide roadmap in the scene
v.client.gui.removeFromGroup("rmL",v.sceneName)
v.client.gui.removeFromGroup("rmR",v.sceneName)






