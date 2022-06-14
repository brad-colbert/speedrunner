#include "graphics.h"
#include "types.h"

#pragma data-name (push,"DISPLAYLIST")
#include "dl.h"
#pragma data-name (pop)

#pragma data-name (push,"MYFONT")
#include "atari-small-4x8-COLOR1.h"
#pragma data-name (pop)

#include <atari.h>

byte SDMCTL_PREV;
short SDLST_PREV;
byte* DL;

void init_font()
{
    //#define COPY_BASE_FONT
    #ifdef COPY_BASE_FONT
    u_short i;
    for(i = 0; i < 1024; ++i) {
        font[i] = *((byte*)0xE000 + i);
    }
    #endif

    // Use the new charset
    OS.chbas = (byte)(((u_short)font)>>8);
}

void init_graphics()
{
    // Save the previous ANTIC state
    SDMCTL_PREV = OS.sdmctl;
    SDLST_PREV = (short)OS.sdlst;

    // Turn off ANTIC
    OS.sdmctl = 0;

    // Set our mode
    #ifdef GFX7
    DL = (byte*)(&DISPLAY_LIST_GFX7);
    #else
    DL = (byte*)(&DISPLAY_LIST_ANTIC4);
    #endif

    // Enable the display list
    #ifdef GFX7
    OS.sdlst = &DISPLAY_LIST_GFX7;
    #else
    OS.sdlst = &DISPLAY_LIST_ANTIC4;
    #endif

    init_font();

    // Turn On ANTIC
    OS.sdmctl = SDMCTL_PREV;
}

void close_graphics()
{
    // Disable ANTIC
    OS.sdmctl = 0;

    // Restore the original display list
    OS.sdlst = (void*)SDLST_PREV;

    // Turn On ANTIC
    OS.sdmctl = SDMCTL_PREV;
}