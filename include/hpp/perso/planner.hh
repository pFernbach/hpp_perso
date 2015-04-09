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

#include <hpp/core/path-planner.hh>
#include <hpp/util/pointer.hh>
#include <hpp/core/basic-configuration-shooter.hh>

#ifndef HPP_PERSO_PLANNER_HH
#define HPP_PERSO_PLANNER_HH

namespace hpp {
  namespace perso {

  // forward declaration of class Planner
  HPP_PREDEF_CLASS (Planner);
  // Planner objects are manipulated only via shared pointers
  typedef boost::shared_ptr <Planner> PlannerPtr_t;

    class Planner : public core::PathPlanner
    {
        public:
            static PlannerPtr_t create (const core::Problem& problem,const core::RoadmapPtr_t& roadmap);
            virtual void oneStep ();
            core::PathVectorPtr_t finishSolve (const core::PathVectorPtr_t& path);
            void dispRoadmap();
        protected:
          /// Protected constructor
          /// Users need to call Planner::create in order to create instances.
          Planner (const core::Problem& problem, const core::RoadmapPtr_t& roadmap);
          void init (const PlannerWkPtr_t& weak);
        private:
          /// Configuration shooter to uniformly shoot random configurations
          core::BasicConfigurationShooter shooter_;
          /// weak pointer to itself
          PlannerWkPtr_t weakPtr_;
          int it_;
    };

  }//perso
}//hpp

#endif // HPP_PERSO_PLANNER_HH
