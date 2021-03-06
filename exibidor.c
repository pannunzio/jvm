///
///  @file exibidor.c
///  @headerfile exibidor.h "exibidor.h"
///
///  @authors
///  Allisson Barros         12/0055619\n
///  Daniel Luz              13/0007714\n
///  Luiz Fernando Vieira    13/0013757\n
///  Mariana Pannunzio       12/0018276\n
///  Mateus Denucci          12/0053080\n
///
///  @date 28/06/2017
///
///  @copyright Copyright © 2017 GrupoSB. All rights reserved.
///
///  @brief Arquivo que exibe na tela uma estrutura ClassFile
///  imprimindo todos os dados armazenados.
///
///  Recebe um ponteiro para uma estrutura ClassFile, imprime
///  cada parte de acordo com seu formato e suas subestruturas,
///  isso tudo com uma interface semelhante ao programa
///  "jclasslib bytecode viewer".
///

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "exibidor.h"

///
/// Funcao principal que imprime as informacoes gerais
/// e coordena as chamadas das funcoes que imprimem
/// as demais estuturas do classfile
///
/// @param ClassFile* Ponteiro para a estrutura Classfile
/// @return @c void
/// @see printaCpInfo printaInterfaces printaFieldInfo printaMethodInfo printaAttributeInfo
/// @see imprimeStringPool printTopo printBase printBlank
void printaClassFile(ClassFile* classFile) {

    // GENERAL INFORMATION
    printTopo();
    printBlank();
    printf("\t*\t\tGENERAL INFORMATION\t\t*\n");
    printBlank();
    printBase();
    printf("\t\tMagic:                 0x%08X\n", classFile->magic);
    printf("\t\tMinor Version:         %d\n", classFile->minorVersion);
    printf("\t\tMajor Version:         %d\n", classFile->majorVersion);
    printf("\t\tConstant Pool Count:   %d\n", classFile->constantPoolCount);
    printf("\t\tAccess Flags:          0x%04X\n", classFile->accessFlags);
    printf("\t\tThis Class:            ");
    imprimeStringPool(classFile->constantPool, classFile->thisClass-1);
    printf("\n");
    printf("\t\tSuper Class:           ");
    imprimeStringPool(classFile->constantPool, classFile->superClass-1);
    printf("\n");
    printf("\t\tInterfaces Count:      %d\n", classFile->interfacesCount);
    printf("\t\tFields Countd:         %d\n", classFile->fieldsCount);
    printf("\t\tMethods Count:         %d\n", classFile->methodsCount);
    printf("\t\tAttributes Count:      %d\n", classFile->attributesCount);

    // CONSTANT POOL
    printTopo();
    printBlank();
    printf("\t*\t\t   CONSTANT POOL   \t\t*\n");
    printBlank();
    printBase();
    printaCpInfo(classFile);

    // INTERFACES
    printTopo();
    printBlank();
    printf("\t*\t\t    INTERFACES     \t\t*\n");
    printBlank();
    printBase();
    printf("\n");
    printaInterfaces(classFile);

    // FIELD INFO
    printTopo();
    printBlank();
    printf("\t*\t\t    FIELD INFO     \t\t*\n");
    printBlank();
    printBase();
    printf("\n");
    printaFieldInfo(classFile);

    // METHOD INFO
    printTopo();
    printBlank();
    printf("\t*\t\t   METHOD INFO     \t\t*\n");
    printBlank();
    printBase();
    printaMethodInfo(classFile);

    // ATTRIBUTE INFO
    printTopo();
    printBlank();
    printf("\t*\t\t  ATTRIBUTE INFO   \t\t*\n");
    printBlank();
    printBase();
    printf("\n");
    printaAttributeInfo(classFile);
    printf("\n");
}

