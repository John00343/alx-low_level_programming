#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void check_elf(unsigned char *e_ident);
void print_header_info(Elf64_Ehdr *header);

void check_elf(unsigned char *e_ident)
{
    if (e_ident[EI_MAG0] != ELFMAG0 || e_ident[EI_MAG1] != ELFMAG1 ||
        e_ident[EI_MAG2] != ELFMAG2 || e_ident[EI_MAG3] != ELFMAG3) {
        dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
        exit(98);
    }
}

void print_header_info(Elf64_Ehdr *header)
{
    printf("ELF Header:\n");
    printf(" Magic: ");
    for (int i = 0; i < EI_NIDENT; i++) {
        printf("%02x%s", header->e_ident[i], (i == EI_NIDENT - 1) ? "\n" : " ");
    }

    printf(" Class: %d\n", header->e_ident[EI_CLASS]);
    printf(" Data: %d\n", header->e_ident[EI_DATA]);
    printf(" Version: %d (current)\n", header->e_ident[EI_VERSION]);
    printf(" OS/ABI: %d\n", header->e_ident[EI_OSABI]);
    printf(" ABI Version: %d\n", header->e_ident[EI_ABIVERSION]);

    printf(" Type: %d\n", header->e_type);

    if (header->e_ident[EI_CLASS] == ELFCLASS32)
        printf(" Entry point address: %#x\n", (unsigned int)header->e_entry);
    else
        printf(" Entry point address: %#lx\n", header->e_entry);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        dprintf(STDERR_FILENO, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    Elf64_Ehdr header;
    ssize_t bytes_read = read(fd, &header, sizeof(Elf64_Ehdr));
    if (bytes_read != sizeof(Elf64_Ehdr)) {
        perror("Error reading file");
        close(fd);
        return 1;
    }

    check_elf(header.e_ident);
    print_header_info(&header);

    close(fd);
    return 0;
}
