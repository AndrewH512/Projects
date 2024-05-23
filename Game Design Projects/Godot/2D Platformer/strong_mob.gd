extends CharacterBody2D


var speed = 200 # 
var facing_right = true
var player_chase = false
var player = null
var is_alive = true

# Get the gravity from the project settings to be synced with RigidBody nodes.
var gravity = ProjectSettings.get_setting("physics/2d/default_gravity")

# Called when the node enters the scene tree for the first time.
func _ready():
	add_to_group("StrongMob")
	var mob_types = $AnimatedSprite2D.sprite_frames.get_animation_names()
	$AnimatedSprite2D.play(mob_types[randi() % mob_types.size()])


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _physics_process(delta):
	if not is_on_floor():
		velocity.y += gravity * delta
	
	# Chase the player
	if player_chase:
		position += (player.position - position)/100
	
	if !player_chase:#Flips the move around when they are near a edge
		if !$floor_checker.is_colliding() && is_on_floor() || is_on_wall():
			flip()
	
	velocity.x = speed
	move_and_slide()

# Player has enter the view of the mob, mob will speed up
func _on_detection_area_body_entered(body):
	player = body
	player_chase = true

# Player has exited the view of the mob, mob will go back to normal speed
func _on_detection_area_body_exited(body):
	player = null
	player_chase = false

# Flips the mob so he doesn't fall off the edge
func flip():
	facing_right = !facing_right
	
	scale.x = abs(scale.x) * -1
	if facing_right:
		speed = abs(speed)
	else:
		speed = abs(speed) * -1



