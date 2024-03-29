## Goblin Caves 
A "simple" dungeon delving roguelike, to try and
remember how programming works, and to get basic systems in fully
functional working order to build the dream RL (Barbarian).

**DESIGN MANTRA: MAKE IT WORK BEFORE MAKING IT PRETTY.** I seem to
always get stuck trying to make things nice and proper, before throwing
in the towel.

Set number of levels - goal is to get to the bottom, kill the chief, nab
some treasure, return to the surface.

Levels are randomly generated, typical RL style.

Each level has a set difficulty (monster level). Players earn exp for
kills at or above their level. Killing the chief increases each levels
difficulty so ascent is more difficult then descent. Maybe. KISS.

Loot in the caves is gold (increases score), health potions (increases
health). Stretch goal would be a more robust inventory as described
below. Again, KISS.

Major Goal: Five data types - structured like unAngband suggests: Player, Enemy,
Playing Field, Effects, Pickups. UPDATE: Player-Enemy is going to be one type.
The four major types for this game are Monster, Tile, Effects, Pickups

Major Goal: Implement a time management system using a circular, double linked
list.
- Determine whose turn it is
- Keep track of future events and make them happen on schedule
- Handle effects with intervals
- Make sure things work when player/monsters have their speed changed or
  are frozen.
Player/monsters have speed, and actions cost a certain amount of
energy/time. Each game 'tick', the player/monster/effect gains action
points equal to speed. If p/m/e action points are greater than 0, then
take a turn deducting cost of action from action points. 

Major Goal: Inventory management, items should be able to be:
- Picked up
- Put down
- Worn/wielded
- Used as a weapon/ammo
- Eat/drink
- Put in a container
- Broken
- Transformed
- Applied

Major Goal: Saving and loading

Major Goal: Map generation
- Representation
- Saving/restoration (dungeon persistence)
- Ranged effects, aiming, obstructions
- Area effects and how they interact with restricted areas
- Player/enemy alterations of map (destructable tiles, etc)
- Planning/pathfinding
- FoV
- Dungeon generation, including using premade 'chunks' (eg ADOM vaults)

Stretch Goal: Player initiated 'effects' (abilities). A targeted ranged attack, an AoE
attack, etc. Fun example ideas:
- Cleave: Aim in a direction to attack all three spaces facing that
  direction. Example below, player (@) cleaves right, dealing damage to
all three goblins (g).
  .....g....
  ....@g....
  .....g....
- Knockback: Player attack forces enemy in direction player attacked, if
  enemy can't be moved in that direction deal extra damage. Maybe even
throwing enemy through closed doors?
- Charge: Player moves rapidly in a direction up to X spaces, damage
  increasing with distance traveled. Obviously has to be able to
traverse the terrain in between the player and the target. Collision
with walls/immovable objects could damage the player?
- Leap: Player jumps into the air to attack a target within X radius.
  Knocks enemy backwards as a secondary effect, since the player will
then occupy the enemy space.

Stretch Goal: Built in random name generator for both player and
goblins. It would be funny if each goblin was named, and even more funny
if they had randomly assigned jobs - "You have slain B'leb the chef!"
"Glar the bodyguard flees in terror!". There could be a whole goblin
economy set up in the caves - random generated themed rooms (forge,
kitchen, brewery, carpenter's shop, etc etc). 

Stretch Goal: Monster intelligence - intellegent monsters can use items. Really
intellegent monsters can be literate and read scrolls. Monsters use the
equipment they have, and then drop it on death.

Stretch Goal (comment on one of my comments on r/roguelikedev back in 2018):
"""
Comment by u/dystheria
I sometimes feel like I'd be better suited to game "design" than "development".

Here are a bunch of ideas your post has given me that I'm sure you probably
would have eventually arrived at yourself:

- change the result of combat based on the degree of overkill, by that I mean
  when the player does enough damage to kill an enemy in a single hit, have the
enemy be cut in to two pieces, or have their corpse be obliterated in to just a
"bloody mess" on the floor. You could develop this further if you wanted to
attempt to implement limbs and potential decapitation. 
- the fireball animations were a big hit, if you can animate the result of
  attacks to have a similar impact on the world (blood splatters, damaged
flooring, etc) you provide the player with a greater sense of agency, even in
ASCII art. 
- create a rage mechanic that increases gradually as the player does damage and
  greatly as they receive damage which allows them access to a small set of
powerful skills (a direct Shield Bash, an area sweep Cleaving Attack, a close
proximity AoE Ground Smash attack) allowing the player to engage more without
the concern of only being able to hit one enemy at a time.  as an extension of
the player rage, have rage accumulated by damage dealt also provide a temporary
buff to hit-points, encouraging the players to continue to deal damage as much
as possible.
- give everything weight and implement a very basic physics system that allows
  the player to kick stools and throw tables at enemies, or better yet, shield
bash an enemy with such force it sends them flying in to a wall with force,
causing further damage to them. 
"""

Minor goal: Random flora to populate the caves, characteristics of the flora add
different effects depending on use. Procgen mushrooms? Or maybe a set series of
mushrooms with certain effects that start unidentified (ADOM potions, "Thick
blue potion" is different from game to game). Since each mushroom can be eaten,
thrown, applied etc (like all items, see the major goal above) there is lots of
fun things that could be done here. What happens if you apply an inkcap to a
scroll you found? Apply the milky fluid from a mushroom to your sword? Eat the
spotted mushroom? Maybe the player can "forage" a tile (and only once per tile,
it would be easy to add a "foraged" flag like "explored"), and certain tiles
have a higher chance of producing forageable items. Unidentified flora should
have hints somewhere to what they do - maybe Goblins will randomly drop 'notes'
that have a hint on it: "This scrap of paper shows a wounded goblin smiling
while holding a small brown mushroom" - the small brown mushroom heals minor
wounds. "A crude drawing of a goblin shaman cooking inkcaps on a writing desk" -
the ink caps can be applied to a scroll to change what spell it casts. 

Idea: Experience points are spent to upgrade skills: eg Weapon (offensive power), Armor
(defensive power), or Luck (bonuses?). Player doesn't find new weapons in the
game, they have one weapon with a generated name. Their base stats are based on
the name of the weapon. Message at the beginning of the adventure: "Player
wields the legendary battlaxe Gladys!". Type of weapon maybe is chosen
(Battleaxe, Greatsword, Sword/Shield combo, Longbow?) at beginning of game and
determines the skills player can use as they gain experience (replacing the idea
of a "class). More skills in their weapon means new abilities - maybe the
abilities gained are in a random order, so there is no guarantee that leveling
up Gladys will get you cleave, maybe you'll get leap. 

Minor goal: All in game text (the flavor and spice) stored and loaded from an
external file. Flavor text procedurally generated if appropriate. Advantage is
that it can be easily added to, modified, and even translated to other languages

Items should be stored in a linked list. The "inventory" for the players and
monsters should be a list, and each tile should have a list. The list would
contain the head node (item), and maybe a count? The list should have functions
to push and pop nodes (items), so that items could be transferred from enemies
to tiles to player etc. 

IDEA: Use random word generator to generate "seed" keys to seed the random
number generator. Those seed keys could be specified via command line when the
game starts up, and written to the log. 
