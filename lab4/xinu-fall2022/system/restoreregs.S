    .text
    .globl restoreregs

restoreregs:
    popal
    popfl
    ret