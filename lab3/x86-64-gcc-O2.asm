exponent:
        movapd  xmm4, xmm0
        test    edi, edi
        jle     .L4
        movsd   xmm1, QWORD PTR .LC0[rip]
        add     edi, 1
        mov     eax, 1
        movapd  xmm2, xmm1
        movapd  xmm0, xmm1
.L3:
        mulsd   xmm2, xmm4
        pxor    xmm3, xmm3
        cvtsi2sd        xmm3, eax
        add     eax, 1
        mulsd   xmm1, xmm3
        movapd  xmm3, xmm2
        divsd   xmm3, xmm1
        addsd   xmm0, xmm3
        cmp     edi, eax
        jne     .L3
        ret
.L4:
        movsd   xmm0, QWORD PTR .LC0[rip]
        ret
.LC1:
        .string "%f\n"
main:
        sub     rsp, 8
        movsd   xmm3, QWORD PTR .LC0[rip]
        mov     eax, 1
        movapd  xmm1, xmm3
        movapd  xmm0, xmm3
.L8:
        pxor    xmm2, xmm2
        cvtsi2sd        xmm2, eax
        add     eax, 1
        mulsd   xmm0, xmm2
        movapd  xmm2, xmm3
        divsd   xmm2, xmm0
        addsd   xmm1, xmm2
        cmp     eax, 1000001
        jne     .L8
        movapd  xmm0, xmm1
        mov     edi, OFFSET FLAT:.LC1
        mov     eax, 1
        call    printf
        xor     eax, eax
        add     rsp, 8
        ret
.LC0:
        .long   0
        .long   1072693248
