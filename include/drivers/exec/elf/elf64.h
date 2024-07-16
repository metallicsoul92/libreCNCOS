#ifndef LCNC_DRIVERS_EXEC_X86_64_ELF_H
#define LCNC_DRIVERS_EXEC_X86_64_ELF_H

#include "../../libc/include/sys/cdefs.h"

/* 64-bit ELF base types. */
typedef uint64_t Elf64_Addr;
typedef uint16_t Elf64_Half;
typedef uint64_t Elf64_Off;
typedef int32_t  Elf64_Sword;
typedef uint32_t Elf64_Word;
typedef uint64_t Elf64_Xword;
typedef int64_t  Elf64_Sxword;

#define PT_NULL    0
#define PT_LOAD    1
#define PT_DYNAMIC 2
#define PT_INTERP  3
#define PT_NOTE    4
#define PT_SHLIB   5
#define PT_PHDR    6
#define PT_TLS     7               /* Thread local storage segment */
#define PT_LOOS    0x60000000      /* OS-specific */
#define PT_HIOS    0x6fffffff      /* OS-specific */
#define PT_LOPROC  0x70000000
#define PT_HIPROC  0x7fffffff
#define PT_GNU_EH_FRAME 0x6474e550

#define PT_GNU_STACK  (PT_LOOS + 0x474e551)

#define PN_XNUM 0xffff

/* These constants define the different ELF file types */
#define ET_NONE   0
#define ET_REL    1
#define ET_EXEC   2
#define ET_DYN    3
#define ET_CORE   4
#define ET_LOPROC 0xff00
#define ET_HIPROC 0xffff

/* This is the info that is needed to parse the dynamic section of the file */
#define DT_NULL    0
#define DT_NEEDED  1
#define DT_PLTRELSZ 2
#define DT_PLTGOT  3
#define DT_HASH    4
#define DT_STRTAB  5
#define DT_SYMTAB  6
#define DT_RELA    7
#define DT_RELASZ  8
#define DT_RELAENT 9
#define DT_STRSZ   10
#define DT_SYMENT  11
#define DT_INIT    12
#define DT_FINI    13
#define DT_SONAME  14
#define DT_RPATH   15
#define DT_SYMBOLIC 16
#define DT_REL     17
#define DT_RELSZ   18
#define DT_RELENT  19
#define DT_PLTREL  20
#define DT_DEBUG   21
#define DT_TEXTREL 22
#define DT_JMPREL  23
#define DT_ENCODING 32
#define OLD_DT_LOOS 0x60000000
#define DT_LOOS    0x6000000d
#define DT_HIOS    0x6ffff000
#define DT_VALRNGLO 0x6ffffd00
#define DT_VALRNGHI 0x6ffffdff
#define DT_ADDRRNGLO 0x6ffffe00
#define DT_ADDRRNGHI 0x6ffffeff
#define DT_VERSYM  0x6ffffff0
#define DT_RELACOUNT 0x6ffffff9
#define DT_RELCOUNT 0x6ffffffa
#define DT_FLAGS_1 0x6ffffffb
#define DT_VERDEF  0x6ffffffc
#define DT_VERDEFNUM 0x6ffffffd
#define DT_VERNEED 0x6ffffffe
#define DT_VERNEEDNUM 0x6fffffff
#define OLD_DT_HIOS 0x6fffffff
#define DT_LOPROC  0x70000000
#define DT_HIPROC  0x7fffffff

/* This info is needed when parsing the symbol table */
#define STB_LOCAL  0
#define STB_GLOBAL 1
#define STB_WEAK   2

#define STT_NOTYPE  0
#define STT_OBJECT  1
#define STT_FUNC    2
#define STT_SECTION 3
#define STT_FILE    4
#define STT_COMMON  5
#define STT_TLS     6

#define ELF_ST_BIND(x)    ((x) >> 4)
#define ELF_ST_TYPE(x)    (((unsigned int) x) & 0xf)
#define ELF64_ST_BIND(x)  ELF_ST_BIND(x)
#define ELF64_ST_TYPE(x)  ELF_ST_TYPE(x)


typedef struct dynamic {
  Elf64_Sxword d_tag;
  union {
    Elf64_Xword d_val;
    Elf64_Addr  d_ptr;
  } d_un;
} Elf64_Dyn;


/* The following are used with relocations */
#define ELF64_R_SYM(x)    ((x) >> 32)
#define ELF64_R_TYPE(x)   ((x) & 0xffffffffL)

typedef struct elf64_rel {
  Elf64_Addr r_offset;
  Elf64_Xword r_info;
} Elf64_Rel;

typedef struct elf64_rela {
  Elf64_Addr r_offset;
  Elf64_Xword r_info;
  Elf64_Sxword r_addend;
} Elf64_Rela;


typedef struct elf64_sym {
  Elf64_Word st_name;
  unsigned char st_info;
  unsigned char st_other;
  Elf64_Half st_shndx;
  Elf64_Addr st_value;
  Elf64_Xword st_size;
} Elf64_Sym;


#define EI_NIDENT 16

typedef struct elf64_hdr {
  unsigned char e_ident[EI_NIDENT];
  Elf64_Half e_type;
  Elf64_Half e_machine;
  Elf64_Word e_version;
  Elf64_Addr e_entry;  /* Entry point */
  Elf64_Off e_phoff;
  Elf64_Off e_shoff;
  Elf64_Word e_flags;
  Elf64_Half e_ehsize;
  Elf64_Half e_phentsize;
  Elf64_Half e_phnum;
  Elf64_Half e_shentsize;
  Elf64_Half e_shnum;
  Elf64_Half e_shstrndx;
} Elf64_Ehdr;

