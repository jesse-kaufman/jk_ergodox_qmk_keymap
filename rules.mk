# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file
LTO_ENABLE = yes
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
AUTO_SHIFT_ENABLE = no
AUTO_SHIFT_MODIFIERS = no
TAP_DANCE_ENABLE = yes
SPACE_CADET_ENABLE = no
CAPS_WORD_ENABLE = yes
SRC = matrix.c
SRC += features/lighting.c
SRC += features/leader.c
SRC += features/tapdance.c
GRAVE_ESC_ENABLE = no
MUSIC_ENABLE = no
LEADER_ENABLE = yes
UNICODE_ENABLE = no
