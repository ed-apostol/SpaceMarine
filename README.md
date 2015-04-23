simple-game
===========

Author: Edsel Apostol
Test project: Space Marine

Details:
This is a test project for Boomzap Entertainment.
The test starts Saturday, 20th April, 2013, and is due night of Monday, 29th April, 2013 (2 weekends full time and 6 working days part time)

Features:
There is a single player with a starting HP of 100 placed in the middle of a level that is 3 x 3 size of (1024x768 screen).
The player has a firing rate of 1 bullet per 150ms at startup.
There are 500 enemies (please see note 1 below) scattered across the level but outside the screen at initialization. 
They will come rushing and will attack the player at all times.
Every time an enemy is killed it will respawn at any random location on the level outside of the current screen.
There are 3 kinds of enemies: 
-the smaller one which is faster (same as player speed) and attacks faster but damage is small
-the medium one with medium speed (half of the player speed) and attacks normally with medium damage
-the big one which is slower (third of player speed) and attacks slowly but with a heavy damage
There are 20 static buildings scattered randomly across the entire level. No 2 game has the same level (unless RNG seed is fixed to a value)
There are 2 kinds of pickups in the game.
There are 10 of each pickup scattered randomly across the level.
Pickup #1 adds 10 to HP.
Pickup #2 reduces time firing rate by 10ms, and maxed out at 70ms firing rate for the player.
Each consumed pickups is respawned after 5 seconds randomly across the level.

Controls:
-controls are from CrimsonLand (A,W,S,D for movements, mouse-click/scroll for firing, mouse pointer location is the target)

Art Assets:
Images - images are from the web and programmer art
Sounds - the BG sound is from Crimsonland and the other one is from the web

Technical Details:
Collision Detection is implemented through a spatial hashing for broad phase collision detection
The game is frame independent so whatever the FPS is the game should still have the same speed
There is still a decent FPS due to the efficient use of collision detection
The game can use an FPS cap but it was not enabled to demonstrate the efficiency showed by FPS
The enemy pathfinding is somewhat simple as there are a lot of open spaces (and there is only one goal, to get towards the player), so a pathfinding algorithm like A* may not be worth it
 
Tips:
Try to get to the edge as soon as possible and collect as much pickups as possible to have a higher survival chance
The scroll button of a mouse also serves as MOUSEBUTTONDOWN in SDL so you can use it to fire bullets faster instead of single-click/steady click
 
Notes:
note 1 - more enemies than this is not fun due to lack of space for player to run to, thereby killing the player in the least amount of time with not enough time to test the gameplay
