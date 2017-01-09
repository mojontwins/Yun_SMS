// MT MK1 SMS version 0.1 [Yun]
// Copyleft 2016 The Mojon Twins

#include "../lib/SMSlib.h"
#include "../lib/PSGlib.h"

#include "../definitions.h"
#include "general.h"
#include "hud.h"
#include "simplecoco.h"
#include "enems.h"

extern unsigned char *en_c_t;
extern unsigned char *en_c_x, *en_c_y;
extern unsigned char *en_c_x1, *en_c_y1;
extern unsigned char *en_c_x2, *en_c_y2;
extern signed char *en_c_mx, *en_c_my;
extern signed char *en_c_fs;
extern unsigned int enoffs;

extern unsigned char baddies_count;

extern unsigned char en_t [MAX_ENEMS];
extern unsigned char en_x [MAX_ENEMS], en_y [MAX_ENEMS];
extern unsigned char en_x1 [MAX_ENEMS], en_y1 [MAX_ENEMS];
extern unsigned char en_x2 [MAX_ENEMS], en_y2 [MAX_ENEMS];
extern signed char en_mx [MAX_ENEMS], en_my [MAX_ENEMS];
extern unsigned char en_fs [MAX_ENEMS];

extern signed int enf_x [MAX_ENEMS_SCREEN], enf_y [MAX_ENEMS_SCREEN];
extern signed char enf_vx [MAX_ENEMS_SCREEN], enf_vy [MAX_ENEMS_SCREEN];
extern unsigned char en_s [MAX_ENEMS_SCREEN], en_ct [MAX_ENEMS_SCREEN];
extern unsigned char en_ud [MAX_ENEMS_SCREEN];
extern unsigned char en_cell [MAX_ENEMS_SCREEN], en_facing, en_fr;
extern unsigned char en_r [MAX_ENEMS_SCREEN];
extern unsigned char mono_sprite;

extern unsigned char c_map_w, c_map_h;
extern const unsigned char *c_enems;

extern const unsigned char *gp_rom;
extern unsigned char gpit, gpjt;
extern unsigned int gpint;
extern unsigned char rda, rdb, rdc, rdct, rdt;
extern unsigned char rdx, rdy;

extern unsigned char cx1, cx2, cy1, cy2;
extern unsigned char at1, at2;

extern unsigned char prx, pry;
extern signed int px, py, pcy, pvx, pvy;
extern unsigned char pctj, pstate, pkilled;

extern unsigned char spr_x, spr_y;
extern unsigned char jitter_x, jitter_y;

extern const unsigned char random_seq [];
extern const unsigned char jitter [];
extern const unsigned char * const spr_en [];

extern unsigned char level, n_pant, half_life, run_flip_flop;
extern unsigned char cur_rand, frame_counter;

extern unsigned char pregotten, pgotten, pj;
extern signed int pgtmx, pgtmy;

extern unsigned char fbl_lock_on [FABOLEES_MAX];
extern unsigned char fbl_ct [FABOLEES_MAX];

extern const unsigned char sfx_shirt_psg [];
extern const unsigned char ss_items_02 [];

extern const unsigned char monococo_state_times [];

// Baddies!

void enems_init_pointers (void) {
	en_c_t = en_t + enoffs;
	en_c_x = en_x + enoffs; en_c_y = en_y + enoffs;
	en_c_x1 = en_x1 + enoffs; en_c_y1 = en_y1 + enoffs;
	en_c_x2 = en_x2 + enoffs; en_c_y2 = en_y2 + enoffs;
	en_c_mx = en_mx + enoffs; en_c_my = en_my + enoffs;
	en_c_fs = en_fs + enoffs;
}

