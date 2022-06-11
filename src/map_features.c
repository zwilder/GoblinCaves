/*
* Goblin Caves
* Copyright (C) Zach Wilder 2022
* 
* This file is a part of Goblin Caves
*
* Goblin Caves is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* * Goblin Caves is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with Goblin Caves.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <goblincaves.h>
/*******************
 * Feature placement
 *******************/
void place_room(Rect room) {
    int x, y;
    for(x = room.pos.x; x <= room.pos.x + room.dim.x; x++){
        for(y=room.pos.y; y <= room.pos.y + room.dim.y; y++) {
            if(room.pos.x == x 
                   || room.pos.y == y
                   || room.dim.x + room.pos.x == x 
                   || room.dim.y + room.pos.y == y) {
                place_tile(make_vec(x,y), TILE_WALL);
            } else {
                place_tile(make_vec(x,y), TILE_FLOOR);
            }
        }
    }
}

void make_fancy_room(Rect room) {
    /* This would be cool if it rolled on a table to place features, or selected
     * a random room from a weighted list or something. */
    int i = mt_rand(1,20);
    switch(i){
        case 1: place_pillars(room); break;
        case 2: place_marsh(room); break;
        case 3: place_altar(room); break;
        case 4: 
        case 5: 
        case 6: 
        case 7:
        case 8:
        case 9:
        case 10: round_room(room); break;
        default: break;
    }
}

void place_kitchen(Rect room) {
    /*           1
     * 01234567890
     * ########### 0
     * #oo.(&)nn.# 1
     * #==.......# 2
     * #oo.......# 3
     * #.........# 4
     * #.........# 5
     * ########### 6
     *
     */
}

void place_marsh(Rect room) {
    /*           1
     * 01234567890
     * ########### 0
     * #.........# 1
     * #."..~"'..# 2
     * #...~~~.;.# 3
     * #....~....# 4
     * #.".......# 5
     * ########### 6
     *
     */
    int x,y,i;
    for(x = room.pos.x + 1; x <= room.pos.x + room.dim.x - 1; x++){
        for(y=room.pos.y + 1; y <= room.pos.y + room.dim.y - 1; y++) {
            i = mt_rand(1,9);
            switch(i){
                case 1: place_tile(make_vec(x,y), TILE_PLANT); break;
                case 2: place_tile(make_vec(x,y), TILE_GRASS); break;
                case 3: place_tile(make_vec(x,y), TILE_SHRUB); break;
                case 4: 
                case 5: 
                case 6: 
                case 7: 
                case 8: 
                case 9: place_tile(make_vec(x,y), TILE_WATER); break;
                default: break;
            }
        }
    }
    /* Run some automata */
    i = 0;
    while(i < 4) {
        for(x = room.pos.x + 1; x <= room.pos.x + room.dim.x - 1; x++){
            for(y=room.pos.y + 1; y <= room.pos.y + room.dim.y - 1; y++) {
               if(count_neighbors(make_vec(x,y), '~') >= 4) {
                    place_tile(make_vec(x,y), TILE_WATER);
               } 
            }
        }
        i++;
    }
}

void place_altar(Rect room) {
    /*           1
     * 01234567890
     * ########### 0
     * #..~0.0~..# 1
     * #..0...0..# 2
     * #...._....# 3
     * #..0...0..# 4
     * #..~0.0~..# 5
     * ########### 6
     *
     */
    Vec2i center = get_center(room);
    if(room.dim.x != 10) {
        return;
    }
    if(room.dim.y < 6) {
        return;
    }

    place_tile(center, TILE_ALTAR);
    place_tile(make_vec(center.x - 2, center.y - 2), TILE_WATER);
    place_tile(make_vec(center.x + 2, center.y - 2), TILE_WATER);
    place_tile(make_vec(center.x - 2, center.y + 2), TILE_WATER);
    place_tile(make_vec(center.x + 2, center.y + 2), TILE_WATER);

    place_tile(make_vec(center.x - 2, center.y - 1), TILE_PILLAR);
    place_tile(make_vec(center.x - 1, center.y - 2), TILE_PILLAR);
    place_tile(make_vec(center.x + 1, center.y - 2), TILE_PILLAR);
    place_tile(make_vec(center.x + 2, center.y - 1), TILE_PILLAR);
    place_tile(make_vec(center.x - 2, center.y + 1), TILE_PILLAR);
    place_tile(make_vec(center.x - 1, center.y + 2), TILE_PILLAR);
    place_tile(make_vec(center.x + 2, center.y + 1), TILE_PILLAR);
    place_tile(make_vec(center.x + 1, center.y + 2), TILE_PILLAR);
}

void place_pillars(Rect room) {
    /*           1
     * 01234567890
     * ########### 0
     * #.........# 1
     * #.0.0.0.0.# 2
     * #.........# 3
     * #.0.0.0.0.# 4
     * #.........# 5
     * ########### 6
     *
     * x,y dimensions have to be odd
     */
    int x,y;
    /*
    x = room.dim.x + room.pos.x;
    x = room.dim.y + room.pos.y;
    if((x % 2) == 0) {

        return;
    }
    if((y % 2) == 0) {
        return;
    }
    */
    /* Only even rows after 0 get pillars */
    for(x = room.pos.x + 2; x <= (room.pos.x + room.dim.x - 2); x += 2){
        for(y=room.pos.y + 2; y <= (room.pos.y + room.dim.y - 2); y += 2) {
            place_tile(make_vec(x,y), TILE_PILLAR);
        }
    }
}

