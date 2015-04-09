#ifndef RRTPERSO_HH
#define RRTPERSO_HH

#include <hpp/core/path-planner.hh>
#include <hpp/util/pointer.hh>
#include <hpp/core/basic-configuration-shooter.hh>

namespace hpp {
    namespace perso {
    // forward declaration of class Planner
    HPP_PREDEF_CLASS (RrtPerso);
    // Planner objects are manipulated only via shared pointers
    typedef boost::shared_ptr <RrtPerso> RrtPersoPtr_t;

        class RrtPerso : public core::PathPlanner
        {
            public:
                static RrtPersoPtr_t create(const core::Problem& problem,const core::RoadmapPtr_t& roadmap);
                virtual void oneStep ();
            protected:
                RrtPerso(const core::Problem& problem, const core::RoadmapPtr_t& roadmap);
                void init (const RrtPersoWkPtr_t& weak);
            private:
                /// Configuration shooter to uniformly shoot random configurations
                core::BasicConfigurationShooter shooter_;
                /// weak pointer to itself
                RrtPersoWkPtr_t weakPtr_;
                core::NodePtr_t extend(core::ConfigurationPtr_t qrand);
        };


    }//perso
}//hpp

#endif // RRTPERSO_HH
