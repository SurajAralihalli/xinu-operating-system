        .text
        .globl addtwo

addtwo:
        pushl   %ebp
        movl    %esp,%ebp
        pushfl
        pushl   %ebx
        movl    8(%ebp),%eax
        movl    12(%ebp),%ebx
        addl    %ebx,%eax
        popl    %ebx
        popfl
        movl    (%esp),%ebp
        add     $4,%esp
        ret
