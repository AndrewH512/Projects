class_name Menus
extends CanvasLayer

## This script is shared by both the main, win and death menu since they
## both use similar functions
## Player pressed the restart button
func _on_start_pressed():
	# This will reset the player back at level 1 and restart the game
	get_tree().change_scene_to_file("res://scences/levels/level_1.tscn")

## Function to handle player hitting quit button
func _on_quit_pressed():
	# The game closes
	get_tree().quit()

## Player pressed the main menu button
func _on_main_menu_pressed():
	# This will bring the player back to the main menu
	get_tree().change_scene_to_file("res://scences/main_menu.tscn")
