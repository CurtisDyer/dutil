;
; bitcount.asm - quickly count bits
; Calling convention: __cdecl
;
; NASM win32 build:
;
;   nasm -f win32 bitcount.asm
;
; Link the resulting object file against the C program calling the
; function. The win32 i386 object file requires the VC++ Microsoft
; compiler, or something else that deals with the format.
;
; vim:set ft=nasm:
;

; Linux C doesn't put underscores on labels
%ifdef ELF_TYPE
    %define _printf     printf
    %define _bitcount   bitcount
%endif

; Code
%ifdef OBJ_TYPE
segment text public align=1 class=code use32
%else
segment .text
%endif
    global _bitcount
    extern _printf

_bitcount:
    enter   0,0                     ; new stack frame

    mov     ebx, 0
    mov     eax, [ebp+8]            ; Parameter on stack
    test    eax, eax
    jz      finish

shift:
    shr     eax, 1                  ; shift a bit, yo
    jc      carry                   ; bit shifted was set
    jmp     next
carry:
    inc     ebx
next:
    test    eax, eax
    jz      finish
    jmp     shift

finish:
    mov     eax, ebx                ; return result

    leave                           ; restore previous stack frame
    ret

