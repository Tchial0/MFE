/* 
 * Manix File Encryptor (MFE)
 * Ficheiro: main.c
 * Description: main file
 */

#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<limits.h>
#include "mfe.h"


int main(int argc, char * argv[]){

	printf("MFE [Version 1.0]\n\n");

	if(argc < 3) {
		fprintf(stderr,"\nError: only 2 arguments are allowed!\n\n");
		return 1;
	}
	
	char const * const file_name = argv[1];
	if(!fexists(file_name)){
		fprintf(stderr,"\nError: the file %s doesn't exist!\n\n",file_name);
		return 1;
	}
	fsize_t file_size =  fbytes(file_name);
	if(file_size > MFE_MAX_FILE_SIZE) {
		fprintf(stderr,"\nError: The file %s is so large!\n\n",file_name);
		return 0;
	} else if(file_size == 0){
		fprintf(stderr,"\nError: The file %s is empty!\n\n",file_name);
		return 0;
	}
	
	char const * const action = argv[2];
	
	if(!strcmp(action,"enc")){
		printf("\n--- File Encryption (%s) --- \n",file_name);
		if(is_mfe_file(file_name)) {
			fprintf(stderr,"\nError: The file %s is already encrypted!\n\n",file_name);
			return 1;
		}
		
		if(encrypt_file(file_name)){
			printf("\nEncrypted file: %s.mfe\n\n",ffname(file_name));
		} else {
			fprintf(stderr,"\nError: encryption failed.\n\n");
			return 1;
		}
	} else if(!strcmp(action,"dec")){
		printf("\n--- File Decryption (%s) --- \n",file_name);
		if(!is_mfe_file(file_name)) {
			fprintf(stderr,"\nError: The file %s is not encrypted!\n\n",file_name);
			return 1;
		}
		
		if(decrypt_file(file_name)){
			printf("\nFile decrypted!\n\n");
		} else {
			fprintf(stderr,"\nError: failed to decrypt file!\n\n");
			return 1;
		}
	}  else if(!strcmp(action,"inf")){
		printf("\n--- File Informations (%s) --- \n",file_name);
		if(!is_mfe_file(file_name)) {
			fprintf(stderr,"\nError: The file %s is not encrypted!\n\n",file_name);
			return 1;
		}
		
		mfe_header * infs = mfe_inf(file_name);
		printf("\nOriginal Size: %ld\n",infs->fsize);
		printf("\nOriginal Name: %s\n",infs->fname);
		printf("\nEncryption Date: %s\n\n",ctime(&(infs->enc_time)));
		
	} else {
		fprintf(stderr,"\nError: invalid argument (%s)\n",action);
		return 1;
	}
	printf("\n");
	system("pause");
	printf("\n");
	return 0;
}
