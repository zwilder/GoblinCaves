/*
* Goblin Caves
* Copyright (C) Zach Wilder 2022-2023
* 
* This file is a part of Goblin Caves
*
* Goblin Caves is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* Goblin Caves is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with Goblin Caves.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <goblincaves.h>

/****
 * Bitflags are the coolest damn thing and I use them all the time. How they
 * work:
 *
 * A flag is just a true/false (on/off) value - is a tile visible? has it been
 * explored? does it block movement? etc etc. The flags could be stored as
 * boolean value for each in the object that uses them... but that's messy
 * right? Enter bitflags. Instead of having an arsenal of boolean values, then
 * having to add a new one each time, the object has a single integer, "flags".
 * This integer is then checked with fancy bitmath to see if a flag is engaged.
 * For example a map tile object could have the following flags:
 * blocks_light        1 << 0 = 0001 = 1
 * blocks_movement     1 << 1 = 0010 = 2
 * explored            1 << 2 = 0100 = 4
 * visible             1 << 3 = 1000 = 8
 *
 * So a Wall would have flags engaged for blocks_light and blocks_movement:
 *      wall.flags = (blocks_light | blocks_movement) = (0001 | 0010) = 0011 = 3
 * Then when the player first sees the wall, we turn on the visible and explored
 * flags:
 *      wall.flags |= (visible | explored) // wall.flags = 1111
 * Finally if the player moves so that the wall is no longer visible, we can
 * turn off the flag by easily calling:
 *      wall.flags &= ~visible // wall.flags = 0111
 * Super neat. Standard integer allows for up to 30 flags (2^31 is
 * 2,147,483,648) - which is a lot of flags. I like to separate flags into types
 * (tile flags, event flags, etc) so that I don't have to worry about running
 * out of flags.
 ****/
bool check_flag(int mask, int flag) {
    /* Is flag on? */
    /* Example:
     * a = 1011
     * b = 0001
     * a & b = 0001
     * (a & b) == b is 0001 == 0001, which is true. 
     */ 
    return((mask & flag) == flag);
}
int toggle_flag(int mask, int flag) {
    /* Toggles flag on/off */
    /* Example:
     * a = 1011
     * b = 0010
     * a ^= b is 1001, turning the flag off.
     *
     * a = 1001
     * a ^= b is 1011, turning the flag on.
     * Neat!
     */
    return(mask ^= flag);
}
int remove_flag(int mask, int flag) {
    /* Turns off flag */
    /* Example:
     * a = 1011
     * b = 0010
     * ~b is 1101
     * a &= ~b is 1011 &= 1101 which is 1001.
     * Turning the flag off. If the flag is already off:
     * a = 1001
     * b = 0010, ~b = 1101
     * a &= ~b is 1001 &= 1101, which is 1001. Flag stays off.
     */
    return(mask &= ~flag);
}
int engage_flag(int mask, int flag) {
    /* Turns on flag */
    /* Example:
     * a = 1001
     * b = 0010
     * a |= b is 1011, turning the flag on. If flag is already on:
     * a = 1011
     * b = 0010
     * a |= b is 1011, keeping the flag on.
     */
    return(mask |= flag);
}

