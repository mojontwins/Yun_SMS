// MT MK1 SMS version 0.1 [Yun]
// Copyleft 2016 The Mojon Twins

// Levelset descriptor arrays

// Level banks
const unsigned char level_banks [] = {
	3, 4, 5, 6, 7
};

// Compressed map data
const unsigned char * const level_maps [] = {
	work_level0_map_0c_bin,
	work_level1_map_1c_bin,
	work_level2_map_2c_bin,
	work_level3_map_3c_bin,
	work_level4_map_4c_bin
};

// Metatileset patterns
const unsigned char * const level_ts_patterns [] = {
	work_level0_ts_patterns0c_bin,
	work_level1_ts_patterns1c_bin,
	work_level2_ts_patterns2c_bin,
	work_level3_ts_patterns3c_bin,
	work_level4_ts_patterns4c_bin
};

// Metaspriteset patterns
const unsigned char * const level_ss_patterns [] = {
	work_level0_ss_patterns_enems0c_bin,
	work_level1_ss_patterns_enems1c_bin,
	work_level2_ss_patterns_enems2c_bin,
	work_level3_ss_patterns_enems3c_bin,
	work_level4_ss_patterns_enems4c_bin
};

// Metatilesets
const unsigned int * const level_ts_tmaps [] = {
	ts_meta0_tmaps,
	ts_meta1_tmaps,
	ts_meta2_tmaps,
	ts_meta3_tmaps,
	ts_meta4_tmaps
};

// Palettes
const unsigned char * const level_pals [] = {
	pals0,
	pals1,
	pals2,
	pals3,
	pals4
};

// Initial position
const unsigned char level_scr_ini [] = {
	20, 20, 23, 9, 0
};

const unsigned char level_ini_x [] = {
	2, 3, 13, 2, 2
};

const unsigned char level_ini_y [] = {
	4, 7, 4, 4, 4
};

// Level width (in screens)
const unsigned char level_map_w [] = {
	4, 4, 4, 3, 6
};

// Enems data
const unsigned char * const level_enems [] = {
	enems_0,
	enems_1,
	enems_2,
	enems_3,
	enems_4
};

// Behaviours
const unsigned char * const level_behs [] = {
	behs0,
	behs1,
	behs2,
	behs3,
	behs4
};

// Hotspots
const unsigned char * const level_hotspots [] = {
	hotspots_0,
	hotspots_1,
	hotspots_2,
	hotspots_3,
	hotspots_4
};

// Music
const unsigned char * const level_tunes [] = {
	work_ogt_m_ingame0_psg,
	work_ogt_m_ingame1_psg,
	work_ogt_m_ingame2_psg,
	work_ogt_m_ingame3_psg,
	work_ogt_m_ingame4_psg
};
