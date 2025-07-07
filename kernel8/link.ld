ENTRY(entry)

PHDRS {
    text PT_LOAD;
    data PT_LOAD;
    bss  PT_LOAD;
}



SECTIONS {
    . = 0x80000;

    .text : {
        KEEP(*(.text.entry))   /* force your entry section to be first */
        *(.text*)              /* rest of the text code */
    } :text

    .rodata : {
        *(.rodata*)
    } :text

    .data : {
        *(.data*)
    } :data

    .bss : {
        *(.bss*)
        *(COMMON)
    } :bss

    . = ALIGN(16);
    .stack (NOLOAD) : {
        stack_bottom = .;
        . = . + 0x1000;     /* Reserve 4 KB stack */
        stack_top = .;
    } :bss
}