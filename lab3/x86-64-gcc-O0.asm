exponent:
        push    rbp
        mov     rbp, rsp
        movsd   QWORD PTR [rbp-40], xmm0
        mov     DWORD PTR [rbp-44], edi
        movsd   xmm0, QWORD PTR .LC0[rip]
        movsd   QWORD PTR [rbp-8], xmm0
        movsd   xmm0, QWORD PTR .LC0[rip]
        movsd   QWORD PTR [rbp-16], xmm0
        movsd   xmm0, QWORD PTR .LC0[rip]
        movsd   QWORD PTR [rbp-24], xmm0
        mov     DWORD PTR [rbp-28], 1
        jmp     .L2
.L3:
        movsd   xmm0, QWORD PTR [rbp-16]
        mulsd   xmm0, QWORD PTR [rbp-40]
        movsd   QWORD PTR [rbp-16], xmm0
        pxor    xmm0, xmm0
        cvtsi2sd        xmm0, DWORD PTR [rbp-28]
        movsd   xmm1, QWORD PTR [rbp-24]
        mulsd   xmm0, xmm1
        movsd   QWORD PTR [rbp-24], xmm0
        movsd   xmm0, QWORD PTR [rbp-16]
        divsd   xmm0, QWORD PTR [rbp-24]
        movsd   xmm1, QWORD PTR [rbp-8]
        addsd   xmm0, xmm1
        movsd   QWORD PTR [rbp-8], xmm0
        add     DWORD PTR [rbp-28], 1
.L2:
        mov     eax, DWORD PTR [rbp-28]
        cmp     eax, DWORD PTR [rbp-44]
        jle     .L3
        movsd   xmm0, QWORD PTR [rbp-8]
        movq    rax, xmm0
        movq    xmm0, rax
        pop     rbp
        ret
.LC1:
        .string "%f\n"
main:
        push    rbp
        mov     rbp, rsp
        sub     rsp, 16
        movsd   xmm0, QWORD PTR .LC0[rip]
        movsd   QWORD PTR [rbp-8], xmm0
        mov     DWORD PTR [rbp-12], 1000000
        mov     edx, DWORD PTR [rbp-12]
        mov     rax, QWORD PTR [rbp-8]
        mov     edi, edx
        movq    xmm0, rax
        call    exponent
        movq    rax, xmm0
        movq    xmm0, rax
        mov     edi, OFFSET FLAT:.LC1
        mov     eax, 1
        call    printf
        mov     eax, 0
        leave
        ret
.LC0:
        .long   0
        .long   1072693248