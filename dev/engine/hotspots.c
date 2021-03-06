// MT MK1 SMS version 0.1 [Yun]
// Copyleft 2016 The Mojon Twins

// (Very) simple hotspots

#include "../lib/SMSlib.h"

#include "../definitions.h"
#include "hud.h"
#include "general.h"
#include "hotspots.h"

extern unsigned char gpit;
extern unsigned char n_pant;
extern const unsigned char *gp_rom;
extern unsigned char rda, rdb;
extern unsigned char pkeys, plife;
extern unsigned char prx, pry;

extern const unsigned char *c_hotspots;
extern unsigned char hact [MAX_SCREENS];
extern unsigned char hrt, hrx, hry;

extern const unsigned char * const spr_it [];

inline void hotspots_init (void) {
	gpit = MAX_SCREENS; while (gpit --) hact [gpit] = 1;
}

inline void hotspots_load (void) {
	hrt = 0;
	gp_rom = (unsigned char *) c_hotspots; gp_rom += (n_pant << 1);
	rdb = *gp_rom ++; rda = *gp_rom;
	if (rdb && rdb < 3 && hact [n_pant]) {
		hrt = rdb;
		hrx = rda & 0xf0; hry = rda << 4;
	}
}

inline void hotspots_do (void) {
	if (hrt) {
		SMS_MT_addMetaspriteSimple (hrx, hry - 1, spr_it [hrt - 1]);

		if (collide (prx, pry - 16, hrx, hry)) {
			switch (hrt) {
				case 1:
					pkeys ++;
					break;
				case 2:
					plife ++;
					break;
			}
			hrt = 0; hact [n_pant] = 0;
			hud_render_numbers ();
			// Sound
		}
	}
}
