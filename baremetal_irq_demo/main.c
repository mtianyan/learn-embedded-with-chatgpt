#include <stdint.h>

volatile unsigned int irq_counter = 0;

extern void enable_irq(void);
extern void disable_irq(void);
extern void init_vector(void);

void timer_init(void) {
    // QEMU Vexpress-A7 私有定时器寄存器基地址
    volatile uint32_t *timer_load   = (uint32_t *)0x1E000600;
    volatile uint32_t *timer_ctrl   = (uint32_t *)0x1E000608;
    volatile uint32_t *timer_intclr = (uint32_t *)0x1E00060C;

    *timer_load = 1000000;        // 计数初始值（根据时钟调整）
    *timer_ctrl = (1 << 7) |      // Enable interrupt
                  (1 << 6) |      // Auto-reload
                  (1 << 0);       // Enable timer

    *timer_intclr = 1;            // 清除 pending 位
}

void gic_init(void) {
    // 这里只是演示，没有实际初始化
}

void c_irq_handler(void) {
    volatile uint32_t *timer_intclr = (uint32_t *)0x1E00060C;
    *timer_intclr = 1; // 清中断
    irq_counter++;
}

int main(void) {
    disable_irq();
    init_vector();
    gic_init();
    timer_init();
    enable_irq();

    while (1) {
        // 主循环可添加检测 irq_counter 的代码
        // 如用串口打印，需自行实现 UART 初始化和输出
    }

    return 0;
}