///
/// Funcao que imprime o Constant Pool, buscando os
/// valores UTF8 finais de cada constatnte e imprimindo
/// tambem suas referencias
///
/// @param ClassFile* Ponteiro para a estrutura Classfile
/// @return @c void
/// @see imprimeStringPool hexToDouble hexToLong
void printaCpInfo(ClassFile* classFile) {
    double valorDouble;
    float valorFloat;
    long valorLong;

    for (int i = 0; i < classFile->constantPoolCount-1; ++i) {

        switch (classFile->constantPool[i].tag) {
            case CONSTANT_Class:
                printf("\t[%d] CONSTANT_Class_Info:   cp_info_#%d  ",i+1, classFile->constantPool[i].info.Class.nameIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.Class.nameIndex -1);
                printf("\n");
                break;
            case CONSTANT_Fieldref:
                printf("\t[%d] CONSTANT_Fieldref_Info", i+1);
                printf("\n");
                printf("\t\tClassIndex:        cp_info_#%d  ", classFile->constantPool[i].info.Fieldref.classIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.Fieldref.classIndex-1);
                printf("\n");
                printf("\t\tNameAndTypeIndex:  cp_info_#%d  ", classFile->constantPool[i].info.Fieldref.nameAndTypeIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.Fieldref.nameAndTypeIndex-1);
                printf("\n");
                break;

            case CONSTANT_NameAndType:
                printf("\t[%d] CONSTANT_NameAndType_Info", i+1);
                printf("\n");
                printf("\t\tNameIndex:          cp_info_#%d  ", classFile->constantPool[i].info.NameAndType.nameIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.NameAndType.nameIndex-1);
                printf("\n");
                printf("\t\tDescriptorIndex:    cp_info_#%d  ", classFile->constantPool[i].info.NameAndType.descriptorIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.NameAndType.descriptorIndex-1);
                printf("\n");
                break;
            case CONSTANT_Utf8:
                printf("\t[%d] CONSTANT_Utf8_Info", i+1);
                printf("\n");
                printf("\t\tLength: %d", classFile->constantPool[i].info.Utf8.length);
                printf("\n");
                printf("\t\tBytes:  %s", classFile->constantPool[i].info.Utf8.bytes);
                printf("\n");
                break;
            case CONSTANT_Methodref:
                printf("\t[%d] CONSTANT_Methodref_Info",i+1);
                printf("\n");
                printf("\t\tClassIndex:        cp_info_#%d  ", classFile->constantPool[i].info.Methodref.classIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.Methodref.classIndex -1);
                printf("\n");
                printf("\t\tNameAndTypeIndex:  cp_info_#%d  ", classFile->constantPool[i].info.Methodref.nameAndTypeIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.Methodref.nameAndTypeIndex -1);
                printf("\n");
                break;
            case CONSTANT_InterfaceMethodref:
                printf("\t[%d] CONSTANT_InterfaceMethodref_Info",i+1);
                printf("\n");
                printf("\t\tClassIndex:        cp_info_#%d  ",classFile->constantPool[i].info.InterfaceMethodref.classIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.InterfaceMethodref.classIndex -1);
                printf("\n");
                printf("\t\tNameAndTypeIndex:  cp_info_#%d  %u",i+1, classFile->constantPool[i].info.InterfaceMethodref.nameAndTypeIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.InterfaceMethodref.nameAndTypeIndex -1);
                printf("\n");
                break;
            case CONSTANT_String:
                printf("\t[%d] CONSTANT_String_Info", i+1);
                printf("\n");
                printf("\t\tStringIndex:       cp_info_#%d  ", classFile->constantPool[i].info.String.stringIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.String.stringIndex -1);
                printf("\n");
                break;
            case CONSTANT_Integer:
                printf("\t[%d] CONSTANT_Integer_Info", i+1);
                printf("\n");
                printf("\t\tValor: %u", classFile->constantPool[i].info.Integer.bytes);
                printf("\n");
                break;
            case CONSTANT_Float:
                memcpy(&valorFloat, &classFile->constantPool[i].info.Float.bytes, sizeof(int32_t));
                printf("\t[%d] CONSTANT_Float_Info", i+1);
                printf("\n");
                printf("\t\tValor: %0.2f", valorFloat);
                printf("\n");
                break;
            case CONSTANT_Double:
                printf("\t[%d] CONSTANT_Double_Info", i+1);
                printf("\n");
                printf("\t\tHighBytes: 0x%08X", classFile->constantPool[i].info.Double.highBytes);
                printf("\n");
                printf("\t\tLowBytes: 0x%08X", classFile->constantPool[i].info.Double.lowBytes);
                printf("\n");
                valorDouble = hexToDouble(classFile->constantPool[i].info.Double.highBytes, classFile->constantPool[i].info.Double.lowBytes);
                printf("\t\tDouble: %.4g", valorDouble);
                printf("\n");
                printf("\t[%d] (large numeric continued)", i+2);
                printf("\n");
                i++;
                break;
            case CONSTANT_Long:
                printf("\t[%d] CONSTANT_Long_Info", i+1);
                printf("\n");
                printf("\tHighBytes: 0x%08X", classFile->constantPool[i].info.Long.highBytes);
                printf("\n");
                printf("\tLowBytes: 0x%08X", classFile->constantPool[i].info.Long.lowBytes);
                printf("\n");
                valorLong = hexToLong(classFile->constantPool[i].info.Long.highBytes, classFile->constantPool[i].info.Long.lowBytes);
                printf("\tLong: %ld", valorLong);
                printf("\n");
                printf("\t[%d] (large numeric continued)", i+2);
                printf("\n");
                i++;
                break;
            default:
                break;
        }
    }
}

