.global _start
.global init_vector
.global c_irq_handler

.section .text
_start:
    b reset
    b undefined
    b swi
    b prefetch_abort
    b data_abort
    b reserved
    b irq_handler
    b fiq_handler

init_vector:
    ldr r0, =_start
    ldr r1, =0x00000000
    mov r2, #8
copy_vector:
    ldr r3, [r0], #4
    str r3, [r1], #4
    subs r2, r2, #1
    bne copy_vector
    bx lr

reset:
    b main
undefined:
swi:
prefetch_abort:
data_abort:
reserved:
fiq_handler:
    subs pc, lr, #4

irq_handler:
    sub lr, lr, #4
    stmfd sp!, {r0-r12, lr}
    bl c_irq_handler
    ldmfd sp!, {r0-r12, lr}
    subs pc, lr, #0
