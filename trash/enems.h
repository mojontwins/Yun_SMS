// MT MK1 SMS version 0.1 [Yun]
// Copyleft 2016 The Mojon Twins

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
	gpit = MAX_ENEMS; while (gpit --) {
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
				en_s [gpit] = en_c_t [gpit] - 1;
				break;
			case 6:
				// Custom yum fanties
				en_c_x [gpit] = en_c_x1 [gpit];
				en_c_y [gpit] = en_c_y1 [gpit];

				enf_x [gpit] = en_c_x [gpit] << FIX_BITS;
				enf_y [gpit] = en_c_y [gpit] << FIX_BITS;

				enf_vx [gpit] = enf_vy [gpit] = 0;
				break;
			case 9:
				// Monococo
				en_c_mx [gpit] = 0; en_c_my [gpit] = BASE_TIME_HIDDEN - (RAND8 & 0xf);
				break;
		}

		en_ct [gpit] = 0;
		en_ud [gpit] = 0;
	}
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
			// gpjt = (prx + 11 >= en_c_x [gpit] && prx <= en_c_x [gpit] + 11);

			// TODO: en_ud management
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
				case 9:
					#include "enemmods/enem_monococo.h"
					break;
			}

			SMS_MT_addMetaspriteSimple (en_c_x [gpit], en_c_y [gpit] - 1, spr_en [en_cell [gpit]]); // embedded here for speed

			if (en_c_t [gpit] == 4) {
				// TODO: Moving platforms
			} else {
				// TODO: Collision
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

void enems_kill (void) {
	
}