///
/// Funcao que imprime Interfaces da classe passada
/// parametro, alem das referencias das constantes
/// que contem as informacoes UTF8 de cada Interface 
///
/// @param ClassFile* Ponteiro para a estrutura Classfile
/// @return @c void
/// @see imprimeStringPool
void printaInterfaces(ClassFile* classFile) {
    if (classFile->interfacesCount) {
        for (int i = 0; i < classFile->interfacesCount; ++i) {

            int index = classFile->constantPool[classFile->interfaces[i]-1].info.Class.nameIndex;

            printf("\tInterface %d:   cp_info_#%d   %d", i, classFile->interfaces[i], index);
            imprimeStringPool(classFile->constantPool, classFile->interfaces[i]-1);
            printf("\n");
        }
    } else {
        printf("\t     !! Esse classe nao possui Interfaces !!");
        printf("\n");
    }
}

///
/// Funcao que imprime as informacoes de Fields da classe,
/// bem como suas referencias no Constant Pool.
///
/// @param ClassFile* Ponteiro para a estrutura Classfile
/// @return @c void
/// @see imprimeStringPool printAccessFlag printSingleLine
void printaFieldInfo(ClassFile* classFile) {

    if(classFile->fieldsCount != 0) {
        for (int i = 0; i < classFile->fieldsCount; i++) {

            printf("\tName:           cp_info_#%d   ", classFile->fields[i].nameIndex);
            imprimeStringPool(classFile->constantPool, classFile->fields[i].nameIndex - 1);
            printf("\n");
            printf("\tDescriptor:     cp_info_#%d   ", classFile->fields[i].descriptorIndex);
            imprimeStringPool(classFile->constantPool, classFile->fields[i].descriptorIndex - 1);
            printf("\n");
            printf("\tAccess Flag:    0x%04X        ", classFile->fields[i].accessFlags);
            printAccessFlag(classFile->fields[i].accessFlags);
            printf("\tNumero de Atributos:  %d", classFile->fields[i].attributesCount);
            printf("\n\n");

            for (int j = 0; j < classFile->fields[i].attributesCount; j++) {

                printf("\tGeneric Info -");
                printSingleLine();
                printf("\n");
                printf("\t\tattribute_name_index:   cp_info_#%d  ", classFile->fields[i].attributes->attributeNameIndex);
                imprimeStringPool(classFile->constantPool, classFile->fields[i].attributes->attributeNameIndex - 1);
                printf("\n");
                printf("\t\tattribute_length:       %u\n", classFile->fields[i].attributes->attributeLength);
                printf("\n");
                printf("\tSpecific Info ");
                printSingleLine();
                printf("\n");
                printf("\t\tconstant_value_index:   cp_info_#%d  ", classFile->fields[i].attributes->constantValueIndex);
                imprimeStringPool(classFile->constantPool, classFile->fields[i].attributes->constantValueIndex - 1);
                printf("\n\n\n");
            }
        }
    } else {
        printf("\t      !! Essa classe nao possui Campos !!");
    }
}