void enems_init (void) {
	// Unpacks enems data to RAM
	gp_rom = c_enems;
	enoffs = 0; enems_init_pointers ();
	// gpit = c_map_w * c_map_h * 3; 
	gpit = 0; gpjt = c_map_h; while (gpjt --) gpit += c_map_w;
	gpit = gpit + gpit + gpit;
	while (gpit --) {
		// read t
		rdt = *gp_rom ++; *en_c_t ++ = rdt;
		if (rdt && rdt != 4) baddies_count ++;

		// read XY1
		rda = *gp_rom ++;
		rdb = rda & 0xf0;
		rdc = rda << 4;
		*en_c_x ++ = rdb; *en_c_y ++ = rdc;
		*en_c_x1 = rdb; *en_c_y1 = rdc;

		// read XY2
		rda = *gp_rom ++;
		rdb = rda & 0xf0;
		rdc = rda << 4;
		*en_c_x2 = rdb; *en_c_y2 = rdc;

		// read P
		rda = *gp_rom ++;
		if (rda == 1) {
			*en_c_fs ++ = 1;
		} else {
			rda >>= 1;
			*en_c_fs ++ = 0;
		}

		*en_c_mx ++ = ADD_SIGN_2 (*en_c_x1, *en_c_x2, rda);
		*en_c_my ++ = ADD_SIGN_2 (*en_c_y1, *en_c_y2, rda);

		// fix limits 
		if (*en_c_x1 > *en_c_x2) { rda = *en_c_x1; *en_c_x1 = *en_c_x2; *en_c_x2 = rda; }
		if (*en_c_y1 > *en_c_y2) { rda = *en_c_y1; *en_c_y1 = *en_c_y2; *en_c_y2 = rda; }

		// advance pointers
		en_c_x1 ++; en_c_y1 ++;
		en_c_x2 ++; en_c_y2 ++;
	}
}

void enems_init_fp (void) {
	enf_x [gpit] = en_c_x [gpit] << FIX_BITS;
	enf_y [gpit] = en_c_y [gpit] << FIX_BITS;
	enf_vx [gpit] = enf_vy [gpit] = 0;
}

void enems_load (void) {
	// Fill / initialize pointers and stuff like that
	// Create temporal enemy data (screen)
	enoffs = n_pant + n_pant + n_pant;
	enems_init_pointers ();

	// Non persistent data, some of it depends upon enemy type
	for (gpit = 0; gpit < MAX_ENEMS_SCREEN; gpit ++) {
		switch (en_c_t [gpit]) {
			case 1:
			case 2:
			case 3:
			case 4:
				en_s [gpit] = (level << 2) + en_c_t [gpit] - 1;

				// You may make an enemy fall using your fabolees
				// and not kill it. It should be restored to its
				// original path next time you enter this screen.
				// As y1 <= y2, the simplest way to achieve this
				// I've found is...
				if (en_c_y [gpit] > en_c_y2 [gpit]) en_c_y [gpit] = en_c_y2 [gpit];

				break;

			case 6:
				// Custom yun fanties
				en_c_x [gpit] = en_c_x1 [gpit];
				en_c_y [gpit] = en_c_y1 [gpit];

				enems_init_fp ();
				break;

			case 8:
				// Pezones (Zurully)
				PEZON_COUNTER [gpit] = PEZON_COUNT_MAX [gpit] = PEZON_WAIT + (rda << 3);
				en_r [gpit] = 0;
				en_y [gpit] = en_y1 [gpit];
				enems_init_fp ();

			case 9:
				// Monococo
				en_c_mx [gpit] = 0; en_c_my [gpit] = BASE_TIME_HIDDEN - (RAND8 & 0xf);
				break;
		}

		en_ct [gpit] = 0;
		en_ud [gpit] = 0;
	}
}

void enems_kill (void) {
	en_ct [gpit] = 8;
	//sfx_play (6, 2);
	PSGSFXPlay (SFX_CLOTHES, SC_ENEMS);
	en_c_t [gpit] = 0;
	baddies_count --;
	hud_render_nenems ();

	// Find fabolee(s) locked on to this
	gpjt = FABOLEES_MAX; while (gpjt --) if (fbl_lock_on [gpjt] == gpit) fbl_ct [gpjt] = 0;
}

