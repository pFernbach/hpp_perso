from hpp.corbaserver import * 
from hpp.corbaserver.stick import Robot
from hpp.corbaserver import ProblemSolver
from hpp.gepetto import Viewer
from hpp.gepetto import PathPlayer
from hpp import display
import time  


print("chargement robot")
robot = Robot ('robot_stick', True)
robot.setJointBounds ("base_joint_xyz", [-10,10,-10,10, 0.5, 0.5])	
#robot.setJointBounds ("base_joint_xyz", [-5,4,-7,5,0.5,0.5])	

robot.tf_root = 'base_link'

ps = ProblemSolver (robot)

v = Viewer (ps)

q_init = robot.getCurrentConfig ()

q_init[0:3] = [6, 7, 0.5]	#z=0.4 pour sphere
#6 7 pour en dehors de la zone
v (q_init)
q_goal = q_init [::]
q_goal [0:3] = [-2.5, -3.5, 0.5]
#v (q_goal)

print("chargement map")
v.loadObstacleModel ("iai_maps", "room", "room")

ps.setInitialConfig (q_init)
ps.addGoalConfig (q_goal)
ps.selectPathPlanner("rrtPerso")

v.solveAndDisplay(white,0.02,1,brown)

ps.solve ()


v.displayRoadmap(white,0.02,1,brown)

pp = PathPlayer (robot.client, v)
print("affichage solution")
pp (0)
print("affichage solution optimise")
pp (1)





