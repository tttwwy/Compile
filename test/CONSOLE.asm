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
local a:DWORD
local b:DWORD
local string0[3]:BYTE
local string1[4]:BYTE
mov a,0
mov b,0
lea eax,a
push eax
mov string0+0,'%'
mov string0+1,'d'
mov string0+2,0
lea eax,string0
push eax
call crt_scanf
push a
mov string1+0,'%'
mov string1+1,'d'
mov string1+2,10
mov string1+3,0
lea eax,string1
push eax
call crt_printf
mov eax,0
invoke StdIn,addr buffer,sizeof buffer
invoke ExitProcess,0
ret
main endp
end main


