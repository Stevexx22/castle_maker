(define (domain castle-maker)
	(:requirements :strips :typing :adl :durative-actions)
	(:types
		location object robot 
	)
	(:predicates
		(clear ?x - object)
		(at ?x - object ?z - location)
		(ontable ?x - object)
		(empty ?z - location)
		(holding ?x - object)
		(on ?x - object ?y - object)
		(emptyhand ?a - robot)
		(notbusy ?a - robot)
	)
	(:durative-action pickup
		:parameters (?ob - object ?from - location ?gripper - robot )
		:duration ( = ?duration 5)
		:condition (and
			(at start (clear ?ob))
			(at start (ontable ?ob))
			(at start (at ?ob ?from))
			(at start (emptyhand ?gripper))
			(at start (notbusy ?gripper))
		)
		:effect (and
			(at start (not (notbusy ?gripper)))
			(at end (notbusy ?gripper))
			(at end (holding ?ob))
			(at end (not (clear ?ob)))
			(at end (not (emptyhand ?gripper)))
			(at end (empty ?from))
			(at end (not (ontable ?ob)))
		)

	)

	(:durative-action move
		:parameters (?ob - object ?from ?to - location ?gripper - robot )
		:duration ( = ?duration 5)
		:condition (and
			(at start (holding ?ob))
			(at start (at ?ob ?from))
			(at start (notbusy ?gripper))
		)
		:effect (and
			(at start (not (notbusy ?gripper)))
			(at end (notbusy ?gripper))
			(at end (holding ?ob))
			(at end (not (at ?ob ?from)))
			(at end (not (emptyhand ?gripper)))
			(at end (not(ontable ?ob)))
			(at end (at ?ob ?to))
		)
	)

	(:durative-action putdown
		:parameters (?ob - object ?to - location ?gripper - robot )
		:duration ( = ?duration 5)
		:condition (and
			(at start (holding ?ob))
			(at start (at ?ob ?to))
			(at start (empty ?to))
			(at start (notbusy ?gripper))
		)
		:effect (and
			(at start (not (notbusy ?gripper)))
			(at end (notbusy ?gripper))
			(at end (not (holding ?ob)))
			(at end (clear ?ob))
			(at end (ontable ?ob))
			(at end (at ?ob ?to))
			(at end (not (empty ?to)))
			(at end (emptyhand ?gripper))
		)
	)

	(:durative-action stack
		:parameters (?ob ?ob1 - object ?to - location ?gripper - robot 
		)
		:duration ( = ?duration 5)
		:condition (and
			(at start (holding ?ob))
			(at start (clear ?ob1))
			(at start (at ?ob ?to))
			(at start (at ?ob1 ?to))
			(at start (notbusy ?gripper))
		)
		:effect (and
			(at start (not (notbusy ?gripper)))
			(at end (notbusy ?gripper))
			(at end (on ?ob ?ob1))
			(at end (clear ?ob))
			(at end (at ?ob ?to))
			(at end (not (clear ?ob1)))
			(at end (not (holding ?ob)))
			(at end (emptyhand ?gripper))
		)
	)
)