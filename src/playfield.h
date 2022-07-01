#ifndef __PLAYFIELD_H__
#define __PLAYFIELD_H__

#include "types.h"

#define PF_PAGE_ROWS 4
#define PF_PAGE_COLS 4

#ifdef GFX7
#else
#define PF_ROW_TILES 24
#define PF_COL_TILES 40

#define PF_COURSE_ROWS (PF_ROW_TILES * PF_PAGE_ROWS)
#define PF_COURSE_COLS (PF_COL_TILES * PF_PAGE_COLS)

#define PF_ROW_PIX 8
#define PF_COL_PIX 4

#define PF_LINES (PF_ROW_PIX * PF_COURSE_ROWS)
#define PF_COLS  (PF_COL_PIX * PF_COURSE_COLS)

#define PF_LINES_PER_PAGE (PF_ROW_TILES * PF_ROW_PIX)
#define PF_COLS_PER_PAGE (PF_COL_TILES * PF_COL_PIX)
#endif

#define NUM_ROWS_TO_SKIP (PF_COURSE_ROWS / (4096 / PF_COURSE_COLS))

extern byte playfield[PF_COURSE_ROWS + NUM_ROWS_TO_SKIP][PF_COURSE_COLS];

void init_playfield(void);

extern u_short pf_x, pf_y;
void scroll_playfield(u_short x, u_short y);

#endif // __PLAYFIELD_H__