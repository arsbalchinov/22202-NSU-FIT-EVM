exponent:
        fmov    d4, d0
        cmp     w0, 0
        ble     .L4
        fmov    d1, 1.0e+0
        add     w1, w0, 1
        mov     w0, 1
        fmov    d2, d1
        fmov    d0, d1
.L3:
        scvtf   d3, w0
        fmul    d2, d2, d4
        add     w0, w0, 1
        fmul    d1, d1, d3
        fdiv    d3, d2, d1
        fadd    d0, d0, d3
        cmp     w1, w0
        bne     .L3
        ret
.L4:
        fmov    d0, 1.0e+0
        ret
.LC0:
        .string "%f\n"
main:
        fmov    d0, 1.0e+0
        mov     w1, 16961
        stp     x29, x30, [sp, -16]!
        mov     w0, 1
        fmov    d1, d0
        fmov    d3, d0
        movk    w1, 0xf, lsl 16
        mov     x29, sp
.L8:
        scvtf   d2, w0
        add     w0, w0, 1
        fmul    d1, d1, d2
        fdiv    d2, d3, d1
        fadd    d0, d0, d2
        cmp     w0, w1
        bne     .L8
        adrp    x0, .LC0
        add     x0, x0, :lo12:.LC0
        bl      printf
        mov     w0, 0
        ldp     x29, x30, [sp], 16
        ret