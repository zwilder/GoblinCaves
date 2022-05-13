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

Major Goal: Five data types - structured like Angband: Player, Enemy, Playing Field,
Effects, Pickups.

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
