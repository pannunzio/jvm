//
//  main.c
//  Java Virtual Machine - Software Basico 2017-1
//
//  Created on 26/05/17.
//  Copyright © 2017 GrupoSB. All rights reserved.
//
//  Allisson Barros         12/0055619
//  Daniel Luz              13/0007714
//  Luiz Fernando Vieira    13/0013757
//  Mariana Pannunzio       12/0018276
//  Mateus Denucci          12/0053080

#include "carregador.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

AreaMetodos areaMetodos;

int primeira = FALSE;
//
void carregaMemClass(char* nomeClass) {
  if(!isClasseCarregada(nomeClass)) {
    areaMetodos.numClasses++;
    ClassFile** arrayClassesAux = NULL;
    arrayClassesAux = (ClassFile**) realloc(areaMetodos.arrayClasses, (areaMetodos.numClasses*sizeof(ClassFile*)));
    areaMetodos.arrayClasses = (ClassFile**) calloc(1, sizeof(ClassFile*));
    areaMetodos.arrayClasses = arrayClassesAux;
    carregaClasse(nomeClass);
  }
}

int isClasseCarregada(char* nomeClass) {
  if (primeira == FALSE) {
      areaMetodos.numClasses = 0;
      primeira = TRUE;
  }

	for (int i = 0; i < areaMetodos.numClasses; i++) {
		if (strcmp(nomeClass, retornaNomeClass(areaMetodos.arrayClasses[i])) == 0) {
			return TRUE;
		}
	}

  return FALSE;
}

void carregaClasse(char* nomeClass) {
  char* destino = malloc(strlen(nomeClass) + 10);

  if (strstr(nomeClass,".class") != NULL) {
    sprintf(destino, "%s", nomeClass);
  } else {
    sprintf(destino, "./%s.class",nomeClass);
  }

  areaMetodos.arrayClasses[areaMetodos.numClasses - 1] = inicializaLeitor(destino);

  if(areaMetodos.arrayClasses[areaMetodos.numClasses -1] == NULL){
    printf("Erro ao carregar classe!\n");
    exit(0);
  }
}

char* retornaNomeClass(ClassFile* classe){
	uint16_t thisClass = classe->thisClass;
	uint16_t nameIndex = (classe->constantPool[thisClass - 1]).info.Class.nameIndex;
	uint16_t indice = classe->constantPool[nameIndex - 1].info.Utf8.length;
	char* retorno = (char*) malloc(indice + 1);

  int i;
	for (i = 0; i < indice; i++) {
		retorno[i] = (char) (classe->constantPool[nameIndex - 1]).info.Utf8.bytes[i];
	}

	retorno[i] = '\0';
	return retorno;
}

ClassFile* buscaClassPorIndice(int indice) {
	return indice >= areaMetodos.numClasses ? NULL : areaMetodos.arrayClasses[indice];
}

char* retornaNome(ClassFile* cf, uint16_t indiceNome) {
	int i;

	char* retorno = malloc((cf->constantPool[indiceNome - 1]).info.Utf8.length + 1);
	uint16_t indice = cf->constantPool[indiceNome - 1].info.Utf8.length;

	for (i = 0; i < indice; i++) {
		retorno[i] = (char) (cf->constantPool[indiceNome - 1]).info.Utf8.bytes[i];
	}

	retorno[i] = '\0';

	return retorno;
}
