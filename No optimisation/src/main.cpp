#include "include/File_String.hpp"
#include "include/Hash_Tables.hpp"

int main()
{
    Text text = {};
    Read_Text(&text, "shakespeare.txt");
    printf("here!\n");
    //Hash_Table* table_hash_1 = {};

    //printf("%d\n", text.words_amount);

    //for (int i = 0; i < text.words_amount; i++)
    //{
    //    printf("%d. %s, %d\n", i+1, text.words[i].word_text, text.words[i].word_len);
    //}


    Hash_Table* table_hash_1 = Hash_Table_Ctor(1500, text.words, text.words_amount, Hash_Just_One);
    Save_Table_Lists_Lengths(table_hash_1, "graphs/csv/1.Return One.csv");
    Hash_Table_Dtor(table_hash_1);

    printf("hui!\n");

    table_hash_1 = Hash_Table_Ctor(1500, text.words, text.words_amount, Hash_Ascii);
    Save_Table_Lists_Lengths(table_hash_1, "graphs/csv/2.ASCII hash.csv");
    Hash_Table_Dtor(table_hash_1);

    table_hash_1 = Hash_Table_Ctor(1500, text.words, text.words_amount, Hash_Strlen);
    Save_Table_Lists_Lengths(table_hash_1, "graphs/csv/3.strlen hash.csv");
    Hash_Table_Dtor(table_hash_1);

    table_hash_1 = Hash_Table_Ctor(1500, text.words, text.words_amount, Hash_Ascii_Sum);
    Save_Table_Lists_Lengths(table_hash_1, "graphs/csv/4.ASCII sum hash.csv");
    Hash_Table_Dtor(table_hash_1);

    table_hash_1 = Hash_Table_Ctor(1500, text.words, text.words_amount, Hash_Rol);
    Save_Table_Lists_Lengths(table_hash_1, "graphs/csv/5.ROL hash.csv");
    Hash_Table_Dtor(table_hash_1);

    table_hash_1 = Hash_Table_Ctor(1500, text.words, text.words_amount, Hash_Ror);
    Save_Table_Lists_Lengths(table_hash_1, "graphs/csv/6.ROR hash.csv");
    Hash_Table_Dtor(table_hash_1);

    table_hash_1 = Hash_Table_Ctor(1500, text.words, text.words_amount, Hash_Polynom);
    bool check = Check_Entry(table_hash_1, "fickle");
    printf("%d!\n", check);

    Save_Table_Lists_Lengths(table_hash_1, "graphs/csv/7.Polynom hash.csv");
    Hash_Table_Dtor(table_hash_1);
    Free_Text(&text);
}