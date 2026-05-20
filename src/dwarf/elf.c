#include <elf.h>

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

void print_elf64_header(Elf64_Ehdr *header) {
  char *format = 
    "Elf64_Ehdr {\n"
    "  e_ident:      %s\n"
    "  e_type:       %"PRIu16"\n"
    "  e_machine:    %"PRIu16"\n"
    "  e_version:    %"PRIu32"\n"
    "  e_entry:      %"PRIu64"\n"
    "  e_phoff:      %"PRIu64"\n"
    "  e_shoff:      %"PRIu64"\n"
    "  e_flags:      %"PRIu32"\n"
    "  e_ehsize:     %"PRIu16"\n"
    "  e_phentsize:  %"PRIu16"\n"
    "  e_phnum:      %"PRIu16"\n"
    "  e_shentsize:  %"PRIu16"\n"
    "  e_shnum:      %"PRIu16"\n"
    "  e_shstrndx:   %"PRIu16"\n"
    "}\n";

  printf(
    format,
    header->e_ident,
    header->e_type,
    header->e_machine,
    header->e_version,
    header->e_entry,
    header->e_phoff,
    header->e_shoff,
    header->e_flags,
    header->e_ehsize,
    header->e_phentsize,
    header->e_phnum,
    header->e_shentsize,
    header->e_shnum,
    header->e_shstrndx
  );
}

void print_elf64_section_header(Elf64_Shdr *header) {
  char *format = 
    "Elf64_Shdr {\n"
    "  sh_name:      %"PRIu32"\n"
    "  sh_type:      %"PRIu32"\n"
    "  sh_flags:     %"PRIu64"\n"
    "  sh_addr:      %"PRIu64"\n"
    "  sh_offset:    %"PRIu64"\n"
    "  sh_size:      %"PRIu64"\n"
    "  sh_link:      %"PRIu32"\n"
    "  sh_info:      %"PRIu32"\n"
    "  sh_addralign: %"PRIu64"\n"
    "  sh_entsize:   %"PRIu64"\n"
    "}\n";

  printf(format,
    header->sh_name,
    header->sh_type,
    header->sh_flags,
    header->sh_addr,
    header->sh_offset,
    header->sh_size,
    header->sh_link,
    header->sh_info,
    header->sh_addralign,
    header->sh_entsize
  );
}

void parse_elf(FILE *file) {
  printf("fd: %p\n", file);
  
  Elf64_Ehdr header;
  fread(&header, sizeof(header), 1, file);
  print_elf64_header(&header);

  int ret = fseek(file, header.e_shoff, SEEK_SET);
  if (ret != 0) { exit(1); }
  printf("Set file cursor to: %"PRIu64"\n", header.e_shoff);
  
  Elf64_Shdr section_header;
  fread(&header, sizeof(section_header), 1, file);
  print_elf64_section_header(&section_header);
}