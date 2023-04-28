#include "include/File_String.hpp"


void Read_Text(Text* text, const char* file_name)
{
    FILE* file = fopen(file_name, "r");

    if (file == NULL)
    {
        printf("No file found!\n");
        exit(101);
    }

    fseek(file, 0l, SEEK_END);              //to the end of file with 0 after
    text->text_length = ftell(file);        //amount of bytes
    rewind(file);                           //back to the beginning

    text->buffer = (char*) calloc(text->text_length, sizeof(char));
    fread(text->buffer, sizeof(char), text->text_length, file);
    fclose(file);

    Split_By_Words(text);
}

void Split_By_Words(Text* text)
{
    int words_amount = 0;

    int i = 0;
    while (i < text->text_length)
    {
        if (!isalpha(text->buffer[i]))
        {
            words_amount++;
            text->buffer[i] = '\0';
            while (!isalpha(text->buffer[i]) && i < text->text_length) i++;
            i--;
        }
        i++;
    }

    text->words_amount = words_amount;
    text->words = (Word*) calloc (words_amount, sizeof(Word));

    char* prev_buffer = text->buffer;

    int word = 1;
    i = 1;
    while (i < text->text_length)
    {
        if (!isalpha(text->buffer[i]))
        {
            int word_len = text->buffer + i - prev_buffer;
            Word_Ctor(&text->words[word-1], prev_buffer, word_len);

            while (!isalpha(text->buffer[i]) && i < text->text_length) i++;
            i--;
            prev_buffer = text->buffer + i + 1;
            word++;
        }
        i++;
    }

    int word_len = text->buffer + text->text_length - prev_buffer;
    Word_Ctor(&text->words[word-1], prev_buffer, word_len);

    
/*
    text->words[0].word_text = text->buffer;

    int word = 1;
    i = 1;
    while (i < text->text_length)
    {
        if (!isalpha(text->buffer[i]))
        {
            text->words[word-1].word_len = text->buffer + i - text->words[word-1].word_text;
            while (!isalpha(text->buffer[i]) && i < text->text_length) i++;
            i--;
            text->words[word].word_text = text->buffer + i + 1;
            word++;
        }
        i++;
    }

    text->words[word-1].word_len = text->buffer + text->text_length - text->words[word-1].word_text;
*/
}


void Free_Text(Text* text)
{
    for (int i = 0; i < text->words_amount; i++)
    {
        Word_Dtor(&text->words[i]);
    }

    free(text->words);
    free(text->buffer);
    text->text_length = 0;
    text->words_amount = 0;
}