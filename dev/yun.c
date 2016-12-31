// MT MK1 SMS version 0.1 [Yun]
// Copyleft 2016 The Mojon Twins

#include "lib/SMSlib.h"
#include "lib/PSGlib.h"
#include "lib/aPLib.h"

// Main shoo

#include "definitions.h"

// Include assets

#include "banks/maindata.h"
#include "banks/bank2.h"
#include "banks/bank3.h"
#include "banks/bank4.h"
#include "banks/bank5.h"
#include "banks/bank6.h"
#include "banks/bank7.h"

#include "assets/precalcs.h"
#include "assets/behs.h"
#include "assets/levels.h"
#include "assets/metasprites.h"	
#include "assets/palettes.h"

// RAM

#include "ram/globals.h"

// Engine
#include "engine/printer.h"
#include "engine/hud.h"
#include "engine/general.h"
#include "engine/level.h"
#include "engine/simplecoco.h"
#include "engine/fabolee.h"
#include "engine/player.h"
#include "engine/map.h"
#include "engine/enems.h"
#include "engine/inits.h"
#include "engine/hotspots.h"
#include "engine/game.h"

void main (void) {
	tv_type = !!(SMS_VDPType () & VDP_NTSC);	// 1 = NTSC, 0 = PAL
	ticks = tv_type ? 60 : 50;

	// Compare
	rda = rdb << 4;

	// Sprites take more patterns, so...
	SMS_useFirstHalfTilesforSprites (1);

	level = 3; 
	plife = 5;
	init_world ();

	SMS_VRAMmemsetW (SMS_PNTAddress, 256, 1536);
	
	while (1) {
		level_prepare ();
		map_prepare ();
		game_init ();

		game_loop ();
	}
}
