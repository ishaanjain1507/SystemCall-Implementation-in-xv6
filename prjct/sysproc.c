#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int sys_fork(void)
{
    return fork();
}

int sys_exit(void)
{
    exit();
    return 0; // not reached
}

int sys_wait(void)
{
    return wait();
}

int sys_kill(void)
{
    int pid;

    if (argint(0, &pid) < 0)
        return -1;
    return kill(pid);
}

int sys_getpid(void)
{
    return myproc()->pid;
}

int sys_sbrk(void)
{
    int addr;
    int n;

    if (argint(0, &n) < 0)
        return -1;
    addr = myproc()->sz;
    if (growproc(n) < 0)
        return -1;
    return addr;
}

int sys_sleep(void)
{
    int n;
    uint ticks0;

    if (argint(0, &n) < 0)
        return -1;
    acquire(&tickslock);
    ticks0 = ticks;
    while (ticks - ticks0 < n)
    {
        if (myproc()->killed)
        {
            release(&tickslock);
            return -1;
        }
        sleep(&ticks, &tickslock);
    }
    release(&tickslock);
    return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int sys_uptime(void)
{
    uint xticks;

    acquire(&tickslock);
    xticks = ticks;
    release(&tickslock);
    return xticks;
}

// function for system call "mydate"
int sys_mydate(void)
{
    struct rtcdate *r;
    if (argptr(0, (void *)&r, sizeof(*r)) < 0)
    {
        return -1;
    }
    cmostime(r);
    return 0;
}

// function for system call "mypgtPrint"
int sys_mypgtPrint(void)
{
    int i, j;
    pte_t *pgtab;
    struct proc *curproc = myproc();
    // char buf[256];
    for (i = 0; i < NPDENTRIES; i++)
    {
        if (!(curproc->pgdir[i] & PTE_P))
        {
            continue;
        }
        pgtab = (pte_t *)P2V(PTE_ADDR(curproc->pgdir[i]));
        for (j = 0; j < NPTENTRIES; j++)
        {
            if (pgtab[j] & PTE_P && pgtab[j] & PTE_U)
            {
                uint virt_addr = (i << PDXSHIFT) | (j << PTXSHIFT);
                uint phys_addr = PTE_ADDR(pgtab[j]);
                cprintf("Entry number: %d\nVirtual address: 0x%x\nPhysical address: 0x%x\n",
                        i * NPTENTRIES + j, virt_addr, phys_addr);
            }
        }
    }
    return 0;
}
