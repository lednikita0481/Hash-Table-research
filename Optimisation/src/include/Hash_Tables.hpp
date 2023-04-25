#ifndef HASH_H
#define HASH_H

//#include "File_String.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <chrono>
#include <immintrin.h>
#include <math.h>

struct Word
{
    const char* word_text;
    long word_len;
    __m256i* avx_text;
};

struct Hash_Table_Node;
struct Hash_Table_Head;
struct Hash_Table;

//void Hash_Table_Ctor(Hash_Table* table, size_t size, Text* text, long (* hash_function) (const Word* word));
Hash_Table* Hash_Table_Ctor(size_t size, Word* words, long words_amount, long (* hash_function) (const Word* word));
void Add_Node_To_List(Hash_Table* table, Word* word);
void Save_Table_Lists_Lengths (Hash_Table* table, const char* file_name);
bool Check_Str_Eq(const Word* word, const Word* node);
bool Check_Entry(const Hash_Table* table, const char* word);
void Hash_Table_Dtor(Hash_Table* table);




void Check_Entry_AVX(Hash_Table* table, const char* words[4], bool entry[4]);
__m256i Hash_Polynom_AVX(const Word* words);

bool Check_Entry_ASM_hash(const Hash_Table* table, const char* word);
extern "C" long Asm_Hash_Polynom(const Word* word);

void Check_Entry_AVX_STRCMPAVX(Hash_Table* table, const char* words[4], bool entry[4]);
void Check_Entry_AVX_STRCMPAVX_NO_STRCPY(Hash_Table* table, const Word* words[4], bool entry[4]);
__m256i Hash_Polynom_AVX_aaa(const Word** words);
bool Check_Entry_ASM_hash_STRCMPAVX_NOSTRCPY(const Hash_Table* table, Word* word);

long CRC32_Hash(const Word* word);
bool Check_Entry_only_STRCMPAVX_NOSTRCPY(const Hash_Table* table, Word* word);

extern "C" long CRC32asm(const Word* word);
bool Check_Entry_ASM_CRC32_hash_STRCMPAVX_NOSTRCPY(const Hash_Table* table, Word* word);




long Hash_Just_One(const Word* word);
long Hash_Ascii(const Word* word);
long Hash_Strlen(const Word* word);
long Hash_Ascii_Sum(const Word* word);
long ROL(long num, int shift);
long Hash_Rol(const Word* word);
long ROR(long num, int shift);
long Hash_Ror(const Word* word);
long Hash_Polynom(const Word* word);
#endif