///
/// Funcao que imprime as informacoes dos Metodos da classe,
/// suas instrucoes (mnemonicos) e suas referencias no Constant Pool.
///
/// @param ClassFile* Ponteiro para a estrutura Classfile
/// @return @c void
/// @see imprimeStringPool imprimeCode imprimeExc
void printaMethodInfo(ClassFile* classFile) {
    uint16_t methodsCount = classFile->methodsCount;
    printf("\tMethods Count: %d\n", methodsCount);

    if(methodsCount == 0)
        return;
    else{
        MethodInfo* cp = classFile->methods;
        for(int i = 0; i < methodsCount; cp++){

            printf("\tname_index:        cp_info_#%d   ",cp->nameIndex);
            imprimeStringPool(classFile->constantPool, cp->nameIndex - 1);
            printf("\n");
            printf("\tdescriptor_index:  cp_info_#%d   ",cp->descriptorIndex);
            imprimeStringPool(classFile->constantPool, cp->descriptorIndex - 1);
            printf("\n");
            printf("\taccess_flag:       0x%0x   ",cp->accessFlags);
            printAccessFlag(cp->accessFlags);
            printf("\tattributes_count:   %04X\n",cp->attributesCount);

            imprimeCode(classFile, cp->cdAtrb);

            if (cp->attributesCount == 2) {
                imprimeExc(classFile, cp->excAtrb);
            }
            i++;
        }
    }
}

///
/// Funcao que imprime as informacoes dos Atributos da classe,
/// bem como suas referencias no Constant Pool.
///
/// @param ClassFile* Ponteiro para a estrutura Classfile
/// @return @c void
/// @see imprimeStringPool printSingleLine
void printaAttributeInfo(ClassFile* classFile) {

    if (classFile->attributesCount) {

        AttributeInfo* attrInfo = classFile->attributes;

        for(int i = 0; i < classFile->attributesCount; attrInfo++){
            printf("\tGeneric Info %c", 196);
            printSingleLine();
            printf("\n\n");
            printf("\tAttribute name index:  cp_info_#%d  ", attrInfo->attributeNameIndex);
            imprimeStringPool(classFile->constantPool, attrInfo->attributeNameIndex-1);
            printf("\n");
            printf("\tAttribute length:  %u", attrInfo->attributeLength);
            printf("\n\n\n");
            printf("\tSpecific Info ");
            printSingleLine();
            printf("\n\n");
            for(uint32_t j = 0; j < attrInfo->attributeLength; attrInfo->info++){
                if(*(attrInfo->info)){
                    printf("\tSource file name index:  cp_info_#%d  ",*(attrInfo->info));
                    imprimeStringPool(classFile->constantPool, *(attrInfo->info) - 1);
                    printf("\n");
                }
                j++;
            }
            i++;
            printf("\n\n");
        }
    } else {
        printf("\t     !! Essa classe nao possui Atributos !!");
        printf("\n\n");
    }
}

