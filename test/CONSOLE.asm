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
F proc i
push ebx
push ecx
push edx
mov eax,i
cmp eax,1
je jmp0
jmp jmp1
jmp0:mov eax,1
pop edx
pop ecx
pop ebx
ret
jmp1:mov eax,i
sub eax,1
mov ebx,eax
push ebx
call F
mov ecx,eax
mov eax,ecx
mov edx,i
imul edx
mov edx,eax
mov eax,edx
pop edx
pop ecx
pop ebx
ret
F endp


main proc 
local score[6]:DWORD
local credit[6]:DWORD
local stu_number:DWORD
local mean:DWORD
local sum:DWORD
local temp:DWORD
local number:DWORD
local i:DWORD
local a[35]:BYTE
local string0[14]:BYTE
local string1[3]:BYTE
local string2[16]:BYTE
local string3[3]:BYTE
local string4[3]:BYTE
local string5[54]:BYTE
local string6[53]:BYTE
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
mov i,0
mov a+0,'p'
mov a+1,'l'
mov a+2,'e'
mov a+3,'a'
mov a+4,'s'
mov a+5,'e'
mov a+6,' '
mov a+7,'i'
mov a+8,'n'
mov a+9,'p'
mov a+10,'u'
mov a+11,'t'
mov a+12,' '
mov a+13,'y'
mov a+14,'o'
mov a+15,'u'
mov a+16,'r'
mov a+17,' '
mov a+18,'s'
mov a+19,'t'
mov a+20,'u'
mov a+21,'d'
mov a+22,'e'
mov a+23,'n'
mov a+24,'t'
mov a+25,' '
mov a+26,'n'
mov a+27,'u'
mov a+28,'m'
mov a+29,'b'
mov a+30,'e'
mov a+31,'r'
mov a+32,':'
mov a+33,10
mov a+34,0
jmp8:mov eax,1
cmp eax,0
jne jmp0
jmp jmp1
jmp0:mov string0+0,'Ç'
mov string0+1,'ë'
mov string0+2,'Ê'
mov string0+3,'ä'
mov string0+4,'È'
mov string0+5,'ë'
mov string0+6,'Ê'
mov string0+7,'ý'
mov string0+8,'×'
mov string0+9,'Ö'
mov string0+10,'£'
mov string0+11,'º'
mov string0+12,10
mov string0+13,0
lea eax,string0
push eax
call crt_printf
lea eax,number
push eax
mov string1+0,'%'
mov string1+1,'d'
mov string1+2,0
lea eax,string1
push eax
call crt_scanf
push number
call F
mov ebx,eax
mov temp,ebx
push temp
push number
mov string2+0,'%'
mov string2+1,'d'
mov string2+2,'µ'
mov string2+3,'Ä'
mov string2+4,'½'
mov string2+5,'×'
mov string2+6,'³'
mov string2+7,'Ë'
mov string2+8,'Î'
mov string2+9,'ª'
mov string2+10,'£'
mov string2+11,'º'
mov string2+12,'%'
mov string2+13,'d'
mov string2+14,10
mov string2+15,0
lea eax,string2
push eax
call crt_printf
lea eax,a
push eax
mov string3+0,'%'
mov string3+1,'s'
mov string3+2,0
lea eax,string3
push eax
call crt_printf
lea eax,stu_number
push eax
mov string4+0,'%'
mov string4+1,'d'
mov string4+2,0
lea eax,string4
push eax
call crt_scanf
mov sum,0
mov temp,0
mov i,0
jmp4:mov eax,i
cmp eax,6
jl jmp2
jmp jmp3
jmp2:mov eax,i
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
jmp jmp4
jmp3:mov ebx,sum
mov eax,ebx
cdq
mov ebx,temp
idiv ebx
mov ebx,eax
mov mean,ebx
mov eax,mean
cmp eax,60
jge jmp5
jmp jmp6
jmp5:mov eax,mean
sub eax,60
mov ebx,eax
mov mean,ebx
push mean
push stu_number
mov string5+0,'t'
mov string5+1,'h'
mov string5+2,'e'
mov string5+3,' '
mov string5+4,'s'
mov string5+5,'c'
mov string5+6,'o'
mov string5+7,'r'
mov string5+8,'e'
mov string5+9,' '
mov string5+10,'o'
mov string5+11,'f'
mov string5+12,' '
mov string5+13,'s'
mov string5+14,'t'
mov string5+15,'u'
mov string5+16,'d'
mov string5+17,'e'
mov string5+18,'n'
mov string5+19,'t'
mov string5+20,' '
mov string5+21,'n'
mov string5+22,'u'
mov string5+23,'m'
mov string5+24,'b'
mov string5+25,'e'
mov string5+26,'r'
mov string5+27,' '
mov string5+28,'%'
mov string5+29,'d'
mov string5+30,' '
mov string5+31,'i'
mov string5+32,'s'
mov string5+33,' '
mov string5+34,'%'
mov string5+35,'d'
mov string5+36,' '
mov string5+37,'h'
mov string5+38,'i'
mov string5+39,'g'
mov string5+40,'h'
mov string5+41,'e'
mov string5+42,'r'
mov string5+43,' '
mov string5+44,'t'
mov string5+45,'h'
mov string5+46,'a'
mov string5+47,'n'
mov string5+48,' '
mov string5+49,'6'
mov string5+50,'0'
mov string5+51,'.'
mov string5+52,10
mov string5+53,0
lea eax,string5
push eax
call crt_printf
jmp jmp7
jmp6:mov eax,60
sub eax,mean
mov ebx,eax
mov mean,ebx
push mean
push stu_number
mov string6+0,'t'
mov string6+1,'h'
mov string6+2,'e'
mov string6+3,' '
mov string6+4,'s'
mov string6+5,'c'
mov string6+6,'o'
mov string6+7,'r'
mov string6+8,'e'
mov string6+9,' '
mov string6+10,'o'
mov string6+11,'f'
mov string6+12,' '
mov string6+13,'s'
mov string6+14,'t'
mov string6+15,'u'
mov string6+16,'d'
mov string6+17,'e'
mov string6+18,'n'
mov string6+19,'t'
mov string6+20,' '
mov string6+21,'n'
mov string6+22,'u'
mov string6+23,'m'
mov string6+24,'b'
mov string6+25,'e'
mov string6+26,'r'
mov string6+27,' '
mov string6+28,'%'
mov string6+29,'d'
mov string6+30,' '
mov string6+31,'i'
mov string6+32,'s'
mov string6+33,' '
mov string6+34,'%'
mov string6+35,'d'
mov string6+36,' '
mov string6+37,'l'
mov string6+38,'o'
mov string6+39,'w'
mov string6+40,'e'
mov string6+41,'r'
mov string6+42,' '
mov string6+43,'t'
mov string6+44,'h'
mov string6+45,'a'
mov string6+46,'n'
mov string6+47,' '
mov string6+48,'6'
mov string6+49,'0'
mov string6+50,'.'
mov string6+51,10
mov string6+52,0
lea eax,string6
push eax
call crt_printf
jmp7:jmp jmp8
jmp1:mov eax,0
invoke StdIn,addr buffer,sizeof buffer
invoke ExitProcess,0
ret
main endp
end main


