// MT MK1 SMS version 0.1 [Yun]
// Copyleft 2016 The Mojon Twins

// Printer. Auxiliary printing functions

#ifndef __PRINTER_H
#define __PRINTER_H

void sprites_out (void);
inline void pal_cycle_desert_do (void);
inline void pal_cycle_waterfall_do (void);
inline void tile_effects_factory_do (void);

void debug_print_hex (unsigned char x, unsigned char y, unsigned char v);

#endif
