void init_world (void) {
	// 0 16 87 117
	aPLib_depack_VRAM (0*32, ss_patterns_hud_c_bin);
	aPLib_depack_VRAM (16*32, ss_patterns_yun_c_bin);
	aPLib_depack_VRAM (86*32, ss_patterns_items_c_bin);
	aPLib_depack_VRAM (118*32, ss_patterns_enems_fixed_c_bin);
	aPLib_depack_VRAM (169*32, ss_patterns_enems_fixed2_c_bin);
}
