        .text
        .globl addfour

addfour:
        pushl   %ebp
        movl    %esp,%ebp
        pushfl
        pushl   %ebx
        movl    8(%ebp),%eax
        movl    12(%ebp),%ebx
        addl    %ebx,%eax
        movl    16(%ebp),%ebx
        addl    %ebx,%eax
        movl    20(%ebp),%ebx
        addl    %ebx,%eax
        popl    %ebx
        popfl
        movl    (%esp),%ebp
        add     $4,%esp
        ret
