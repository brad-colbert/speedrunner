#include <atari.h>

//extern void __fastcall__ scroll_playfield_fast(unsigned char len, void *src, void *dst); //void* dl_address, u_short row, u_short col);

extern void spf();
extern void setup_vbi();
extern void wait_wsync();
