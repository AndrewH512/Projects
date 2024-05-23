Game 4: Thomas, Bob, and Kevin are Late 

Prescribed Change #1 - Refactoring
- Observer Design Pattern
	- Added the observer pattern to take care of when the player falls into water and lava.
	- An Observer interface is created with two methods: onPlayerFallInFire and onPlayerFallInWater.
	- The SoundManager class implements the Observer interface.It provides specific implementations 
	  for onPlayerFallInFire and onPlayerFallInWater.
	- These methods define the reactions or actions the SoundManager takes when notified of a player 
	  falling in fire or water.
	- The engine class acts as the subjust that notifes the observers. It has the list of observers, 
	  and methods to remove or add observers
	- So when the player falls in fire or water, the Engine calls the methods and iterate over the list
	  of observers and calls theuir corresponding notifciation methods

- State Design Pattern

Discretionary Change #1 New Tile Type
- Added a new tile type into the game, sand. The movement of the player is slowed
since the sand disperses the player's energy. This is tile type "5".

Discretionary Change #2 - New Character Option
- New Charcter Kevin (Blue)
- Kevin will be just as tall as Thomas, and will have the same speed and jump stats, but he has a ability over sand
- His speacil ability is that he is actually faster on sand and can jump higher while on sand
- The new character will switch out with bob every other level. So he will be playable on Level 1 and 2. 

Prescribed Change #2 - New Level Designs
- Level 1
	- Level 1 is the easiest level as it should be. Some little jumps showcasing the sand is there. But this level's
	  job is to just make the 1st level a little harder.
	- Characters: Thomas and Kevin
	- Time limit of 60 seconds 
- Level 2
	- Level 2 is where things start to get a little harder. To better showcase the split screen, this level Bob and Thomas
	  could take different routes if tehy want to. Bob can only take the top route, which has a lot of sand and lava. While
	  both Thomas and Bob can take the bottom route which is longer and harder from both of them to take. Bob
	  will need Thomas's help with some of the jumps.
	- Characters: Thomas and Bob
	- Time limit of 100 seconds 
- Level 3
	- Level 3 is to better showcase the sand effect on the game. Most of the jumps are sand, this level is a little more diffult,
	  because the time limit is less, so you can't really make a mistake.
	- Characters: Thomas and Kevin
	- Time limit of 60 seconds 
- Level 4
	- Level 4 takes some inspiration from the minecraft map "dropper". Where esetnally you are jumping blindly into a pit, and you
	  could hit water, lava, sand etc. This is most diffult level and I've given the player the most time out of any level to 
	  finish it.
	- Characters: Thomas and Bob
	- Time limit of 160 seconds 
- All levels are play tested, and all are able to be finished within the time given. 

Discretionary Change - New Particles
- Change the beahvior of particles
	- The radius of the particles is now random
	- Added more particles for different parts of the game
- Added New Particles into the game
	- Sand Particle: when you touch sand, every 5 seconds yellow particles appear.
	- Water Particle: When you die in water, or get close to water blue particles appear
	- Lava Particle: When you die in water, or get close to lava red particles appear
	- Finsih Particle: When you finish, there are now particles that are green, showing that you
	  finished the level.