        .text
        .globl testgreaterfirst

testgreaterfirst:
        pushl   %ebp
        movl    %esp,%ebp
        pushfl
        pushl   %ebx
        movl    8(%ebp),%eax
        movl    12(%ebp),%ebx
        pushl   %ebx
        pushl   %eax
        call    greaterfirst
        popl    %ebx
        popl    %ebx
        popl    %ebx
        popfl
        movl    (%esp),%ebp
        add     $4,%esp
        ret
