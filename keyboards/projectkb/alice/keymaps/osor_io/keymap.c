#include QMK_KEYBOARD_H

#define BA0 0
#define FN0 1
#define BA1 2
#define FN1 3
#define SY1 4
#define EX1 5

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = 
{
	//
	// Base layer that's as default as it can be. Both spacebars are spaces, we have a windows key, 
	// and only the right control key is replaced to go to the classic function layer to do the F keys,
	// some movement, some RGB stuff, etc.
	//
	[BA0] = LAYOUT_alice_split_bs(
	    KC_ESC,  KC_TILD, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_DEL,  KC_BSPC,
	    KC_PGUP, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
	    KC_PGDN, KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
	             KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RGUI,
	             KC_LCTL,                   KC_LALT, KC_SPC,  KC_LWIN,          KC_SPC, KC_RALT,          			  						  MO(FN0)
	),

	//
	// @@DEPENDENCY: Keep updated with FN1
	//
	// Base function layer that does the classic custom function layer stuff, like some movement, RGB modification and all.
	// Besides this, it also switches between base layers, that is, in the 3 key column at the top left, we have all the base layers
	// so we can quickly switch to them. BA0 is likely to be used for gaming (cause of the spacebar) or other people using this keyboard
	// and the other one for text/code.
	//
	[FN0] = LAYOUT_alice_split_bs(
	    DF(BA0), RGB_TOG, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,  KC_DEL,
	    DF(BA1), RGB_MOD, _______, KC_LWIN, KC_UP,   _______, RGB_TOG,          RGB_SAI, RGB_HUI, RGB_VAI, _______, KC_PSCR, _______, _______, _______,
	    _______, RGB_RMOD,_______, KC_LEFT, KC_DOWN, KC_RGHT, RGB_MOD,          RGB_SAD, RGB_HUD, RGB_VAD, _______, _______, _______,          _______,
	             _______, BL_INC,  BL_DEC,  BL_TOGG, BL_BRTG, RGB_RMOD,         _______, _______, _______, _______, _______, _______, _______, _______,
	             RESET,                     _______, _______, _______,          _______, _______,                                              _______
	),

	//
	// Base layer that has the left spacebar go into the symbol layer and the "code" key go into the movement layer. 
	//
	[BA1] = LAYOUT_alice_split_bs(
	    KC_ESC,  KC_TILD, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_DEL,  KC_BSPC,
	    KC_PGUP, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
	    KC_PGDN, KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
	             KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RGUI,
	             KC_LCTL,                   KC_LALT, MO(SY1), MO(EX1),          KC_SPC, KC_RALT,                                              MO(FN1)
	),

	//
	// @@DEPENDENCY: Keep updated with FN1
	//
	// Copy of FN0 cause it seems to be doing weird stuff when trying to access that one from BA1.
	//
	[FN1] = LAYOUT_alice_split_bs(
	    DF(BA0), RGB_TOG, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,  KC_DEL,
	    DF(BA1), RGB_MOD, _______, KC_LWIN, KC_UP,   _______, RGB_TOG,          RGB_SAI, RGB_HUI, RGB_VAI, _______, KC_PSCR, _______, _______, _______,
	    _______, RGB_RMOD,_______, KC_LEFT, KC_DOWN, KC_RGHT, RGB_MOD,          RGB_SAD, RGB_HUD, RGB_VAD, _______, _______, _______,          _______,
	             _______, BL_INC,  BL_DEC,  BL_TOGG, BL_BRTG, RGB_RMOD,         _______, _______, _______, _______, _______, _______, _______, _______,
	             RESET,                     _______, _______, _______,          _______, _______,                                              _______
	),

	//
	// Symbol layer to have close to the home row most symbols and keys that I'd normally use for programming. A lot of them are made so they
	// can be used with pianoing (pressing keys together in a row) such as -> := () [] {} etc. It also has underscore on the right spacebar
	// so it's easy to write snake_case_words. Also escape is on C so it's not a big strain to get out of insert modes on modal editors.
	//
	[SY1] = LAYOUT_alice_split_bs(
	    _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_DEL,
	    _______, _______, _______, KC_LWIN, KC_PLUS, KC_AMPR, KC_ASTR,          _______, KC_LPRN, KC_RPRN, KC_PIPE, KC_HASH, _______, _______, _______,
	    _______, _______, _______, KC_LABK, KC_MINS, KC_RABK, _______,          _______, KC_LCBR, KC_RCBR, KC_COLN, KC_EQL,  _______,          _______,
	             _______, _______, _______, KC_ESC,  _______, KC_EXLM,          KC_EXLM, _______, KC_LBRC, KC_RBRC, _______, _______, _______, _______,
	             _______,                   _______, _______, _______,          KC_UNDS, _______,                                              _______
	),

	//
	// Extra/Movement layer. Not much to say on this one, basically you have the arrows where they would normally be in VI-like editors. You just need to
	// keep the modifier key pressed to move with them. Maybe some other movement stuff will be added here in the future. It might also host other stuff that
	// didn't fit well on other layers, like insert, pause, etc.
	//
	[EX1] = LAYOUT_alice_split_bs(
	    _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_DEL,
	    _______, _______, _______, _______, _______, _______, _______,          _______, _______, KC_INS,  _______, KC_PAUS, _______, _______, _______,
	    _______, _______, _______, _______, _______, _______, _______,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,          _______,
	             _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______,
	             _______,                   _______, _______, _______,          _______, _______,                                              _______
	)
};