#include <hpp/perso/rrtperso.hh>
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
#include <hpp/model/configuration.hh>
#include <hpp/core/weighed-distance.hh>

namespace hpp {
  namespace perso {
         /// Create an instance and return a shared pointer to the instance
        RrtPersoPtr_t RrtPerso::create(const core::Problem& problem,const core::RoadmapPtr_t& roadmap)
        {
            RrtPerso* ptr = new RrtPerso (problem, roadmap);
            RrtPersoPtr_t shPtr (ptr);
            ptr->init (shPtr);
            return shPtr;
        }


        /// une itération de l'algo
        void RrtPerso::oneStep ()
        {
            core::ConfigurationPtr_t qrand;
            core::ConfigValidationsPtr_t configValidations (problem ().configValidations ());
            core::SteeringMethodPtr_t sm (problem ().steeringMethod ());
            core::RoadmapPtr_t T = roadmap();
            core::PathValidationPtr_t pathValidation (problem ().pathValidation ());
            core::PathPtr_t validPart;


            // tire une configuration random sans collision
            do {
                qrand = shooter_.shoot ();
            } while (!configValidations->validate (*qrand));


            //extend : genere qnew le plus proche possible de qrand, si possible
            core::NodePtr_t xnew = extend(qrand);
            core::ConfigurationPtr_t qnew = xnew->configuration();

           if(xnew){
                // ---- tente de connecter à qgoal:
                core::ConfigurationPtr_t qnew = xnew->configuration();
                core::NodePtr_t xgoal = T->goalNodes().front();

                //core::ConfigurationPtr_t qgoal = problem().goalConfigs().front();   //(on considère que des pb à 1 but
                core::ConfigurationPtr_t qgoal = xgoal->configuration();
                core::PathPtr_t localPath = (*sm)(*qnew,*qgoal);
                if(pathValidation->validate (localPath, false, validPart)){ // si chemin valide, on connect
                    //hppDout(notice,"qgoal add");
                    T->addEdge (xnew, xgoal, localPath);
                    T->addEdge (xgoal, xnew, localPath->reverse ());
                }
            }


        }


        core::NodePtr_t RrtPerso::extend(core::ConfigurationPtr_t qrand)
        {
            double d;
            core::SteeringMethodPtr_t sm (problem ().steeringMethod ());
            core::PathValidationPtr_t pathValidation (problem ().pathValidation ());
            core::PathPtr_t validPart;
            core::ConfigValidationsPtr_t configValidations (problem ().configValidations ());
            core::RoadmapPtr_t T = roadmap();
            problem().distance();
            // recherche noeud le plus proche dans l'arbre lié à qinit
            core::NodePtr_t xnear= T->nearestNode(qrand,T->initNode()->connectedComponent(),d);

            core::ConfigurationPtr_t qnear = xnear->configuration();
            //hppDout(notice,"qnear"<<*qnear<<std::endl);
            //creation trajectoire entre les deux configurations
            core::PathPtr_t localPath = (*sm) (*qnear, *qrand);
            //test colision sur cette trajectoire
            pathValidation->validate (localPath, false, validPart);
            //on récupère la derniere conf valide
            core::ConfigurationPtr_t qnew (new core::Configuration_t(validPart->end()));
           // hppDout(notice,"qnew"<<*qnew<<std::endl);
            // si elle est sans collision on va l'ajouter a l'arbre (normalement elle l'est forcément puisque validPart ... )
            // on test aussi que qnear et qnew ne sont pas identiques
           if(validPart->length()>0 && configValidations->validate(*qnew)){
                //ajout du noeud :
                core::NodePtr_t xnew = T->addNode (qnew);
                //ajout des arcs (bi directionnel)
                //hppDout(notice,"extend add");
                //hppDout(notice,"distance"<<validPart->length());
                T->addEdge (xnear, xnew, validPart);
                T->addEdge (xnew, xnear, validPart->reverse ());
                return xnew;
            }else
                return xnear;
        }

        /// constructeur ( en protected )
        RrtPerso::RrtPerso(const core::Problem& problem, const core::RoadmapPtr_t& roadmap) :
                core::PathPlanner (problem, roadmap), shooter_ (problem.robot ())
        {
        }


         /// Store weak pointer to itself
        void RrtPerso::init (const RrtPersoWkPtr_t& weak)
        {

            core::PathPlanner::init (weak);
            weakPtr_ = weak;
        }


  }//perso
}//hpp
