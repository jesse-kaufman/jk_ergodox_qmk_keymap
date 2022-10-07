# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file
LTO_ENABLE = yes
TAP_DANCE_ENABLE = yes
CAPS_WORD_ENABLE = yes
LEADER_ENABLE = yes
COMBO_ENABLE = yes
KEYBOARD_SHARED_EP = yes


CONSOLE_ENABLE = no
COMMAND_ENABLE = no
AUTO_SHIFT_ENABLE = no
AUTO_SHIFT_MODIFIERS = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MUSIC_ENABLE = no
UNICODE_ENABLE = no
KEY_OVERRIDE_ENABLE = no
NKRO_ENABLE = no
BOOTMAGIC_ENABLE = no
MAGIC_ENABLE = no
RING_BUFFERED_6KRO_REPORT_ENABLE = no
MIDI_ENABLE = no

SRC = matrix.c
SRC += definitions/keycodes.c
SRC += features/lighting.c
SRC += features/leader.c
SRC += features/tapdance.c
SRC += features/combos.c
