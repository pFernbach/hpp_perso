#ifndef RrtConnect_HH
#define RrtConnect_HH

#include <hpp/core/path-planner.hh>
#include <hpp/util/pointer.hh>
#include <hpp/core/basic-configuration-shooter.hh>

namespace hpp {
    namespace perso {
    // forward declaration of class Planner
    HPP_PREDEF_CLASS (RrtConnect);
    // Planner objects are manipulated only via shared pointers
    typedef boost::shared_ptr <RrtConnect> RrtConnectPtr_t;

        class RrtConnect : public core::PathPlanner
        {
            public:
                static RrtConnectPtr_t create(const core::Problem& problem,const core::RoadmapPtr_t& roadmap);
                virtual void oneStep ();
            protected:
                RrtConnect(const core::Problem& problem, const core::RoadmapPtr_t& roadmap);
                void init (const RrtConnectWkPtr_t& weak);
            private:
                /// Configuration shooter to uniformly shoot random configurations
                core::BasicConfigurationShooter shooter_;
                /// weak pointer to itself
                RrtConnectWkPtr_t weakPtr_;
                core::NodePtr_t extend(core::ConfigurationPtr_t qrand);
        };


    }//perso
}//hpp

#endif // RrtConnect_HH
