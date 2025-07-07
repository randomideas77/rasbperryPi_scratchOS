.extern stack_top

.section .text
.global entry

entry:
    ldr     x0, =stack_top  // load 64bits from memory at addr=stack_top to x0
    mov     sp, x0          // sp = x0 (sp = stack pointer)
    bl      kernel_main     // branch to kernel_main, store current address in x30

1:  wfe                     // wait for event
    bl      1b              // branch up to 1:, store current address in x30

.section .bss
.balign 16
stack:
    .skip 0x4000
stack_top:
