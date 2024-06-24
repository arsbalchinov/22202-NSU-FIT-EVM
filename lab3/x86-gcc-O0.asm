exponent:
        push    ebp
        mov     ebp, esp
        sub     esp, 40
        mov     eax, DWORD PTR [ebp+8]
        mov     edx, DWORD PTR [ebp+12]
        mov     DWORD PTR [ebp-40], eax
        mov     DWORD PTR [ebp-36], edx
        fld1
        fstp    QWORD PTR [ebp-8]
        fld1
        fstp    QWORD PTR [ebp-16]
        fld1
        fstp    QWORD PTR [ebp-24]
        mov     DWORD PTR [ebp-28], 1
        jmp     .L2
.L3:
        fld     QWORD PTR [ebp-16]
        fmul    QWORD PTR [ebp-40]
        fstp    QWORD PTR [ebp-16]
        fild    DWORD PTR [ebp-28]
        fld     QWORD PTR [ebp-24]
        fmulp   st(1), st
        fstp    QWORD PTR [ebp-24]
        fld     QWORD PTR [ebp-16]
        fdiv    QWORD PTR [ebp-24]
        fld     QWORD PTR [ebp-8]
        faddp   st(1), st
        fstp    QWORD PTR [ebp-8]
        add     DWORD PTR [ebp-28], 1
.L2:
        mov     eax, DWORD PTR [ebp-28]
        cmp     eax, DWORD PTR [ebp+16]
        jle     .L3
        fld     QWORD PTR [ebp-8]
        leave
        ret
main:
        lea     ecx, [esp+4]
        and     esp, -8
        push    DWORD PTR [ecx-4]
        push    ebp
        mov     ebp, esp
        push    ecx
        sub     esp, 20
        fld1
        fstp    QWORD PTR [ebp-16]
        mov     DWORD PTR [ebp-20], 1000000
        sub     esp, 4
        push    DWORD PTR [ebp-20]
        push    DWORD PTR [ebp-12]
        push    DWORD PTR [ebp-16]
        call    exponent
        fstp    st(0)
        add     esp, 16
        mov     eax, 0
        mov     ecx, DWORD PTR [ebp-4]
        leave
        lea     esp, [ecx-4]
        ret
