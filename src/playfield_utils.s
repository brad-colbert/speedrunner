;; Playfield utils

;.include "util.s"
;.include "hardware.s"

.export _spf
.export _setup_vbi
.export _playfield_init
.export _fine_scroll_left
.export _fine_scroll_right
.export _fine_scroll_up
.export _fine_scroll_down

delay_count = $80       ; counter for scrolling updates
vert_scroll = $90       ; variable used to store VSCROL value
horz_scroll = $91       ; variable used to store HSCROL value
delay = 5               ; number of VBLANKs between scrolling updates
vert_scroll_max = 8     ; ANTIC mode 4 has 8 scan lines
horz_scroll_max = 4     ; ANTIC mode 4 has 4 color clocks
vscroll_x2 = $a4        ; twice vertical scrolling? no = 0, yes = $ff

_playfield_init:
        HSCROL   = $d404
        VSCROL   = $d405
        lda #0          ; initialize horizontal scrolling value
        sta horz_scroll
        sta HSCROL      ; initialize hardware register

        lda #0          ; initialize vertical scrolling value
        sta vert_scroll
        sta VSCROL      ; initialize hardware register

        lda #delay      ; number of VBLANKs to wait
        sta delay_count

; scroll one color clock right and check if at HSCROL limit, returns
; HSCROL value in A
_fine_scroll_right:
        dec horz_scroll
        lda horz_scroll
        bpl @done       ; if non-negative, still in the middle of the character
        jsr _coarse_scroll_right ; wrapped to $ff, do a coarse scroll...
        lda #horz_scroll_max-1  ;  ...followed by reseting the HSCROL register
        sta horz_scroll
@done:  rts

; move viewport one byte to the right by pointing each display list start
; address to one byte higher in memory
_coarse_scroll_right:
        .import _DISPLAY_LIST_ANTIC4
        ldy #24         ; 24 lines to modify
        ldx #4          ; 4th byte after start of display list is low byte of address
@loop:  inc _DISPLAY_LIST_ANTIC4,x
        inx             ; skip to next low byte which is 3 bytes away
        inx
        inx
        dey
        bne @loop
        rts

; scroll one color clock left and check if at HSCROL limit, returns
; HSCROL value in A
_fine_scroll_left:
        inc horz_scroll
        lda horz_scroll
        cmp #horz_scroll_max ; check to see if we need to do a coarse scroll
        bcc @done       ; nope, still in the middle of the character
        jsr _coarse_scroll_left ; yep, do a coarse scroll...
        lda #0          ;  ...followed by reseting the HSCROL register
        sta horz_scroll
@done:  rts

; move viewport one byte to the left by pointing each display list start
; address to one byte lower in memory
_coarse_scroll_left:
        .import _DISPLAY_LIST_ANTIC4
        ldy #24         ; 24 lines to modify
        ldx #4          ; 4th byte after start of display list is low byte of address
@loop:  dec _DISPLAY_LIST_ANTIC4,x
        inx             ; skip to next low byte which is 3 bytes away
        inx
        inx
        dey
        bne @loop
        rts   
        
; scroll one scan line up and check if at VSCROL limit, returns
; VSCROL value in A
_fine_scroll_up:
        dec vert_scroll
        bit vscroll_x2
        bpl @not_2x
        dec vert_scroll
@not_2x:lda vert_scroll
        bpl @done       ; if non-negative, still in the middle of the character
        jsr _coarse_scroll_up   ; wrapped to $ff, do a coarse scroll...
        lda #vert_scroll_max-1 ;  ...followed by reseting the vscroll register
        sta vert_scroll
@done:  rts

; move viewport one line up by pointing display list start address
; to the address one page earlier in memory
_coarse_scroll_up:
        .import _DISPLAY_LIST_ANTIC4
        ldy #24         ; 24 lines to modify
        ldx #5          ; 5th byte after start of display list is high byte of address
@loop:  dec _DISPLAY_LIST_ANTIC4,x
        inx             ; skip to next low byte which is 3 bytes away
        inx
        inx
        dey
        bne @loop
        rts

; scroll one scan line down and check if at VSCROL limit, returns
; VSCROL value in A
_fine_scroll_down:
        inc vert_scroll
        bit vscroll_x2
        bpl @not_2x
        inc vert_scroll
@not_2x:lda vert_scroll
        cmp #vert_scroll_max ; check to see if we need to do a coarse scroll
        bcc @done       ; nope, still in the middle of the character
        jsr _coarse_scroll_down ; yep, do a coarse scroll...
        lda #0          ;  ...followed by reseting the vscroll register
        sta vert_scroll
@done:  rts

; move viewport one line down by pointing display list start address
; to the address one page later in memory
_coarse_scroll_down:
        .import _DISPLAY_LIST_ANTIC4
        ldy #24         ; 24 lines to modify
        ldx #5          ; 5th byte after start of display list is high byte of address
@loop:  inc _DISPLAY_LIST_ANTIC4,x
        inx             ; skip to next low byte which is 3 bytes away
        inx
        inx
        dey
        bne @loop
        rts        


;; An interupt routine for the VBI
;;.interruptor _spf
XITVBV = $E462
SYSVBV = $E45F
_spf:
        ;.import _DISPLAY_LIST_ANTIC4
        ;lda #$FF
        ;sta _DISPLAY_LIST_ANTIC4
        .import _col_d, _line_d

        ; Perform slower updates
        dec delay_count ; wait for number of VBLANKs before updating
        bne @exit       ;   fine/coarse scrolling

        ; Check if horizontal
        lda _col_d            ; NUM1
        cmp #0                ; NUM2
        beq @vertical         ; No change
        bmi @left             ; NUM2 > NUM1
        bcs @right            ; NUM2 < NUM1
        jmp @vertical         ; done

@left:  jsr _fine_scroll_left
        jmp @doneh
@right: jsr _fine_scroll_right

@doneh: lda #0                 
        sta _col_d            ; set as handled

        ; Check if vertical
@vertical: lda _line_d        ; NUM1
        cmp #0                ; NUM2
        beq @donev            ; No change
        bmi @up               ; NUM2 > NUM1
        bcs @down             ; NUM2 < NUM1
        jmp @donev            ; done

@up:    jsr _fine_scroll_up
        jmp @donev
@down:  jsr _fine_scroll_down

@donev: lda #0                 
        sta _line_d           ; set as handled

        lda #delay            ; reset counter
        sta delay_count
        
@exit:  jmp XITVBV

.IFDEF TEST
_iter_test:
        .import _counter
        inc _counter
@exit:  jmp XITVBV     
.ENDIF

SETVBV = $E45C
PORTB  = $d301
_setup_vbi:
    .IFDEF ATARIXL
    ;.import _enable_os_ram
    ;.import _disable_os_ram
    ; Disable OS RAM
    lda        PORTB
    pha

    ora        #1
    sta        PORTB
    .ENDIF

    ;jsr _disable_os_ram

    ; Setup VBI
    ldy         #<_spf
    ldx         #>_spf
    lda         #7
    jsr         SETVBV

    .IFDEF ATARIXL
    ; Enable OS RAM
    pla
    sta        PORTB

    ;jsr _enable_os_ram
    .ENDIF

    rts

WSYNC = $D40A
_wait_wsync:
    sta WSYNC
    rts