void round_room(Rect room) {
    /* chance to round corners */
    /*
     * p.x,p.y               p.x+d.x,p.y
     *
     *
     * p.x,p.y+d.y           p.x+d.x,p.y+d.y
     */
    place_tile(make_vec(room.pos.x + 1, room.pos.y + 1), TILE_WALL);
    place_tile(make_vec(room.pos.x + 1,
                room.pos.y + room.dim.y - 1), TILE_WALL);
    place_tile(make_vec(room.pos.x + room.dim.x - 1,
                room.pos.y + room.dim.y - 1), TILE_WALL);
    place_tile(make_vec(room.pos.x + room.dim.x - 1,
                    room.pos.y + 1), TILE_WALL);
}

void place_htunnel(int x1, int x2, int y) {
    int i;
    int min = (x1 < x2 ? x1 : x2);
    int max = (x1 > x2 ? x1 : x2);
    for(i = min; i <= max; ++i)
    {
        if(get_glyphch_at(i,y) == '#') {
            place_tile(make_vec(i,y), TILE_FLOOR);
        }
    }
}

void place_vtunnel(int y1, int y2, int x) {
    int i;
    int min = (y1 < y2 ? y1 : y2);
    int max = (y1 > y2 ? y1 : y2);
    for(i = min; i <= max; ++i)
    {
        if(get_glyphch_at(x,i) == '#') {
            place_tile(make_vec(x,i), TILE_FLOOR);
        }
    }
}

void place_orthogonal_tunnel(Vec2i a, Vec2i b) {
    /* Orthogonal walk, courtesy of RedBlobGames
     * https://www.redblobgames.com/grids/line-drawing.html */

    /* I think this is broken? */
    int dx, dy, nx, ny, signx, signy, ix, iy;
    Vec2i p;
    dx = a.x - b.x;
    dy = a.y - b.y;
    nx = abs(dx);
    ny = abs(dy);
    signx = dx > 0 ? 1 : -1;
    signy = dy > 0 ? 1 : -1;
    p = make_vec(b.x,b.y);
    ix = 0;
    iy = 0;
    while(ix < nx || iy < ny) {
        /*if(((0.5 + ix) / nx) < ((0.5 + iy) /ny)) { */
        if(((1 + 2*ix) * ny) < ((1 + 2*iy) * nx)) {
            /* Horizontal step */
            p.x += signx;
            ix++;
        } else {
            /* Vertical step */
            p.y += signy;
            iy++;
        }
        if(get_glyphch_at(p.x,p.y) == '#') {
            place_tile(p,TILE_FLOOR);
        }
    }
}

void place_corridor(Vec2i a, Vec2i b) {
    if(mt_bool()) {
        place_htunnel(b.x, a.x, b.y);
        place_vtunnel(b.y, a.y, a.x);
    } else if (mt_bool()) {
        place_vtunnel(b.y, a.y, b.x);
        place_htunnel(b.x, a.x, a.y);
    } else {
        place_orthogonal_tunnel(a,b);
    }
}

void place_hdoor(int x, int y) {
    if(get_glyphch_at(x,y) == '.' &&
            get_glyphch_at(x - 1, y) == '#' &&
            get_glyphch_at(x + 1, y) == '#' &&
            get_glyphch_at(x, y - 1) != '+' &&
            get_glyphch_at(x, y - 1) != '/' &&
            get_glyphch_at(x, y + 1) != '+' &&
            get_glyphch_at(x, y + 1) != '/') {
        place_tile(make_vec(x,y), (mt_chance(20) ? TILE_CDOOR : TILE_ODOOR));
    }
}

void place_vdoor(int x, int y) {
    if(get_glyphch_at(x,y) == '.' &&
            get_glyphch_at(x, y - 1) == '#' &&
            get_glyphch_at(x, y + 1) == '#' &&
            get_glyphch_at(x - 1, y) != '+' &&
            get_glyphch_at(x - 1, y) != '/' &&
            get_glyphch_at(x + 1, y) != '+' &&
            get_glyphch_at(x + 1, y) != '/') {
        place_tile(make_vec(x,y), (mt_chance(20) ? TILE_CDOOR : TILE_ODOOR));
    }
}

void place_doors(Rect room) {
    int x,y;
    for(x = room.pos.x; x < room.pos.x + room.dim.x; x++) {
        place_hdoor(x,room.pos.y);
        place_hdoor(x, room.pos.y + room.dim.y);
    }
    for(y = room.pos.y; y < room.pos.y + room.dim.y; y++) {
        place_vdoor(room.pos.x, y);
        place_vdoor(room.pos.x + room.dim.x, y);
    }
}

void place_border(void) {
    int x, y;
    for(x = 0; x < MAP_WIDTH; x++) {
        place_tile(make_vec(x,0), TILE_ROCK);
        place_tile(make_vec(x, MAP_HEIGHT - 1), TILE_ROCK);
    }
    for(y = 0; y < MAP_HEIGHT; y++) {
        place_tile(make_vec(0,y), TILE_ROCK);
        place_tile(make_vec(MAP_WIDTH - 1, y), TILE_ROCK);
    }
}

void place_monsters(Rect room) {
    int num = mt_rand(0, MAX_MONSTERS);
    Vec2i pos;
    int i = 0;
    while(i < num) {
        pos = random_point_in_rect(room);
        //Monster *newMonster = create_goblin_at(pos);
        Monster *newMonster = create_monster_at(pos, M_GOBLIN);
        newMonster->locID = g_mapcur->lvl;
        push_mlist(&g_mlist, newMonster);
        i++;
    }
}
