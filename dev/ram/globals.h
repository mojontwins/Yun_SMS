// MT MK1 SMS version 0.1 [Yun]
// Copyleft 2016 The Mojon Twins

unsigned char fskipctr;

unsigned char tv_type, ticks, ticker;
unsigned char half_life, frame_counter;
unsigned char run_flip_flop;
unsigned char cur_rand;

// Current level
unsigned char level;
unsigned char c_bank;
unsigned char c_map_w, c_map_h;
const unsigned char *c_map;
const unsigned int *c_ts_tmaps;
const unsigned char *c_pals;
const unsigned char *c_enems;
const unsigned char *c_hotspots;
unsigned char c_lenb;
const unsigned char *c_behs;

// General 
unsigned char *gp_gen, *gp_map;
const unsigned char *gp_rom;
unsigned char rda, rdb, rdc, rdct, rdt;
unsigned char gpit, gpjt, cocoit;
unsigned char rdx, rdy, rdyn;
unsigned char spr_x, spr_y;
unsigned int gpint, adr1, adr2;
signed int rds16;
unsigned char jitter_x, jitter_y;

// Used for collision with scenary
unsigned char cx1, cx2, cy1, cy2;
unsigned char at1, at2;

// Contains an uncompressed copy of the current level map
unsigned char map [4608];				// which is 192*24

// Current screen
unsigned char *map_scr;					// pointer to current screen
unsigned char n_pant, on_pant;
unsigned char scroll_y;
unsigned char cur_col_y;

// Enemies. general
unsigned char baddies_count;

// Enemies. Persistent
unsigned char en_t [MAX_ENEMS];
unsigned char en_x [MAX_ENEMS], en_y [MAX_ENEMS];
unsigned char en_x1 [MAX_ENEMS], en_y1 [MAX_ENEMS];
unsigned char en_x2 [MAX_ENEMS], en_y2 [MAX_ENEMS];
signed char en_mx [MAX_ENEMS], en_my [MAX_ENEMS];
unsigned char en_fs [MAX_ENEMS];

// Enemies. Current screen
signed int enf_x [MAX_ENEMS_SCREEN], enf_y [MAX_ENEMS_SCREEN];
signed char enf_vx [MAX_ENEMS_SCREEN], enf_vy [MAX_ENEMS_SCREEN];
unsigned char en_s [MAX_ENEMS_SCREEN], en_ct [MAX_ENEMS_SCREEN];
unsigned char en_ud [MAX_ENEMS_SCREEN];
unsigned char en_cell [MAX_ENEMS_SCREEN], en_facing, en_fr;
unsigned char en_r [MAX_ENEMS_SCREEN];
unsigned char mono_sprite;

// Pointers for current screen
unsigned char *en_c_t;
unsigned char *en_c_x, *en_c_y;
unsigned char *en_c_x1, *en_c_y1;
unsigned char *en_c_x2, *en_c_y2;
signed char *en_c_mx, *en_c_my;
signed char *en_c_fs;
unsigned int enoffs;

// Cocos
signed int coco_x [COCOS_MAX], coco_y [COCOS_MAX];
signed int coco_vx [COCOS_MAX], coco_vy [COCOS_MAX];
unsigned char coco_flag [COCOS_MAX];

// Player
signed int px, py, pcy, pvx, pvy;
unsigned char pfacing, psprid;
unsigned char pj, pctj, pjb, pgotten, pregotten, ppossee, psprint;
unsigned char pobjs, plife, pcontinues, pkeys, pkilled;
unsigned char pstate, pctstate, pkilled, phit;
signed int pgtmx, pgtmy;
unsigned char pfiring, pice, pconveyor, pconvd1, pconvd2;
unsigned char pisdead;

// Aux player
unsigned char prx, pry, ptx1, ptx2, pty1, pty2;
unsigned char pfacingv, pfacingh;

// Safe spot
signed int px_safe, py_safe;
unsigned char n_pant_safe;

#ifdef ENABLE_PROPELLERS
unsigned char ppropelled;
#endif

// Fabolees
// Those are for regular, fp fabolees
signed int fbl_x [FABOLEES_MAX], fbl_y [FABOLEES_MAX];
signed int fbl_vx [FABOLEES_MAX], fbl_vy [FABOLEES_MAX];
unsigned char fbl_ct [FABOLEES_MAX];
unsigned char fbl_lock_on [FABOLEES_MAX];
unsigned char fbl_accctr [FABOLEES_MAX];

// Arrays for simple, integer, precalculated fabolees
/*
unsigned char fbl_x [FABOLEES_MAX], fbl_y [FABOLEES_MAX];
unsigned char fbl_ct [FABOLEES_MAX];
unsigned char fbl_lock_on [FABOLEES_MAX];
unsigned char fbl_accctr [FABOLEES_MAX];
unsigned char fbl_idx_y [FABOLEES_MAX], fbl_idx_my [FABOLEES_MAX], fbl_idx_x [FABOLEES_MAX];
unsigned char fbl_facing [FABOLEES_MAX];
*/
// (Very) simple hotspots
unsigned char hact [MAX_SCREENS];
unsigned char hrt, hrx, hry;

// Extra shit
unsigned char no_ct, no_x, no_y;