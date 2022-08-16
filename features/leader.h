#include QMK_KEYBOARD_H
#include "../definitions/layers.h"
#include "../definitions/keycodes.h"
#include "../features/tapdance.h"
#include "lighting.h"

bool did_leader_succeed;
void my_leader_matrix_scan_user(void);
