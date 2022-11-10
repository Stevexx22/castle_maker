#include <math.h>

#include <memory>
#include <string>
#include <map>
#include <algorithm>

#include "geometry_msgs/msg/pose_stamped.hpp"
#include "geometry_msgs/msg/pose.hpp"
#include "geometry_msgs/msg/pose_with_covariance_stamped.hpp"

#include "plansys2_executor/ActionExecutorClient.hpp"
#include <unistd.h>
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "std_msgs/msg/string.hpp"
using namespace std::chrono_literals;
  std::string confirm;
class StackAction : public plansys2::ActionExecutorClient
{
public:
  StackAction()
  : plansys2::ActionExecutorClient("stack", 2s)
  {
    //assegno le coordinate spaziali e le rotazioni in cui andranno posizionati i blocchi
    geometry_msgs::msg::PoseStamped p;
    p.header.frame_id = "map";
    p.header.stamp = now();
    p.pose.position.x = -0.405;
    p.pose.position.y = 0.06;
    p.pose.position.z = 1.07;
    p.pose.orientation.x = -1.0;
    p.pose.orientation.y = 0.0;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;
    waypoints_["destination1"] = p;

    p.pose.position.x = -0.48;
    p.pose.position.y = 0.06;
    p.pose.position.z = 1.07;
    p.pose.orientation.x = -1.0;
    p.pose.orientation.y = 0.0;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;    
    waypoints_["destination2"] = p;

    p.pose.position.x = -0.48;
    p.pose.position.y = 0.135;
    p.pose.position.z = 1.07;
    p.pose.orientation.x = -1.0;
    p.pose.orientation.y = 0.0;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;    
    waypoints_["destination3"] = p;

    p.pose.position.x = -0.405;
    p.pose.position.y = 0.135;
    p.pose.position.z = 1.07;
    p.pose.orientation.x = -1.0;
    p.pose.orientation.y = 0.0;
    p.pose.orientation.z = 0.0;
    p.pose.orientation.w = 0.0;    
    waypoints_["destination4"] = p;
    

    //subscription al topic in cui il nodo del movimento pubblica l'avvenuto movimento
    using namespace std::placeholders;
    confirm_ = create_subscription<std_msgs::msg::String>(
      "/confirmation_topic",
      10,
      std::bind(&StackAction::confirm_callback, this, _1));
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
    publisher_ = this->create_publisher<geometry_msgs::msg::PoseStamped>("/points/stack", 10);
    publisher_->on_activate();
    publisher1_ = this->create_publisher<std_msgs::msg::String>("/confirmation_topic", 10);
    publisher1_->on_activate();

       // while(confirm!= "SUCCESS"){
   // send_feedback(0.1, "Moving");  
   // }
    
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
auto message = std_msgs::msg::String();
message.data = "BUSY";
auto getdestination = get_arguments()[2];   // Il goal è nel quarto argomento dell'azione
    RCLCPP_INFO(get_logger(), "Go to [%s]", getdestination.c_str());
    goal_pos_ = waypoints_[getdestination]; //assegno le coordinate spaziali corrispondenti
    if (progress==0.0){
      progress+=0.05;
        publisher_->publish(goal_pos_);} //pubblico il goal
    progress+=0.05;
    send_feedback(progress, "Move starting");
      if ((confirm== "NOT BUSY")){//quando ricevo la conferma dell' avvenuto successo del movimento concludo l'azione
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
  auto node = std::make_shared<StackAction>();

  node->set_parameter(rclcpp::Parameter("action_name", "stack"));
  node->trigger_transition(lifecycle_msgs::msg::Transition::TRANSITION_CONFIGURE);

  rclcpp::spin(node->get_node_base_interface());

  rclcpp::shutdown();

  return 0;
}
