(define (domain castle-maker)
	(:requirements :strips :typing)
	(:types
		location object robot
	)
	(:predicates
		(clear ?x - object)
		(at ?x - object ?z - location)
		(on-table ?x - object)
		(empty ?z - location)
		(holding ?x - object ?a - robot)
		(on ?x - object ?y - object)
		(free ?a - robot)
	)
	(:action pickup
		:parameters (?ob - object ?from - location ?gripper - robot)
		:precondition (and (clear ?ob) (on-table ?ob) (at ?ob ?from) (free ?gripper))
		:effect (and (holding ?ob ?gripper)
			(not (clear ?ob))
			(not (on-table ?ob))
			(empty ?from)
			(not (free ?gripper))
		)

	)

	(:action move
		:parameters (?ob - object ?from ?to - location ?gripper - robot)
		:precondition (and (holding ?ob ?gripper) (at ?ob ?from));(not (free)))
		:effect (and (holding ?ob ?gripper)
			(at ?ob ?to)
			(not (at ?ob ?from))
			(not (free ?gripper))
		)
	)

	(:action putdown
		:parameters (?ob - object ?to - location ?gripper - robot)
		:precondition (and (holding ?ob ?gripper) (at ?ob ?to) (empty ?to));(not (free)))
		:effect (and (not (holding ?ob ?gripper))
			(clear ?ob)
			(on-table ?ob)
			(at ?ob ?to)
			(not (empty ?to))
			(free ?gripper)
		)
	)

	(:action stack
		:parameters (?ob ?ob1 - object ?to - location ?gripper - robot)
		:precondition (and (holding ?ob ?gripper) (clear ?ob1) (at ?ob ?to) (at ?ob1 ?to))
		;(not (empty ?to)); (not (free)))
		:effect (and (on ?ob ?ob1)
			(clear ?ob)
			(at ?ob ?to)
			(not (clear ?ob1))
			(not (holding ?ob ?gripper))
			(free ?gripper)
		)
	)
)

(define (domain castle-maker)
	(:requirements :strips :typing :adl :durative-actions)
	(:types
		location object robot 
	)
	(:predicates
		(clear ?x - object)
		(at ?x - object ?z - location)
		(ontable ?x - object)
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
			(at start (emptyhand ?gripper))
			(at start (notbusy ?gripper))
			(at start (at ?ob ?from))
		)
		:effect (and
			(at start (not (notbusy ?gripper)))
			(at end (notbusy ?gripper))
			(at end (holding ?ob))
			(at end (at ?ob ?from))
			(at end (not (clear ?ob)))
			(at end (not (emptyhand ?gripper)))
			(at end (not (ontable ?ob)))
		)

	)

	(:durative-action putdown
		:parameters (?ob - object ?to - location ?gripper - robot )
		:duration ( = ?duration 5)
		:condition (and
			(at start (holding ?ob))
			(at start (notbusy ?gripper))
		)
		:effect (and
			(at start (not (notbusy ?gripper)))
			(at end (notbusy ?gripper))
			(at end (not (holding ?ob)))
			(at end (clear ?ob))
			(at end (ontable ?ob))
			(at end (at ?ob ?to))
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
			(at start (at ?ob1 ?to))
			(at start (notbusy ?gripper))
		)
		:effect (and
			(at start (not (notbusy ?gripper)))
			(at end (notbusy ?gripper))
			(at end (on ?ob ?ob1))
			(at end (clear ?ob))
			(at end (not (clear ?ob1)))
			(at end (not (holding ?ob)))
			(at end (emptyhand ?gripper))
		)
	)
)