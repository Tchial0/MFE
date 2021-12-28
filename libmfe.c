/* 
 * Manix File Encryptor (MFE)
 * Ficheiro: libmfe.c
 * Descricão: biblioteca do MFE
 */

#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "mfe.h"

/* Verifica a existência de um ficheiro */
int fexists(const char * fname){
	int fd = open(fname,O_RDONLY);
	close(fd);
	return (fd > 0);
}

/* Retorna o tamanho de um ficheiro */
fsize_t fbytes(const char * name){
    FILE * fp = fopen(name,"rb");
    if(fp == NULL) return 0;
	fsize_t size = 0;
	while(getc(fp) != EOF){
		size++;
	}
	fclose(fp);
	return size;
}

/* Retorna o nome de um ficheiro sem seu caminho completo */
char * ffname(const char * name) {
	char * new_name = (char *) calloc(strlen(name),sizeof(char));
	strcpy(new_name,name);
	char * ptr = strrchr(new_name,'\\');
	if(ptr == NULL) return new_name;
	return (ptr+1);
}

/* Verifica se um ficheiro está encriptado */
int is_mfe_file(const char * name) {
	fsize_t size = fbytes(name);
	if(size < sizeof(mfe_header)) return 0;
	mfe_header infs;
	FILE * fp = fopen(name,"rb");
	fread(&infs,sizeof(mfe_header),1,fp);
	fclose(fp);
    return ((infs.mfe_file == MFE_FILE) && (infs.encrypted_file == MFE_ENCRYPTED_FILE));
}

/* Retorna o cabeçalho de um ficheiro encriptado */
mfe_header * mfe_inf(const char * fname){
	if(!is_mfe_file(fname)) return NULL;
	
	mfe_header *  infs = (mfe_header *) malloc(sizeof(mfe_header));
	FILE * fp = fopen(fname,"rb");
	fread(infs,sizeof(mfe_header),1,fp);
	fclose(fp);
    return infs;
}

/* Encripta um ficheiro */
int encrypt_file(const char * fname) {
    fsize_t fsize = fbytes(fname);
    FILE * fori = fopen(fname,"rb");
	char enc_name[MFE_MAX_FILE_NAME];
    strcpy(enc_name,ffname(fname));
    strcat(enc_name,".mfe");
    
    FILE * fenc = fopen(enc_name,"wb");
    
    if(fori == NULL || fsize < 1 || fenc == NULL) return 0;

    int ch,i;
    i = 0;
    
    mfe_header infs;
    infs.mfe_file = MFE_FILE;
    infs.encrypted_file = MFE_ENCRYPTED_FILE;
    infs.enc_time = time(0);
    strcpy(infs.fname,ffname(fname));
    infs.fsize = fsize;
     
    fwrite(&infs,sizeof(mfe_header),1,fenc);
    
    while((ch = getc(fori)) != EOF){
		putc(~ch,fenc);
    }
    
    fclose(fori);
    fclose(fenc);
    
    return 1;
	
}

/* Desencripta um ficheiro */
int decrypt_file(const char * fname) {
	
	fsize_t fsize = fbytes(fname);

	FILE * fenc = fopen(fname,"rb");
    mfe_header infs;
    fread(&infs,sizeof(mfe_header),1,fenc);
    FILE * fdec = fopen(infs.fname,"wb");
    
    if(fenc == NULL || fsize < 0 || fdec == NULL) return 0;
    
    int ch,i;
    i = 0;
    
    while((ch = getc(fenc)) != EOF){
    	putc(~ch,fdec);
    }

    fclose(fenc);
    fclose(fdec);
	return 1;    
    
}
	
