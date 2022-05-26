/* 
 * Manix File Encryptor (MFE)
 * File: mfe.h
 * Description: contains necessary constants and declarations of the finctions from de libmfe.c
 */
 
#define MFE_FILE 222019
#define MFE_ENCRYPTED_FILE 24122001
#define MFE_MAX_FILE_NAME 100
#define MFE_MAX_FILE_SIZE 1000000000

typedef unsigned long long fsize_t;

typedef struct {
	unsigned int mfe_file;
	unsigned int encrypted_file;
	time_t enc_time; 
	char fname[MFE_MAX_FILE_NAME];
	fsize_t fsize;
} mfe_header;


int fexists(const char * file_name);

fsize_t fbytes(const char * file_name);

char * ffname(const char * file_name);

int is_mfe_file(const char * file_name);

int encrypt_file(const char * file_name);

int decrypt_file(const char * file_name);

mfe_header * mfe_inf(const char * file_name);
