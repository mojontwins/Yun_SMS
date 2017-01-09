// MT MK1 SMS version 0.1 [Yun]
// Copyleft 2016 The Mojon Twins

// Initializers

#include "../lib/aPLib.h"

#include "inits.h"

extern const unsigned char ss_patterns_hud_c_bin [];
extern const unsigned char ss_patterns_yun_c_bin [];
extern const unsigned char ss_patterns_items_c_bin [];
extern const unsigned char ss_patterns_enems_fixed_c_bin [];
extern const unsigned char ss_patterns_enems_fixed2_c_bin [];
extern const unsigned char ts_hex_c_bin [];

void init_world (void) {
	aPLib_depack_VRAM (0*32, ss_patterns_hud_c_bin);
	aPLib_depack_VRAM (16*32, ss_patterns_yun_c_bin);
	aPLib_depack_VRAM (86*32, ss_patterns_items_c_bin);
	aPLib_depack_VRAM (118*32, ss_patterns_enems_fixed_c_bin);
	aPLib_depack_VRAM (169*32, ss_patterns_enems_fixed2_c_bin);
	aPLib_depack_VRAM (432*32, ts_hex_c_bin);
}
