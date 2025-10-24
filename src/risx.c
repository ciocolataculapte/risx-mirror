#include <stdint.h>
#include <multiboot2.h>

uint32_t risx(uint32_t magic, uint32_t addr) {
        if (magic != MULTIBOOT2_MAGIC) {
                return 0x0badc0de;
        }

        // struct multiboot2_t *mb2 = (struct multiboot2_t *)addr;

        return 0xdeadbeef;
        // return addr;
}
