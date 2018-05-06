#include "keypress_emul.h"

uint8_t readbuff[64] absolute 0x500;
uint8_t writebuff[64] absolute 0x540;

// Function Definitions

void key_emulator_init( void )
{
  HID_Enable(readbuff, writebuff);
  // Give some delay
  Delay_ms(1000);
}

void key_emulator_text( char* text )
{
  while( *text )
  {
    key_emulator_send(*text);
    text++;
  }
}

void key_emulator_send( char value )
{
  /*
  ready = 0 Invalid Value
  ready = 1 Alphabet Value
  ready = 2 Numeric Value
  ready = 3 Control or Delete Character
  */
  uint8_t ready = 0x00;
  uint8_t modifier = 0x00;
  if ( iscntrl(value) )
  {
    ready = 0x01;
  }
  else if ( isalpha(value) )
  {
    ready = 0x02;
    if ( isupper(value) )
    {
      modifier = KEY_MOD_LSHIFT;
    }
    else
    {
      modifier = 0x00;
    }
  }
  else if ( isdigit(value) )
  {
    ready = 0x03;
  }
  else
  {
    ready = 0x04;
  }
  switch( ready )
  {
    case 0x01:
    /*
    I think Look-Up table will be a best idea, for demo purpose, i just hardcoding the values
    Check usb_hid_keys.h file for more information
    */
    if( value == '\r' || value == '\n' )
    {
      value = KEY_ENTER;
    }
    else if( value == '\t' )
    {
      value = KEY_TAB;
    }
    else if( value == '\b' )  // backspace key
    {
      value = KEY_BACKSPACE;
    }
    break;
    case 0x02:
    // Convert value to Upper case
    value = toupper(value);
    /*
    'A' = 0x41 (65)
    'Z' = 0x5A (90)
    In usb_hid_keys.h scan code for 'a' is KEY_A (0x04)
    */
    value = value - 'A' + KEY_A;
    break;
    case 0x03:
    /*
    Considering Numeric Keypad
    '0' = 0x30 (48)
    '1' = 0x31 (49)
    '9' = 0x39 (57)
    In usb_hid_keys.h scan code for '1' is KEY_KP1 (0x59)
    Note: '0' is exception with KEY_KP0 (0x62)
    */
    if ( value == '0' )
    {
      value = KEY_KP0;
    }
    else
    {
      value = value - '1' + KEY_KP1;
    }
    break;
    case 0x04:
    /*
    Check usb_hid_keys.h file
    Untidy way of doing things, maybe in next release I will make a look-up table
    */
    if ( value == '-' || value == '_')
    {
      if( value == '_')
      {
        modifier = KEY_MOD_LSHIFT;
      }
      value = KEY_MINUS;
    }
    else if ( value == '+' || value == '=' )
    {
      if( value == '=' )
      {
        modifier = KEY_MOD_LSHIFT;
      }
      value = KEY_EQUAL;
    }
    else if ( value == '{' || value == '[' )
    {
      if ( value == '{' )
      {
        modifier = KEY_MOD_LSHIFT;
      }
      value = KEY_LEFTBRACE;
    }
    else if ( value == '}' || value == ']' )
    {
      if ( value == '}' )
      {
        modifier = KEY_MOD_LSHIFT;
      }
      value = KEY_RIGHTBRACE;
    }
    else if ( value == '\\' || value == '|' )
    {
      if( value == '|' )
      {
        modifier = KEY_MOD_LSHIFT;
      }
      value = KEY_BACKSLASH;
    }
    else if ( value == '\t' )
    {
      value = KEY_TAB;
    }
    else if( value == ':' || value == ';' )
    {
      if ( value == ':' )
      {
        modifier = KEY_MOD_LSHIFT;
      }
      value = KEY_SEMICOLON;
    }
    else if( value == '\'' || value == '"' )
    {
      if ( value == '"' )
      {
        modifier = KEY_MOD_LSHIFT;
      }
      value = KEY_APOSTROPHE;
    }
    else if( value == '`' || value == '~' )
    {
      if ( value == '~' )
      {
        modifier = KEY_MOD_LSHIFT;
      }
      value = KEY_GRAVE;
    }
    else if( value == ',' || value == '<' )
    {
      if ( value == '<' )
      {
        modifier = KEY_MOD_LSHIFT;
      }
      value = KEY_COMMA;
    }
    else if( value == '.' || value == '>' )
    {
      if ( value == '>' )
      {
        modifier = KEY_MOD_LSHIFT;
      }
      value = KEY_DOT;
    }
    else if( value == '/' || value == '?' )
    {
      if ( value == '?' )
      {
        modifier = KEY_MOD_LSHIFT;
      }
      value = KEY_SLASH;
    }
    else if ( value == '!' )
    {
      modifier = KEY_MOD_LSHIFT;
      value = KEY_1;
    }
    else if( value == '@' )
    {
      modifier = KEY_MOD_LSHIFT;
      value = KEY_2;
    }
    else if( value == '#' )
    {
      modifier = KEY_MOD_LSHIFT;
      value = KEY_3;
    }
    else if( value == '$' )
    {
      modifier = KEY_MOD_LSHIFT;
      value = KEY_4;
    }
    else if( value == '%' )
    {
      modifier = KEY_MOD_LSHIFT;
      value = KEY_5;
    }
    else if( value == '^' )
    {
      modifier = KEY_MOD_LSHIFT;
      value = KEY_6;
    }
    else if( value == '&' )
    {
      modifier = KEY_MOD_LSHIFT;
      value = KEY_7;
    }
    else if( value == '*' )
    {
      modifier = KEY_MOD_LSHIFT;
      value = KEY_8;
    }
    else if( value == '(' )
    {
      modifier = KEY_MOD_LSHIFT;
      value = KEY_9;
    }
    else if( value == ')' )
    {
      modifier = KEY_MOD_LSHIFT;
      value = KEY_0;
    }
    else if( value == ' ' )
    {
      value = KEY_SPACE;
    }
    break;
    default:
    break;
  }
  // Update these values in Write Buffer
  writebuff[0] = modifier;  // Modifier
  writebuff[1] = 0x00;      // Reserved
  writebuff[2] = value;
  writebuff[3] = 0x00;  // Future Use
  writebuff[4] = 0x00;  // Future Use
  writebuff[5] = 0x00;  // Future Use
  writebuff[6] = 0x00;  // Future Use
  writebuff[7] = 0x00;  // Future Use
  while( !HID_Write(writebuff,8) );
  Delay_ms(30);
  writebuff[0] = 0x00;  // Modifier
  writebuff[2] = 0x00;
  while( !HID_Write(writebuff,8) );
  Delay_ms(30);
}
