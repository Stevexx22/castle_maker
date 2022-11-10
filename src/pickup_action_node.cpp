#include <math.h>

#include <memory>
#include <string>
#include <map>
#include <algorithm>

#include "geometry_msgs/msg/pose_stamped.hpp"
#include "geometry_msgs/msg/pose.hpp"
#include "geometry_msgs/msg/pose_with_covariance_stamped.hpp"
#include <unistd.h>
#include "plansys2_executor/ActionExecutorClient.hpp"
#include "std_msgs/msg/string.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
std::string confirm;
using namespace std::chrono_literals;
int i=0;
class PickupAction : public plansys2::ActionExecutorClient
{
public:
  PickupAction()
  : plansys2::ActionExecutorClient("pickup", 2s)
  {
    //assegno le coordinate spaziali e le rotazioni dei blocchi presenti in ogni posizione del buffer
    geometry_msgs::msg::PoseStamped p;
    p.header.frame_id = "map";
    p.header.stamp = now();
    p.pose.position.x = 0.45;
    p.pose.position.y = 0.4;
    p.pose.position.z = 1.02;
    p.pose.orientation.x = -1.0;
    p.pose.orientation.y = 0.0;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;
    waypoints_["position1"] = p;

    p.pose.position.x = 0.45;
    p.pose.position.y = 0.355;
    p.pose.position.z = 1.02;
    p.pose.orientation.x = -1.0;
    p.pose.orientation.y = 0.0;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;
    waypoints_["position2"] = p;

    p.pose.position.x = 0.45;
    p.pose.position.y = 0.31;
    p.pose.position.z = 1.02;
    p.pose.orientation.x = -1.0;
    p.pose.orientation.y = 0.0;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;
    waypoints_["position3"] = p;

    p.pose.position.x = 0.45;
    p.pose.position.y = 0.265;
    p.pose.position.z = 1.02;
    p.pose.orientation.x = -1.0;
    p.pose.orientation.y = 0.0;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;
    waypoints_["position4"] = p;

    p.pose.position.x = 0.45;
    p.pose.position.y = 0.22;
    p.pose.position.z = 1.02;
    p.pose.orientation.x = -1.0;
    p.pose.orientation.y = 0.0;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;
    waypoints_["position5"] = p;

    p.pose.position.x = 0.45;
    p.pose.position.y = 0.175;
    p.pose.position.z = 1.02;
    p.pose.orientation.x = -1.0;
    p.pose.orientation.y = 0.0;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;
    waypoints_["position6"] = p;

    p.pose.position.x = 0.45;
    p.pose.position.y = 0.13;
    p.pose.position.z = 1.02;
    p.pose.orientation.x = -1.0;
    p.pose.orientation.y = 0.0;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;
    waypoints_["position7"] = p;

    p.pose.position.x = 0.45;
    p.pose.position.y = 0.085;
    p.pose.position.z = 1.02;
    p.pose.orientation.x = -1.0;
    p.pose.orientation.y = 0.0;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;
    waypoints_["position8"] = p; 

    p.pose.position.x = 0.45;
    p.pose.position.y = 0.04;
    p.pose.position.z = 1.02;
    p.pose.orientation.x = -1.0;
    p.pose.orientation.y = 0.0;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;
    waypoints_["position9"] = p;

    p.pose.position.x = 0.45;
    p.pose.position.y = -0.005;
    p.pose.position.z = 1.02;
    p.pose.orientation.x = -1.0;
    p.pose.orientation.y = 0.0;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;
    waypoints_["position10"] = p;
   
    p.pose.position.x = 0.37;
    p.pose.position.y = 0.4;
    p.pose.position.z = 1.02;
    p.pose.orientation.x = -1.0;
    p.pose.orientation.y = 0.0;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;
    waypoints_["position11"] = p;

    p.pose.position.x = 0.37;
    p.pose.position.y = 0.355;
    p.pose.position.z = 1.02;
    p.pose.orientation.x = -1.0;
    p.pose.orientation.y = 0.0;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;
    waypoints_["position12"] = p;

    p.pose.position.x = 0.37;
    p.pose.position.y = 0.31;
    p.pose.position.z = 1.02;
    p.pose.orientation.x = -1.0;
    p.pose.orientation.y = 0.0;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;
    waypoints_["position13"] = p;

    p.pose.position.x = 0.37;
    p.pose.position.y = 0.265;
    p.pose.position.z = 1.02;
    p.pose.orientation.x = -1.0;
    p.pose.orientation.y = 0.0;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;
    waypoints_["position14"] = p;

    p.pose.position.x = 0.37;
    p.pose.position.y = 0.22;
    p.pose.position.z = 1.02;
    p.pose.orientation.x = -1.0;
    p.pose.orientation.y = 0.0;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;
    waypoints_["position15"] = p;

    p.pose.position.x = 0.37;
    p.pose.position.y = 0.175;
    p.pose.position.z = 1.02;
    p.pose.orientation.x = -1.0;
    p.pose.orientation.y = 0.0;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;
    waypoints_["position16"] = p;

    p.pose.position.x = 0.37;
    p.pose.position.y = 0.13;
    p.pose.position.z = 1.02;
    p.pose.orientation.x = -1.0;
    p.pose.orientation.y = 0.0;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;
    waypoints_["position17"] = p;

    p.pose.position.x = 0.37;
    p.pose.position.y = 0.085;
    p.pose.position.z = 1.02;
    p.pose.orientation.x = -1.0;
    p.pose.orientation.y = 0.0;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;
    waypoints_["position18"] = p; 

    p.pose.position.x = 0.37;
    p.pose.position.y = 0.04;
    p.pose.position.z = 1.02;
    p.pose.orientation.x = -1.0;
    p.pose.orientation.y = 0.0;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;
    waypoints_["position19"] = p;
    
    p.pose.position.x = 0.37;
    p.pose.position.y = -0.005;
    p.pose.position.z = 1.02;
    p.pose.orientation.x = -1.0;
    p.pose.orientation.y = 0.0;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;
    waypoints_["position20"] = p;

    p.pose.position.x = 0.29;
    p.pose.position.y = 0.395;
    p.pose.position.z = 1.02;
    p.pose.orientation.x = -0.7;
    p.pose.orientation.y = 0.7;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;
    waypoints_["position21"] = p;

    p.pose.position.x = 0.29;
    p.pose.position.y = 0.325;
    p.pose.position.z = 1.02;
    p.pose.orientation.x = -0.7;
    p.pose.orientation.y = 0.7;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;
    waypoints_["position22"] = p;

    p.pose.position.x = 0.29;
    p.pose.position.y = 0.255;
    p.pose.position.z = 1.02;
    p.pose.orientation.x = -0.7;
    p.pose.orientation.y = 0.7;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;
    waypoints_["position23"] = p;    

    p.pose.position.x = 0.29;
    p.pose.position.y = 0.185;
    p.pose.position.z = 1.02;
    p.pose.orientation.x = -0.7;
    p.pose.orientation.y = 0.7;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;
    waypoints_["position24"] = p;

    p.pose.position.x = 0.29;
    p.pose.position.y = 0.115;
    p.pose.position.z = 1.02;
    p.pose.orientation.x = -0.7;
    p.pose.orientation.y = 0.7;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;
    waypoints_["position25"] = p;

    p.pose.position.x = 0.29;
    p.pose.position.y = 0.045;
    p.pose.position.z = 1.02;
    p.pose.orientation.x = -0.7;
    p.pose.orientation.y = 0.7;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;
    waypoints_["position26"] = p;
    
    p.pose.position.x = 0.29;
    p.pose.position.y = -0.025;
    p.pose.position.z = 1.02;
    p.pose.orientation.x = -0.7;
    p.pose.orientation.y = 0.7;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;
    waypoints_["position27"] = p;



    //subscription al topic in cui il nodo del movimento pubblica l'avvenuto movimento
    using namespace std::placeholders;
    confirm_ = create_subscription<std_msgs::msg::String>(
      "/confirmation_topic",
      10,
      std::bind(&PickupAction::confirm_callback, this, _1));
  }

