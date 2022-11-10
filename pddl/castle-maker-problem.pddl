(define (problem castle-maker-problem)
  (:domain castle-maker)
  (:objects
    cube1 cube2 cube3 parallelepiped1 parallelepiped2 parallelepiped3 - object
    position1 position2 position3 position4 position5 position6 destination1 destination2 destination3 - location
    gripper - robot
  )
  (:init
    (ontable cube1)
    (ontable cube2)
    (ontable cube3)
    (ontable parallelepiped1)
    (ontable parallelepiped2)
    (ontable parallelepiped3)
    (clear cube1)
    (clear cube2)
    (clear cube3)
    (clear parallelepiped1)
    (clear parallelepiped2)
    (clear parallelepiped3)
    (at cube1 position1)
    (at cube2 position2)
    (at cube3 position3)
    (at parallelepiped1 position4)
    (at parallelepiped2 position5)
    (at parallelepiped3 position6)
    (emptyhand gripper)
    (notbusy gripper)
  )
  (:goal
    (and (at parallelepiped2 destination2) (on cube1 parallelepiped1) (at parallelepiped1 destination1)
      (on cube3 cube2) (on cube2 parallelepiped3) (at parallelepiped3 destination3))
  )
)