// Our includes first
#include "graphics.h"
#include "playfield.h"
#include "types.h"

// Atari specific includes next
#include <atari.h>
#include <conio.h>
#include <peekpoke.h>

// Standard C includes
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define offset(pr, pc, r, c) (pr * PAGE_COLS * 24 * 40  +  pc * 40  +  r * PAGE_COLS * 40  +  c)

int main()
{
    // cprintf("Hello World!\n\r");
    unsigned short page_row = 0, page_col, row;
    byte vscroll;

    init_graphics();
    init_playfield();

    // Don't quit
    while(1)
    {
        for(page_row = 0; page_row < (PF_PAGE_ROWS-1) * 24; ++page_row)
        {
            for(vscroll = 0; vscroll < 8; ++vscroll)
            {
                ANTIC.vscrol = vscroll;
                ANTIC.hscrol = 4-(vscroll%4);
                sleep(1);
            }

            page_col = page_row;
            for(row = 0; row < 24; ++row)
            {
                //byte* memloc = &playfield[page_row + row][page_col];

                *((short*)&DL[(row * 3 + 1) + 3]) = (unsigned short)&playfield[page_row + row][page_col];//(unsigned short)memloc;
            }
        }
    }

    close_graphics();

    return 0;
}
