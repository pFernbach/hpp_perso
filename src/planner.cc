//
// Copyright (c) 2014 CNRS
// Authors: Florent Lamiraux
//
// This file is part of hpp_tutorial
// hpp_tutorial is free software: you can redistribute it
// and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either version
// 3 of the License, or (at your option) any later version.
//
// hpp_tutorial is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Lesser Public License for more details.  You should have
// received a copy of the GNU Lesser General Public License along with
// hpp_tutorial  If not, see
// <http://www.gnu.org/licenses/>.


#include <hpp/util/debug.hh>
#include <hpp/core/config-validations.hh>
#include <hpp/core/connected-component.hh>
#include <hpp/core/constraint-set.hh>
#include <hpp/core/path-validation.hh>
#include <hpp/core/steering-method.hh>
#include <hpp/core/roadmap.hh>
#include <hpp/core/problem.hh>
#include <hpp/model/configuration.hh>
#include <hpp/perso/planner.hh>
#include <hpp/core/node.hh>
#include <hpp/core/edge.hh>
#include <hpp/perso/config.hh>
#include <fstream>

namespace hpp {
  namespace perso {

      /// Create an instance and return a shared pointer to the instance
      PlannerPtr_t Planner::create (const core::Problem& problem,
                  const core::RoadmapPtr_t& roadmap)
      {
        Planner* ptr = new Planner (problem, roadmap);
        PlannerPtr_t shPtr (ptr);
        ptr->init (shPtr);
        return shPtr;
      }

      /// One step of extension.
      ///
      /// This method implements one step of your algorithm. The method
      /// will be called iteratively until one goal configuration is accessible
      /// from the initial configuration.
      ///
      /// We will see how to implement a basic PRM algorithm.
      void Planner::oneStep ()
      {
        // Retrieve the robot the problem has been defined for.
        model::DevicePtr_t robot (problem ().robot ());
        // Retrieve the path validation algorithm associated to the problem
        core::PathValidationPtr_t pathValidation (problem ().pathValidation ());
        // Retrieve configuration validation methods associated to the problem
        core::ConfigValidationsPtr_t configValidations
          (problem ().configValidations ());
        // Retrieve the steering method
        core::SteeringMethodPtr_t sm (problem ().steeringMethod ());
        // Retrieve the constraints the robot is subject to
        core::ConstraintSetPtr_t constraints (problem ().constraints ());
        // Retrieve roadmap of the path planner
        core::RoadmapPtr_t r (roadmap ());
        // shoot a valid random configuration
        core::ConfigurationPtr_t qrand;

        do {
            qrand = shooter_.shoot ();
        } while (!configValidations->validate (*qrand));


        // Add qrand as a new node
        core::NodePtr_t newNode = r->addNode (qrand);
        // try to connect the random configuration to each connected component
        // of the roadmap.
        for (core::ConnectedComponents_t::const_iterator itcc = r->connectedComponents ().begin (); itcc != r->connectedComponents ().end (); ++itcc) {
          core::ConnectedComponentPtr_t cc = *itcc;
          // except its own connected component of course
          if (cc != newNode->connectedComponent ()) {
            double d;
            // Get nearest node to qrand in connected component
            core::NodePtr_t nearest = r->nearestNode (qrand, cc, d);
            core::ConfigurationPtr_t qnear = nearest->configuration ();

            // Create local path between qnear and qrand
            core::PathPtr_t localPath = (*sm) (*qnear, *qrand);
            // validate local path
            core::PathPtr_t validPart;
            if (pathValidation->validate (localPath, false, validPart)) {
              // Create node and edges with qrand and the local path
              r->addEdge (nearest, newNode, localPath);
              r->addEdge (newNode, nearest, localPath->reverse ());
            }
          }
        }
       // hppDout(notice,"--------------------------");
      }

      /// Protected constructor
      /// Users need to call Planner::create in order to create instances.
      Planner::Planner (const core::Problem& problem,const core::RoadmapPtr_t& roadmap) :
    core::PathPlanner (problem, roadmap), shooter_ (problem.robot ())
      {
          it_=0;
      }
      /// Store weak pointer to itself
      void Planner::init (const PlannerWkPtr_t& weak)
      {
        core::PathPlanner::init (weak);
        weakPtr_ = weak;
      }

      core::PathVectorPtr_t Planner::finishSolve (const core::PathVectorPtr_t& path)
      {
        Planner::dispRoadmap();



        return path;
      }

      // Permet d'ecrire la structure de la roadmap dans un fichier
      void Planner::dispRoadmap(){


         int i =1;
         bool exist = true;
         while(exist){//permet de creer le fichier avec un numero pas encore utilisé
             std::stringstream path;
             path<<hpp::debug::getPrefix("PERSO")<<"/map"<<i<<".txt";
             std::ifstream file(path.str().c_str(),std::ios::in);
             if(file)
                 i++;
             else
                 exist=false;
             file.close();
         }
         std::stringstream path;
         path<<hpp::debug::getPrefix("PERSO")<<"/map"<<i<<".txt";
         std::ofstream fichier(path.str().c_str(),std::ios::out);
         int iNode = 1;
         for(core::Nodes_t::const_iterator itn = roadmap()->nodes().begin();itn != roadmap()->nodes().end() ;++itn ){//pour tout les noeuds
             core::NodePtr_t node = *itn;
             core::ConfigurationPtr_t q = node->configuration();
             fichier<<"noeud "<<iNode<<" : "<<std::endl<<(*q)<<std::endl<<"------------------------------------"<<std::endl;
             iNode++;
         }
    //TODO format dot, et edge





         fichier<<"test";
         fichier.close();  // on ferme le fichier
      }

  } // namespace perso
} // namespace hpp

