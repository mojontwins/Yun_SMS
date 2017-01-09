// MT MK1 SMS version 0.1 [Yun]
// Copyleft 2016 The Mojon Twins

// Game loop & related shit

#include "../lib/SMSlib.h"
#include "../lib/PSGlib.h"

#include "../definitions.h"
#include "player.h"
#include "enems.h"
#include "hotspots.h"
#include "fabolee.h"
#include "simplecoco.h"
#include "level.h"
#include "map.h"
#include "hud.h"
#include "inits.h"
#include "general.h"
#include "printer.h"
#include "scroller.h"
#include "game.h"

extern signed int cam_x;
extern unsigned char pisdead;
extern unsigned char fskipctr;
extern unsigned char tv_type, ticks, ticker;

extern unsigned int gpint;
extern unsigned char advance_cam;

extern unsigned char no_ct, no_x, no_y;
extern unsigned char anim_tile_conveyor_offs;
extern unsigned char n_pant, on_pant;
extern unsigned char half_life, frame_counter, run_flip_flop;

extern unsigned char prx, pry;
extern signed int px, py, pcy, pvx, pvy;
extern unsigned char pkilled;

extern unsigned char level;
extern unsigned char c_bank;
extern unsigned char c_map_w, c_map_h;

extern unsigned char jitter_x, jitter_y;
extern const unsigned char jitter [];
extern const unsigned char random_seq [];

extern const unsigned char * const level_tunes [];
extern const unsigned char * const spr_it [];

extern unsigned char cam_x_module;
extern unsigned char collision_buffer [];
extern unsigned char *map_scr;

inline void game_init (void) {
	enems_init ();
	player_init ();
	hotspots_init ();

	anim_tile_conveyor_offs = 0;
}

inline void game_screen_flick (void) {
	if (prx == 4 && pvx < 0) {
		n_pant --;
	} else if (prx >= 244 && pvx > 0) {
		n_pant ++;
	} else if (pry == 0 && pvy < 0 && n_pant >= c_map_w) {
		n_pant -= c_map_w;
		pvy = - PLAYER_VY_JUMP_MAX;
	} else if (pry >= 192 && pvy > 0) {
		n_pant += c_map_w;
	}
}

inline void game_prepare_scr (void) {
	if (on_pant == 99) {
		if (pkilled) {
			map_scr_clear ();
		} 
		map_scr_draw_box ();
	} else {
		if (n_pant == on_pant + 1) {
			map_scr_draw_from_right ();
		} else if (n_pant + 1 == on_pant) {
			map_scr_draw_from_left ();
		} else if (n_pant == on_pant + c_map_w) {
			map_scr_draw_from_down ();
		} else if (n_pant + c_map_w == on_pant) {
			map_scr_draw_from_up ();
		}
		px = prx << FIX_BITS;
		py = pry << FIX_BITS;
	}

	enems_load ();
	hotspots_load ();
	fabolee_init ();
	pkilled = 0;
	no_ct = 0;
}

inline void game_extra_shit_do (void) {
	if (no_ct) {
		no_ct --;
		//SMS_MT_addMetaspriteSimple (no_x, no_y, spr_it [3]);
		SMS_MT_add2x2MetaSpriteSimpleUnrolled (no_x, no_y, spr_it [3]);
	}
}

inline void game_pal_effects (void) {
	switch (level) {
		case 2: pal_cycle_desert_do (); break;
		case 3: pal_cycle_waterfall_do (); break;		
	}
}

inline void game_tile_effects (void) {
	switch (level) {
		case 1: tile_effects_factory_do (); break;
	}
}

inline void game_flickscreen_stage (void) {
	// VDP On
	SMS_displayOn ();

	hud_render_base ();
	hud_render_numbers ();
	hud_render_nenems ();

	fskipctr = pisdead = 0;

	PSGPlay (level_tunes [level]);
	on_pant = 99;
	
	while (1) {
		//SMS_setBGPaletteColor (0, 0x1A);		
		
		if (on_pant != n_pant) {
			game_prepare_scr ();
			on_pant = n_pant;
		}

		half_life = 1 - half_life; frame_counter ++;
		run_flip_flop = half_life;
		jitter_x = jitter [frame_counter & 15];
		jitter_y = jitter [15 - (frame_counter & 15)];

		fskipctr ++; if (fskipctr == 6) fskipctr = 0;
		if (!tv_type || fskipctr) {
			// Read controller
			gpint = SMS_getKeysStatus ();

			// Uglier but saves cycles: sprite rendering embedded in "do" functions
			if (pkilled) player_kill (); else player_do ();
			SMS_MT_initSpritesEx (7); 	// Sprites 0-6 are reserved for the hud.
			simplecoco_do ();
			fabolee_do ();
			hotspots_do ();
			enems_do ();
			player_render ();
			game_extra_shit_do ();
			SMS_MT_finalizeSpritesEx ();
		} 

		// Waits until it's safe to copy sprites to SAT

		//SMS_setBGPaletteColor (0, 0x10);

		SMS_waitForVBlank ();
		UNSAFE_SMS_copySpritestoSAT ();
		game_pal_effects ();
		game_tile_effects (); 
		
		// OGT
		ogt_run ();	
		
		// Check if we should flick the screen
		game_screen_flick ();
//debug_print_hex (16, 1, (unsigned char) pvy);
		// Exit conditions
		if (pisdead) break;
	}	
}

inline void game_scrolling_stage (void) {
	// Init
	scroller_init ();
	SMS_VDPturnOnFeature (VDPFEATURE_HIDEFIRSTCOL);
	map_scr = collision_buffer;

	// VDP On
	SMS_displayOn ();

	hud_render_base ();
	hud_render_numbers ();
	hud_render_nenems ();

	pisdead = 0;

	PSGPlay (level_tunes [level]);

	while (1) {
		half_life = 1 - half_life; frame_counter ++;
		run_flip_flop = half_life;
		
		// Waits until it's safe to copy sprites to SAT

		SMS_waitForVBlank ();

		UNSAFE_SMS_copySpritestoSAT ();

		scroller_draw_new_column_in_blank ();	
		
		fskipctr ++; if (fskipctr == 6) fskipctr = 0;
		if (!tv_type || fskipctr) {
			advance_cam = half_life;
			scroller_cam_advance ();
			scroller_fill_buffer ();	
			cam_x_module = (unsigned char) (cam_x & 0xff);
			SMS_setBGScrollX (- cam_x_module);
			
			// Read controller
			gpint = SMS_getKeysStatus ();

			if (pkilled) player_kill (); else player_do ();
			SMS_MT_initSpritesEx (7); 	// Sprites 0-6 are reserved for the hud.
			player_render_scrolly ();
			SMS_MT_finalizeSpritesEx ();
		} 

		// OGT
		ogt_run ();

		// Exit conditions
		if (pisdead) break;
	}

	SMS_VDPturnOffFeature (VDPFEATURE_HIDEFIRSTCOL);
}

inline void game_loop (void) {
	if (level < 5) {
		game_flickscreen_stage ();
	} else {
		game_scrolling_stage ();
	}

	PSGStop ();

	// Add stuff to exit cleanly
	map_scr_clear ();
	SMS_displayOff ();
}
