from hpp.corbaserver import * 
from hpp.corbaserver.boule import Robot
from hpp.gepetto import PathPlayer
from hpp.corbaserver import ProblemSolver
from hpp.gepetto import Viewer

import time  

white=[1.0,1.0,1.0,1.0]
green=[0.23,0.75,0.2,0.5]
brown=[0.85,0.75,0.15,0.5]

print("chargement robot")
robot = Robot ('robot_boule', True)
robot.setJointBounds ("base_joint_xyz", [0,9,0,12,0.5,0.5])	
#robot.setJointBounds("base_joint_SO3",[1,1,0,0,0,0,0,0])
# room : -5,4,-7,5,0.5,0.5
robot.tf_root = 'base_link'

ps = ProblemSolver (robot)
v = Viewer (ps)
q_init = robot.getCurrentConfig ()

q_init[0:3] = [9, 7.5,0.5]	
v (q_init)
q_goal = q_init [::]
q_goal [0:3] = [0,1.5,0.5]
#v (q_goal)

print("chargement map")
v.loadObstacleModel ("iai_maps", "labyrinth2", "labyrinth2")

ps.setInitialConfig (q_init)
ps.addGoalConfig (q_goal)
ps.selectPathPlanner("rrtConnect")

v.solveAndDisplay(white,0.02,1,brown)

ps.solve ()

v.displayRoadmap(white,0.02,1,brown)


pp = PathPlayer (robot.client, v)
#print("affichage solution")
#pp (0)
print("affichage solution optimise")




