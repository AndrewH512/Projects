class_name Demon
extends CharacterBody2D

# Declaring States 
enum MovementState { GROUNDED, FLYING }
var movement_state: MovementState = MovementState.GROUNDED

# The Jump and fly velocity speed
const JUMP_VELOCITY = -50.0
const FLY_VELOCITY = -100.0

# Delcaring Variables
@export var speed = 100.0
@export var health = 60
@export var knock_back: float = 100000
@export var knock_up: float = 200
var facing_right = true
var is_alive = true
# Get the gravity from the project settings to be synced with RigidBody nodes.
var gravity = ProjectSettings.get_setting("physics/2d/default_gravity")

func _ready():
	add_to_group("Mobs")
	$AnimatedSprite2D.play('walking')
	start_flying()
	$laugh.play()

func _physics_process(delta):
	# Handle movement
	match movement_state:
		MovementState.GROUNDED:
			handle_ground_movement(delta)
		MovementState.FLYING:
			handle_flying_movement(delta)
	 # Handle jump
	if movement_state == MovementState.GROUNDED and is_on_floor():
		jump()
	# Handle gravity
	if movement_state == MovementState.GROUNDED and !is_on_floor():
		velocity.y += gravity * delta

	# Handles Enemy Death
	if !is_alive:
		$AnimatedSprite2D.play("death")
		$CollisionShape2D.disabled = true
		movement_state == MovementState.GROUNDED
		speed = 0

	# Add the gravity.
	if not is_on_floor():
		velocity.y += gravity * delta
	
	# Check if demon is colliding with a ceiling
	if movement_state == MovementState.FLYING and is_on_ceiling():
		$AnimatedSprite2D.play('walking')
		stop_flying()
	
	# Check if demon is colliding with a ceiling
	if movement_state == MovementState.GROUNDED and is_on_floor():
		$AnimatedSprite2D.play('walking')
		start_flying()
	
	if !$floor_checker.is_colliding() && is_on_wall():
		flip()
	
	velocity.x = -speed
	move_and_slide()

## Flips the mob so he doesn't fall off the edge
func flip():
	facing_right = !facing_right
	scale.x = abs(scale.x) * -1
	if facing_right:
		speed = abs(speed)
	else:
		speed = abs(speed) * -1

## Handle Combat
# Handling Enemey Taking Damge
func take_damage(body):
	# Will be a 4 hit
	health = health - player.strength
	$AnimatedSprite2D.play("hurt")
	print("Demon HP = ", health)
	var direction = (global_transform.origin - body.global_transform.origin).normalized()
	knockback(direction)
	if health <= 0:
		die()

## Adds knockback to the Demon
## This will only apply to the buff or boss slimes
func knockback(direction: Vector2):
	velocity = direction.normalized() * knock_back
	velocity.y = -knock_up
	move_and_slide()

# Handling Enemy Death
func die():
	if health <= 0:
		is_alive = false
		speed = 0

## Theses next functions are to handle the demon flying
func handle_ground_movement(delta):
	velocity.x = speed 

func handle_flying_movement(delta):
	# Implement AI-controlled flying behavior here
	velocity.y = FLY_VELOCITY

func jump():
	velocity.y = JUMP_VELOCITY

func start_flying():
	movement_state = MovementState.FLYING

func stop_flying():
	movement_state = MovementState.GROUNDED
