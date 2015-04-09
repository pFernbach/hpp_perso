from hpp.corbaserver.r2d2 import Robot
robot = Robot ('r2d2')


from hpp.corbaserver import ProblemSolver
ps = ProblemSolver (robot)

from hpp.gepetto import Viewer
r = Viewer (ps)

q_init = robot.getCurrentConfig ()

r (q_init)