void enems_do (void) {
	for (gpit = 0; gpit < 3; gpit ++) {
		if (en_ct [gpit]) {
			en_ct [gpit] --;
			SMS_MT_addMetaspriteSimple (en_c_x [gpit], en_c_y [gpit] - 1, SPR_EXPLOSION); // Embedded here for speed
			continue;
		}

		if (en_c_t [gpit]) {
			// Gotten preliminary:
			pregotten = (prx + 9 >= en_c_x [gpit] && prx <= en_c_x [gpit] + 17);

			// Upside down state
			if (en_ud [gpit]) {
				cx1 = (en_c_x [gpit] + 4) >> 4;
				cx2 = (en_c_x [gpit] + 11) >> 4;
				cy1 = cy2 = ((en_c_y [gpit] + 15) >> 4) + TILE_ORIGIN;	// Cheese
				cm_two_points ();
				if (at1 + at2) {
					if (en_c_t [gpit] == 9) {
						enems_kill ();
						continue;
					}
				} else {
					en_c_y [gpit] ++; 
					enf_y [gpit] = en_c_y [gpit] << FIX_BITS; 
				} 
			}

			// Move enemies
			switch (en_c_t [gpit]) {
				case 1:
				case 2:
				case 3:
				case 4:
					#include "enemmods/enem_linear.h"
					break;
				case 6:
					#include "enemmods/enem_fanty.h"
					break;
				case 8:
					#include "enemmods/enem_pezons.h"
					break;
				case 9:
					#include "enemmods/enem_monococo.h"
					break;
			}

			//SMS_MT_addMetaspriteSimple (spr_x, spr_y - 1, spr_en [en_cell [gpit]]); // embedded here for speed
			SMS_MT_add2x2MetaSpriteSimpleUnrolled (spr_x, spr_y - 1, spr_en [en_cell [gpit]]); // embedded here for speed

			if (en_c_t [gpit] == 4) {
				if (pregotten && !pgotten && !pj) {
					// Horizontal moving platforms
					if (en_c_mx [gpit]) {
						if (pry >= en_c_y [gpit] && pry <= en_c_y [gpit] + 4) {
							pgotten = 1;
							pgtmx = en_c_mx [gpit] << (FIX_BITS - en_c_fs [gpit]);
							pry = en_c_y [gpit]; py = pry << FIX_BITS;
							pvy = 0;
						}
					}
					
					// Vertical moving platforms
					if (
						(en_c_my [gpit] < 0 && pry + 1 >= en_c_y [gpit] && pry <= en_c_y [gpit] + 4) ||
						(en_c_my [gpit] > 0 && pry + en_c_my [gpit] >= en_c_y [gpit] && pry <= en_c_y [gpit] + 4)
					) {
						pgotten = 1;
						pgtmy = en_c_my [gpit] << (FIX_BITS - en_c_fs [gpit]);
						pry = en_c_y [gpit]; py = pry << FIX_BITS;						
						pvy = 0;
					}
				}
			} else if (collide (prx - 4, pry - 16, spr_x, spr_y)) {
				if (en_ud [gpit]) {
					if (!(gpint & PORT_A_KEY_2)) {
						pvy = -PLAYER_VY_JUMP_INITIAL << 1;
					} else {
						pj = 1; 
						pctj = 0;
						pvy = -PLAYER_VY_JUMP_INITIAL;
					}

					if (!en_ct [gpit]) enems_kill ();
				} else if (en_c_t [gpit] != 9 || en_c_mx [gpit] == 2) {
					if (pstate == STATE_NORMAL) pkilled = 1;
				}				
			}
		}
	}
}

/*
void enems_render (void) {
	for (gpit = 0; gpit < 3; gpit ++) {
		if (en_ct [gpit]) {
			SMS_MT_addMetaspriteSimple (en_c_x [gpit], en_c_y [gpit] - 1, SPR_EXPLOSION);
		} else if (en_c_t [gpit]) {
			SMS_MT_addMetaspriteSimple (en_c_x [gpit], en_c_y [gpit] - 1, spr_en [en_cell [gpit]]);
		}
	}
}
*/
