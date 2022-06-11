#include "playfield.h"
#include "graphics.h"
#include "types.h"
#include "playfield_utils.h"

// Atari specific includes next
#include <atari.h>
#include <conio.h>

// Standard C includes
#include <unistd.h>
#include <string.h>

#define COLOR_CLOCK_BUFF 4

#pragma bss-name (push,"PLAYFIELD")
byte playfield[PF_ROW_BYTES][PF_COL_BYTES];
#pragma bss-name (pop)

// A description about the "playfield":
// There are PF_PAGE_ROWS x PF_PAGE_COLS pages in the playfield.
// Each page consists of PF_ROW_TILES x PF_COL_TILES tiles.
// Each tile is PF_ROW_PIX x PF_COL_PIX in pixels.
// A line is a pixel in row space, and a col (maybe horrible name) is a pixel in col space.

#pragma data-name(push,"ZEROPAGE")
byte* ul_addr_tmp = &playfield[0][0];
byte* row_addr = 0x0000;
byte scroll_flag = 0x00; // goes into ZEROPAGE
byte h_fs = 0x00;        // horizontal fine scroll
byte v_fs = 0x00;        // vertical fine scroll
#pragma data-name(pop)
u_short line_r, col_r;
byte* ul_addr = &playfield[0][0];

void init_playfield()
{
    u_short page_row = 0, page_col, row;

    setup_vbi();

    // Initialize memory
    for(page_row = 0; page_row < PF_PAGE_ROWS; ++page_row)
    {
        for(page_col = 0; page_col < PF_PAGE_COLS; ++page_col)
        {
            for(row = 0; row < PF_ROW_TILES-1; ++row) {
                memset((void*)&playfield[page_row * PF_ROW_TILES + row][page_col * PF_COL_TILES],
                       (int)'a' + page_row * PF_PAGE_COLS + page_col,
                       (size_t)PF_COL_TILES);

                playfield[page_row * PF_ROW_TILES + row][page_col * PF_COL_TILES + (PF_COL_TILES-1)] = (byte)'|';        
            }

            memset((void*)&playfield[page_row * PF_ROW_TILES + row][page_col * PF_COL_TILES],
                    (int)'?',
                    (size_t)PF_COL_TILES-1);
        }
    }
}

void scroll_playfield(u_short line, u_short col)
{
    // Local temporaries.  Values get copied when we have a lock on the memory accessed by the VBI.
    byte h_cs, v_cs, h_fs_lcl, v_fs_lcl;
    //byte* ul_addr_lcl;

    // Put some bounds on the coordinates
    if(line >= (PF_LINES - PF_LINES_PER_PAGE))
        line = PF_LINES - PF_LINES_PER_PAGE;

    if(col >= (PF_COLS - PF_COLS_PER_PAGE))
        col = PF_COLS - PF_COLS_PER_PAGE;

    v_cs = (byte)(line / (u_short)PF_ROW_PIX);
    h_cs = (byte)(col  / (u_short)PF_COL_PIX);

    v_fs_lcl = (byte)(line % (u_short)PF_ROW_PIX); 
    h_fs_lcl = PF_COL_PIX - (byte)(col %  (u_short)PF_COL_PIX);

    //ul_addr_lcl = &playfield[v_cs][h_cs];

    // Keep the VBI from reading while we update the values.
    scroll_flag = 0xFF;

    v_fs = v_fs_lcl; 
    h_fs = h_fs_lcl;

    ul_addr = &playfield[v_cs][h_cs];
    row_addr = &playfield[v_cs][0];
    
    scroll_flag = 0x00;  // allow screen to update
}