///
/// Funcao que imprime na tela o UTF8 final de uma constante
/// a partir de sua posicao. O UTF8 eh encontrado recursivamente.
///
/// @param ClassFile* Ponteiro para a estrutura Classfile
/// @param int Posicao da costante que sera impressa
/// @return @c void
void imprimeStringPool(CpInfo* cp, int pos) {
    int tag;

    tag = cp[pos].tag;

    if (tag == CONSTANT_Utf8) {
        printf("%s", cp[pos].info.Utf8.bytes);
        return;
    }

    switch(tag) {
        case CONSTANT_Class:
            imprimeStringPool(cp, cp[pos].info.Class.nameIndex - 1);
            break;

        case CONSTANT_Fieldref:
            imprimeStringPool(cp, cp[pos].info.Fieldref.classIndex - 1);
            imprimeStringPool(cp, cp[pos].info.Fieldref.nameAndTypeIndex - 1);
            break;

        case CONSTANT_NameAndType:
            imprimeStringPool(cp, cp[pos].info.NameAndType.nameIndex - 1 );
            imprimeStringPool(cp, cp[pos].info.NameAndType.descriptorIndex - 1);
            break;

        case CONSTANT_Methodref:
            imprimeStringPool(cp, cp[pos].info.Methodref.classIndex - 1);
            imprimeStringPool(cp, cp[pos].info.Methodref.nameAndTypeIndex - 1);
            break;

        case CONSTANT_InterfaceMethodref:
            imprimeStringPool(cp, cp[pos].info.InterfaceMethodref.classIndex - 1);
            imprimeStringPool(cp, cp[pos].info.InterfaceMethodref.nameAndTypeIndex - 1);
            break;

        case CONSTANT_String:
            imprimeStringPool(cp, cp[pos].info.String.stringIndex - 1);
            break;

        case CONSTANT_Integer:
            printf("%u", cp[pos].info.Integer.bytes);
            break;

        case CONSTANT_Float:
            printf("%u", cp[pos].info.Float.bytes);
            break;

        default:
            break;
    }
}

///
/// Funcao converte um valor Hexademical lido em bytes para
/// uma variavel double (tipada de acordo com C99).
///
/// @param uint32_t Parte alta dos 64 bits
/// @param uint32_t Parte baixa dos 64 bits
/// @return @c double O valor Hexadecimal de entrada salvo numa variavel do tipo double
double hexToDouble(uint32_t highBytes, uint32_t lowBytes){

    double retorno;
    uint64_t valorDouble;

    valorDouble = highBytes;
    valorDouble <<= 32;
    valorDouble |= lowBytes;

    memcpy(&retorno, &valorDouble, sizeof(uint64_t));

    return retorno;
}

///
/// Funcao converte um valor Hexademical lido em bytes para
/// uma variavel long (tipada de acordo com C99).
///
/// @param uint32_t Parte alta dos 64 bits
/// @param uint32_t Parte baixa dos 64 bits
/// @return @c long O valor Hexadecimal de entrada salvo numa variavel do tipo long
long hexToLong(uint32_t highBytes, uint32_t lowBytes){
    long retorno;
    long negativo;

    negativo = pow(-1, (highBytes >> 31));
    memcpy(&retorno, &lowBytes, sizeof(uint32_t));

    return retorno * negativo;
}

///
/// Funcao que imprime o tipo de Access Flag de acordo
/// com o parametro Hexadecimal passado. Se o valor for
//  uma combinacao de flags, tambem eh reconhecido e uma
/// string com todas as flags eh impressa na tela.
///
/// @param uint16_t Valor Hexadecimal referente a uma flag ou combinacao de flags
/// @param uint32_t Parte baixa dos 64 bits
/// @return @c void
void printAccessFlag(uint16_t accessFlags){

    switch(accessFlags){
        case 0x0001:
            printf("Public\n");
        break;
        case 0x0009:
            printf("Public Static\n");
        break;
        case 0x0041:
            printf("Public Volatile\n");
        break;
        case 0x00019:
            printf("Public Static Final\n");
        break;
        case 0x0002:
            printf("Private\n");
        break;
        case 0x000A:
            printf("Private Static\n");
        break;
        case 0x0042:
            printf("Private Volatile\n");
        break;
        case 0x0001A:
            printf("Private Static Final\n");
        break;
        case 0x0004:
            printf("Protected\n");
        break;
        case 0x000C:
            printf("Protected Static\n");
        break;
        case 0x0044:
            printf("Protected Volatile\n");
        break;
        case 0x0001C:
            printf("Protected Static Final\n");
        break;
        case 0x0008:
            printf("Static\n");
        break;
        case 0x0010:
            printf("Final\n");
        break;
        case 0x0040:
            printf("Volatile\n");
        break;
        case 0x0080:
            printf("Transient\n");
        break;

    }
}