  void confirm_callback(const std_msgs::msg::String::SharedPtr msg)
  {
    confirm = msg->data;
  }
  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_activate(const rclcpp_lifecycle::State & previous_state)
  {
    progress = 0.0;
     //creazione del publisher sul topic che verrà letto dal nodo del movimento
    publisher_ = this->create_publisher<geometry_msgs::msg::PoseStamped>("/points/pickup", 10);
    publisher_->on_activate();
    publisher1_ = this->create_publisher<std_msgs::msg::String>("/confirmation_topic", 10);
    publisher1_->on_activate();

    return ActionExecutorClient::on_activate(previous_state);
  }
  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
   on_deactivate(const rclcpp_lifecycle::State & previous_state)
   {
     publisher_->on_deactivate();
    publisher1_->on_deactivate();
     return ActionExecutorClient::on_deactivate(previous_state);
   }
    void do_work()
  {
auto getdestination = get_arguments()[1];  // Il goal è nel terzo argomento dell'azione
auto message = std_msgs::msg::String();
message.data = "BUSY";
    RCLCPP_INFO(get_logger(), "Go to [%s]", getdestination.c_str());
    goal_pos_ = waypoints_[getdestination]; //assegno le coordinate spaziali corrispondenti
    if (progress==0.0){
      progress+=0.05;
        publisher_->publish(goal_pos_);} //pubblico il goal
    progress+=0.05;
    send_feedback(progress, "Move starting");
    //if ((confirm== "NOT BUSY")&&(progress>1.0)){
      if ((confirm== "NOT BUSY")){ //quando ricevo la conferma dell' avvenuto successo del movimento concludo l'azione
            publisher1_->publish(message);
            finish(true, 1.0, "Move completed");}
  }
   float progress;


  std::map<std::string, geometry_msgs::msg::PoseStamped> waypoints_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr confirm_;
  geometry_msgs::msg::PoseStamped goal_pos_;
  rclcpp_lifecycle::LifecyclePublisher<geometry_msgs::msg::PoseStamped>::SharedPtr publisher_;
  rclcpp_lifecycle::LifecyclePublisher<std_msgs::msg::String>::SharedPtr publisher1_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<PickupAction>();

  node->set_parameter(rclcpp::Parameter("action_name", "pickup"));
  node->trigger_transition(lifecycle_msgs::msg::Transition::TRANSITION_CONFIGURE);

  rclcpp::spin(node->get_node_base_interface());

  rclcpp::shutdown();

  return 0;
}
