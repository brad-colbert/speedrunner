#include <atari.h>

//extern void __fastcall__ scroll_playfield_fast(unsigned char len, void *src, void *dst); //void* dl_address, u_short row, u_short col);

//extern void init_vbi();
extern void spf();
extern void scroll_playfield_fast();
extern void initVBI();

/*
;; An interupt routine for the VBI
;;.interruptor _spf
XITVBV = $E462
SYSVBV = $E45F

.proc _spf: near
.code
	;lda #$70
	;sta $3303
	;sta $3304
	;sta $3305
	lda #$FF
	sta $3300
	jmp XITVBV
.endproc*/
