class_name Player
extends CharacterBody2D

# This is for the health bar
signal healthChanged
# This signal death to world script
signal death
# This signals to hud about how about fly jumps the player has left
signal fly_counts
# Signal to nofity the hud about the force field
signal force_field_hud

# Declaring Varibles
@export var SPEED = 300.0
var JUMP_VELOCITY = -450.0
const UP = Vector2.UP
@export var coin_total = 0
@export var health = 100
@onready var currentHealth: int = health
# Set up for knockback
@export var knock_back: float = 3000
@export var knock_up: float = 500

# Give Player Acess to invetory NOTE: This did not make the final game
@export var inv: Inv

# Pickup Variables
# For Flying Pickup
var is_flying = false
var flyCount = 5
const MAX_FLY_COUNT = 0
# Variables for Force Field Pickup
var have_force_field = false
var using_shield = false

# Get the gravity from the project settings to be synced with RigidBody nodes.
var gravity = ProjectSettings.get_setting("physics/2d/default_gravity")
var simultaneous_scene = preload("res://scences/death_menu.tscn").instantiate()

func _ready():
	add_to_group("Player")
	# Start by playing the idle animation since player is not moving
	$AnimatedSprite2D.play("idle")
	# Hide the Force Field for now too
	$Shield.hide()
func _physics_process(delta):
	# Add the gravity.
	if not is_on_floor():
		velocity.y += gravity * delta

	# Handle jump.
	if Input.is_action_just_pressed("jump") and is_on_floor():
		if is_flying == true:
			flyCount -= 1
			fly_counts.emit(flyCount)
			print(flyCount)
			if flyCount == MAX_FLY_COUNT:
				stop_fly()
		velocity.y = JUMP_VELOCITY
	# This is to handle the input for the force field
	if have_force_field == true:
		if Input.is_action_pressed("force_field") and is_on_floor():
			$AnimatedSprite2D.play("crouch") 
			# Show Shield
			$Shield.show()
			using_shield = true
			print("here")
		else:
			# Hide Shield
			using_shield = false
			$Shield.hide()

	# Get the input direction and handle the movement/deceleration.
	# As good practice, you should replace UI actions with custom gameplay actions.
	var direction = Input.get_axis("left", "right")
	if direction:
		velocity.x = direction * SPEED
	else:
		velocity.x = move_toward(velocity.x, 0, SPEED)
	
	# Handling Combat Inputs
	# You must be standing still to swing your sword
	if Input.is_mouse_button_pressed(1) and is_on_floor() and velocity.x == 0 and !using_shield:
		$player_hitbox/CollisionShape2D.disabled = false
		$AnimatedSprite2D.play("attack")
		# Play the swing sound effect
		$Sword_Swing.play()
	else:
		# Disable hitbox for combat
		$player_hitbox/CollisionShape2D.disabled = true
	
	# Handling Animations
	if velocity.x != 0 :
		$AnimatedSprite2D.animation = "running"
		$AnimatedSprite2D.flip_v = false
		# See the note below about boolean assignment.
		$AnimatedSprite2D.flip_h = velocity.x < 0
	elif velocity.y != 0 and !is_on_floor():
		$AnimatedSprite2D.animation = "jumping"
	
	# If the player is not moving and not attacking, set idle animation
	if velocity.x == 0 and velocity.y == 0 and !Input.is_mouse_button_pressed(1) and !Input.is_action_just_pressed("force_field"):
		$AnimatedSprite2D.animation = "idle"
		 # Face left if previously moving left, otherwise face right
		$AnimatedSprite2D.flip_h = $AnimatedSprite2D.flip_h if velocity.x == 0 else velocity.x < 0
	
	# This if statement flip the hitbox for the player's sword. So say the player is facing to the right
	# The player can hit things on the right if they are facing there
	if $AnimatedSprite2D.flip_h:  # If facing left
		$player_hitbox.position.x = 0  # Offset to the left
	else:
		$player_hitbox.position.x = 70  # Offset to the right
	
	# If playing is not using shield, they will be able to move
	if not using_shield:
		move_and_slide()

## Handling Combat
## Checks to see if there is an enemy within the hitbox for the sword
func _on_player_hitbox_body_entered(body):
	print("an hit enemy") # Testing
	if body.is_in_group("Enemy"):
		body.take_damage(body)

## This will enable the player to get knockedback when hit
func knockback(direction: Vector2):
	velocity = direction.normalized() * knock_back
	velocity.y = -knock_up
	move_and_slide()

# Basic Death System for now, will update
# Player right takes the same amount of damage from every mob
func _on_damage_hitbox_body_entered(body):
	if body.is_in_group("Enemy"):
			# Player will not take damage if holding shield
			if !using_shield:
				# Knockback
				var direction = (global_transform.origin - body.global_transform.origin).normalized()
				knockback(direction)
				# Player takes damage
				health = health - 35
				# Play hurt sound
				$Hurt_Sound.play()
				# This is for the hud, signals to the hub
				healthChanged.emit(health)
				death.emit(health)

# Collection Function For Inventory
# This did not make the final version of the game
func collect(item):
	inv.insert(item)

## Next functions will handle item pickups for the player
## This for the item pick for health
## This will give the player more health
func more_health(body):
	if health <= 200:
		health = health + 34
		healthChanged.emit(health)
	# This is so it caps the player health at 200 in case it goes over
	if health > 200:
		health = 200

## This on pickup will give the player more strength
func more_strength(body):
	player.strength = player.strength + 20

## Pickup that gives the player more speed
func more_speed(body):
	SPEED = SPEED + 30
	print(SPEED)

## This pickup gives the player the ability to fly
func fly(body):
	is_flying = true
	JUMP_VELOCITY = -600.0
	# Reduce gravity to simulate floating
	gravity = gravity / 2
	print(flyCount)
## After using the jump five times, the player's physics will reset
func stop_fly():
	is_flying = false
	JUMP_VELOCITY = -450.0
	gravity = ProjectSettings.get_setting("physics/2d/default_gravity")
	flyCount = 5

## This is handle the force field pickup, signals to hud also.
func force_field(body):
	have_force_field = true
	force_field_hud.emit()
