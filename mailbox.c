// mailbox.c v0.0.3
#include "main.h" // main header file

static volatile unsigned int __attribute__((aligned(16))) mbox[36]; // mailbox buffer in memory

void mailbox_write(unsigned int message, unsigned int channel) {
    while (*MAILBOX_STATUS & MAILBOX_FULL);                 // wait if mailbox is full
    *MAILBOX_WRITE = (message & ~0xF) | (channel & 0xF);    // write message + channel
}

unsigned int mailbox_read(unsigned int channel) {
    unsigned int data;
    int timeout;

    do {
        timeout = 100000;
        while ((*MAILBOX_STATUS & MAILBOX_EMPTY) && --timeout); // wait for mailbox to have data
        if (timeout == 0) return MAILBOX_TIMEOUT_ERROR;                    // return if the mailbox timesout
        
        data = *MAILBOX_READ;
    } while ((data & 0xF) != channel);                          // check if response is for correct channel
    return data & ~0xF;
}

// ------------- mailbox commands -------------

// gets board revision number
unsigned int get_revision_number(void) {
    mbox[0] = 8 * 4;
    mbox[1] = 0;
    mbox[2] = 0x00010002; // tag for board revision
    mbox[3] = 4;
    mbox[4] = 0;
    mbox[5] = 0;
    mbox[6] = 0;

    mailbox_write((unsigned int)((unsigned long)mbox) >> 4, 8);
    if (mailbox_read(8) == MAILBOX_TIMEOUT_ERROR) {
        return 0xFFFFFFFF;
    }
    return mbox[5];
}