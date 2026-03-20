.386
.model flat

.code

public __alldiv

;***
;lldiv - signed long divide
;*******************************************************************************

__alldiv PROC NEAR

        push    edi
        push    esi
        push    ebx

; Stack offsets after 3 pushes (12 bytes) + 4 byte return address = 16 bytes
DVND_LO equ     [esp + 16]      ; low word of dividend (a)
DVND_HI equ     [esp + 20]      ; high word of dividend (a)
DVSR_LO equ     [esp + 24]      ; low word of divisor (b)
DVSR_HI equ     [esp + 28]      ; high word of divisor (b)

; Determine sign of the result and make operands positive.
        xor     edi,edi         ; result sign assumed positive

        mov     eax, DVND_HI
        or      eax,eax         
        jge     short L1        ; skip rest if a is already positive
        inc     edi             ; complement result sign flag
        mov     edx, DVND_LO
        neg     eax             ; make a positive
        neg     edx
        sbb     eax,0
        mov     DVND_HI, eax
        mov     DVND_LO, edx
L1:
        mov     eax, DVSR_HI
        or      eax,eax         
        jge     short L2        ; skip rest if b is already positive
        inc     edi             ; complement the result sign flag
        mov     edx, DVSR_LO
        neg     eax             ; make b positive
        neg     edx
        sbb     eax,0
        mov     DVSR_HI, eax
        mov     DVSR_LO, edx
L2:

; Now do the divide. First look to see if the divisor is less than 4194304K.
        or      eax,eax         ; check to see if divisor < 4194304K
        jnz     short L3        ; nope, gotta do this the hard way
        mov     ecx, DVSR_LO
        mov     eax, DVND_HI
        xor     edx,edx
        div     ecx             ; eax <- high order bits of quotient
        mov     ebx,eax         ; save high bits of quotient
        mov     eax, DVND_LO
        div     ecx             ; eax <- low order bits of quotient
        mov     edx,ebx         ; edx:eax <- quotient
        jmp     short L4        

; Here we do it the hard way.
L3:
        mov     ebx,eax         
        mov     ecx, DVSR_LO
        mov     edx, DVND_HI
        mov     eax, DVND_LO
L5:
        shr     ebx,1           
        rcr     ecx,1
        shr     edx,1           
        rcr     eax,1
        or      ebx,ebx
        jnz     short L5        ; loop until divisor < 4194304K
        div     ecx             ; now divide, ignore remainder
        mov     esi,eax         ; save quotient

; Check for off-by-one by multiplying quotient by divisor
        mul     dword ptr DVSR_HI 
        mov     ecx,eax
        mov     eax, DVSR_LO
        mul     esi             
        add     edx,ecx         
        jc      short L6        ; carry means Quotient is off by 1

; Compare original dividend to multiply result
        cmp     edx, DVND_HI
        ja      short L6        ; if result > original, do subtract
        jb      short L7        ; if result < original, we are ok
        cmp     eax, DVND_LO
        jbe     short L7        ; if less or equal we are ok, else subtract
L6:
        dec     esi             ; subtract 1 from quotient
L7:
        xor     edx,edx         ; edx:eax <- quotient
        mov     eax,esi

; Cleanup and sign application
L4:
        dec     edi             
        jnz     short L8        
        neg     edx             ; negate the result
        neg     eax
        sbb     edx,0

L8:
        pop     ebx
        pop     esi
        pop     edi

        ret     16

__alldiv ENDP

end