class_name Night_Ninja
extends CharacterBody2D


var speed = 100
var speed_change = 10
const JUMP_VELOCITY = -400.0
var facing_right = true
var is_alive = true
@export var health = 45
var Player = null
var see_player = false

# Get the gravity from the project settings to be synced with RigidBody nodes.
var gravity = ProjectSettings.get_setting("physics/2d/default_gravity")

func _ready():
	# Set him to start walking off the start
	$AnimatedSprite2D.play("walking")

func _physics_process(delta):
	if !is_alive:
		$CollisionShape2D.disabled = true
		$Vision/CollisionShape2D.disabled = true
		$AnimatedSprite2D.play("death")
		speed = 0
	# Add the gravity.
	if not is_on_floor():
		velocity.y += gravity * delta
	
	# Behavior for the Ninja
	# If the ninja sees the player, he will speed towards them
	if see_player:
		if facing_right:
			speed = speed + speed_change
		if !facing_right:
			speed = speed - speed_change
	# If the ninja doesn't see the player, he his speed will be set
	# to normal depending on the direction
	if !see_player:
		if facing_right:
			speed = 100
		if !facing_right:
			speed = -100
	
	if !$floor_checker.is_colliding() and is_on_floor() or is_on_wall():
		flip()
	velocity.x = speed
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
func _on_vision_body_entered(body):
	Player = body
	see_player = true
func _on_vision_body_exited(body):
	Player = null
	see_player = false

# Handling Enemey Taking Damge
func take_damage(body):
	# Will be a two hit
	health = health - player.strength
	print("Ninja HP = ", health)
	$hurt.play()
	if health <= 0:
		die()
# Handling Enemy Death
func die():
	if health <= 0:
		is_alive = false
		$death.play()

# Handling attack animations
func _on_attack_body_entered(body):
	$AnimatedSprite2D.play("attack")

func _on_attack_body_exited(body):
	$AnimatedSprite2D.play("walking")
