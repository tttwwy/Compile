.386
.model flat,stdcall
option casemap :none
include windows.inc
include user32.inc
include msvcrt.inc
include kernel32.inc
include masm32.inc
include gdi32.inc
includelib gdi32.lib
includelib user32.lib
includelib kernel32.lib
includelib masm32.lib
includelib msvcrt.lib
include macro.asm
.data
buffer	db MAX_PATH dup(?)
.code
main proc 
local string0[10]:BYTE
jmp2:mov eax,1
cmp eax,0
jne jmp0
jmp jmp1
jmp0:mov string0+0,'a'
mov string0+1,'s'
mov string0+2,'d'
mov string0+3,'f'
mov string0+4,'a'
mov string0+5,'s'
mov string0+6,'d'
mov string0+7,'f'
mov string0+8,10
mov string0+9,0
lea eax,string0
push eax
call crt_printf
jmp jmp2
jmp1:mov eax,0
invoke StdIn,addr buffer,sizeof buffer
invoke ExitProcess,0
ret
main endp
end main


