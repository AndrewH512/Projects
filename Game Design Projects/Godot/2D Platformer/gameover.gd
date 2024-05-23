extends CanvasLayer

# Player pressed the restart button
func _on_start_pressed():
	# This will reset the player back at level 1 and restart the game
	get_tree().change_scene_to_file("res://level_1.tscn")


func _on_quit_pressed():
	# The game closes
	get_tree().quit()


func _on_main_pressed():
	get_tree().change_scene_to_file("res://main.tscn")