///
/// Funcao que imprime as instrucoes (mnemonicos) de um metodo, alem
/// das informacoes sobre o Code do metodo e das referencias de cada
/// valor no Constant Pool.
///
/// @param ClassFile* Ponteiro para a estrutura Classfile
/// @param CodeAttributte* Ponteiro para a estrutura CodeAttribute
/// @return @c void
/// @see printSingleLine imprimeStringPool inicializaDecodificador
void imprimeCode(ClassFile* classFile, CodeAttribute* cdAtrb) {
    int opcode, posReferencia;
    int bytesPreench, offsets;
    uint32_t defautV, low, high, npairs, temp;

    printf("\n\tCode Info");
    printSingleLine();
    printf("\n");
    printf("\tattribute_name_index:    cp_info_#%d   ",cdAtrb->attributeNameIndex);
    imprimeStringPool(classFile->constantPool, cdAtrb->attributeNameIndex - 1);
    printf("\n");
    printf("\tattribute_length:        %u\n   ",cdAtrb->attributeLength);

    printf("\tTamanho maximo do Stack: %d\n", cdAtrb->maxStack);
    printf("\tNumero maximo de variaveis locais: %d\n",cdAtrb->maxLocals);
    printf("\tTamanho do codigo: %u\n", cdAtrb->codeLength);

    Decodificador dec[NUM_INSTRUCAO];
    inicializaDecodificador(dec);

    for(uint32_t k = 0; k < cdAtrb->codeLength; ) {
        opcode = cdAtrb->code[k];
        printf("\t%u: %s  ", k, dec[opcode].instrucao);
        k++;

        if (opcode == TABLESWITCH) {
            posReferencia = k - 1;
            bytesPreench = (4 - (k % 4)) % 4;
            for (int l = 0; l < bytesPreench; l++) {
                k++;
            }

            defautV = 0;
            for (int l = 0; l < 4; l++) {
                defautV = (defautV << 4) + cdAtrb->code[k];
                k++;
            }

            low = 0;
            for (int l = 0; l < 4; l++) {
                low = (low << 4) + cdAtrb->code[k];
                k++;
            }

            high = 0;
            for (int l = 0; l < 4; l++) {
                high = (high << 4) + cdAtrb->code[k];
                k++;
            }

            printf("  from  %u to %u\n", low, high);

            offsets = 1 + high - low;
            for (int l = 0; l < offsets; l++) {
                temp = 0;
                for (int i = 0; i < 4; i++) {
                    temp = (temp << 4) + cdAtrb->code[k];
                    k++;
                }
                printf("\t%d: %u (+%u)\n", l, (posReferencia + temp), temp);
            }
            printf("\tdefault: %u (+%u)\n", (defautV + posReferencia), defautV);
        } else if (opcode == LOOKUPSWITCH) {
            posReferencia = k - 1;
            bytesPreench = (4 - (k % 4)) % 4;
            for (int l = 0; l < bytesPreench; l++) {
                k++;
            }

            defautV = 0;
            for (int l = 0; l < 4; l++) {
                defautV = (defautV << 4) + cdAtrb->code[k];
                k++;
            }

            npairs = 0;
            for (int l = 0; l < 4; l++) {
                npairs = (npairs << 4) + cdAtrb->code[k];
                k++;
            }

            printf("  %u\n", npairs);

            for (uint32_t l = 0; l < npairs; l++) {
                temp = 0;
                for (int i = 0; i < 4; i++) {
                    temp = (temp << 8) + cdAtrb->code[k];
                    k++;
                }
                printf("\t%u:  ", temp);

                temp = 0;
                for (int i = 0; i < 4; i++) {
                    temp = (temp << 8) + cdAtrb->code[k];
                    k++;
                }
                printf("%u (+%u)\n", temp + posReferencia, temp);

            }
            printf("\tdefault: %u (+%u)\n", defautV + posReferencia, defautV);

        } else if (opcode == WIDE) {
            printf("\n");

            opcode = cdAtrb->code[k];
            k++;

            if (opcode == ILOAD || opcode == FLOAD || opcode == ALOAD || opcode == LLOAD ||
                opcode == DLOAD || opcode == ISTORE || opcode == FSTORE || opcode == ASTORE ||
                opcode == LSTORE || opcode == DSTORE || opcode == RET) {

                printf("%u: %s  ", k - 1, dec[opcode].instrucao);
                k+=2;
                temp = cdAtrb->code[k-2] << 8;
                temp += cdAtrb->code[k-1];
                printf(" %u \n", temp);
                printf("%u: iinc ", k - 1);
                k+=2;
                temp = cdAtrb->code[k-2] << 8;
                temp += cdAtrb->code[k-1];
                printf(" %u ", temp);
                k+=2;
                temp = cdAtrb->code[k-2] << 8;
                temp += cdAtrb->code[k-1];
                printf(" por  %u \n", temp);

            } else {
                printf("arquivo .class invalido na instrucao wide");
                exit(1);
            }
        } else {
            int num_bytes = dec[opcode].bytes;
            for (int l = 0; l < num_bytes; l++) {

                printf("%d  ", cdAtrb->code[k]);
                if(cdAtrb->code[k] != 0)
                    imprimeStringPool(classFile->constantPool, cdAtrb->code[k] - 1);
                k++;
            }
            printf("\n");
        }
    }
    printf("\n\n");
}

