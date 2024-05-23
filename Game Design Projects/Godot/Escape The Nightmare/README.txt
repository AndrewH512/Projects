Escape The Nightmare Version 1.0
-------------------------------------------------------------------------------------------
Title Screen and Two Playable level
- There is a Main Menu Screen
	- Options to play the game and quit
- Level 1 
	- Made to be like a maze, player can explore as much as they want to find 
	the exit to the next level
- Level 2
	- This level takes it too the next level. More hallways, more dead-ends, bigger
	map. Players will get lost and stuggle to find the exit. This map is very easy to 
	get lost on.
- Death Screen
	- Options to play again (brings player straight to level
	- Players can also quit or go back to main menu
- Win Screen
	- This is shown when the player finishes the game!
	- This also shows the credits
-----------------------------------------------------------------------------------------------
Hud
- Health Bar - Players can see their health on the bottom left of the screen. When the bar is empty, 
the player will die and bring them to the death screen. 
- Timer - Player is given 20 minutes to escape, if they fail it will bring them to the death screen and 
they will start over.
- Coin Total - This shows the player how many coins they have collected.
- Gate Locked/Unlocked - shows the player wether they can advance to the next level. The Player need 3 coins
to unlock the next level
- Flying Jumps - this only shows when the player picks up the flying superpower. This will shows how many more
flying jumps they have left. They only can use it 5 times. 
- Force Field Ready - This text shows up at the bottom left of the screen by the health bar to let the player know
they can use the force field power. This text only shows up when they pickup the force field item pickup
--------------------------------------------------------------------------------------------
Three Game Systems: AI, Combat, Superpower Pickups
--------------------------------------------------------------------------------------------
Enemy AI
- Basic AI logic has been implmented in all mobs of the game and more
- All mobs have animations and sound effects. 
- There are 6 types of enemies. There will be basic mobs and strong mobs
- Basic Mobs
	- Slime - The Slime is suppose to be the easiest mob in the game. They just roam around
	the platforms and deal the least amount of damage and are one hits.
	- Night Ninja - This mob will only be found at the bottom of the maps. When this mob sees a
	player, their speed will increase.
	- T-Rex Robot - this is a strong yet slow mob. The T-Rex can see when a player is behind them
	and turns arounds to combat them. 
- Strong Mobs
	- Minotaur - strong mob, suppose to be like a tank. Takes forward knockback when hit. Spawns
	with a randomize speed
	- Demon - this mob can fly. This is the only flying mob in the game. If this mob lands on top of you,
	you have a chance at getting one hit.
	- Red Smile - this is the hardest mob in the game. This mob is invisble to the player from a distance. 
	Once the player gets into range of the Red Smike's vision, it speeds up every frame. The mob will hide
	and be invisble again when the player is out of his sight. 
- Bosses
	- Each mob has a boss version of itself on one of the levels (mostly level 2)
	- Theses bosses are like the regular mobs just scaled bigged, with more health and speed.
	- Typically around theses bosses on the map are more Superpower pickups and coins
--------------------------------------------------------------------------------------------
Combat
- Combat has been implmented
- The player has 100 health and the enemies have different healths based on
their diffulty
- Player can use left click to swing their sword BUT THEY MUST be standing still and on the ground.
You can not swing your sword and jump at the same time. This is to add some type of diffultly to the combat.
- Player has a strength stat that determines how much damge they do.
- Enemies can hit the player if they get close to them and the player can die from them.
--------------------------------------------------------------------------------------------
SuperPower Pickups
- Theses pickups will give the player powers like, Increased Strength, Flying, and Stronger Health.
- Strength Super Powerup
	- Gives the player move strength to better combat mobs. 
	- Player Strength is increased by + 20
	- No limit
- Flying Super Powerup
	- When pickup, the player gets super jumps.
	- Player can only use this 5 times
- Increased Health Pickup
	- Increases player health by 34
	- Player will max out at 200 health (Player only starts at 100 health)
- Speed Power
	- Increases player speed by 30
	- No Limit
- Force Field (Only 1 On Each Level)
	- When pressed, player will not be able to get hit by mobs
	- However the player can't move and must be standing still
	- Player can not attack using Force Field
--------------------------------------------------------------------------------------------
Coins
- Coins are placed around the map for the player to go find a collected!
- The player needs to find three coins to be able to unlock the gate for the next level
- If the player doesn't have three coins, they will be unable to pass through the gate
--------------------------------------------------------------------------------------------
The Use Of Core Godot Components
- Used Node Functions like _input, _ready, _process, and _phyiscs_process
- Used Signals for combat, collision dectections, hud etc.
- Used Timer. Player only has 20 minutes to complete each level. When timer runs
- Used Collisons, Area, and bodies to create player and mobs
- Used canvas layers and control items for hud as well as menus
Other Components Used Included
- TileMap
- Parallax background
- 2DAudioStreamPlayer for music, sound effects
- Raycast2D so mobs don't get stuck on walls or fall off platforms
--------------------------------------------------------------------------------------------
Game Patterns: Observer, State
Observer: Used Godot signals for things like the hud
State: Used in my Demon's ai logic. There is a state for when he's on the ground and when he's flying in the air


