// mailbox.c v0.0.2
#include "main.h" // main header file

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