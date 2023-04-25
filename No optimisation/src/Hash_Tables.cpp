#include "include/Hash_Tables.hpp"
//#include "include/File_String.hpp"

struct Hash_Table_Node
{
    Word* word;
    Hash_Table_Node* next_node;
};

struct Hash_Table_Head
{
    size_t list_length;
    Hash_Table_Node* nodes;
};

struct Hash_Table
{
    size_t hash_amount;
    Hash_Table_Head* heads;
    unsigned long (* hash_function) (const Word* word);
};

/*
void Hash_Table_Ctor(Hash_Table* table, size_t size, Text* text, long (* hash_function) (const Word* word))
{
    table->hash_amount = size;
    table->heads = (Hash_Table_Head*) calloc(size, sizeof(Hash_Table_Head));
    table->hash_function = hash_function;

    for (long i = 0; i < text->words_amount; i++)
    {
        //int hash_list = ((*hash_function)(&text->words[i]))%size;
        Add_Node_To_List(table, &text->words[i]);
        //printf("%ld of %ld\n", i, text->words_amount);
    }
}
*/

Hash_Table* Hash_Table_Ctor(size_t size, Word* words, long words_amount, unsigned long (* hash_function) (const Word* word))
{
    Hash_Table* table = (Hash_Table*) calloc (1, sizeof(Hash_Table));
    table->hash_amount = size;
    table->heads = (Hash_Table_Head*) calloc(size, sizeof(Hash_Table_Head));
    table->hash_function = hash_function;

    for (long i = 0; i < words_amount; i++)
    {
        //int hash_list = ((*hash_function)(&text->words[i]))%size;
        Add_Node_To_List(table, &words[i]);
        //printf("%ld of %ld\n", i, text->words_amount);
    }

    return table;
}

void Add_Node_To_List(Hash_Table* table, Word* word)
{
    unsigned long hash_list = ((*table->hash_function)(word))%table->hash_amount;
    bool first_node = false;
    if (table->heads[hash_list].list_length == 0)
    {
        first_node = true;
        table->heads[hash_list].nodes = (Hash_Table_Node*) calloc(1, sizeof(Hash_Table_Node));
    }

    Hash_Table_Node* node = table->heads[hash_list].nodes;

    long word_len = word->word_len;
    while (node->next_node != NULL) 
    {
        if (word_len == node->word->word_len)
        {
            if (strncmp(word->word_text, node->word->word_text, word_len) == 0) return;
        }
        node = node->next_node;
    }

    if (!first_node)
    {
        node->next_node = (Hash_Table_Node*) calloc(1, sizeof(Hash_Table_Node));
        node = node->next_node;
    }
    node->word = word;

    table->heads[hash_list].list_length++;
}


void Save_Table_Lists_Lengths (Hash_Table* table, const char* file_name)
{
    FILE* file = fopen(file_name, "w");

    fprintf(file, "index;list_len\n");
    for (long i = 0; i < table->hash_amount; i++)
    {
        fprintf(file, "%ld;%ld\n", i, table->heads[i].list_length);
    }

    fclose(file);
}

bool Check_Entry(const Hash_Table* table, const char* word)
{
    Word struct_word = {word, strlen(word)};
    unsigned long hash_list = ((*table->hash_function)(&struct_word))%table->hash_amount;

    bool entry = false;

    Hash_Table_Node* node = table->heads[hash_list].nodes;
    for (size_t i = 0; i < table->heads[hash_list].list_length; i++)
    {
        if (struct_word.word_len == node->word->word_len)
        {
            if (strncmp(struct_word.word_text, node->word->word_text, struct_word.word_len) == 0)
            {
                entry = true;
                break;
            }
        }

        node = node->next_node;
    }

    return entry;
}

void Hash_Table_Dtor(Hash_Table* table)
{
    for (size_t head = 0; head <= table->hash_amount; head++)
    {
        Hash_Table_Node* next_node_to_free = table->heads[head].nodes;
        Hash_Table_Node* node_to_free = table->heads[head].nodes;
        for (size_t node = 0; node < table->heads[head].list_length; node++)
        {
            next_node_to_free = node_to_free->next_node;
            node_to_free->word = NULL;
            node_to_free->next_node = NULL;
            free(node_to_free);
            node_to_free = next_node_to_free;
        }
    }

    free(table->heads);
    table->hash_amount = 0;
    free(table);
}



//------------------------------------------HASH----------------------------------------------------

unsigned long Hash_Just_One(const Word* word)
{
    return 1;
}

unsigned long Hash_Ascii(const Word* word)
{
    return (long)word->word_text[0];
}

unsigned long Hash_Strlen(const Word* word)
{
    return word->word_len;
}

unsigned long Hash_Ascii_Sum(const Word* word)
{
    long sum = 0;
    for (long i = 0; i < word->word_len; i++)
    {
        sum += (long) word->word_text[i];
    }

    return sum;
}

unsigned long ROL(long num, int shift) {return (num << shift) | (num >> (sizeof(long) - shift));}
unsigned long Hash_Rol(const Word* word)
{
    long hash = 0;

    for (int i = 0; i < word->word_len; i++)
    {
        hash = ROL(hash, 1) ^ word->word_text[i];
    }

    return hash;
}

unsigned long ROR(long num, int shift) {return (num >> shift) | (num << (sizeof(long) - shift));}
unsigned long Hash_Ror(const Word* word)
{
    long hash = 0;

    for (int i = 0; i < word->word_len; i++)
    {
        hash = ROR(hash, 1) ^ word->word_text[i];
    }

    return hash;
}

unsigned long Hash_Polynom(const Word* word)
{
    int k = 31;
    int pow_k = 1;
    long hash = 0;

    for (int i = 0; i < word->word_len; i++)
    {
        hash += ((long) word->word_text[i]) * pow_k;
        pow_k *= k;
    }

    return hash;
}