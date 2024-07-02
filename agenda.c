#include <stdio.h>
#include <stdlib.h>
#include "contatos.h"

void ver(void);
void adicionar(void);
void remover(void);

int main(void){
	int opt;
	int off = 0; 

	do{
	printf("---------- CONTATO ----------\n\n[1]Ver Contatos.\n[2]Adicionar.\n[3]Remover.\n[4]Sair.\n\nSelecione:  ");
	scanf("%i", &opt);
	system("cls");
	printf("\n");
	
	switch(opt){
		case 1:
			ver();
		break;
		case 2:
			system("cls");
			adicionar();
		break;
		case 3:
			system("cls");	
			remover();
		break;
		case 4:
			off = 1;
		break;
		default:
			printf("\nINVALIDO - Selecione novamente.\n\n");
	}
	}while(off != 1);
	return 0;
}

void ver(void){
	Contato contato;
	
	FILE *arquivo;
    arquivo = fopen("contatos.bin", "rb");
    if (arquivo == NULL)
    {
        printf("\n---\nNenhum Contato foi registrado!\n---\n\n");
        return 1;
    }

    while (fread(&contato, sizeof(Contato), 1, arquivo)) {
        printf("Nome: %s\n", contato.nome);
        printf("Telefone: %d\n\n", contato.numero);
    }
    fclose(arquivo);	
}

void adicionar(){
	Contato contato;
    
    FILE *arquivo;
    arquivo = fopen("contatos.bin", "ab");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
	
	printf("\n----- ADICIONAR CONTATO -----\n\nNome:");
	    scanf(" %[^\n]", contato.nome);
    printf("Telefone: ");
    scanf("%i", &contato.numero);
    fwrite(&contato, sizeof(Contato), 1, arquivo);
    fclose(arquivo);
	
}

void remover() {
    char nomeRemover[50];
    int encontrado = 0;

    printf("Digite o nome do contato para remover: ");
    scanf(" %[^\n]", nomeRemover);
    FILE *arquivo;
    arquivo = fopen("contatos.bin", "rb+");
    FILE *temp;
    temp = fopen("temp.bin", "wb");
    
    Contato contato;

    while (fread(&contato, sizeof(Contato), 1, arquivo)) {
        if (strcmp(contato.nome, nomeRemover) == 0) {
            encontrado = 1;
            printf("Contato removido: %s\n", contato.nome);
        } else {
            fwrite(&contato, sizeof(Contato), 1, temp);
        }
    }

    fclose(arquivo);
    fclose(temp);
remove("contatos.bin");
    rename("temp.bin", "contatos.bin");
    if (!encontrado) {
        printf("Não existe '%s' .\n", nomeRemover);
    }
}

