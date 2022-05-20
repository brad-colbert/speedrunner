#include <atari.h>
#include <conio.h>
#include <peekpoke.h>

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define byte unsigned char
/*
#pragma bss-name (push,"DLIST_R")  
extern byte dlist_red[]; 
#pragma bss-name (pop)
#pragma bss-name (push,"DLIST_G")  
extern byte dlist_green[]; 
#pragma bss-name (pop)
#pragma bss-name (push,"DLIST_B")  
extern byte dlist_blue[]; 
#pragma bss-name (pop)
#pragma bss-name (push,"SCREEN_R")  
extern byte screen_red[]; 
#pragma bss-name (pop)
#pragma bss-name (push,"SCREEN_G")  
extern byte screen_green[]; 
#pragma bss-name (pop)
#pragma bss-name (push,"SCREEN_B")  
extern byte screen_blue[]; 
#pragma bss-name (pop)
*/
// #pragma bss-name (push,"PLAYFIELD")  
// extern byte screenmem[]; 
// #pragma bss-name (pop)

#define PAGE_ROWS 4
#define PAGE_COLS 4

#pragma bss-name (push,"PLAYFIELD")
//byte playarea[16384];
byte playfield[PAGE_ROWS * 24][PAGE_COLS * 40];
#pragma bss-name (pop)
//byte* screenmem = (byte*)0x3000;

#pragma data-name (push,"DISPLAYLIST")
#include "dl.h"
#pragma data-name (pop)

//#define offset(pr, pc, r, c) (pr * PAGE_COLS * 24 * 40 + pc * 24 * 40 + r * 40 + c)
#define offset(pr, pc, r, c) (pr * PAGE_COLS * 24 * 40  +  pc * 40  +  r * PAGE_COLS * 40  +  c)

