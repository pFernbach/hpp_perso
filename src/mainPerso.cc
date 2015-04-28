#include "hpp/corbaserver/server.hh"
#include <hpp/perso/planner.hh>
#include <hpp/perso/rrtconnect.hh>
#include <hpp/perso/rrtperso.hh>
#include "hpp/core/diffusing-planner.hh"


// main function of the corba server
int main (int argc, const char* argv[])
{
  // create a ProblemSolver instance.
  // This class is a container that does the interface between hpp-core library
  // and component to be running in a middleware like CORBA or ROS.
  hpp::core::ProblemSolverPtr_t problemSolver = new hpp::core::ProblemSolver;
  // Add the new planner type in order to be able to select it from python
  // client.
  problemSolver->addPathPlannerType ("test2", hpp::perso::Planner::create);
  problemSolver->addPathPlannerType("rrtPerso",hpp::perso::RrtPerso::create);
  problemSolver->addPathPlannerType("rrtConnect",hpp::perso::RrtConnect::create);
  // problemSolver->addPathPlannerType ("testPierre", hpp::core::DiffusingPlanner::createWithRoadmap);
  // Create the CORBA server.
  hpp::corbaServer::Server server (problemSolver, argc, argv, false);    // par défaut : true (multi thread)
  // Start the CORBA server.
  server.startCorbaServer ();
  // Wait for CORBA requests.
  server.processRequest (true);
}
