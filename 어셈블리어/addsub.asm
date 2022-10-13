TITLE addvssub ;같은 수식이래도 명령어를 add로 쓰느냐 sub를 쓰느냐에 따라 CF값이 달라질 수 있다.      

INCLUDE Irvine32.inc

.data
.code
main PROC

	mov al, 0
	add al, -1
	call	DumpRegs ;CF=0


	mov al, 0
	sub al, 1
	call	DumpRegs ;CF=1 
                  ;sub명령어는 carry가 없어야 CF=1

exit
main ENDP
END main
