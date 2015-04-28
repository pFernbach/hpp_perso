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
robot.setJointBounds ("base_joint_xy", [-8,0,-10,-2])
ps = ProblemSolver (robot)
v = Viewer (ps)

q_init = robot.getCurrentConfig ()
q_goal = q_init [::]
q_init [0:2] = [-5.503,-3.564]
rank = robot.rankInConfiguration ['shoulder_pan_joint']
q_init [rank] = -6.05
rank = robot.rankInConfiguration ['shoulder_lift_joint']
q_init [rank] = 0.622
rank = robot.rankInConfiguration ['elbow_joint']
q_init [rank] = -0.665
rank = robot.rankInConfiguration ['wrist_1_joint']
q_init [rank] = -3.109
rank = robot.rankInConfiguration ['wrist_2_joint']
q_init [rank] = -1.607

v (q_init)

q_goal [0:2] = [-1.873,-6.319]
rank = robot.rankInConfiguration ['shoulder_pan_joint']
q_goal [rank] = -2.426
rank = robot.rankInConfiguration ['shoulder_lift_joint']
q_goal [rank] = -0.512
rank = robot.rankInConfiguration ['elbow_joint']
q_goal [rank] = 0.772
rank = robot.rankInConfiguration ['wrist_1_joint']
q_goal [rank] = -1.778
rank = robot.rankInConfiguration ['wrist_2_joint']
q_goal [rank] = -1.607

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
v.displayRoadmap("rmEND",blue,0.02,1,green,'ee_fixed_joint')



# alternative method : replace ps.solve() and v.displayRoadmap() with :
# v.solveAndDisplay("rmB",2,white,0.02,1,brown)
################################################################

pp = PathPlayer (robot.client, v)
#display path
pp (0)
#display path with post-optimisation
pp (1)


# hide roadmap in the scene
v.client.gui.removeFromGroup("rmL",v.sceneName)
v.client.gui.removeFromGroup("rmR",v.sceneName)






