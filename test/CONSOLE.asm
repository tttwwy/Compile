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
local score[6]:DWORD
local credit[6]:DWORD
local stu_number:DWORD
local mean:DWORD
local sum:DWORD
local temp:DWORD
local i:DWORD
local a[9]:BYTE
local string0[34]:BYTE
local string1[3]:BYTE
local string2[54]:BYTE
local string3[53]:BYTE
mov score+0,76
mov score+4,82
mov score+8,90
mov score+12,86
mov score+16,79
mov score+20,62
mov credit+0,2
mov credit+4,2
mov credit+8,1
mov credit+12,2
mov credit+16,2
mov credit+20,3
mov a+0,'a'
mov a+1,'s'
mov a+2,'d'
mov a+3,'f'
mov a+4,'a'
mov a+5,'s'
mov a+6,'d'
mov a+7,'f'
mov a+8,0
mov string0+0,'p'
mov string0+1,'l'
mov string0+2,'e'
mov string0+3,'a'
mov string0+4,'s'
mov string0+5,'e'
mov string0+6,' '
mov string0+7,'i'
mov string0+8,'n'
mov string0+9,'p'
mov string0+10,'u'
mov string0+11,'t'
mov string0+12,' '
mov string0+13,'y'
mov string0+14,'o'
mov string0+15,'u'
mov string0+16,'r'
mov string0+17,' '
mov string0+18,'s'
mov string0+19,'t'
mov string0+20,'u'
mov string0+21,'d'
mov string0+22,'e'
mov string0+23,'n'
mov string0+24,'t'
mov string0+25,' '
mov string0+26,'n'
mov string0+27,'u'
mov string0+28,'m'
mov string0+29,'b'
mov string0+30,'e'
mov string0+31,'r'
mov string0+32,':'
mov string0+33,0
lea eax,string0
push eax
call crt_printf
lea eax,stu_number
push eax
mov string1+0,'%'
mov string1+1,'d'
mov string1+2,0
lea eax,string1
push eax
call crt_scanf
mov sum,0
mov temp,0
mov i,0
jmp2:mov eax,i
cmp eax,6
jl jmp0
jmp jmp1
jmp0:mov eax,i
mov edx,4
imul edx
mov ebx,eax
mov ebx,score+[ebx]
mov eax,i
mov edx,4
imul edx
mov ecx,eax
mov ecx,credit+[ecx]
mov eax,ebx
mov edx,ecx
imul edx
mov edx,eax
mov eax,sum
add eax,edx
mov ebx,eax
mov sum,ebx
mov eax,i
mov edx,4
imul edx
mov ebx,eax
mov ebx,credit+[ebx]
mov eax,temp
add eax,ebx
mov ecx,eax
mov temp,ecx
mov eax,i
add eax,1
mov i,eax
jmp jmp2
jmp1:mov ebx,sum
mov eax,ebx
cdq
mov ebx,temp
idiv ebx
mov ebx,eax
mov mean,ebx
mov eax,mean
cmp eax,60
jge jmp3
jmp jmp4
jmp3:mov eax,mean
sub eax,60
mov ebx,eax
mov mean,ebx
push stu_number
push mean
mov string2+0,'t'
mov string2+1,'h'
mov string2+2,'e'
mov string2+3,' '
mov string2+4,'s'
mov string2+5,'c'
mov string2+6,'o'
mov string2+7,'r'
mov string2+8,'e'
mov string2+9,' '
mov string2+10,'o'
mov string2+11,'f'
mov string2+12,' '
mov string2+13,'s'
mov string2+14,'t'
mov string2+15,'u'
mov string2+16,'d'
mov string2+17,'e'
mov string2+18,'n'
mov string2+19,'t'
mov string2+20,' '
mov string2+21,'n'
mov string2+22,'u'
mov string2+23,'m'
mov string2+24,'b'
mov string2+25,'e'
mov string2+26,'r'
mov string2+27,' '
mov string2+28,'%'
mov string2+29,'d'
mov string2+30,' '
mov string2+31,'i'
mov string2+32,'s'
mov string2+33,' '
mov string2+34,'%'
mov string2+35,'d'
mov string2+36,' '
mov string2+37,'h'
mov string2+38,'i'
mov string2+39,'g'
mov string2+40,'h'
mov string2+41,'e'
mov string2+42,'r'
mov string2+43,' '
mov string2+44,'t'
mov string2+45,'h'
mov string2+46,'a'
mov string2+47,'n'
mov string2+48,' '
mov string2+49,'6'
mov string2+50,'0'
mov string2+51,'.'
mov string2+52,10
mov string2+53,0
lea eax,string2
push eax
call crt_printf
jmp jmp5
jmp4:mov eax,60
sub eax,mean
mov ebx,eax
mov mean,ebx
push stu_number
push mean
mov string3+0,'t'
mov string3+1,'h'
mov string3+2,'e'
mov string3+3,' '
mov string3+4,'s'
mov string3+5,'c'
mov string3+6,'o'
mov string3+7,'r'
mov string3+8,'e'
mov string3+9,' '
mov string3+10,'o'
mov string3+11,'f'
mov string3+12,' '
mov string3+13,'s'
mov string3+14,'t'
mov string3+15,'u'
mov string3+16,'d'
mov string3+17,'e'
mov string3+18,'n'
mov string3+19,'t'
mov string3+20,' '
mov string3+21,'n'
mov string3+22,'u'
mov string3+23,'m'
mov string3+24,'b'
mov string3+25,'e'
mov string3+26,'r'
mov string3+27,' '
mov string3+28,'%'
mov string3+29,'d'
mov string3+30,' '
mov string3+31,'i'
mov string3+32,'s'
mov string3+33,' '
mov string3+34,'%'
mov string3+35,'d'
mov string3+36,' '
mov string3+37,'l'
mov string3+38,'o'
mov string3+39,'w'
mov string3+40,'e'
mov string3+41,'r'
mov string3+42,' '
mov string3+43,'t'
mov string3+44,'h'
mov string3+45,'a'
mov string3+46,'n'
mov string3+47,' '
mov string3+48,'6'
mov string3+49,'0'
mov string3+50,'.'
mov string3+51,10
mov string3+52,0
lea eax,string3
push eax
call crt_printf
jmp5:mov eax,0
invoke StdIn,addr buffer,sizeof buffer
invoke ExitProcess,0
ret
main endp
end main


