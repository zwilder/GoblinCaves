#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

/*************************
 * game_engine.c functions
 *************************/
void engine_init(void);
void engine_run(void);
void engine_close(void);
int get_input(void);

int mt_rand(int min, int max); 
bool mt_bool(void); 
bool mt_chance(int chance);

#endif
