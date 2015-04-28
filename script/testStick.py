from hpp.corbaserver import * 
from hpp.corbaserver.stick import Robot
from hpp.corbaserver import Viewer
from hpp.corbaserver import ProblemSolver
from hpp.gepetto import PathPlayer
import time  


white=[1.0,1.0,1.0,1.0]
green=[0.23,0.75,0.2,0.5]
yellow=[0.85,0.75,0.15,0.5]

robot = Robot ('robot_Stick')
robot.tf_root = 'base_link'
robot.setJointBounds ("base_joint_xyz", [-10,10,-10,10, 0.5, 0.5])	
#robot.setJointBounds ("base_joint_xyz", [-5,4,-7,5,0.5,0.5])

ps = ProblemSolver (robot)
v = Viewer (ps)
pp = PathPlayer (robot.client, v)

q_init = robot.getCurrentConfig ()

q_init[0:3] = [6, 7, 0.5]	#z=0.4 pour sphere
v (q_init)
q_goal = q_init [::]
q_goal [0:3] = [-2.5, -3.5, 0.5]
#v (q_goal)


v.loadObstacleModel ("iai_maps", "room", "room")

ps.setInitialConfig (q_init)
ps.addGoalConfig (q_goal)
ps.solve ()



v.displayRoadmap("rm1",white,0.02,1,yellow)


v.solveAndDisplay("rm1",10,white,0.02,1,yellow)
#print("affichage solution")
#pp (0)
print("affichage solution optimise")
pp (1)


