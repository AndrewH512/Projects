extends CharacterBody2D

const SPEED = 300.0
const JUMP_VELOCITY = -550.0
var is_dying = false
signal hit

# Get the gravity from the project settings to be synced with RigidBody nodes.
var gravity = ProjectSettings.get_setting("physics/2d/default_gravity")

func _ready():
	add_to_group("Player")

func _physics_process(delta):
	# Add the gravity.
	if not is_on_floor():
		velocity.y += gravity * delta
	
	if Input.is_action_pressed("ui_down") and is_on_floor():
		$AnimatedSprite2D.animation = "hunker"
		return

	# Handle jump.
	if Input.is_action_just_pressed("ui_accept") and is_on_floor():
		velocity.y = JUMP_VELOCITY
	
	# Get the input direction and handle the movement/deceleration.
	# As good practice, you should replace UI actions with custom gameplay actions.
	var direction = Input.get_axis("ui_left", "ui_right")
	if direction:
		velocity.x = direction * SPEED
	else:
		velocity.x = move_toward(velocity.x, 0, SPEED)
	
	# Player Animations
	if velocity.length() > 0:
		$AnimatedSprite2D.play()
	else:
		$AnimatedSprite2D.stop()
	
	if velocity.x != 0:
		$AnimatedSprite2D.animation = "run"
		$AnimatedSprite2D.flip_v = false
		# See the note below about boolean assignment.
		$AnimatedSprite2D.flip_h = velocity.x < 0
	elif velocity.y != 0:
		$AnimatedSprite2D.animation = "jump"
	
	if velocity.x < 0:
		$AnimatedSprite2D.flip_h = true
	else:
		$AnimatedSprite2D.flip_h = false
	
	if !Input.is_anything_pressed():
		$AnimatedSprite2D.play("idle")
	
	move_and_slide()

#Death for when player hit enemy or falls out of world
func _on_hitbox_body_entered(body):
	if body.is_in_group("Mobs") and body.is_alive:
		die()

# Handling Player Death
func die():
	if is_dying:
			return
	
	# Checking to make sure player isn't in hunker mode
	var ui_down_pressed = Input.is_action_pressed("ui_down")
	if !ui_down_pressed:
		is_dying = true
		hit.emit()
		queue_free()

