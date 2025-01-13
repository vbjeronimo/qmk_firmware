BOOTLOADER = atmel-dfu

CAPS_WORD_ENABLE = yes
COMMAND_ENABLE = no
EXTRAKEY_ENABLE = no    # Audio control and System control
OLED_ENABLE = yes		# OLED display

# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/logo_reader.c
