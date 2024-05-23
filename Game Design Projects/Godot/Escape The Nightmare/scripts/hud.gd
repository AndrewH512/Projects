class_name Hud
extends Control

# Variables for Timer
@onready var label = $Label
@onready var timer = $Timer

func _ready():
	# Start the timer on game startup
	timer.start()
	$Gate.text ="Gate Locked"
	$Fly_Pickup.hide()
	$Shield.hide()
## Updates health bar
func _on_player_health_changed(health):
	$HealthBar.value = health

## Setting up the Timer
func time_left_to_live():
	var time_left = timer.time_left
	var minute = floor(time_left/60)
	var second = int(time_left) % 60
	return [minute, second]

## Printing the timer to the screen
func _process(delta):
	label.text = "Time To Escape: %02d:%02d" % time_left_to_live()
	$Coin.text = "Coins: " + str(player.total_coins)
	# Player must have 3 coins for the next level to unlock
	if player.total_coins == 3:
		# Show On Screen
		$Gate.text = "Gate UnLocked!"

## This called when player runs out of time
func _on_timer_timeout():
	# Will Change to the failed screen
	# Level will then be reset and player will have to try again
	get_tree().change_scene_to_file("res://scences/death_menu.tscn")

## This is to show the player how many "fly jumps" they have left on screen
func _on_player_fly_counts(flyCount):
	$Fly_Pickup.show()
	$Fly_Pickup.text = "Fly Jumps: " + str(flyCount)
	if flyCount == 0:
		$Fly_Pickup.hide()

## This will show the player they can use their force field
func _on_player_force_field_hud():
	$Shield.show()
	$Shield.text= "Force Field Available"
