#include <goblincaves.h>

/* Mostly unnecessary helper functions, but keeping them here as a reminder how
 * do */
bool check_flag(int mask, int flag) {
    /* Is flag on? */
    return((mask & flag) == flag);
}
int toggle_flag(int mask, int flag) {
    /* Toggles flag on/off */
    return(mask ^= flag);
}
int remove_flag(int mask, int flag) {
    /* Turns off flag */
    return(mask &= ~flag);
}
int engage_flag(int mask, int flag) {
    /* Turns on flag */
    return(mask |= flag);
}

