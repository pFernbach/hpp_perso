from hpp.corbaserver import * 
from hpp.corbaserver.boule import Robot
from hpp.gepetto import PathPlayer
from hpp import display
from hpp.corbaserver import ProblemSolver
from hpp.gepetto import Viewer

import time  

print("chargement robot")
robot = Robot ('robot_boule', True)
robot.setJointBounds ("base_joint_xyz", [0,5,0,2,0,2])	
# room : -5,4,-7,5,0.5,0.5
robot.tf_root = 'base_link'

ps = ProblemSolver (robot)
v = Viewer (ps)
q_init = robot.getCurrentConfig ()

q_init[0:3] = [0.5, 1, 1]	#z=0.4 pour sphere
v (q_init)
q_goal = q_init [::]
q_goal [0:3] = [5,1, 1]
#v (q_goal)

print("chargement map")
v.loadObstacleModel ("iai_maps", "tunnel", "tunnel")

ps.setInitialConfig (q_init)
ps.addGoalConfig (q_goal)

ps.selectPathPlanner("rrtPerso")
print("Debut motion planning")


v.solveAndDisplay(white,0.02,1,brown)

ps.solve ()

v.displayRoadmap(white,0.02,1,brown)


pp = PathPlayer (robot.client, v)
#print("affichage solution")
#pp (0)
print("affichage solution optimise")




