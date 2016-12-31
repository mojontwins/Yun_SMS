// MT MK1 SMS version 0.1 [Yun]
// Copyleft 2016 The Mojon Twins

// Metaspriteset
// Include this file *after* bank2.h and bank3.h, as it may reference stuff imported there.

#include "ss_yun.h"			// Yun sprites
#include "ss_items.h"		// Item sprites (and more)
#include "ss_fixed0.h"		// Fixed enemies
#include "ss_fixed1.h"		// Fixed enemies

// Facing left == 7
const unsigned char * const spr_pl [] = {
	ss_yun_00_a, ss_yun_01_a, ss_yun_02_a, ss_yun_03_a, ss_yun_04_a, ss_yun_05_a, ss_yun_06_a, 
	ss_yun_00_b, ss_yun_01_b, ss_yun_02_b, ss_yun_03_b, ss_yun_04_b, ss_yun_05_b, ss_yun_06_b
};


const unsigned char * const spr_en [] = {
	// Fixed: mono (0)
	ss_fixed_00_a, ss_fixed_00_b, ss_fixed_01_a, ss_fixed_01_b,

	// Fixed: fanty (4)
	ss_fixed_02_a, ss_fixed_03_a, ss_fixed_02_b, ss_fixed_03_b,	

	// each: frames A-B right, frames A-B left. (+CELL_LEVELENEMS_BASE) (8)
	ss_enems0_00_a, ss_enems0_01_a, ss_enems0_00_b, ss_enems0_01_b, 
	ss_enems0_02_a, ss_enems0_03_a, ss_enems0_02_b, ss_enems0_03_b, 
	ss_enems0_04_a, ss_enems0_05_a, ss_enems0_04_b, ss_enems0_05_b, 
	ss_enems0_06_a, ss_enems0_07_a, ss_enems0_06_b, ss_enems0_07_b,

	ss_enems1_00_a, ss_enems1_01_a, ss_enems1_00_b, ss_enems1_01_b, 
	ss_enems1_02_a, ss_enems1_03_a, ss_enems1_02_b, ss_enems1_03_b, 
	ss_enems1_04_a, ss_enems1_05_a, ss_enems1_04_b, ss_enems1_05_b, 
	ss_enems1_06_a, ss_enems1_07_a, ss_enems1_06_b, ss_enems1_07_b,

	ss_enems2_00_a, ss_enems2_01_a, ss_enems2_00_b, ss_enems2_01_b, 
	ss_enems2_02_a, ss_enems2_03_a, ss_enems2_02_b, ss_enems2_03_b, 
	ss_enems2_04_a, ss_enems2_05_a, ss_enems2_04_b, ss_enems2_05_b, 
	ss_enems2_06_a, ss_enems2_07_a, ss_enems2_06_b, ss_enems2_07_b,

	ss_enems3_00_a, ss_enems3_01_a, ss_enems3_00_b, ss_enems3_01_b, 
	ss_enems3_02_a, ss_enems3_03_a, ss_enems3_02_b, ss_enems3_03_b, 
	ss_enems3_04_a, ss_enems3_05_a, ss_enems3_04_b, ss_enems3_05_b, 
	ss_enems3_06_a, ss_enems3_07_a, ss_enems3_06_b, ss_enems3_07_b,

	ss_enems4_00_a, ss_enems4_01_a, ss_enems4_00_b, ss_enems4_01_b, 
	ss_enems4_02_a, ss_enems4_03_a, ss_enems4_02_b, ss_enems4_03_b, 
	ss_enems4_04_a, ss_enems4_05_a, ss_enems4_04_b, ss_enems4_05_b, 
	ss_enems4_06_a, ss_enems4_07_a, ss_enems4_06_b, ss_enems4_07_b,

	// Upside down (+CELL_UPSIDEDOWN_BASE) (88)

	ss_fixed_00_ud, ss_fixed_01_ud, 
	ss_fixed_02_ud, ss_fixed_03_ud, 
	
	ss_enems0_00_ud, ss_enems0_01_ud,
	ss_enems0_02_ud, ss_enems0_03_ud,
	ss_enems0_04_ud, ss_enems0_05_ud,
	ss_enems0_06_ud, ss_enems0_07_ud,

	ss_enems1_00_ud, ss_enems1_01_ud,
	ss_enems1_02_ud, ss_enems1_03_ud,
	ss_enems1_04_ud, ss_enems1_05_ud,
	ss_enems1_06_ud, ss_enems1_07_ud,

	ss_enems2_00_ud, ss_enems2_01_ud,
	ss_enems2_02_ud, ss_enems2_03_ud,
	ss_enems2_04_ud, ss_enems2_05_ud,
	ss_enems2_06_ud, ss_enems2_07_ud,

	ss_enems3_00_ud, ss_enems3_01_ud,
	ss_enems3_02_ud, ss_enems3_03_ud,
	ss_enems3_04_ud, ss_enems3_05_ud,
	ss_enems3_06_ud, ss_enems3_07_ud,

	ss_enems4_00_ud, ss_enems4_01_ud,
	ss_enems4_02_ud, ss_enems4_03_ud,
	ss_enems4_04_ud, ss_enems4_05_ud,
	ss_enems4_06_ud, ss_enems4_07_ud,

	// Whatever (132)
	ss_items_07,

	// Zurully (133)
	ss_fixed2_00, ss_fixed2_00_ud,

	// Monococo appearing alt (135)
	ss_fixed_04_a
};

const unsigned char * const spr_it [] = {
	ss_items_00, ss_items_01, ss_items_02, ss_items_03, ss_items_04, ss_items_05, ss_items_06, ss_items_07
};
