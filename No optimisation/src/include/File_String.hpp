#ifndef FILE_STR_H
#define FILE_STR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Hash_Tables.hpp"


struct Text
{
    char* buffer;
    long text_length;
    long words_amount;
    Word* words;
};


void Read_Text(Text* text, const char* file_name);
void Split_By_Words(Text* text);
void Free_Text(Text* text);
#endif