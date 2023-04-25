#ifndef HASH_H
#define HASH_H

//#include "File_String.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Word
{
    const char* word_text;
    long word_len;
};


struct Hash_Table_Node;
struct Hash_Table_Head;
struct Hash_Table;

//void Hash_Table_Ctor(Hash_Table* table, size_t size, Text* text, long (* hash_function) (const Word* word));
Hash_Table* Hash_Table_Ctor(size_t size, Word* words, long words_amount, unsigned long (* hash_function) (const Word* word));
void Add_Node_To_List(Hash_Table* table, Word* word);
void Save_Table_Lists_Lengths (Hash_Table* table, const char* file_name);
bool Check_Entry(const Hash_Table* table, const char* word);
void Hash_Table_Dtor(Hash_Table* table);


unsigned long Hash_Just_One(const Word* word);
unsigned long Hash_Ascii(const Word* word);
unsigned long Hash_Strlen(const Word* word);
unsigned long Hash_Ascii_Sum(const Word* word);
unsigned long ROL(long num, int shift);
unsigned long Hash_Rol(const Word* word);
unsigned long ROR(long num, int shift);
unsigned long Hash_Ror(const Word* word);
unsigned long Hash_Polynom(const Word* word);
#endif