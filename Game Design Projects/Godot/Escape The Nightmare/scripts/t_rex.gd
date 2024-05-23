class_name T_Rex
extends CharacterBody2D



const JUMP_VELOCITY = -400.0
@export var health = 200
@export var speed = 50.0
var facing_right = true
var is_alive = true
# Get the gravity from the project settings to be synced with RigidBody nodes.
var gravity = ProjectSettings.get_setting("physics/2d/default_gravity")
@export var knock_back: float = 100000
@export var knock_up: float = 200

func _ready():
	add_to_group("Mobs")
	$AnimatedSprite2D.play('walking')

func _physics_process(delta):
	
	if !is_alive:
		$CollisionShape2D.disabled = true
		$AnimatedSprite2D.play("jump")
		speed = 0
	# Add the gravity.
	if not is_on_floor():
		velocity.y += gravity * delta
		$AnimatedSprite2D.play("walking")
	#Flips the move around when they are near a edge
	if !$floor_checker.is_colliding() && is_on_floor() || is_on_wall():
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
	health = health - player.strength
	print("Rexy HP = ", health)
	$rex_death.play()
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
		$rex_death.play()

# Handle Attack Animation
func _on_attack_body_entered(body):
	if body.is_in_group("Player"):
		$AnimatedSprite2D.play("attack")

func _on_attack_body_exited(body):
	if body.is_in_group("Player"):
		$AnimatedSprite2D.play("walking")


func _on_player_behind_body_entered(body):
	if body.is_in_group("Player"):
		flip()
