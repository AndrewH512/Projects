class_name Pickups
extends Sprite2D

# Delcaring Variables
var is_collected_health = false
var is_collected_strength = false
var is_collected_fly = false
var is_collected_speed = false
var is_collected_force_field = false

## This handles the health pickups
func _on_interaction_body_entered(body):
	if body.is_in_group("Player") and not is_collected_health:
		is_collected_health = true
		$health_sound.play()
		body.more_health(body)
		hide()

## This handles the strength pickups
func _on_strength_interaction_body_entered(body):
	if body.is_in_group("Player") and not is_collected_strength:
		is_collected_strength = true
		$strength_sound.play()
		body.more_strength(body)
		hide()

## This will handle the fly pickup
func _on_fly_interaction_body_entered(body):
	if body.is_in_group("Player") and not is_collected_fly:
		is_collected_fly = true
		body.fly(body)
		$fly_sound.play()
		hide()

## This will handle the speed pickup
func _on_interaction_speed_body_entered(body):
	if body.is_in_group("Player") and not is_collected_speed:
		is_collected_speed = true
		$speed_sound.play()
		body.more_speed(body)
		hide()

## This will handle the force field pickup
func _on_interaction_force_field_body_entered(body):
	if body.is_in_group("Player") and not is_collected_force_field:
		is_collected_force_field = true
		$force_field_sound.play()
		body.force_field(body)
		hide()
