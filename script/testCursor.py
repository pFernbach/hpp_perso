from hpp.corbaserver import * 
from hpp.corbaserver.cursor import Robot
import time  
print("chargement robot")
robot = Robot ('robot_cursor', True)
robot.setJointBounds ("base_joint_xyz", [-10,10,-10,10, 0.5, 0.5])	
# room : -5,4,-7,5,0.5,0.5
robot.tf_root = 'base_link'


from hpp.corbaserver import ProblemSolver
ps = ProblemSolver (robot)

from hpp.gepetto import Viewer
v = Viewer (ps)


q_init = robot.getCurrentConfig ()

q_init[0:3] = [6, 7, 0.5]	#z=0.4 pour sphere
v (q_init)
q_goal = q_init [::]
q_goal [0:3] = [-2.5, -3.5, 0.5]
#v (q_goal)

print("chargement map")
v.loadObstacleModel ("iai_maps", "room", "room")

ps.setInitialConfig (q_init)
ps.addGoalConfig (q_goal)

ps.selectPathPlanner("test2")

print("debut motion plannning")

tps1 = time.clock()
ps.solve ()
tps2 = time.clock()
print(tps2-tps1)


from hpp.gepetto import PathPlayer
pp = PathPlayer (robot.client, v)
#print("affichage solution")
#pp (0)
while 1 :
	print("Appuyer sur entree pour afficher la solution")
	raw_input()
	pp (1)


