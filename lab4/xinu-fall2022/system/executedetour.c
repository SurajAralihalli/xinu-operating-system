/* executedetour.c - executedetour */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  executedetour  -  Called by clock interrupt handler to awaken processes
 *------------------------------------------------------------------------
 */

static struct procent *prptr;

static unsigned long  *esp;
static unsigned long  *ebp;
static unsigned long  *ret;

static unsigned long  *Oldeax;
static unsigned long  *Oldebx;
static unsigned long  *Oldecx;
static unsigned long  *Oldedx;
static unsigned long  *Oldesi;
static unsigned long  *Oldedi;
static unsigned long  *Oldebp;
static unsigned long  *Oldesp;

static unsigned long  *Oldeip;
static unsigned long  *Oldeflags;
static unsigned long  *Oldcs;

// static unsigned long  *OldeflagsValue;

static int popi;


void executedetour(void)
{
    // initialize
    prptr = &proctab[currpid];

    // exit
    if(prptr->prmakedetour!=1)
    {
        return;
    }

    // Store in variables
    asm("movl %ebp,ebp");

    ret = (unsigned long *)*(ebp+1);

    Oldedi = (unsigned long *)*(ebp+2);
    Oldesi = (unsigned long *)*(ebp+3);
    Oldebp = (unsigned long *)*(ebp+4);
    Oldesp = (unsigned long *)*(ebp+5);
    Oldebx = (unsigned long *)*(ebp+6);
    Oldedx = (unsigned long *)*(ebp+7);
    Oldecx = (unsigned long *)*(ebp+8);
    Oldeax = (unsigned long *)*(ebp+9);

    Oldeip = (unsigned long *)*(ebp+10);
    Oldcs = (unsigned long *)*(ebp+11);
    Oldeflags = (unsigned long *)*(ebp+12);
    

    // Capture Eflags value
    // OldeflagsValue = (unsigned long *)*Oldeflags;

    for(popi=1;popi<=13;popi++)
    {
        asm("popl %ecx");
    }


    // Push Eip (return address to process)
    asm("pushl %0"
        :
        : "r"(Oldeip)
    );

    // Push Eflags
    asm("pushl %0"
        :
        : "r"(Oldeflags)
    );

    // Push general pupose Registers
    asm("pushl %0"
        :
        : "r"(Oldeax)
    );
    asm("pushl %0"
        :
        : "r"(Oldecx)
    );
    asm("pushl %0"
        :
        : "r"(Oldedx)
    );
    asm("pushl %0"
        :
        : "r"(Oldebx)
    );
    asm("pushl %0"
        :
        : "r"(Oldesp+1)
    );
    asm("pushl %0"
        :
        : "r"(Oldebp)
    );
    asm("pushl %0"
        :
        : "r"(Oldesi)
    );
    asm("pushl %0"
        :
        : "r"(Oldedi)
    );


    // Push restore reg address
    asm("pushl %0"
        :
        : "r"(restoreregs)
    );

    // Push iret variables
    asm("pushl %0"
        :
        : "r"(Oldeflags)
    );
    asm("pushl %0"
        :
        : "r"(Oldcs)
    );
    asm("pushl %0"
        :
        : "r"(proctab[currpid].prcbftn)
    );

    // Capture latest esp
    asm("movl %esp,esp");

    // Push general purpose registers
    asm("pushl %0"
        :
        : "r"(Oldeax)
    );
    asm("pushl %0"
        :
        : "r"(Oldecx)
    );
    asm("pushl %0"
        :
        : "r"(Oldedx)
    );
    asm("pushl %0"
        :
        : "r"(Oldebx)
    );
    asm("pushl %0"
        :
        : "r"(esp)
    );
    asm("pushl $0xDEADBEEF"); // push ebp (not used by anyone)
    asm("pushl %0"
        :
        : "r"(Oldesi)
    );
    asm("pushl %0"
        :
        : "r"(Oldedi)
    );

    // Push return address to clksdisp
    asm("pushl %0"
        :
        : "r"(ret)
    );
    asm("pushl $0xDEADBEEF"); // push ebp (not used by anyone)

    // Set ebp
    asm("movl %esp,%ebp");

    // Reset prptr->prmakedetour
    prptr->prmakedetour = 0;
}

void debugStack()
{
    if(currpid==5 && popi==14)
    {
        // kprintf("\nEflags %x\n",OldeflagsValue);
        popi = 0;
    }
}

