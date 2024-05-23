extends Node2D
var entered = false

# Called when the node enters the scene tree for the first time.
func _ready():
	$UserInterface/Retry.hide()

func _on_interact_body_entered(body):
	if body.is_in_group("Player"):
		body.die()


func _on_player_hit():
	$UserInterface/Retry.show()
	pass # Replace with function body.

func _unhandled_input(event):
	if event.is_action_pressed("ui_accept") and $UserInterface/Retry.visible:
		# This restarts the current scene.
		get_tree().reload_current_scene()


func _on_finish_body_entered(body: PhysicsBody2D):
	entered = true


func _physics_process(delta):
	if entered == true:
			# Change to next level
			get_tree().change_scene_to_file("res://gameover.tscn")