/* These constants define the permissions on sections in the program
   header, p_flags. */
#define PF_R 0x4
#define PF_W 0x2
#define PF_X 0x1

typedef struct elf64_phdr {
  Elf64_Word p_type;
  Elf64_Word p_flags;
  Elf64_Off p_offset;
  Elf64_Addr p_vaddr;
  Elf64_Addr p_paddr;
  Elf64_Xword p_filesz;
  Elf64_Xword p_memsz;
  Elf64_Xword p_align;
} Elf64_Phdr;


/* sh_type */
#define SHT_NULL   0
#define SHT_PROGBITS  1
#define SHT_SYMTAB  2
#define SHT_STRTAB  3
#define SHT_RELA  4
#define SHT_HASH  5
#define SHT_DYNAMIC  6
#define SHT_NOTE  7
#define SHT_NOBITS  8
#define SHT_REL  9
#define SHT_SHLIB  10
#define SHT_DYNSYM  11
#define SHT_NUM  12
#define SHT_LOPROC  0x70000000
#define SHT_HIPROC  0x7fffffff
#define SHT_LOUSER  0x80000000
#define SHT_HIUSER  0xffffffff

/* sh_flags */
#define SHF_WRITE  0x1
#define SHF_ALLOC  0x2
#define SHF_EXECINSTR  0x4
#define SHF_RELA_LIVEPATCH  0x00100000
#define SHF_RO_AFTER_INIT  0x00200000
#define SHF_MASKPROC  0xf0000000

/* special section indexes */
#define SHN_UNDEF  0
#define SHN_LORESERVE  0xff00
#define SHN_LOPROC  0xff00
#define SHN_HIPROC  0xff1f
#define SHN_LIVEPATCH  0xff20
#define SHN_ABS  0xfff1
#define SHN_COMMON  0xfff2
#define SHN_HIRESERVE  0xffff

typedef struct elf64_shdr {
  Elf64_Word sh_name;
  Elf64_Word sh_type;
  Elf64_Xword sh_flags;
  Elf64_Addr sh_addr;
  Elf64_Off sh_offset;
  Elf64_Xword sh_size;
  Elf64_Word sh_link;
  Elf64_Word sh_info;
  Elf64_Xword sh_addralign;
  Elf64_Xword sh_entsize;
} Elf64_Shdr;


#define EI_MAG0  0  /* e_ident[] indexes */
#define EI_MAG1  1
#define EI_MAG2  2
#define EI_MAG3  3
#define EI_CLASS  4
#define EI_DATA  5
#define EI_VERSION  6
#define EI_OSABI  7
#define EI_PAD  8

#define ELFMAG0  0x7f  /* EI_MAG */
#define ELFMAG1  'E'
#define ELFMAG2  'L'
#define ELFMAG3  'F'
#define ELFMAG  "\177ELF"
#define SELFMAG  4

#define ELFCLASSNONE  0  /*Here is the continuation and completion of the `elf64.h` header file:

```c
#define ELFCLASSNONE  0
#define ELFCLASS32    1
#define ELFCLASS64    2
#define ELFCLASSNUM   3

#define ELFDATANONE   0
#define ELFDATA2LSB   1
#define ELFDATA2MSB   2

#define EV_NONE       0
#define EV_CURRENT    1
#define EV_NUM        2

#define ELFOSABI_NONE       0
#define ELFOSABI_LINUX      3
#define ELFOSABI_HURD       4
#define ELFOSABI_SOLARIS    6
#define ELFOSABI_AIX        7
#define ELFOSABI_FREEBSD    9
#define ELFOSABI_OPENBSD    12
#define ELFOSABI_ARM_AEABI  64
#define ELFOSABI_ARM        97
#define ELFOSABI_STANDALONE 255

#define EI_NIDENT     16

#define R_X86_64_NONE          0
#define R_X86_64_64            1
#define R_X86_64_PC32          2
#define R_X86_64_GOT32         3
#define R_X86_64_PLT32         4
#define R_X86_64_COPY          5
#define R_X86_64_GLOB_DAT      6
#define R_X86_64_JUMP_SLOT     7
#define R_X86_64_RELATIVE      8
#define R_X86_64_GOTPCREL      9
#define R_X86_64_32           10
#define R_X86_64_32S          11
#define R_X86_64_16           12
#define R_X86_64_PC16         13
#define R_X86_64_8            14
#define R_X86_64_PC8          15
#define R_X86_64_DTPMOD64     16
#define R_X86_64_DTPOFF64     17
#define R_X86_64_TPOFF64      18
#define R_X86_64_TLSGD        19
#define R_X86_64_TLSLD        20
#define R_X86_64_DTPOFF32     21
#define R_X86_64_GOTTPOFF     22
#define R_X86_64_TPOFF32      23
#define R_X86_64_PC64         24
#define R_X86_64_GOTOFF64     25
#define R_X86_64_GOTPC32      26
#define R_X86_64_GOT64        27
#define R_X86_64_GOTPCREL64   28
#define R_X86_64_GOTPC64      29
#define R_X86_64_GOTPLT64     30
#define R_X86_64_PLTOFF64     31
#define R_X86_64_SIZE32       32
#define R_X86_64_SIZE64       33
#define R_X86_64_GOTPC32_TLSDESC 34
#define R_X86_64_TLSDESC_CALL 35
#define R_X86_64_TLSDESC      36
#define R_X86_64_IRELATIVE    37
#define R_X86_64_RELATIVE64   38
#define R_X86_64_PC32_BND     39
#define R_X86_64_PLT32_BND    40

#endif /* X86_64_ELF_H */
