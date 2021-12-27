/* 
 * Manix File Encryptor (MFE)
 * ficheiro: main.c
 * Descrição: ficheiro principal do projecto
 */

#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<limits.h>
#include<locale.h>
#include "mfe.h"


int main(int argc, char * argv[]){
        setlocale(LC_ALL,"Portuguese");
	
	if(argc < 3) {
		fprintf(stderr,"\nErro: apenas 2 argumentos são necessários!\n\n");
		return 1;
	}
	
	char const * const file_name = argv[1];
	if(!fexists(file_name)){
		fprintf(stderr,"\nErro: O ficheiro %s não existe!\n\n",file_name);
		return 1;
	}
	fsize_t file_size =  fbytes(file_name);
	if(file_size > MFE_MAX_FILE_SIZE) {
		fprintf(stderr,"\nErro: O ficheiro %s é muito pesado!\n\n",file_name);
		return 0;
	} else if(file_size == 0){
		fprintf(stderr,"\nErro: O ficheiro %s está vazio!\n\n",file_name);
		return 0;
	}
	
	char const * const action = argv[2];
	
	if(!strcmp(action,"enc")){
		printf("\n--- Encriptação de ficheiro (%s) --- \n",file_name);
		if(is_mfe_file(file_name)) {
			fprintf(stderr,"\nErro: O ficheiro %s já está encriptado!\n\n",file_name);
			return 1;
		}
		
		if(encrypt_file(file_name)){
			printf("\nVersão encriptada: %s.mfe\n\n",ffname(file_name));
		} else {
			fprintf(stderr,"\nErro: Falha ao encriptar o ficheiro\n\n");
			return 1;
		}
	} else if(!strcmp(action,"dec")){
		printf("\n--- Desencriptação de ficheiro (%s) --- \n",file_name);
		if(!is_mfe_file(file_name)) {
			fprintf(stderr,"\nErro: O ficheiro %s não está encriptado!\n\n",file_name);
			return 1;
		}
		
		if(decrypt_file(file_name)){
			printf("\nFicheiro desencriptado!\n\n");
		} else {
			fprintf(stderr,"\nErro: Falha ao desencriptar!\n\n");
			return 1;
		}
	}  else if(!strcmp(action,"inf")){
		printf("\n--- Informações do ficheiro (%s) --- \n",file_name);
		if(!is_mfe_file(file_name)) {
			fprintf(stderr,"\nErro: O ficheiro %s não está encriptado!\n\n",file_name);
			return 1;
		}
		
		mfe_header * infs = mfe_inf(file_name);
		printf("\nTamanho original: %ld\n",infs->fsize);
		printf("\nNome original: %s\n",infs->fname);
		printf("\nDara de encriptação: %s\n\n",ctime(&(infs->enc_time)));
		
	} else {
		fprintf(stderr,"\nErro: Argumento inválido (%s)\n",action);
		return 1;
	}
	printf("\n");
	system("pause");
	printf("\n");
	return 0;
}
