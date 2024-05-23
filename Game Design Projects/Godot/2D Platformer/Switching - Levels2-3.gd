extends Area2D

#Switching From Level 2 to Level 3
var entered = false
var simultaneous_scene = preload("res://level_3.tscn").instantiate()

#Player has reached the flag
func _on_body_entered(body: PhysicsBody2D):
	entered = true

#Player has reached the flag
func _on_body_exited(body):
	entered = false

func _physics_process(delta):
	if entered == true:
			#Player has reached the flag
			get_tree().change_scene_to_file("res://level_3.tscn")

