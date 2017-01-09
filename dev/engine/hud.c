// MT MK1 SMS version 0.1 [Yun]
// Copyleft 2016 The Mojon Twins

// Sprite based hud

#include "../lib/SMSlib.h"

#include "hud.h"

extern unsigned char plife, pkeys, baddies_count;

void hud_render_base (void) {
	SMS_MT_setSpriteFastAt (8, 8, 0, 10);
	SMS_MT_setSpriteFastAt (8, 16, 1, 12);
	SMS_MT_setSpriteFastAt (8, 24, 2, 11);
}

void hud_render_numbers (void) {
	SMS_MT_setSpriteFastAt (20, 8, 3, plife < 10 ? plife : 9);
	SMS_MT_setSpriteFastAt (20, 16, 4, pkeys);
}

void hud_render_nenems (void) {
	SMS_MT_setSpriteFastAt (20, 24, 5, baddies_count / 10); 
	SMS_MT_setSpriteFastAt (28, 24, 6, baddies_count % 10);
}

