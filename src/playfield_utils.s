;; Playfield utils

.export _spf
.export _initVBI
	
;; An interupt routine for the VBI
;;.interruptor _spf
XITVBV = $E462
SYSVBV = $E45F
_spf:
	lda #$FF
	sta $2700
	jmp XITVBV

SETVBV = $E45C
_initVBI:
    ;lda        $d301
    ;pha

    ;ora        #1
    ;sta        $d301

    ldy         #<_spf
    ldx         #>_spf
    lda         #7
    jsr         SETVBV

    ;pla
    ;sta        $d301

    rts
