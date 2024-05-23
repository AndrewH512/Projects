class_name Red_Smile
extends CharacterBody2D

# Declare Variables
const JUMP_VELOCITY = -400.0
var facing_right = true
var is_alive = true
var see_player = false
var jump_scared = false
@export var speed = 100
@export var health = 175

# Knockback Variables
@export var knock_back: float = 100000
@export var knock_up: float = 200
# Get the gravity from the project settings to be synced with RigidBody nodes.
var gravity = ProjectSettings.get_setting("physics/2d/default_gravity")

# On game Startup
func _ready():
	add_to_group("Mobs")
	$AnimatedSprite2D.play("running")
	# He starts invisble to the player
	hide()

func _physics_process(delta):
	# Handles the smile's death
	if !is_alive:
		$CollisionShape2D.disabled = true
		$AnimatedSprite2D.play("death")
		speed = 0
	
	# Speeds up if he sees the player
	# Slows down to normal speed if he doesn't see player
	if see_player:
		if facing_right:
			speed = speed + 10
		else:
			speed = speed - 10
	else:
		if facing_right:
			speed = 100
		else: 
			speed = -100
	
	# Add the gravity.
	if not is_on_floor():
		velocity.y += gravity * delta
	#Flips the move around when they are near a edge
	if !$floor_checker.is_colliding() && is_on_floor() || is_on_wall():
		flip()
	
	# Move
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

## When he see's a player, he will be visible again
func _on_player_detection_front_body_entered(body):
	if body.is_in_group("Player"):
		show()
		see_player = true
		# Only play the jump scare sound once
		if jump_scared == false:
			$run.play()
			jump_scared = true
## When he doesn't see a player, he will hide
func _on_player_detection_front_body_exited(body):
	if body.is_in_group("Player"):
		# Hide from player
		hide()
		see_player = false
		jump_scared = false

## Handle Combat
# Handling Enemey Taking Damge
func take_damage(body):
	health = health - player.strength
	print("Red Smile HP = ", health)
	# If health is zero, call death function
	if health <= 0:
		die()

## Handling Enemy Death
func die():
	if health <= 0:
		is_alive = false
