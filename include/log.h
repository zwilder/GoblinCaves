#ifndef LOG_H
#define LOG_H

/*****************
 * log.c functions 
 *****************/
void start_log(void);
void write_log(char *msg);
void log_map(void);
void log_time(void);
void log_vec(Vec2i a);
void log_rect(Rect a);
void log_leaves(Node *node);

#endif 
