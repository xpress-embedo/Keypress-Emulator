#include "keypress_emul.h"

void interrupt()
{
  // USB Servicing is done inside the interrupt
  USB_Interrupt_Proc();
}

void main()
{
  // Initialize USB for Keypress Emulation
  key_emulator_init();
  key_emulator_text("/*");
  key_emulator_text("\tKeyboard Emulator Program\r");
  key_emulator_text("\tabcdefghijklmnopqrstuvwxyz\r");
  key_emulator_text("\tABCDEFGHIJKLMNOPQRSTUVWXYZ\r");
  key_emulator_text("\t0123456789\r");
  key_emulator_text("\t`~!@#$%^&*()_+-=,./;'[]\\<>?:\"{}|\r");
  key_emulator_text("\t################################n");
  key_emulator_text("*/\r\r");
  // Write a Simple Program
  key_emulator_text("#include <stdio.h>\r");
  key_emulator_text("void main()\r");
  key_emulator_text("{\r");
  key_emulator_text("\tprintf(\"Hello World\");\r");
  key_emulator_text("}\r");
  while(1)
  {
  }
}