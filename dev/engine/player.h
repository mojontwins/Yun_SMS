// MT MK1 SMS version 0.1 [Yun]
// Copyleft 2016 The Mojon Twins

// Player movement & stuff

#ifndef __PLAYER_H
#define __PLAYER_H

inline void player_init (void);
inline void player_kill (void);
void player_process_block (unsigned char x0, unsigned char y0);
inline void player_do (void);
inline void player_render (void);
inline void player_render_scrolly (void);

#endif
