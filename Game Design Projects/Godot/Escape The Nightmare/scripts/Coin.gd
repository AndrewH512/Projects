class_name Coin
extends Sprite2D
var is_collected = false

# When the player enters a coin's collsion box
func _on_interaction_body_entered(body):
	# Must be a player and the coin is not collected yet
	if body.is_in_group("Player") and not is_collected:
		is_collected = true
		# Play coin sound
		$interaction/Coin_Sound.play()
		player.total_coins += 1
		# Coin will disappear
		hide()
