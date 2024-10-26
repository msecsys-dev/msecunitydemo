//
// Created by nhchung on 23/03/2023.
//
#ifndef UTILS_H
#define UTILS_H
#define MAX_LINE 512
#define MAX_LENGTH 256

enum arch_type{
    ARCH_X86 = 0,
    ARCH_X86_64 =1,
    ARCH_ARM32 =2,
    ARCH_ARM64 =3
};
#define MAX_FILENAME_LENGTH 1024

ssize_t read_one_line(int fd, char *buf, unsigned int max_len);
size_t atfd_strlcpy(char *dst, const char *src, size_t siz);
size_t atfd_strlen(const char *s);
int atfd_strncmp(const char *s1, const char *s2, size_t n);
char * atfd_strstr(const char *s, const char *find);
void *atfd_memset(void *dst, int c, size_t n);
int atfd_strcmp(const char *s1, const char *s2);
int atfd_atoi(const char *s);
ssize_t read_one_line(int fd, char *buf, unsigned int max_len);
//void bytearray_to_str(uint8_t* input, int length, char* output);
//void print_bytearray(uint8_t* input, int length);
void get_certificate_info(const char* domain);


// hashes funcs
int str_hcs_hash(char *s);
int mem_hcs_hash(char *mem, int len);
int shiftLeft(char a, int count);

// maps related funcs
void dump_region(int fd, uintptr_t start, uintptr_t end, char* mem);

////cpu related funcs
//const char* get_cpu_info_str();
//
////zmq test funcs
//void zmqtest_print_version();
#endif //UTILS_H
