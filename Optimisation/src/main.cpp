#include "include/File_String.hpp"
#include "include/Hash_Tables.hpp"

void kukareku_i_begu_po_vsemu_textu(Text* text, Hash_Table* table_hash_1);
void kukareku_i_begu_po_vsemu_textu_AVX(Text* text, Hash_Table* table_hash_1);
void kukareku_i_begu_po_vsemu_textu_ASM_hash(Text* text, Hash_Table* table_hash_1);
void kukareku_i_begu_po_vsemu_textu_AVX_STRCMPAVX(Text* text, Hash_Table* table_hash_1);
void kukareku_i_begu_po_vsemu_textu_AVX_STRCMPAVX_NOSTRCPY(Text* text, Hash_Table* table_hash_1);
void kukareku_i_begu_po_vsemu_textu_ASM_hash_STRCMPAVX_NOSTRCPY(Text* text, Hash_Table* table_hash_1);
void kukareku_i_begu_po_vsemu_textu_only_STRCMPAVX_NOSTRCPY(Text* text, Hash_Table* table_hash_1);
void kukareku_i_begu_po_vsemu_textu_ASM_hash_CRC32_STRCMPAVX_NOSTRCPY(Text* text, Hash_Table* table_hash_1);

int main()
{
    printf("%d!!!\n\n\n\n", sizeof(Word));
    Text text = {};
    Read_Text(&text, "shakespeare.txt");
    printf("here!\n");

    Hash_Table* table_hash_1 = Hash_Table_Ctor(1500, text.words, text.words_amount, Hash_Polynom);


    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    kukareku_i_begu_po_vsemu_textu(&text, table_hash_1);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    printf ("Elapsed time(ms) standart: %u\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());

    begin = std::chrono::steady_clock::now();
    kukareku_i_begu_po_vsemu_textu(&text, table_hash_1);
    end = std::chrono::steady_clock::now();
    printf ("Elapsed time(ms) standart: %u\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());

    begin = std::chrono::steady_clock::now();
    kukareku_i_begu_po_vsemu_textu(&text, table_hash_1);
    end = std::chrono::steady_clock::now();
    printf ("Elapsed time(ms) standart: %u\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());

    begin = std::chrono::steady_clock::now();
    kukareku_i_begu_po_vsemu_textu_AVX(&text, table_hash_1);
    end = std::chrono::steady_clock::now();
    printf ("Elapsed time(ms) avx: %u\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());

    begin = std::chrono::steady_clock::now();
    kukareku_i_begu_po_vsemu_textu_ASM_hash(&text, table_hash_1);
    end = std::chrono::steady_clock::now();
    printf ("Elapsed time(ms) asm: %u\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());

    begin = std::chrono::steady_clock::now();
    kukareku_i_begu_po_vsemu_textu_AVX_STRCMPAVX(&text, table_hash_1);
    end = std::chrono::steady_clock::now();
    printf ("Elapsed time(ms) avx + strcmp avx: %u\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());


    begin = std::chrono::steady_clock::now();
    kukareku_i_begu_po_vsemu_textu_AVX_STRCMPAVX_NOSTRCPY(&text, table_hash_1);
    end = std::chrono::steady_clock::now();
    printf ("Elapsed time(ms) avx + strcmp avx no strcpy: %u\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());

    begin = std::chrono::steady_clock::now();
    kukareku_i_begu_po_vsemu_textu_ASM_hash_STRCMPAVX_NOSTRCPY(&text, table_hash_1);
    end = std::chrono::steady_clock::now();
    printf ("Elapsed time(ms) asm + strcmp avx no strcpy: %u\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());

    Hash_Table_Dtor(table_hash_1);

    table_hash_1 = Hash_Table_Ctor(1500, text.words, text.words_amount, CRC32_Hash);

    printf("заситорил\n");

    begin = std::chrono::steady_clock::now();
    kukareku_i_begu_po_vsemu_textu(&text, table_hash_1);
    end = std::chrono::steady_clock::now();
    printf ("Elapsed time(ms) standart CRC32: %u\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());

    begin = std::chrono::steady_clock::now();
    kukareku_i_begu_po_vsemu_textu_only_STRCMPAVX_NOSTRCPY(&text, table_hash_1);
    end = std::chrono::steady_clock::now();
    printf ("Elapsed time(ms) strcmp avx no strcpy CRC32: %u\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());

    begin = std::chrono::steady_clock::now();
    kukareku_i_begu_po_vsemu_textu_ASM_hash_CRC32_STRCMPAVX_NOSTRCPY(&text, table_hash_1);
    end = std::chrono::steady_clock::now();
    printf ("Elapsed time(ms) asm CRC32  strcmp avx no strcpy CRC32: %u\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());

    bool entry[4] = {false, false, false, false};
    const char* words[4] = {"hui", "indulgences", "GLOUCESTER", "Gargrave"};
    Check_Entry_AVX(table_hash_1, words, entry);
    for (int i = 0; i < 4; i++)
    {
        printf("%d\n", entry[i]);
    }

    //Save_Table_Lists_Lengths(table_hash_1, "graphs/csv/7.Polynom hash.csv");
    Hash_Table_Dtor(table_hash_1);
    Free_Text(&text);
}

void kukareku_i_begu_po_vsemu_textu(Text* text, Hash_Table* table_hash_1)
{
    for (int j = 0; j < 100; j ++)
    {
        for (long i = 0; i < text->words_amount; i++)
        {
            bool check = Check_Entry(table_hash_1, text->words[i].word_text);
            //printf("%d %s %d\n", i, text->words[i].word_text, check);
        }
    }
}

void kukareku_i_begu_po_vsemu_textu_AVX(Text* text, Hash_Table* table_hash_1)
{
    for (int j = 0; j < 100; j++)
    {
        bool check[4] = {};
        const char* words[4] = {};
        for (long i = 0; i < text->words_amount/4; i++)
        {
            words[0] = text->words[i+0].word_text;
            words[1] = text->words[i+1].word_text;
            words[2] = text->words[i+2].word_text;
            words[3] = text->words[i+3].word_text;

            Check_Entry_AVX(table_hash_1, words, check);

            /*
            printf("%d\n", check[0]);
            printf("%d\n", check[1]);
            printf("%d\n", check[2]);
            printf("%d\n", check[3]);
            */
            
        }

        /*long i = (text->words_amount/4)*4;
        long j = 0;
        while (i < text->words_amount)
        {
            words[j] = text->words[i].word_text;
            j++;
            i++;
        }
        while (j < 4) words[j] = "h";

        Check_Entry_AVX(table_hash_1, words, check);


        printf("%d\n", check[0]);
        printf("%d\n", check[1]);
        printf("%d\n", check[2]);
        printf("%d\n", check[3]);*/
    }
}

void kukareku_i_begu_po_vsemu_textu_ASM_hash(Text* text, Hash_Table* table_hash_1)
{
    for (int j = 0; j < 100; j++)
    {
        for (long i = 0; i < text->words_amount; i++)
        {
            bool check = Check_Entry_ASM_hash(table_hash_1, text->words[i].word_text);
            //printf("%d for word with len %d\n", check, text->words[i].word_len);
            //if (!check) printf("%s\n", text->words[i].word_text);
        }
    }
}

void kukareku_i_begu_po_vsemu_textu_AVX_STRCMPAVX(Text* text, Hash_Table* table_hash_1)
{
    for (int j = 0; j < 100; j++)
    {
        bool check[4] = {};
        const char* words[4] = {};
        for (long i = 0; i < text->words_amount/4; i++)
        {
            words[0] = text->words[i+0].word_text;
            words[1] = text->words[i+1].word_text;
            words[2] = text->words[i+2].word_text;
            words[3] = text->words[i+3].word_text;

            Check_Entry_AVX_STRCMPAVX(table_hash_1, words, check);

            /*
            printf("%d\n", check[0]);
            printf("%d\n", check[1]);
            printf("%d\n", check[2]);
            printf("%d\n", check[3]);
            */
            
        }

        /*long i = (text->words_amount/4)*4;
        long j = 0;
        while (i < text->words_amount)
        {
            words[j] = text->words[i].word_text;
            j++;
            i++;
        }
        while (j < 4) words[j] = "h";

        Check_Entry_AVX(table_hash_1, words, check);


        printf("%d\n", check[0]);
        printf("%d\n", check[1]);
        printf("%d\n", check[2]);
        printf("%d\n", check[3]);*/
    }
}

void kukareku_i_begu_po_vsemu_textu_AVX_STRCMPAVX_NOSTRCPY(Text* text, Hash_Table* table_hash_1)
{
    for (int j = 0; j < 100; j++)
    {
        bool check[4] = {};
        const Word* words[4] = {};
        for (long i = 0; i < text->words_amount/4; i++)
        {
            words[0] = &text->words[i+0];
            words[1] = &text->words[i+1];
            words[2] = &text->words[i+2];
            words[3] = &text->words[i+3];

            Check_Entry_AVX_STRCMPAVX_NO_STRCPY(table_hash_1, words, check);

            /*
            printf("%d\n", check[0]);
            printf("%d\n", check[1]);
            printf("%d\n", check[2]);
            printf("%d\n", check[3]);
            */
            
        }

        /*long i = (text->words_amount/4)*4;
        long j = 0;
        while (i < text->words_amount)
        {
            words[j] = text->words[i].word_text;
            j++;
            i++;
        }
        while (j < 4) words[j] = "h";

        Check_Entry_AVX(table_hash_1, words, check);


        printf("%d\n", check[0]);
        printf("%d\n", check[1]);
        printf("%d\n", check[2]);
        printf("%d\n", check[3]);*/
    }
}


void kukareku_i_begu_po_vsemu_textu_ASM_hash_STRCMPAVX_NOSTRCPY(Text* text, Hash_Table* table_hash_1)
{
    for (int j = 0; j < 100; j++)
    {
        for (long i = 0; i < text->words_amount; i++)
        {
            bool check = Check_Entry_ASM_hash_STRCMPAVX_NOSTRCPY(table_hash_1, &text->words[i]);
            //printf("%d for word with len %d\n", check, text->words[i].word_len);
            //if (!check) printf("%s\n", text->words[i].word_text);
        }
    }
}

void kukareku_i_begu_po_vsemu_textu_only_STRCMPAVX_NOSTRCPY(Text* text, Hash_Table* table_hash_1)
{
    for (int j = 0; j < 100; j ++)
    {
        for (long i = 0; i < text->words_amount; i++)
        {
            bool check = Check_Entry_only_STRCMPAVX_NOSTRCPY(table_hash_1, &text->words[i]);
            //printf("%d %s %d\n", i, text->words[i].word_text, check);
        }
    }
}

void kukareku_i_begu_po_vsemu_textu_ASM_hash_CRC32_STRCMPAVX_NOSTRCPY(Text* text, Hash_Table* table_hash_1)
{
    for (int j = 0; j < 100; j++)
    {
        for (long i = 0; i < text->words_amount; i++)
        {
            bool check = Check_Entry_ASM_CRC32_hash_STRCMPAVX_NOSTRCPY(table_hash_1, &text->words[i]);
            //printf("%d for word with len %d\n", check, text->words[i].word_len);
            //if (!check) printf("%s\n", text->words[i].word_text);
        }
    }
}