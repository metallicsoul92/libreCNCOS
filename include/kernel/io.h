#ifndef LCNC_KERNEL_IO_H_
#define LCNC_KERNEL_IO_H_ 1

extern uint8_t inb(uint16_t port);
extern uint16_t inw(uint16_t port);
extern uint32_t inl(uint16_t port);
extern uint64_t inq(uint16_t port);

extern void outb(uint16_t port, uint8_t val);
extern void outw(uint16_t port, uint16_t val);
extern void outl(uint16_t port, uint32_t val);
extern void outq(uint16_t port, uint64_t val);

#endif
