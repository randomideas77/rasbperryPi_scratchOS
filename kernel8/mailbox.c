// mailbox.c
#include "main.h" // main header file

void mailbox_write(unsigned int message, unsigned int channel) {
    while (*MAILBOX_STATUS & MAILBOX_FULL);                 // wait if mailbox is full
    *MAILBOX_WRITE = (message & ~0xF) | (channel & 0xF);    // write message + channel
}

unsigned int mailbox_read(unsigned int channel) {
    unsigned int data;
    do {
        while (*MAILBOX_STATUS & MAILBOX_EMPTY);            // wait for mailbox to have data
        data = *MAILBOX_READ;
    } while ((data & 0xF) != channel);                      // check if respoinse is for correct channel
    return data & ~0xF;
}