// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┐
     * │TAB│ 8 │ S │
     * ├───┼───┼───┤
     * │TAB│ UP│ 9 │
     * ├───┼───┼───┤
     * │ESC│DOWN│ENT│
     * └───┴───┴───┘
     */
    [0] = LAYOUT(
        KC_TAB,  KC_P8,   KC_S,
        KC_TAB,  KC_UP,   KC_P9,
        KC_ESC,  KC_DOWN, KC_ENT
    )
};


#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {  // If you have one encoder, this is usually 0
        if (clockwise) {
            tap_code(KC_O);  // Increase volume
        } else {
            tap_code(KC_L);  // Decrease volume
        }
    }else if (index == 1) {  // If you have one encoder, this is usually 0
        if (clockwise) {
            tap_code(KC_I);  // Increase volume
        } else {
            tap_code(KC_K);  // Decrease volume
        }
    }
    return false;
}
#endif