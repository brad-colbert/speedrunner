#include "graphics.h"
#include "types.h"

#pragma data-name (push,"DISPLAYLIST")
#include "dl.h"
#pragma data-name (pop)

#include <atari.h>

byte SDMCTL_PREV;
short SDLST_PREV;
byte* DL;

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