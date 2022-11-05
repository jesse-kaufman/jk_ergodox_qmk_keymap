bool did_leader_succeed;
bool leading;

void my_leader_matrix_scan_user(void);

#define MY_KEY_SEQ(kc1,kc2,kc3,kc4,kc5,tap_kc) \
	if (kc5) { SEQ_FIVE_KEYS(kc1,kc2,kc3,kc4,kc5) { tap_code16(tap_kc); did_leader_succeed = true; } } \
	else if (kc4) { SEQ_FOUR_KEYS(kc1,kc2,kc3,kc4) { tap_code16(tap_kc); did_leader_succeed = true; } } \
	else if (kc3) { SEQ_THREE_KEYS(kc1,kc2,kc3) { tap_code16(tap_kc); did_leader_succeed = true; } } \
	else if (kc2) { SEQ_TWO_KEYS(kc1,kc2) { tap_code16(tap_kc); did_leader_succeed = true; } } \
	else if (kc1) { SEQ_ONE_KEY(kc1) { tap_code16(tap_kc); did_leader_succeed = true; } };

#define MY_SS_SEQ(kc1,kc2,kc3,kc4,kc5,string) \
	if (kc5) { SEQ_FIVE_KEYS(kc1,kc2,kc3,kc4,kc5) { SEND_STRING(string); did_leader_succeed = true; } } \
	else if (kc4) { SEQ_FOUR_KEYS(kc1,kc2,kc3,kc4) { SEND_STRING(string); did_leader_succeed = true; } } \
	else if (kc3) { SEQ_THREE_KEYS(kc1,kc2,kc3) { SEND_STRING(string); did_leader_succeed = true; } } \
	else if (kc2) { SEQ_TWO_KEYS(kc1,kc2) { SEND_STRING(string); did_leader_succeed = true; } } \
	else if (kc1) { SEQ_ONE_KEY(kc1) { SEND_STRING(string); did_leader_succeed = true; } };
