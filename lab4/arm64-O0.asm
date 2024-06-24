exponent:
        sub     sp, sp, #48
        str     d0, [sp, 8]
        str     w0, [sp, 4]
        fmov    d0, 1.0e+0
        str     d0, [sp, 40]
        fmov    d0, 1.0e+0
        str     d0, [sp, 32]
        fmov    d0, 1.0e+0
        str     d0, [sp, 24]
        mov     w0, 1
        str     w0, [sp, 20]
        b       .L2
.L3:
        ldr     d1, [sp, 32]
        ldr     d0, [sp, 8]
        fmul    d0, d1, d0
        str     d0, [sp, 32]
        ldr     w0, [sp, 20]
        scvtf   d0, w0
        ldr     d1, [sp, 24]
        fmul    d0, d1, d0
        str     d0, [sp, 24]
        ldr     d0, [sp, 24]
        ldr     d1, [sp, 32]
        fdiv    d0, d1, d0
        ldr     d1, [sp, 40]
        fadd    d0, d1, d0
        str     d0, [sp, 40]
        ldr     w0, [sp, 20]
        add     w0, w0, 1
        str     w0, [sp, 20]
.L2:
        ldr     w1, [sp, 20]
        ldr     w0, [sp, 4]
        cmp     w1, w0
        ble     .L3
        ldr     d0, [sp, 40]
        add     sp, sp, 48
        ret
.LC0:
        .string "%f\n"
main:
        stp     x29, x30, [sp, -32]!
        mov     x29, sp
        fmov    d0, 1.0e+0
        str     d0, [sp, 24]
        mov     w0, 16960
        movk    w0, 0xf, lsl 16
        str     w0, [sp, 20]
        ldr     w0, [sp, 20]
        ldr     d0, [sp, 24]
        bl      exponent
        adrp    x0, .LC0
        add     x0, x0, :lo12:.LC0
        bl      printf
        mov     w0, 0
        ldp     x29, x30, [sp], 32
        ret