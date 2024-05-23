class_name World
extends Node2D
## The point of this script is to handle changing the levels and also handling
## the death of players

## Declaring Varibles
var player_dead = false
var player_level_one_done = false
var player_level_two_done = false
var simultaneous_scene = preload("res://scences/win_menu.tscn").instantiate()

func _ready():
	$player/background.play()
	$Switch_Levels/CollisionShape2D.disabled = true

func _physics_process(delta):
	# We will use this function to handle when we should change the scenes
	# Checks to see if the player has died. If the player is dead, we change to
	# the death screen
	if player_dead:
		player.strength = 20
		get_tree().change_scene_to_file("res://scences/death_menu.tscn")
	
	# Player Finished Level 1, change to level 2
	if player_level_one_done:
		# Reset Player's Coins
		player.total_coins = 0
		get_tree().change_scene_to_file("res://scences/levels/level_2.tscn")
	
	# Player Finishes Level 2, change to win scene
	if player_level_two_done:
		get_tree().change_scene_to_file("res://scences/win_menu.tscn")
	
	# Handles the player exiting the game
	if Input.is_action_just_pressed("escape"):
		get_tree().quit()
	
	if player.total_coins == 3:
		$Switch_Levels/CollisionShape2D.disabled = false

## Handles the death of the player
func _on_player_death(health):
	print(health) # Testing
	if health <= 0:
		player_dead = true
		# Reset Player's Coins
		player.total_coins = 0

## Handles Level Switching
func _on_switch_levels_body_entered(body:PhysicsBody2D):
	# Player has reached end of level 1
	player_level_one_done = true
func _on_switch_levels_2_body_entered(body:PhysicsBody2D):
	# Player has reached end of level 2
	player_level_two_done = true
