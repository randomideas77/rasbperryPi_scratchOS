// main.h
#ifndef MAIN_H
#define MAIN_H

// GPIO setup
#define GPIO_BASE 0x3F200000  // For Pi 3B+ (BCM2837)
#define GPFSEL2   ((volatile unsigned int*)(GPIO_BASE + 0x08))
#define GPSET0    ((volatile unsigned int*)(GPIO_BASE + 0x1C))
#define GPCLR0    ((volatile unsigned int*)(GPIO_BASE + 0x28))

// Mailbox setup
#define MMIO_BASE       0x3F000000
#define MAILBOX_BASE    (MMIO_BASE + 0xB880)
#define MAILBOX_READ    ((volatile unsigned int*)(MAILBOX_BASE + 0x0))
#define MAILBOX_STATUS  ((volatile unsigned int*)(MAILBOX_BASE + 0x18))
#define MAILBOX_WRITE  ((volatile unsigned int*)(MAILBOX_BASE + 0x20))
#define MAILBOX_EMPTY   0x40000000
#define MAILBOX_FULL   0x80000000
#define MAILBOX_TIMEOUT_ERROR 0xFFFFFFFF

#endif