///
/// Funcao que imprime as excecoes (quando especificadas) e
/// as referencias de cada ao Constant Pool.
///
/// @param ClassFile* Ponteiro para a estrutura Classfile
/// @param ExceptionsAttribute* Ponteiro para a estrutura ExceptionsAttribute
/// @return @c void
/// @see printSingleLine imprimeStringPool
void imprimeExc(ClassFile* classFile, ExceptionsAttribute* excAtrb) {
    printf("\n\tException Info\n");
    printSingleLine();
    printf("\tattribute_name_index:     cp_info_#%d   ", excAtrb->attributeNameIndex);
    imprimeStringPool(classFile->constantPool, excAtrb->attributeNameIndex - 1);
    printf("\n");
    printf("\t# - Excecao\n");
    for (int k = 0; k < excAtrb->numberExceptions; k++) {
        printf("\t\t%d - %d\n", k, excAtrb->exceptionIndexTable[k]);
    }
}

///
/// Funcao de estilizacao que imprime uma linha no topo de cada titulo
/// @param Nenhum
/// @return @c void
void printTopo() {

    printf("\n\t*");
    for (int i = 0; i < 47; ++i) {
        printf("*");
    }
    printf("*\n");
}

///
/// Funcao de estilizacao que imprime uma linha em branco, mas com as bordas
/// @param Nenhum
/// @return @c void
void printBlank() {

    printf("\t*");
    for (int i = 0; i < 47; ++i) {
        printf(" ");
    }
    printf("*\n");
}

///
/// Funcao de estilizacao que imprime uma linha na base de cada titulo
/// @param Nenhum
/// @return @c void
void printBase() {

    printf("\t*");
    for (int i = 0; i < 47; ++i) {
        printf("*");
    }
    printf("*\n");
}

///
/// Funcao de estilizacao que imprime uma linha na lateral de um titulo
/// @param Nenhum
/// @return @c void
void printSingleLine(){
    for (int i = 0; i < 34; ++i) {
        printf("_");
    }
}
