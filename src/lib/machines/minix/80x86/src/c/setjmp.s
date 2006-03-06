.sect .text; .sect .rom; .sect .data; .sect .bss
.sect .text

.define ___setjmp
___setjmp:

  mov eax, 4(esp)    ! address of sigjmp_buf structure, env
  mov   (eax), ebx   ! env[0].__regs[JB_BX] = ebx, ...
  mov  4(eax), esi
  mov  8(eax), edi
  mov 12(eax), ebp
  lea ecx, 4(esp)    ! stack pointer after returning from ___setjmp
  mov 16(eax), ecx
  mov ecx, (esp)     ! return address
  mov 20(eax), ecx

  cmp 8(esp), 0      ! do we need to save the signal mask?
  je .dontsavemask
  mov 24(eax), 1     ! env[0].__flag = 1
  lea ecx, 28(eax)   ! address of env[0].__mask
  push ecx
  call ___newsigset  ! /usr/src/lib/ansi/sigmisc.c
  pop ecx
  xor eax, eax       ! return 0
  ret
.dontsavemask:
  mov 24(eax), 0     ! env[0].__flag = 0
  xor eax, eax       ! return 0
  ret

.define ___longjmp
___longjmp:

  mov eax, 4(esp)    ! address of sigjmp_buf structure, env
  cmp 24(eax), 0     ! env[0].__flag == 0? (did we save the signal mask?)
  je .masknotsaved
  lea ecx, 28(eax)   ! address of env[0].__mask
  push ecx
  call ___oldsigset  ! /usr/src/lib/ansi/sigmisc.c
  pop ecx

.masknotsaved:
  mov ecx, 4(esp)    ! address of sigjmp_buf structure, env
  mov eax, 8(esp)    ! (faked) return value for (sig)setjmp

  mov ebx, (ecx)     ! ebx = env[0].__regs[JB_BX], ...
  mov esi, 4(ecx)
  mov edi, 8(ecx)
  mov ebp, 12(ecx)
  mov esp, 16(ecx)
  mov edx, 20(ecx)   ! edx = return address of original (sig)setjmp call
  jmp edx            ! faked return
