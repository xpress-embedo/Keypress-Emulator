#ifndef KEYPRESS_EMUL_H
#define KEYPRESS_EMUL_H

#include <stdint.h>
#include "usb_hid_keys.h"

// Function Prototypes
void key_emulator_init( void );
void key_emulator_send( char value );
void key_emulator_text( char* text );

#endif // KEYPRESS_EMUL_H