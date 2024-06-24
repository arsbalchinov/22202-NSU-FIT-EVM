exponent:
        sub     esp, 12
        mov     edx, DWORD PTR [esp+24]
        fld     QWORD PTR [esp+16]
        test    edx, edx
        jle     .L4
        fld1
        add     edx, 1
        mov     eax, 1
        fld     st(0)
        fld     st(1)
.L3:
        fmul    st, st(3)
        mov     DWORD PTR [esp+4], eax
        fild    DWORD PTR [esp+4]
        add     eax, 1
        fmulp   st(2), st
        fld     st(0)
        fdiv    st, st(2)
        faddp   st(3), st
        cmp     edx, eax
        jne     .L3
        fstp    st(0)
        fstp    st(0)
        fstp    st(1)
        add     esp, 12
        ret
.L4:
        fstp    st(0)
        fld1
        add     esp, 12
        ret
.LC2:
        .string "%f"
main:
        lea     ecx, [esp+4]
        fld1
        and     esp, -16
        mov     eax, 1
        push    DWORD PTR [ecx-4]
        fld     st(0)
        push    ebp
        mov     ebp, esp
        push    ecx
        sub     esp, 20
.L9:
        mov     DWORD PTR [ebp-12], eax
        fild    DWORD PTR [ebp-12]
        add     eax, 1
        fmulp   st(2), st
        fld     st(1)
        fdivr   DWORD PTR .LC0
        faddp   st(1), st
        cmp     eax, 1000001
        jne     .L9
        fstp    st(1)
        sub     esp, 12
        fstp    QWORD PTR [esp]
        push    OFFSET FLAT:.LC2
        call    printf
        mov     ecx, DWORD PTR [ebp-4]
        add     esp, 16
        xor     eax, eax
        leave
        lea     esp, [ecx-4]
        ret
.LC0:
        .long   1065353216
