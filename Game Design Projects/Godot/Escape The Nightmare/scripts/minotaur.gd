class_name Minotaur
extends CharacterBody2D

@export var speed = 80
@export var health = 150
const JUMP_VELOCITY = -400.0
var facing_right = true
var is_alive = true
var see_player = false

@export var knock_back: float = 100000
@export var knock_up: float = 200

# Get the gravity from the project settings to be synced with RigidBody nodes.
var gravity = ProjectSettings.get_setting("physics/2d/default_gravity")

func _ready():
	# Set him to start walking off the start
	$AnimatedSprite2D.play("walking")
	randomize_speed(30, 80)

func _physics_process(delta):
	# Handling Death
	if !is_alive:
		$AnimatedSprite2D.play("death")
		$Attack/CollisionShape2D.disabled = true
		$CollisionShape2D.disabled = true
		speed = 0
	
	# Adding Gravity
	if not is_on_floor():
		velocity.y += gravity * delta
	
	#Flips the move around when they are near a edge
	if !$floor_checker.is_colliding() && is_on_floor() || is_on_wall():
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

# Function to randomize speed within a specified range
func randomize_speed(min_speed: float, max_speed: float):
	# Generate a random speed within the specified range
	speed = randf_range(min_speed, max_speed)
	# Apply the random speed
	velocity.x = speed

## Handle Combat
# Handling Enemey Taking Damge
func take_damage(body):
	health = health - player.strength
	var direction = (global_transform.origin - body.global_transform.origin).normalized()
	knockback(direction)
	$hurt.play()
	print("Minotaur HP = ", health)
	if health <= 0:
		die()

# When hit the mintour will be knockback slightly
func knockback(direction: Vector2):
	velocity = direction.normalized() * knock_back
	velocity.y = -knock_up
	move_and_slide()

# Handling Enemy Death
func die():
	if health <= 0:
		is_alive = false

## Handling the Attack Animations
func _on_attack_body_entered(body):
	# Will Swing his axe
	$AnimatedSprite2D.play("attack")

func _on_attack_body_exited(body):
	$AnimatedSprite2D.play("walking")

func _on_hitbox_body_entered(body):
	if !body.is_in_group("Player"):
		flip()
