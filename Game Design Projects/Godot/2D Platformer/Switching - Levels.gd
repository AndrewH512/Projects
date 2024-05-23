extends Area2D
#Switching From Level 1 to Level 2
var entered = false
var simultaneous_scene = preload("res://level_2.tscn").instantiate()

#Player has reached the flag
func _on_body_entered(body: PhysicsBody2D):
	entered = true

#Player has not reached the flag
func _on_body_exited(body):
	entered = false

func _physics_process(delta):
	if entered == true:
			# Change to next level
			get_tree().change_scene_to_file("res://level_2.tscn")
