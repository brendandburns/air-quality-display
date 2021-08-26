#ifndef __BATTERY_ICON_H__
#define __BATTERY_ICON_H__

#include <pgmspace.h>

#define battery_width 24
#define battery_height 24

PROGMEM const unsigned char batteryIcon[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xfe, 0xff, 0x07, 0xff, 0xff, 0x0f, 0x03, 0x00, 0x0c,
   0x03, 0x00, 0x0c, 0x03, 0x00, 0x0c, 0x03, 0x00, 0xcc, 0x03, 0x00, 0xcc,
   0x03, 0x00, 0xcc, 0x03, 0x00, 0xcc, 0x03, 0x00, 0x0c, 0x03, 0x00, 0x0c,
   0x03, 0x00, 0x0c, 0xff, 0xff, 0x0f, 0xfe, 0xff, 0x07, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

#endif // __BATTERY_ICON_H__