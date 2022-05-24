;; Playfield utils

.export _spf
.export _initVBI
	
;; An interupt routine for the VBI
;;.interruptor _spf
XITVBV = $E462
SYSVBV = $E45F
_spf:
	lda #$FF
	sta $3300
	jmp XITVBV

SETVBV = $E45C
_initVBI: ldy         #<_spf
 		  ldx         #>_spf
          lda         #7
          jsr         SETVBV
          rts