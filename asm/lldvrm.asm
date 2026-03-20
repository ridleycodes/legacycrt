.386
.model flat
.code

public _alldvrm

;***
;lldvrm - signed long divide and remainder
;*******************************************************************************

_alldvrm PROC NEAR

        push    edi
        push    esi
        push    ebp

DVND_LO equ     [esp + 16]      ; low word of dividend (a)
DVND_HI equ     [esp + 20]      ; high word of dividend (a)
DVSR_LO equ     [esp + 24]      ; low word of divisor (b)
DVSR_HI equ     [esp + 28]      ; high word of divisor (b)

        xor     edi,edi         
        xor     ebp,ebp         

        mov     eax, DVND_HI 
        or      eax,eax         
        jge     short L1        
        inc     edi             
        inc     ebp             
        mov     edx, DVND_LO 
        neg     eax             
        neg     edx
        sbb     eax,0
        mov     DVND_HI, eax
        mov     DVND_LO, edx
L1:
        mov     eax, DVSR_HI 
        or      eax,eax         
        jge     short L2        
        inc     edi             
        mov     edx, DVSR_LO 
        neg     eax             
        neg     edx
        sbb     eax,0
        mov     DVSR_HI, eax
        mov     DVSR_LO, edx
L2:
        or      eax,eax         
        jnz     short L3        
        mov     ecx, DVSR_LO 
        mov     eax, DVND_HI 
        xor     edx,edx
        div     ecx             
        mov     ebx,eax         
        mov     eax, DVND_LO 
        div     ecx             
        mov     esi,eax         

        mov     eax,ebx         
        mul     dword ptr DVSR_LO 
        mov     ecx,eax         
        mov     eax,esi         
        mul     dword ptr DVSR_LO 
        add     edx,ecx         
        jmp     short L4        

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
        jnz     short L5        
        div     ecx             
        mov     esi,eax         

        mul     dword ptr DVSR_HI 
        mov     ecx,eax
        mov     eax, DVSR_LO
        mul     esi             
        add     edx,ecx         
        jc      short L6        

        cmp     edx, DVND_HI 
        ja      short L6        
        jb      short L7        
        cmp     eax, DVND_LO 
        jbe     short L7        
L6:
        dec     esi             
        sub     eax, DVSR_LO 
        sbb     edx, DVSR_HI
L7:
        xor     ebx,ebx         

L4:
        sub     eax, DVND_LO 
        sbb     edx, DVND_HI

        dec     ebp             
        jns     short L9        
        neg     edx             
        neg     eax
        sbb     edx,0

L9:
        mov     ecx,edx
        mov     edx,ebx
        mov     ebx,ecx
        mov     ecx,eax
        mov     eax,esi

        dec     edi             
        jnz     short L8        
        neg     edx             
        neg     eax
        sbb     edx,0

L8:
        pop     ebp
        pop     esi
        pop     edi

        ret     16

_alldvrm ENDP

end