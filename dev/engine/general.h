// MT MK1 SMS version 0.1 [Yun]
// Copyleft 2016 The Mojon Twins

// General & all purpose

#ifndef __GENERAL_H
#define __GENERAL_H

inline signed int saturate (signed int v, signed int max);
inline void cm_two_points (void);
inline signed int add_sign (signed int sign, signed int value);
inline unsigned char collide (unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);
inline void ogt_run (void);
void wait_for (unsigned char nticks);

#endif
