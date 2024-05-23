class_name Slime
extends CharacterBody2D


@export var speed = 30 
var facing_right = true
var is_alive = true
@export var health = 30

@export var knock_back: float = 100000
@export var knock_up: float = 200

# Get the gravity from the project settings to be synced with RigidBody nodes.
var gravity = ProjectSettings.get_setting("physics/2d/default_gravity")

func _ready():
	add_to_group("Mobs")
	var mob_types = $AnimatedSprite2D.sprite_frames.get_animation_names()
	$AnimatedSprite2D.play(mob_types[randi() % mob_types.size()])
	$slime_moving.play()
func _physics_process(delta):
	# Handling Death
	if !is_alive:
		$CollisionShape2D.disabled = true
		$slime_hitbox/CollisionShape2D.disabled = true
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

## Handle Combat
# Handling Enemey Taking Damge
func take_damage(body):
	health = health - player.strength
	print("Slime HP = ", health)
	# If health is zero, call death function
	var direction = (global_transform.origin - body.global_transform.origin).normalized()
	knockback(direction)
	if health <= 0:
		die()

## Adds knockback to the slime
## This will only apply to the buff or boss slimes
func knockback(direction: Vector2):
	velocity = direction.normalized() * knock_back
	velocity.y = -knock_up
	move_and_slide()

## Handling Enemy Death
func die():
	if health <= 0:
		is_alive = false
		# Play the death sound
		$slime_death.play()
