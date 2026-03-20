.386
.model flat
.code

public __allmul

;***
;llmul - long multiply routine
;*******************************************************************************

__allmul PROC NEAR

A_LO    EQU     [esp + 4]       
A_HI    EQU     [esp + 8]       
B_LO    EQU     [esp + 12]      
B_HI    EQU     [esp + 16]      

        mov     eax, A_HI
        mov     ecx, B_HI
        or      ecx,eax         
        mov     ecx, B_LO
        jnz     short hard      

        mov     eax, A_LO
        mul     ecx

        ret     16              

hard:
        push    ebx

; Redefine stack offsets since esp was shifted by push ebx
A2_LO   EQU     [esp + 8]       
B2_HI   EQU     [esp + 20]      

        mul     ecx             
        mov     ebx,eax         

        mov     eax, A2_LO
        mul     dword ptr B2_HI 
        add     ebx,eax         

        mov     eax, A2_LO  
        mul     ecx             
        add     edx,ebx         

        pop     ebx

        ret     16              

__allmul ENDP

end