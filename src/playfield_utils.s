;; Playfield utils

.export _spf
.export _setup_vbi
	
;; An interupt routine for the VBI
;;.interruptor _spf
XITVBV = $E462
SYSVBV = $E45F
_spf:
	lda #$FF
	sta $2700
	jmp XITVBV

SETVBV = $E45C
_setup_vbi:
    ; Disable OS RAM
    lda        $d301
    pha

    ora        #1
    sta        $d301

    ; Setup VBI
    ldy         #<_spf
    ldx         #>_spf
    lda         #7
    jsr         SETVBV

    ; Enable OS RAM
    pla
    sta        $d301

    rts

WSYNC = $D40A
_wait_wsync:
    pha
    sta WSYNC
    pla
    rts
