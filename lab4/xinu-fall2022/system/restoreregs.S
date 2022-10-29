    .text
    .globl restoreregs

restoreregs:
    popal
    popfl
    sti           #necessary because we are restoring eflags
    ret