int main()
{
    // cprintf("Hello World!\n\r");
    // Save the previous ANTIC state
    byte SDMCTL_PREV = OS.sdmctl;
    short SDLST_PREV = (short)OS.sdlst;
    unsigned short page_row = 0, page_col, row, col;
    byte vscroll;
    #ifdef GFX7
    byte* DL = (byte*)(&DISPLAY_LIST_GFX7);
    

    // Initialize memory
    // memset((void*)screenmem, (int)0x1B, (size_t)0x2000);
    for(; row < 51; ++row)
    {
        memset((void*)(playarea + (row * 80)), (int)0x01, (size_t)40);
        memset((void*)(playarea + (row * 80) + 40), (int)0x02, (size_t)40);
    }
    memset((void*)(playarea + 0x1000 + (0 * 80)), (int)0xFF, (size_t)40);
    memset((void*)(playarea + 0x1000 + (0 * 80) + 40), (int)0x55, (size_t)40);
    for(row = 1; row < 45; ++row)
    {
        memset((void*)(playarea + 0x1000 + (row * 80)), (int)0x01, (size_t)40);
        memset((void*)(playarea + 0x1000 + (row * 80) + 40), (int)0x02, (size_t)40);
    }
    /*
    for(row = 46; row < 51; ++row)
    {
        memset((void*)(screenmem + 0x1000 + (row * 80)), (int)0x03, (size_t)40);
        memset((void*)(screenmem + 0x1000 + (row * 80) + 40), (int)0x32, (size_t)40);
    }
    for(row = 0; row < 45; ++row)
    {
        memset((void*)(screenmem + 0x2000 + (row * 80)), (int)0x03, (size_t)40);
        memset((void*)(screenmem + 0x2000 + (row * 80) + 40), (int)0x32, (size_t)40);
    }
    */
    #else
    byte* DL = (byte*)(&DISPLAY_LIST_ANTIC4);
    

    // Initialize memory
    #ifdef OLD_PLAYFIELD
    memset((void*)playarea, (int)0, (size_t)160*96);
    for(page_row = 0; page_row < 3; ++page_row)
    {
        for(page_col = 0; page_col < 3; ++page_col)
        {
            for(row = 0; row < 24; ++row)
            {
                /*
                unsigned short x = offset(page_row, page_col, row, 0);
                memset((void*)(playfield + x),
                       (int)'a' + page_row * PAGE_COLS + page_col,
                       (size_t)40);
                */

                // memset((void*)(playarea + (row * 160) + (40*24*page_row) + (40*page_col)),
                //        (int)'a' + page_col + 4*page_row,
                //        (size_t)40);
            }
        }
    }
    #else
    for(page_row = 0; page_row < PAGE_ROWS; ++page_row)
    {
        for(page_col = 0; page_col < PAGE_COLS; ++page_col)
        {
            for(row = 0; row < 24; ++row)
            {
                //memset((void*)(&playfield[page_row + row][page_col]), (int)'a' + page_row/24 * 4 + page_col/40, (size_t)40);
                memset((void*)&playfield[page_row * 24 + row][page_col * 40], (int)'a' + page_row * PAGE_COLS + page_col, (size_t)40);
            }
        }
    }
    #endif
    #endif

    // Turn off ANTIC
    OS.sdmctl = 0;

    // Enable the display list
    #ifdef GFX7
    OS.sdlst = &DISPLAY_LIST_GFX7;
    #else
    OS.sdlst = &DISPLAY_LIST_ANTIC4;
    #endif

    // Turn On ANTIC
    OS.sdmctl = SDMCTL_PREV;

    // Delay
    //sleep(5);

    // Disable ANTIC
    //OS.sdmctl = 0;

    // Restore the original display list
    //OS.sdlst = (void*)SDLST_PREV;

    // Turn On ANTIC
    //OS.sdmctl = SDMCTL_PREV;

    //cprintf("%p\n\r", playarea); //(byte*)&DISPLAY_LIST_GFX7);

    // Don't quit
    while(1)
    {
        #ifdef OLD_PLAYFIELD
        //for(page_row = 0; page_row < 24; ++page_row)
        {
            for(col = 0; col < 40; ++col)
            {
                #ifdef GFX7
                for(row = 0; row < 51; ++row)  // line 77 is on a 4K boundary
                {
                    offset = row * 0x0050;
                    offset += col;
                    //((byte*)&DISPLAY_LIST_GFX7)[3 + ((row * 3) + 1)] = (unsigned short)playarea;// + offset;

                    *((short*)&DL[(row * 3 + 1) + 3]) = playfield + col;
                }
                /*
                for(row = 0; row < 45; ++row)  // line 77 is on a 4K boundary
                    ((byte*)&DISPLAY_LIST_GFX7)[((row + 51) * 3 + 1) + 3] = playarea + 0x1000 + (row * 80) + col;
                */

                //sleep(1);
                #else
                for(row = 0; row < 24; ++row)  // line 77 is on a 4K boundary
                {
                    //*((short*)&DL[(row * 3 + 1) + 3]) = (short)playarea + offset(0, 0, row, col);//(playarea + row * 80 + col);
                    *((short*)&DL[(row * 3 + 1) + 3]) = (short)playfield + row * 160 + col;//(playarea + row * 80 + col);
                }
                #endif
            }
        }
        #else
        /*
        for(page_row = 0; page_row < (PAGE_ROWS-1) * 24; ++page_row)
        {
            for(page_col = 0; page_col < (PAGE_COLS-1) * 40; ++page_row)
            {
                for(row = 0; row < 24; ++row)
                {
                    //unsigned short memloc = (page_row + row) * 4 * 40 + page_col;
                    byte* memloc = &playfield[page_row + row][page_col];
                    *((short*)&DL[(row * 3 + 1) + 3]) = (unsigned short)memloc;
                }
            }
        }
        */
        for(page_row = 0; page_row < (PAGE_ROWS-1) * 24; ++page_row)
        {
            for(vscroll = 0; vscroll < 8; ++vscroll)
            {
                ANTIC.vscrol = vscroll;
                sleep(1);
            }

            page_col = page_row;
            for(row = 0; row < 24; ++row)
            {
                byte* memloc = &playfield[page_row + row][page_col];

                *((short*)&DL[(row * 3 + 1) + 3]) = (unsigned short)memloc;
            }
        }
        #endif
    }

    return 0;
}
