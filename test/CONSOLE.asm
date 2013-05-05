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
cal proc a,b,d
push ebx
push ecx
push edx
mov ebx,a
mov eax,ebx
mov edx,b
imul edx
mov ebx,eax
mov eax,ebx
mov edx,d
imul edx
mov ecx,eax
mov eax,ecx
pop edx
pop ecx
pop ebx
ret
cal endp


main proc 
local a[1]:DWORD
local b:DWORD
local string0[4]:BYTE
mov a+0,1
mov a+4,2
mov a+8,3
push 3
push 2
push 1
call cal
mov ebx,eax
mov b,ebx
mov string0+0,'%'
mov string0+1,'d'
mov string0+2,10
mov string0+3,0
invoke crt_printf,addr string0,b
mov eax,0
invoke StdIn,addr buffer,sizeof buffer
invoke ExitProcess,0
ret
main endp
end main


