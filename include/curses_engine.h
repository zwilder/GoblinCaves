#ifndef CURSES_ENGINE_H
#define CURSES_ENGINE_H

/***************************
 * curses_engine.c functions
 ***************************/
bool curses_setup(void);
void setcolor(int fg, int bg);
void unsetcolor(int fg, int bg);
void curses_draw(int x, int y, Glyph glyph);
void msg_box(char* msg, Color fg, Color bg);
bool yn_prompt(char* msg, Color fg, Color bg);
void curses_close(void);

#endif
