;; Playfield utils

.export _setup_vbi
.export update_scroll

WSYNC = $D40A
_wait_wsync:
    sta WSYNC
    rts

;; An interupt routine for the VBI
XITVBV = $E462
SYSVBV = $E45F
HSCROL   = $d404
VSCROL   = $d405
.PROC update_scroll
        .importzp _scroll_flag
        .importzp _h_fs         ; horizontal fine scroll
        .importzp _v_fs         ; vertical fine scroll
        .import _ul_addr
        .import _ul_addr_tmp
        .import _DISPLAY_LIST_ANTIC4

        ; check to see if the x, y are being written, skip if so
        lda _scroll_flag
        bne @exit
 
        ; Horizontal fine scroll
@fine_scroll:
        lda _h_fs
        sta HSCROL

        ; Vertical fine scroll
        lda _v_fs
        sta VSCROL

        ; Compare the _ul_addr with the first address in _DISPLAY_LIST_ANTIC4
        ; If they are the same, jump to the exit (no change)
        lda _ul_addr              ;LSB of 1st number
        cmp _DISPLAY_LIST_ANTIC4+4      ;LSB of 2nd number
        bne @course_scroll               ;X > Y

        lda _ul_addr+1              ;MSB of 1st number
        cmp _DISPLAY_LIST_ANTIC4+5      ;MSB of 2nd number
        beq @exit             ;X = Y

        ; Perform course scroll
@course_scroll:
        ldx #4          ; 5th byte after start of display list is high byte of address
        clc
        lda _ul_addr  ; low byte
        sta _DISPLAY_LIST_ANTIC4,x  ; low byte
        lda _ul_addr+1  ; high byte
        inx
        sta _DISPLAY_LIST_ANTIC4,x  ; high byte
        inx
        inx

        ; copy current ul to a work variable
        lda _ul_addr  ; low byte
        sta _ul_addr_tmp
        lda _ul_addr+1  ; high byte
        sta _ul_addr_tmp+1

        ldy #24         ; 24 lines to modify
@loop:  clc
        lda _ul_addr_tmp  ; low byte
        adc #<160
        sta _DISPLAY_LIST_ANTIC4,x  ; low byte
        sta _ul_addr_tmp
        lda _ul_addr_tmp+1  ; high byte
        adc #>160
        inx
        sta _DISPLAY_LIST_ANTIC4,x  ; high byte
        sta _ul_addr_tmp+1
        inx
        inx
        dey
        bne @loop

        jsr _wait_wsync
@exit:  jmp XITVBV
.ENDPROC

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
        ldy         #<update_scroll  ; hight byte of address
        ldx         #>update_scroll  ; low byte of address
        lda         #7
        jsr         SETVBV

        .IFDEF ATARIXL
        ; Enable OS RAM
        pla
        sta        PORTB

        ;jsr _enable_os_ram
        .ENDIF

        rts