#ifndef RISX_MULTIBOOT2_H
#define RISX_MULTIBOOT2_H 1

// #include <stdint.h>

#define MULTIBOOT2_MAGIC 0x36D76289

// struct multiboot2_t {
//         uint32_t total_size;
//         uint32_t reserved;
//         tag_t    tags[];
// };

// struct tag_t {
//         uint32_t type;
//         uint32_t size;
// };

// // basic memory information
// struct meminfo_t {
//         uint32_t type; // 4
//         uint32_t size; // 16
//         uint32_t mem_lower;
//         uint32_t mem_upper;
// }

// // BIOS boot device information
// struct bootdev_t {
//         uint32_t type; // 5
//         uint32_t size; // 20
//         uint32_t biosdev;
//         uint32_t partition;
//         uint32_t sub_partition;
// };

// // Boot command line information
// struct cmdline_t {
//         uint32_t type; // 1
//         uint32_t size;
//         char     cmdline[];
// };

// // Module information
// struct module_t {
//         uint32_t type; // 3
//         uint32_t size;
//         uint32_t mod_start;
//         uint32_t mod_end;
//         char     cmdline[];
// }

// // ELF symbols information
// struct elfsyms_t {
//         uint32_t type; // 9
//         uint32_t size;
//         uint32_t num;
//         uint32_t entsize;
//         uint32_t shndx;
//         uint32_t reserved;
//         // varies section headers
// };

// // Memory map information
// struct mmap_t {
//         uint32_t type; // 6
//         uint32_t size;
//         uint32_t entry_size;
//         uint32_t entry_version;
//         struct {
//                 uint64_t addr;
//                 uint64_t len;
//                 uint32_t type;
//                 uint32_t reserved;
//         } entries[];
// };

// // Bootloader name information
// struct bootloader_t {
//         uint32_t type; // 2
//         uint32_t size;
//         char     name[];
// };

#endif
