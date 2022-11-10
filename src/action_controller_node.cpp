#include <plansys2_pddl_parser/Utils.h>
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include "plansys2_msgs/msg/action_execution_info.hpp"
#include "plansys2_msgs/msg/plan.hpp"
#include "plansys2_domain_expert/DomainExpertClient.hpp"
#include "plansys2_executor/ExecutorClient.hpp"
#include "plansys2_planner/PlannerClient.hpp"
#include "plansys2_problem_expert/ProblemExpertClient.hpp"
#include "std_msgs/msg/string.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "geometry_msgs/msg/pose.hpp"
#include "geometry_msgs/msg/pose_with_covariance_stamped.hpp"
const std::string red("\033[0;31m");
const std::string reset("\033[0m");
const std::string green("\033[1;32m");
const std::string purple("\033[0;35m");
const std::string yellow("\033[1;33m");
const std::string cyan("\033[0;36m");
const std::string magenta("\033[0;35m");
std::vector<std::string> piece;
std::string color[4];
std::string color1a, color2a, color3a, color4a, firstgoal, secondgoal, thirdgoal, fourthgoal;
int y=0,r=0,b=0,f=0,p=20,pc=0,rc=0,bc=0,yc=0,id=6,i=1;
class planningModule : public rclcpp::Node
{
public:
  planningModule()
  :Node("Planning_Module")
 {
  using namespace std::placeholders;
  piece_ = this->create_subscription<std_msgs::msg::String>("/visionModuleid",10,std::bind(&planningModule::getpieces, this, _1));
  } 
//metodo callback per popolare l'array contenente gli oggetti comunicati dal modulo di visione
  void getpieces(const std_msgs::msg::String::SharedPtr msg)
  { 
   id = stoi(msg->data);
   if ((id == 0))
   {
    ++pc;  
    piece.push_back(("parallelepiped"+ std::to_string(pc)));
    std::cout<<reset<<i<<".Parallelepipedo"<<std::endl;
    ++i;
   }
   else if ((id == 1))
   {
    ++rc;
    piece.push_back(("redcube"+std::to_string(rc)));
    std::cout<<reset<<i<<".Cubo rosso"<<std::endl;
    ++i;
   }    
   else if ((id == 2))
   {
    ++bc;
    piece.push_back(("bluecube"+std::to_string(bc)));
    std::cout<<reset<<i<<".Cubo blu"<<std::endl;
    ++i;
   }    
   else if ((id == 3))
   {
    ++yc;
    piece.push_back(("yellowcube"+std::to_string(yc)));
    std::cout<<reset<<i<<".Cubo giallo"<<std::endl;
    ++i;
   }    
  }
//inizializzazione del nodo
  void init()
  {
    domain_expert_ = std::make_shared<plansys2::DomainExpertClient>();
    planner_client_ = std::make_shared<plansys2::PlannerClient>();
    problem_expert_ = std::make_shared<plansys2::ProblemExpertClient>();
    executor_client_ = std::make_shared<plansys2::ExecutorClient>();
    //addSimulatedInstances();
    //addSimulatedPredicates();
    addInstances();
    addPredicates(); 
  }

//metodo per aggiungere le istanze con i dati letti dal modulo di visione
  void addInstances()
  { 
    for (int i=0; i<piece.size();i++){
      problem_expert_->addInstance(plansys2::Instance{piece[i], "object"});
      if((piece[i].find("parallelepiped") != std::string::npos)){
        p++;
        problem_expert_->addInstance(plansys2::Instance{"position" + std::to_string(p)+"","location"});
      }
      else {
        ++f;
        problem_expert_->addInstance(plansys2::Instance{"position" + std::to_string(f)+"","location"});
      }
    }
    p=20;
    f=0;
    for (int i=1; i<9;i++){ 
      problem_expert_->addInstance(plansys2::Instance{"destination" + std::to_string(i)+"","location"});
    }
    problem_expert_->addInstance(plansys2::Instance{"gripper", "robot"});
  }
//metodo per aggiungere in automatico le istanze del problema (utilizzabile per effettuare delle prove)
  void addSimulatedInstances()
  {
    problem_expert_->addInstance(plansys2::Instance{"yellowcube1", "object"});
    problem_expert_->addInstance(plansys2::Instance{"yellowcube2", "object"});
    problem_expert_->addInstance(plansys2::Instance{"yellowcube3", "object"});
    problem_expert_->addInstance(plansys2::Instance{"yellowcube4", "object"});
    problem_expert_->addInstance(plansys2::Instance{"redcube1", "object"});
    problem_expert_->addInstance(plansys2::Instance{"redcube2", "object"});
    problem_expert_->addInstance(plansys2::Instance{"redcube3", "object"});
    problem_expert_->addInstance(plansys2::Instance{"redcube4", "object"});
    problem_expert_->addInstance(plansys2::Instance{"bluecube1", "object"});
    problem_expert_->addInstance(plansys2::Instance{"bluecube2", "object"});
    problem_expert_->addInstance(plansys2::Instance{"bluecube3", "object"});
    problem_expert_->addInstance(plansys2::Instance{"bluecube4", "object"});
    problem_expert_->addInstance(plansys2::Instance{"parallelepiped1", "object"});
    problem_expert_->addInstance(plansys2::Instance{"parallelepiped2", "object"});
    problem_expert_->addInstance(plansys2::Instance{"parallelepiped3", "object"});
    problem_expert_->addInstance(plansys2::Instance{"parallelepiped4", "object"});
    problem_expert_->addInstance(plansys2::Instance{"position1", "location"});
    problem_expert_->addInstance(plansys2::Instance{"position2", "location"});
    problem_expert_->addInstance(plansys2::Instance{"position3", "location"});
    problem_expert_->addInstance(plansys2::Instance{"position4", "location"});
    problem_expert_->addInstance(plansys2::Instance{"position5", "location"});
    problem_expert_->addInstance(plansys2::Instance{"position6", "location"});
    problem_expert_->addInstance(plansys2::Instance{"position7", "location"});
    problem_expert_->addInstance(plansys2::Instance{"position8", "location"});
    problem_expert_->addInstance(plansys2::Instance{"position9", "location"});
    problem_expert_->addInstance(plansys2::Instance{"position10", "location"});
    problem_expert_->addInstance(plansys2::Instance{"position11", "location"});
    problem_expert_->addInstance(plansys2::Instance{"position12", "location"});
    problem_expert_->addInstance(plansys2::Instance{"position21", "location"});
    problem_expert_->addInstance(plansys2::Instance{"position22", "location"});
    problem_expert_->addInstance(plansys2::Instance{"position23", "location"});
    problem_expert_->addInstance(plansys2::Instance{"position24", "location"});
    problem_expert_->addInstance(plansys2::Instance{"destination1", "location"});
    problem_expert_->addInstance(plansys2::Instance{"destination2", "location"});
    problem_expert_->addInstance(plansys2::Instance{"destination3", "location"});
    problem_expert_->addInstance(plansys2::Instance{"destination4", "location"});
    problem_expert_->addInstance(plansys2::Instance{"destination5", "location"});
    problem_expert_->addInstance(plansys2::Instance{"destination6", "location"});
    problem_expert_->addInstance(plansys2::Instance{"destination7", "location"});
    problem_expert_->addInstance(plansys2::Instance{"destination8", "location"});
    problem_expert_->addInstance(plansys2::Instance{"gripper", "robot"});
  }
//metodo per aggiungere i predicati con i dati letti dal modulo di visione
  void addPredicates(){
    for (int i=0; i<piece.size();i++){      
      problem_expert_->addPredicate(plansys2::Predicate("(ontable " + piece[i] + ")"));
      problem_expert_->addPredicate(plansys2::Predicate("(clear " + piece[i] + ")"));
      if((piece[i].find("parallelepiped") != std::string::npos)){
        ++p;
        problem_expert_->addPredicate(plansys2::Predicate("(at " + piece[i] + " position" + std::to_string(p) + ")"));
      }
      else {
        ++f;
        problem_expert_->addPredicate(plansys2::Predicate("(at " + piece[i] + " position" + std::to_string(f) + ")"));
      }
    }
      problem_expert_->addPredicate(plansys2::Predicate("(emptyhand gripper)"));
      problem_expert_->addPredicate(plansys2::Predicate("(notbusy gripper)"));}
//metodo per aggiungere in automatico i predicati del problema (utilizzabile per effettuare delle prove)
  void addSimulatedPredicates(){
    problem_expert_->addPredicate(plansys2::Predicate("(ontable yellowcube1)"));
    problem_expert_->addPredicate(plansys2::Predicate("(ontable yellowcube2)"));
    problem_expert_->addPredicate(plansys2::Predicate("(ontable yellowcube3)"));
    problem_expert_->addPredicate(plansys2::Predicate("(ontable yellowcube4)"));
    problem_expert_->addPredicate(plansys2::Predicate("(ontable redcube1)"));
    problem_expert_->addPredicate(plansys2::Predicate("(ontable redcube2)"));
    problem_expert_->addPredicate(plansys2::Predicate("(ontable redcube3)"));
    problem_expert_->addPredicate(plansys2::Predicate("(ontable redcube4)"));
    problem_expert_->addPredicate(plansys2::Predicate("(ontable bluecube1)"));
    problem_expert_->addPredicate(plansys2::Predicate("(ontable bluecube2)"));
    problem_expert_->addPredicate(plansys2::Predicate("(ontable bluecube3)"));
    problem_expert_->addPredicate(plansys2::Predicate("(ontable bluecube4)"));
    problem_expert_->addPredicate(plansys2::Predicate("(ontable parallelepiped1)"));
    problem_expert_->addPredicate(plansys2::Predicate("(ontable parallelepiped2)"));
    problem_expert_->addPredicate(plansys2::Predicate("(ontable parallelepiped3)"));
    problem_expert_->addPredicate(plansys2::Predicate("(ontable parallelepiped4)")); 
    problem_expert_->addPredicate(plansys2::Predicate("(at yellowcube1 position1)"));
    problem_expert_->addPredicate(plansys2::Predicate("(at yellowcube2 position2)"));
    problem_expert_->addPredicate(plansys2::Predicate("(at yellowcube3 position3)"));
    problem_expert_->addPredicate(plansys2::Predicate("(at yellowcube4 position4)"));
    problem_expert_->addPredicate(plansys2::Predicate("(at redcube1 position5)"));
    problem_expert_->addPredicate(plansys2::Predicate("(at redcube2 position6)"));
    problem_expert_->addPredicate(plansys2::Predicate("(at redcube3 position7)"));
    problem_expert_->addPredicate(plansys2::Predicate("(at redcube4 position8)"));
    problem_expert_->addPredicate(plansys2::Predicate("(at bluecube1 position9)"));
    problem_expert_->addPredicate(plansys2::Predicate("(at bluecube2 position10)"));
    problem_expert_->addPredicate(plansys2::Predicate("(at bluecube3 position11)"));
    problem_expert_->addPredicate(plansys2::Predicate("(at bluecube4 position12)"));
    problem_expert_->addPredicate(plansys2::Predicate("(at parallelepiped1 position21)"));
    problem_expert_->addPredicate(plansys2::Predicate("(at parallelepiped2 position22)"));
    problem_expert_->addPredicate(plansys2::Predicate("(at parallelepiped3 position23)"));
    problem_expert_->addPredicate(plansys2::Predicate("(at parallelepiped4 position24)"));
    problem_expert_->addPredicate(plansys2::Predicate("(clear yellowcube1)"));
    problem_expert_->addPredicate(plansys2::Predicate("(clear yellowcube2)"));
    problem_expert_->addPredicate(plansys2::Predicate("(clear yellowcube3)"));
    problem_expert_->addPredicate(plansys2::Predicate("(clear yellowcube4)"));
    problem_expert_->addPredicate(plansys2::Predicate("(clear redcube1)"));
    problem_expert_->addPredicate(plansys2::Predicate("(clear redcube2)"));
    problem_expert_->addPredicate(plansys2::Predicate("(clear redcube3)"));
    problem_expert_->addPredicate(plansys2::Predicate("(clear redcube4)"));
    problem_expert_->addPredicate(plansys2::Predicate("(clear bluecube1)"));
    problem_expert_->addPredicate(plansys2::Predicate("(clear bluecube2)"));
    problem_expert_->addPredicate(plansys2::Predicate("(clear bluecube3)"));
    problem_expert_->addPredicate(plansys2::Predicate("(clear bluecube4)"));
    problem_expert_->addPredicate(plansys2::Predicate("(clear parallelepiped1)"));
    problem_expert_->addPredicate(plansys2::Predicate("(clear parallelepiped2)"));
    problem_expert_->addPredicate(plansys2::Predicate("(clear parallelepiped3)"));
    problem_expert_->addPredicate(plansys2::Predicate("(clear parallelepiped4)"));                 
    problem_expert_->addPredicate(plansys2::Predicate("(emptyhand gripper)"));
    problem_expert_->addPredicate(plansys2::Predicate("(notbusy gripper)"));
  }
  //creazione dei topic per trasmettere le posizioni al modulo di movimento
  void initializegeometrytopic(){ 
    publisher1_ = this->create_publisher<geometry_msgs::msg::PoseStamped>("/points/pickup", 10);
    publisher2_ = this->create_publisher<geometry_msgs::msg::PoseStamped>("/points/place", 10);
    publisher3_ = this->create_publisher<geometry_msgs::msg::PoseStamped>("/points/stack", 10);
    geometry_msgs::msg::PoseStamped message;
    message.header.frame_id = "map";
    message.header.stamp = now();
    message.pose.position.x = 0.0;
    message.pose.position.y = 0.0;
    message.pose.position.z = 0.0;
    message.pose.orientation.x = 0.0;
    message.pose.orientation.y = 0.0;
    message.pose.orientation.z = 0.0;
    message.pose.orientation.w = 0.0;
    publisher1_->publish(message);
    publisher2_->publish(message);
    publisher3_->publish(message);

}
  void step()
  {
    switch (state_) {
      case STARTING:
        {
          // Settaggio dell'obiettivo
          problem_expert_->setGoal(plansys2::Goal("(and "+ firstgoal+secondgoal+thirdgoal+fourthgoal+" (ontable parallelepiped1) (at parallelepiped1 destination5)(ontable parallelepiped2) (at parallelepiped2 destination6)(ontable parallelepiped3) (at parallelepiped3 destination7)(ontable parallelepiped4) (at parallelepiped4 destination8))"));
          // Calcolo del piano
          auto domain = domain_expert_->getDomain();
          auto problem = problem_expert_->getProblem();
          auto plan = planner_client_->getPlan(domain, problem);
          if (!plan.has_value()) {
            std::cout << "Could not find plan to reach goal " <<
              parser::pddl::toString(problem_expert_->getGoal()) << std::endl;
            break;
          }
          // Esecuzione del piano
          if (executor_client_->start_plan_execution(plan.value())) {
            state_ = MOVING;
          }
        }
        break;
    case MOVING:
        {
          auto feedback = executor_client_->getFeedBack();
          if (!executor_client_->execute_and_check_plan() && executor_client_->getResult()) {
            if (executor_client_->getResult().value().success) {
              std::cout << "Successful finished " << std::endl;
            }}}
            break;      
            default:
        break;
    }
  }

private:
  typedef enum {STARTING, MOVING} StateType;
  StateType state_;
  std::shared_ptr<plansys2::DomainExpertClient> domain_expert_;
  std::shared_ptr<plansys2::PlannerClient> planner_client_;
  std::shared_ptr<plansys2::ProblemExpertClient> problem_expert_;
  std::shared_ptr<plansys2::ExecutorClient> executor_client_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr piece_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr piece1_;
  rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr publisher1_;
  rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr publisher2_;
  rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr publisher3_;
};
void castle_choice (){
  for (int k=0;k<5;k++){
    if (k==0){
      color1a=("\033[0;35m");
      color2a=("\033[0m");
      color3a=("\033[0m");
      color4a=("\033[0m");  
    }
    else if (k==1){
      color2a=("\033[0;35m");
    }
    else if (k==2){
      color3a=("\033[0;35m");
    }
    else if (k==3){
      color4a=("\033[0;35m"); 
    }
    std::cout<< u8"\033[2J\033[1;1H"; 
    std::cout<<reset<< "Struttura del castello"<<std::endl;
    std::cout<<color1a<<"                        /XXXXXXX/|"<<color2a<<"                           /XXXXXXX/|"<<std::endl;
    std::cout<<color1a<<"                       /XXXXXXX/x| "<<color2a<<"                         /XXXXXXX/x|"<<std::endl;
    std::cout<<color1a<<"                      /XXXXXXX/xx|"<<color2a<<"                         /XXXXXXX/xx|"<<std::endl;
    std::cout<<color1a<<"                     |XXXXXXX|xxx|"<<color2a<<"                        |XXXXXXX|xxx|"<<std::endl;
    std::cout<<color1a<<"                     |XXXXXXX|xxx|"<<color2a<<"                        |XXXXXXX|xxx|"<<std::endl;
    std::cout<<color1a<<"                     |XXXXXXX|xxx|"<<color2a<<"                        |XXXXXXX|xxx|"<<std::endl;
    std::cout<<color1a<<"                     |XXXXXXX|xxx|"<<color2a<<"                        |XXXXXXX|xxx|"<<std::endl;
    std::cout<<color1a<<"                     |XXXXXXX|xxx/"<<green<<"zzzzzzzzzzzzzzzzzzzzzzzz"<<color2a<<"|XXXXXXX|xxx|"<<std::endl;
    std::cout<<color1a<<"                     |XXXXXXX|xx/"<<green<<"zzzzzzzzzzzzzzzzzzzzzzzzz"<<color2a<<"|XXXXXXX|xxx|"<<std::endl; 
    std::cout<<color1a<<"                     |XXXXXXX|x/"<<green<<"zzzzzzzzzzzzzzzzzzzzzzzzzz"<<color2a<<"|XXXXXXX|xxx|"<<std::endl;
    std::cout<<green<<"                    /ZZZZZZZ/|ZZZZZZZZZZZZZZZZZZZZZZZZZZZ/ZZZZZZZ/"<<color2a<<"|xxx|"<<std::endl;  
    std::cout<<green<<"                   /ZZZZZZZ/z|ZZZZZZZZZZZZZZZZZZZZZZZZZZ/ZZZZZZZ/z"<<color2a<<"|xxx|"<<std::endl;  
    std::cout<<green<<"                  /ZZZZZZZ/zz|ZZZZZZZZZZZZZZZZZZZZZZZZZ/ZZZZZZZ/zz"<<color2a<<"|xxx/"<<std::endl;
    std::cout<<green<<"                 /ZZZZZZZ/zzz|ZZZZZZZZZZZZZZZZZZZZZZZZ/ZZZZZZZ/zzz"<<color2a<<"|xx/"<<std::endl;
    std::cout<<green<<"                /ZZZZZZZ/zzzz|ZZZZZZZZZZZZZZZZZZZZZZZ/ZZZZZZZ/zzzz"<<color2a<<"|x/"<<std::endl;
    std::cout<<green<<"               /ZZZZZZZ/zzzzz|ZZZZZZZZZZZZZZZZZZZZZZ/ZZZZZZZ/zzzzz"<<color2a<<"|/"<<std::endl;
    std::cout<<green<<"              /ZZZZZZZ/zzzzzz|ZZZZZZZZZZZZZZZZZZZZZ/ZZZZZZZ/zzzzzz/"<<std::endl;
    std::cout<<green<<"             /ZZZZZZZ/zzzzzz/                     /ZZZZZZZ/zzzzzz/"<<std::endl;
    std::cout<<green<<"            /ZZZZZZZ/zzzzzz/                     /ZZZZZZZ/zzzzzz/"<<std::endl;
    std::cout<<color4a<<"   /XXXXXXX/|"<<green<<"ZZZZZZ/zzzzzz/"<<color3a<<"              /XXXXXXX/|"<<green<<"ZZZZZ/zzzzzz/"<<std::endl;
    std::cout<<color4a<<"  /XXXXXXX/x|"<<green<<"ZZZZZ/zzzzzz/"<<color3a<<"              /XXXXXXX/x|"<<green<<"ZZZZ/zzzzzz/"<<std::endl;
    std::cout<<color4a<<" /XXXXXXX/xx|"<<green<<"ZZZZ/zzzzzz/"<<color3a<<"              /XXXXXXX/xx|"<<green<<"ZZZ/zzzzzz/"<<std::endl;
    std::cout<<color4a<<"|XXXXXXX|xxx|"<<green<<"ZZZ/zzzzzz/"<<color3a<<"              |XXXXXXX|xxx|"<<green<<"ZZ/zzzzzz/"<<std::endl;
    std::cout<<color4a<<"|XXXXXXX|xxx|"<<green<<"ZZ/zzzzzz/"<<color3a<<"               |XXXXXXX|xxx|"<<green<<"Z/zzzzzz/"<<std::endl;
    std::cout<<color4a<<"|XXXXXXX|xxx|"<<green<<"Z/zzzzzz/"<<color3a<<"                |XXXXXXX|xxx|"<<green<<"/zzzzzz/"<<std::endl;
    std::cout<<color4a<<"|XXXXXXX|xxx/"<<green<<"zzzzzzzzzzzzzzzzzzzzzzzzz"<<color3a<<"|XXXXXXX|xxx|"<<green<<"zzzzzz/"<<std::endl;
    std::cout<<color4a<<"|XXXXXXX|xx/"<<green<<"zzzzzzzzzzzzzzzzzzzzzzzzzz"<<color3a<<"|XXXXXXX|xxx|"<<green<<"zzzzz/"<<std::endl;
    std::cout<<color4a<<"|XXXXXXX|x/"<<green<<"zzzzzzzzzzzzzzzzzzzzzzzzzzz"<<color3a<<"|XXXXXXX|xxx|"<<green<<"zzzz/"<<std::endl;
    std::cout<<color4a<<"|XXXXXXX|"<<green<<"ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"<<color3a<<"|XXXXXXX|xxx|"<<green<<"zzz/"<<std::endl;
    std::cout<<color4a<<"|XXXXXXX|"<<green<<"ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"<<color3a<<"|XXXXXXX|xxx|"<<green<<"zz/"<<std::endl; 
    std::cout<<color4a<<"|XXXXXXX|"<<green<<"ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"<<color3a<<"|XXXXXXX|xxx|"<<green<<"z/"<<std::endl;
    std::cout<<color4a<<"|XXXXXXX|"<<green<<"ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"<<color3a<<"|XXXXXXX|xxx|"<<green<<"/"<<std::endl; 
    std::cout<<color4a<<"|XXXXXXX|"<<green<<"ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"<<color3a<<"|XXXXXXX|xxx/"<<std::endl;  
    std::cout<<color4a<<"|XXXXXXX|"<<green<<"ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"<<color3a<<"|XXXXXXX|xx/"<<std::endl;
    std::cout<<color4a<<"|XXXXXXX|"<<green<<"ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"<<color3a<<"|XXXXXXX|x/"<<std::endl;
    std::cout<<color4a<<"|XXXXXXX|"<<green<<"ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"<<color3a<<"|XXXXXXX|/"<<std::endl;  
    std::cout<<""<<std::endl;  
    std::cout<<reset<<"Di che colore ("<<yellow<<"giallo"<<reset<<","<<red<<" rosso"<<reset<<" o"<<cyan<<" blu"<<reset<<") devono essere i cubi che compongono la torre evidenziata di "<<purple<<"viola"<<reset<<"?"<<std::endl;
    if (k==0){
      std::cin>>color[k];
      if (color[k]=="giallo"){
        color1a=("\033[1;33m");
        firstgoal="(on yellowcube"+ std::to_string(y+=2)+" yellowcube"+ std::to_string(y+1)+") (at yellowcube"+std::to_string(y+1)+" destination1)";
      }
      else if (color[k]=="rosso"){
        color1a=("\033[0;31m");
        firstgoal="(on redcube"+ std::to_string(r+=2)+" redcube"+ std::to_string(r+1)+") (at redcube"+std::to_string(r+1)+" destination1)";
      }
      else if (color[k]=="blu"){
        color1a=("\033[0;36m");
        firstgoal="(on bluecube"+ std::to_string(b+=2)+" bluecube"+ std::to_string(b+1)+") (at bluecube"+std::to_string(b+1)+" destination1)";
      }
      else{
        std::cout<<red<<"Errore, è stato inserito un colore non disponibile"<<std::endl;
        exit(1);
      }
    }
    else if (k==1){
      std::cin>>color[k];
      if (color[k]=="giallo"){
        color2a=("\033[1;33m");
        secondgoal="(on yellowcube"+ std::to_string(y+=2)+" yellowcube"+ std::to_string(y+1)+") (at yellowcube"+std::to_string(y+1)+" destination2)";
      }
      else if (color[k]=="rosso"){
        color2a=("\033[0;31m");
        secondgoal="(on redcube"+ std::to_string(r+=2)+" redcube"+ std::to_string(r+1)+") (at redcube"+std::to_string(r+1)+" destination2)";
      }
      else if (color[k]=="blu"){
        color2a=("\033[0;36m");
        secondgoal="(on bluecube"+ std::to_string(b+=2)+" bluecube"+ std::to_string(b+1)+") (at bluecube"+std::to_string(b+1)+" destination2)";
      }
      else{
        std::cout<<red<<"Errore, è stato inserito un colore non disponibile"<<std::endl;
        exit(1);
      }
    }
    else if (k==2){
      std::cin>>color[k]; 
      if (color[k]=="giallo"){
        color3a=("\033[1;33m");
        thirdgoal="(on yellowcube"+ std::to_string(y+=2)+" yellowcube"+ std::to_string(y+1)+") (at yellowcube"+std::to_string(y+1)+" destination3)";
      }
      else if (color[k]=="rosso"){
        color3a=("\033[0;31m");
        thirdgoal="(on redcube"+ std::to_string(r+=2)+" redcube"+ std::to_string(r+1)+") (at redcube"+std::to_string(r+1)+" destination3)";
      }
      else if (color[k]=="blu"){
        color3a=("\033[0;36m");
        thirdgoal="(on bluecube"+ std::to_string(b+=2)+" bluecube"+ std::to_string(b+1)+") (at bluecube"+std::to_string(b+1)+" destination3)";
      }
      else{
        std::cout<<red<<"Errore, è stato inserito un colore non disponibile"<<std::endl;
        exit(1);
      }
    }
    else if (k==3){
      std::cin>>color[k];  
      if (color[k]=="giallo"){
        color4a=("\033[1;33m");
        fourthgoal="(on yellowcube"+ std::to_string(y+=2)+" yellowcube"+ std::to_string(y+1)+") (at yellowcube"+std::to_string(y+1)+" destination4)";
      }
      else if (color[k]=="rosso"){
        color4a=("\033[0;31m");
        fourthgoal="(on redcube"+ std::to_string(r+=2)+" redcube"+ std::to_string(r+1)+") (at redcube"+std::to_string(r+1)+" destination4)";
      }
      else if (color[k]=="blu"){
        color4a=("\033[0;36m");
        fourthgoal="(on bluecube"+ std::to_string(b+=2)+" bluecube"+ std::to_string(b+1)+") (at bluecube"+std::to_string(b+1)+" destination4)";
      }
      else{
        std::cout<<red<<"Errore, è stato inserito un colore non disponibile"<<std::endl;
        exit(1);
      }
    }
    else if (k==4){
      std::cout<< u8"\033[2J\033[1;1H"; 
      std::cout<<"Struttura del castello"<<std::endl<<std::endl<<std::endl;
      std::cout<<color1a<<"                        /XXXXXXX/|"<<color2a<<"                           /XXXXXXX/|"<<std::endl;
      std::cout<<color1a<<"                       /XXXXXXX/x| "<<color2a<<"                         /XXXXXXX/x|"<<std::endl;
      std::cout<<color1a<<"                      /XXXXXXX/xx|"<<color2a<<"                         /XXXXXXX/xx|"<<std::endl;
      std::cout<<color1a<<"                     |XXXXXXX|xxx|"<<color2a<<"                        |XXXXXXX|xxx|"<<std::endl;
      std::cout<<color1a<<"                     |XXXXXXX|xxx|"<<color2a<<"                        |XXXXXXX|xxx|"<<std::endl;
      std::cout<<color1a<<"                     |XXXXXXX|xxx|"<<color2a<<"                        |XXXXXXX|xxx|"<<std::endl;
      std::cout<<color1a<<"                     |XXXXXXX|xxx|"<<color2a<<"                        |XXXXXXX|xxx|"<<std::endl;
      std::cout<<color1a<<"                     |XXXXXXX|xxx/"<<green<<"zzzzzzzzzzzzzzzzzzzzzzzz"<<color2a<<"|XXXXXXX|xxx|"<<std::endl;
      std::cout<<color1a<<"                     |XXXXXXX|xx/"<<green<<"zzzzzzzzzzzzzzzzzzzzzzzzz"<<color2a<<"|XXXXXXX|xxx|"<<std::endl; 
      std::cout<<color1a<<"                     |XXXXXXX|x/"<<green<<"zzzzzzzzzzzzzzzzzzzzzzzzzz"<<color2a<<"|XXXXXXX|xxx|"<<std::endl;
      std::cout<<green<<"                    /ZZZZZZZ/|ZZZZZZZZZZZZZZZZZZZZZZZZZZZ/ZZZZZZZ/"<<color2a<<"|xxx|"<<std::endl;  
      std::cout<<green<<"                   /ZZZZZZZ/z|ZZZZZZZZZZZZZZZZZZZZZZZZZZ/ZZZZZZZ/z"<<color2a<<"|xxx|"<<std::endl;  
      std::cout<<green<<"                  /ZZZZZZZ/zz|ZZZZZZZZZZZZZZZZZZZZZZZZZ/ZZZZZZZ/zz"<<color2a<<"|xxx/"<<std::endl;
      std::cout<<green<<"                 /ZZZZZZZ/zzz|ZZZZZZZZZZZZZZZZZZZZZZZZ/ZZZZZZZ/zzz"<<color2a<<"|xx/"<<std::endl;
      std::cout<<green<<"                /ZZZZZZZ/zzzz|ZZZZZZZZZZZZZZZZZZZZZZZ/ZZZZZZZ/zzzz"<<color2a<<"|x/"<<std::endl;
      std::cout<<green<<"               /ZZZZZZZ/zzzzz|ZZZZZZZZZZZZZZZZZZZZZZ/ZZZZZZZ/zzzzz"<<color2a<<"|/"<<std::endl;
      std::cout<<green<<"              /ZZZZZZZ/zzzzzz|ZZZZZZZZZZZZZZZZZZZZZ/ZZZZZZZ/zzzzzz/"<<std::endl;
      std::cout<<green<<"             /ZZZZZZZ/zzzzzz/                     /ZZZZZZZ/zzzzzz/"<<std::endl;
      std::cout<<green<<"            /ZZZZZZZ/zzzzzz/                     /ZZZZZZZ/zzzzzz/"<<std::endl;
      std::cout<<color4a<<"   /XXXXXXX/|"<<green<<"ZZZZZZ/zzzzzz/"<<color3a<<"              /XXXXXXX/|"<<green<<"ZZZZZ/zzzzzz/"<<std::endl;
      std::cout<<color4a<<"  /XXXXXXX/x|"<<green<<"ZZZZZ/zzzzzz/"<<color3a<<"              /XXXXXXX/x|"<<green<<"ZZZZ/zzzzzz/"<<std::endl;
      std::cout<<color4a<<" /XXXXXXX/xx|"<<green<<"ZZZZ/zzzzzz/"<<color3a<<"              /XXXXXXX/xx|"<<green<<"ZZZ/zzzzzz/"<<std::endl;
      std::cout<<color4a<<"|XXXXXXX|xxx|"<<green<<"ZZZ/zzzzzz/"<<color3a<<"              |XXXXXXX|xxx|"<<green<<"ZZ/zzzzzz/"<<std::endl;
      std::cout<<color4a<<"|XXXXXXX|xxx|"<<green<<"ZZ/zzzzzz/"<<color3a<<"               |XXXXXXX|xxx|"<<green<<"Z/zzzzzz/"<<std::endl;
      std::cout<<color4a<<"|XXXXXXX|xxx|"<<green<<"Z/zzzzzz/"<<color3a<<"                |XXXXXXX|xxx|"<<green<<"/zzzzzz/"<<std::endl;
      std::cout<<color4a<<"|XXXXXXX|xxx/"<<green<<"zzzzzzzzzzzzzzzzzzzzzzzzz"<<color3a<<"|XXXXXXX|xxx|"<<green<<"zzzzzz/"<<std::endl;
      std::cout<<color4a<<"|XXXXXXX|xx/"<<green<<"zzzzzzzzzzzzzzzzzzzzzzzzzz"<<color3a<<"|XXXXXXX|xxx|"<<green<<"zzzzz/"<<std::endl;
      std::cout<<color4a<<"|XXXXXXX|x/"<<green<<"zzzzzzzzzzzzzzzzzzzzzzzzzzz"<<color3a<<"|XXXXXXX|xxx|"<<green<<"zzzz/"<<std::endl;
      std::cout<<color4a<<"|XXXXXXX|"<<green<<"ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"<<color3a<<"|XXXXXXX|xxx|"<<green<<"zzz/"<<std::endl;
      std::cout<<color4a<<"|XXXXXXX|"<<green<<"ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"<<color3a<<"|XXXXXXX|xxx|"<<green<<"zz/"<<std::endl; 
      std::cout<<color4a<<"|XXXXXXX|"<<green<<"ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"<<color3a<<"|XXXXXXX|xxx|"<<green<<"z/"<<std::endl;
      std::cout<<color4a<<"|XXXXXXX|"<<green<<"ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"<<color3a<<"|XXXXXXX|xxx|"<<green<<"/"<<std::endl; 
      std::cout<<color4a<<"|XXXXXXX|"<<green<<"ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"<<color3a<<"|XXXXXXX|xxx/"<<std::endl;  
      std::cout<<color4a<<"|XXXXXXX|"<<green<<"ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"<<color3a<<"|XXXXXXX|xx/"<<std::endl;
      std::cout<<color4a<<"|XXXXXXX|"<<green<<"ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"<<color3a<<"|XXXXXXX|x/"<<std::endl;
      std::cout<<color4a<<"|XXXXXXX|"<<green<<"ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"<<color3a<<"|XXXXXXX|/"<<std::endl;
    }
  }
}
int main(int argc, char ** argv)
{
  castle_choice();
  rclcpp::init(argc, argv);
  auto node = std::make_shared<planningModule>();
  rclcpp::Rate rate(5);
  std::cout<<reset<<"Lettura dei blocchi dal modulo di visione..."<<std::endl;
  while (id!=4) {
    rclcpp::spin_some(node);
  }
  node->initializegeometrytopic();
  rate.sleep();
  std::cout<<reset<<"Generazione del piano di risoluzione..."<<std::endl;
  node->init();
  rate.sleep();
  std::cout<<reset<<"Esecuzione del piano..."<<std::endl;
  while (rclcpp::ok()) {
    node->step();
    rate.sleep();
    rclcpp::spin_some(node->get_node_base_interface());
  }
  rclcpp::shutdown();
  return 0;
}
