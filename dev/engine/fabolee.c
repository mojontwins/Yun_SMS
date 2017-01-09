// MT MK1 SMS version 0.1 [Yun]
// Copyleft 2016 The Mojon Twins

// Fabolee - Simple bubbles
// Original implementation
// Accurate but slowish.

#include "../lib/SMSlib.h"
#include "../lib/PSGlib.h"

#include "../definitions.h"
#include "enems.h"
#include "general.h"
#include "fabolee.h"

extern unsigned char gpit;
extern signed int fbl_x [FABOLEES_MAX], fbl_y [FABOLEES_MAX];
extern signed int fbl_vx [FABOLEES_MAX], fbl_vy [FABOLEES_MAX];
extern unsigned char fbl_ct [FABOLEES_MAX];
extern unsigned char fbl_lock_on [FABOLEES_MAX];
extern unsigned char fbl_accctr [FABOLEES_MAX];

extern unsigned char gpit, gpjt;
extern unsigned char rda, rdct, run_flip_flop;
extern unsigned char rdx, rdy;
extern unsigned char half_life, frame_counter;

extern const unsigned char random_seq [];
extern unsigned char cur_rand;
extern const unsigned char * const spr_it [];

extern unsigned char *en_c_t;
extern unsigned char *en_c_x, *en_c_y;
extern signed char *en_c_mx, *en_c_my;
extern unsigned char en_ud [MAX_ENEMS_SCREEN];

extern signed int px, py;
extern unsigned char prx, pry, pvy;
extern unsigned char pfacing, pj;
extern unsigned char pgotten;
extern signed int pgtmx, pgtmy;

extern const unsigned char sfx_kill_psg [];
extern const unsigned char sfx_fanty_psg [];

const unsigned char fabolee_frames [] = { 4, 5, 6, 5 };

inline void fabolee_init (void) {
	gpit = FABOLEES_MAX; while (gpit --) {
		fbl_ct [gpit] = 0; 
	}
}

inline void fabolee_new (void) {
	// Creates new fabolee at px, py.
	gpit = FABOLEES_MAX; while (gpit --) {
		if (!fbl_ct [gpit]) {
			fbl_y [gpit] = py - (16<<FIX_BITS); fbl_x [gpit] = px - (4<<FIX_BITS);
			fbl_vy [gpit] = 0; fbl_vx [gpit] = pfacing ? -FABOLEES_VX_INI : FABOLEES_VX_INI;
			fbl_ct [gpit] = 200; fbl_lock_on [gpit] = 0xff;
			fbl_accctr [rdct] = 0;
			//sfx_play (5, 0);
			PSGSFXPlay (SFX_SPIKE, SC_PLAYER);
			break;
		}
	}
}

inline void fabolee_do (void) {
	rdct = FABOLEES_MAX; while (rdct --) {
		if (fbl_ct [rdct]) {
			gpit = fbl_lock_on [rdct];

			if (gpit == 0xff) {
				if (run_flip_flop) {
					// Vertical
#if FABOLEES_AY == 129
					fbl_vy [rdct] = saturate (fbl_vy [rdct] - 1, FABOLEES_VY_MAX);
#else
					fbl_vy [rdct] = saturate (fbl_vy [rdct] - FABOLEES_AY - FABOLEES_AY, FABOLEES_VY_MAX);
#endif
					if (fbl_y [rdct] <= 0) { fbl_y [rdct] = 0; fbl_vy [rdct] = 4 + (RAND8 & 7); /*16 + (RAND8 & 31);*/ }
					
					// Horizontal
					rda = fbl_accctr [rdct] ? 0 : FABOLEES_AX; fbl_accctr [rdct] ++; if (fbl_accctr [rdct] == 3) fbl_accctr [rdct] = 0;
					fbl_vx [rdct] = (ABS (fbl_vx [rdct]) < FABOLEES_AX) ? 0 : fbl_vx [rdct] - add_sign (fbl_vx [rdct], FABOLEES_AX + rda);

					if (fbl_x [rdct] < 0)					{ fbl_x [rdct] = 0;					fbl_vx [rdct] = -fbl_vx [rdct]; }
					if (fbl_x [rdct] > (240 << FIX_BITS))	{ fbl_x [rdct] = (240<<FIX_BITS);	fbl_vx [rdct] = -fbl_vx [rdct]; }
				}
				fbl_x [rdct] += fbl_vx [rdct];
				fbl_y [rdct] += fbl_vy [rdct];
			} else {	
				fbl_x [rdct] = en_c_x [gpit] << FIX_BITS; fbl_y [rdct] = en_c_y [gpit] << FIX_BITS;
				if (en_c_y [gpit] == 240) {
					fbl_lock_on [rdct] = 0xff;
					enems_kill ();
				}
			}	

			rdx = fbl_x [rdct] >> FIX_BITS;
			rdy = fbl_y [rdct] >> FIX_BITS;

			//if (fbl_ct [rdct] > 50 || half_life) SMS_MT_addMetaspriteSimple (rdx, rdy, spr_it [fabolee_frames [(frame_counter + rdct) & 3]]); // Embedded here for speed
			if (fbl_ct [rdct] > 50 || half_life) SMS_MT_add2x2MetaSpriteSimpleUnrolled (rdx, rdy, spr_it [fabolee_frames [(frame_counter + rdct) & 3]]); // Embedded here for speed

			// Collide
			if (gpit == 0xff) {
				
				if (run_flip_flop) {
					gpjt = 3; while (gpjt --) {
						if (en_c_t [gpjt] && en_c_t [gpjt] != 4 && (en_c_t [gpjt] != 9 || en_c_mx [gpjt] == 2) && !en_ud [gpjt]) {
							if (collide (rdx, rdy, en_c_x [gpjt], en_c_y [gpjt])) {
								en_ud [gpjt] = 1;
								fbl_lock_on [rdct] = gpjt;
								PSGSFXPlay (SFX_FANTY, SC_ENEMS);
								//sfx_play (5, 0);
							}
						}
					}	
				}
				
				if (rdy > 16 && (!pj)) {
					if (prx + 9 >= rdx && prx <= rdx + 17) {
						//if (pry + 17 >= rdy && pry + 12 <= rdy) {
						if (pry + 1 >= rdy && pry <= rdy + 4) {
							pgotten = 1; 
							pgtmy = fbl_vy [rdct]; pgtmx = fbl_vx [rdct];
							//py = (rdy - 16) << FIX_BITS; pry = py >> FIX_BITS;
							pry = rdy; py = pry << FIX_BITS;
							pvy = 0;
						}
					}
				}
			}

			fbl_ct [rdct] --;

			// Free?
			if (!fbl_ct [rdct] && gpit != 0xff) {
				en_ud [gpit] = 0;
				if (en_c_t [gpit] == 9) enems_kill ();
			}

			// Next?
			run_flip_flop = !run_flip_flop;
		} 
	}
}

/*
void fabolee_render (void) {
	rdct = FABOLEES_MAX; while (rdct --) {
		if (fbl_ct [rdct]) {
			rdx = fbl_x [rdct] >> FIX_BITS;
			rdy = fbl_y [rdct] >> FIX_BITS;
			if (fbl_ct [rdct] > 50 || half_life) SMS_MT_addMetaspriteSimple (rdx, rdy, spr_it [fabolee_frames [(frame_counter + rdct) & 3]]);
		}
	}
}
*/
