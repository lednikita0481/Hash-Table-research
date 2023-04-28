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
    long (* hash_function) (const Word* word);
};

void Word_Ctor(Word* word, const char* text, int lendth)
{
    word->word_text = (char*) calloc(32, sizeof(char));
    if (lendth < 0)
    {
        strncpy(word->word_text, text, 31);
        word->word_len = strlen(word->word_text);
    }

    else
    {
        if (lendth > 31) lendth = 31;
        strncpy(word->word_text, text, lendth);
        word->word_len = lendth;
    }

    __m256i* avx_text = (__m256i*) aligned_alloc(32, sizeof(__m256i));
    *avx_text = _mm256_loadu_si256((__m256i*) word->word_text);
    word->avx_text = avx_text;
}

Hash_Table* Hash_Table_Ctor(size_t size, Word* words, long words_amount, long (* hash_function) (const Word* word))
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
    long hash_list = ((*table->hash_function)(word))%table->hash_amount;
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

bool Check_List_Entry(Hash_Table_Node* node, const size_t list_length, const Word* word)
{
    bool entry = false;

    for (size_t i = 0; i < list_length; i++)
    {
        if (word->word_len == node->word->word_len)
        {
            if (strncmp(word->word_text, node->word->word_text, word->word_len) == 0)
            {
                entry = true;
                break;
            }
        }

        node = node->next_node;
    }

    return entry;
}

bool Check_Entry(const Hash_Table* table, const Word* word)
{
    long hash_list = ((*table->hash_function)(word))%table->hash_amount;
    Hash_Table_Node* node = table->heads[hash_list].nodes;
    bool entry = Check_List_Entry(node, table->heads[hash_list].list_length, word);

    return entry;
}

//------------------------------OPTIMIZATION------------------------------------------------------------

void Check_Entry_AVX(Hash_Table* table, const Word words[4], bool entry[4])
{
    __m256i avx_hashes = Hash_Polynom_AVX(words);
    long long* hashes = (long long*) &avx_hashes;
    for (int i = 0; i < 4; i++)
    {
        hashes[i] = ((long long*) &avx_hashes)[i];
    }


    for (long j = 0; j < 4; j++)
    {
        long hash_list = hashes[j]%table->hash_amount;
        Hash_Table_Node* node = table->heads[hash_list].nodes;
        entry[j] = Check_List_Entry(node, table->heads[hash_list].list_length, &words[j]);
    }
}

__m256i Hash_Polynom_AVX(const Word* words)
{
    __m256i pow_k = _mm256_set1_epi64x(1);
    const __m256i k = _mm256_set1_epi64x((long)31);
    const __m256i words_lengths = _mm256_set_epi64x(words[3].word_len, words[2].word_len, words[1].word_len, words[0].word_len);
    __m256i hashes = _mm256_set1_epi64x(0);
    __m256i letter_num = _mm256_set1_epi64x(0);
    const __m256i just_ones = _mm256_set1_epi64x(1);
    __m256i letters = _mm256_set_epi64x(words[3].word_text[0], words[2].word_text[0], words[1].word_text[0], words[0].word_text[0]);

    long max_len = 0;
    for (int j = 0; j < 4; j ++)
    {
        if (words[j].word_len > max_len) max_len = words[j].word_len;
    }

    for (int j = 0; j < max_len; j ++)
    {
        __m256i cur_letter_term = _mm256_mul_epi32(pow_k, letters);
        hashes = _mm256_add_epi64(hashes, cur_letter_term);
        pow_k = _mm256_mul_epi32(pow_k, k);

        __m256i cmp = _mm256_cmpeq_epi64(letter_num, words_lengths);
        letter_num = _mm256_add_epi64(letter_num, _mm256_add_epi64(just_ones, cmp));
        long* letter_num_array = (long*) &letter_num;
        letters = _mm256_set_epi64x(words[3].word_text[letter_num_array[3]], words[2].word_text[letter_num_array[2]], words[1].word_text[letter_num_array[1]], words[0].word_text[letter_num_array[0]]);
    }

    return hashes;
}

__m256i Hash_Polynom_AVX_another(const Word* words)
{
    __m256i pow_k = _mm256_set1_epi64x(1);
    const __m256i k = _mm256_set1_epi64x((long)31);
    //const __m256i words_lengths = _mm256_set_epi64x(words[3].word_len, words[2].word_len, words[1].word_len, words[0].word_len);
    __m256i hashes = _mm256_set1_epi64x(0);
    //__m256i letter_num = _mm256_set1_epi64x(0);
    const __m256i just_ones = _mm256_set1_epi64x(1);
    __m256i letters = _mm256_set_epi64x(words[3].word_text[0], words[2].word_text[0], words[1].word_text[0], words[0].word_text[0]);

    long max_len = 0;
    for (int j = 0; j < 4; j ++)
    {
        if (words[j].word_len > max_len) max_len = words[j].word_len;
    }

    for (int j = 0; j < max_len; j ++)
    {
        __m256i cur_letter_term = _mm256_mul_epi32(pow_k, letters);
        hashes = _mm256_add_epi64(hashes, cur_letter_term);
        pow_k = _mm256_mul_epi32(pow_k, k);

        //__m256i cmp = _mm256_cmpeq_epi64(letter_num, words_lengths);
        //letter_num = _mm256_add_epi64(letter_num, _mm256_add_epi64(just_ones, cmp));
        //long* letter_num_array = (long*) &letter_num;
        letters = _mm256_set_epi64x(words[3].word_text[j+1], words[2].word_text[j+1], words[1].word_text[j+1], words[0].word_text[j+1]);
    }

    return hashes;
}

void Check_Mass_Entry(Hash_Table* table, const Word* words, bool* entry, long amount)
{
    for (long i = 0; i < amount; i+=4)
    {
        bool aaab[4] = {};
        Word aaaw[4] = {words[i], words[i+1], words[i+2], words[i+3]};
        Check_Entry_AVX(table, aaaw, aaab);
        for (int j = 0; j < 4; j++) entry[i+j] = aaab[j];
    }

    long i = (amount/4)*4;
    while (i < amount)
    {
        printf("%d\n", i);
        printf("%d. %s\n", i, words[i].word_text);
        entry[i] = Check_Entry(table, &words[i]);
        i++;
    }
}

long Hash_Polynom_AVX_one_word(const Word* word)
{
    long k = 31;
    long cur_pow = 1;
    alignas(32) long pow_k[4] = {};
    __m256i hashes = _mm256_set1_epi64x(0);
    long hash = 0;

    for (int i = 0; i < word->word_len; i+=4)
    {
        for (int j = 0; j < 4; j++)
        {
            pow_k[j] = cur_pow;
            cur_pow *= k;
        }

        __m256i avx_pow = _mm256_load_si256((__m256i*)pow_k);
        __m128i letters_loaded = _mm_load_si128((__m128i*)((char*)word->avx_text) + i);
        __m256i letters = _mm256_cvtepi8_epi64(letters_loaded);
        __m256i hash_mass_avx = _mm256_mul_epi32(letters, avx_pow);
        hashes = _mm256_add_epi64(hash_mass_avx, hashes);
    }

    long long* hash_mass = (long long*) &hashes;
    for (int j = 0; j < 4; j++) hash+=hash_mass[j];

    return hash;
}

bool Check_Entry_AVX_One_word(const Hash_Table* table, const Word* word)
{
    long hash_list = Hash_Polynom_AVX_one_word(word)%table->hash_amount;

    Hash_Table_Node* node = table->heads[hash_list].nodes;
    bool entry = Check_List_Entry(node, table->heads[hash_list].list_length, word);

    return entry;
}

bool Check_Entry_ASM_hash(const Hash_Table* table, const Word* word)
{
    long hash_list = Asm_Hash_Polynom(word)%table->hash_amount;

    Hash_Table_Node* node = table->heads[hash_list].nodes;
    bool entry = Check_List_Entry(node, table->heads[hash_list].list_length, word);

    return entry;
}                                                                                                                                

void Check_Entry_AVX_STRCMPAVX(Hash_Table* table, const Word words[4], bool entry[4])
{
    __m256i avx_hashes = Hash_Polynom_AVX(words);
    long long* hashes = (long long*) &avx_hashes;
    for (int i = 0; i < 4; i++)
    {
        hashes[i] = ((long long*) &avx_hashes)[i];
    }


    for (long j = 0; j < 4; j++)
    {
        long hash_list = hashes[j]%table->hash_amount;
        Hash_Table_Node* node = table->heads[hash_list].nodes;

        alignas(32) char word_text[32] = "";
        strncpy(word_text, words[j].word_text, words[j].word_len);

        __m256i text_to_find = _mm256_load_si256((__m256i*)word_text);

        
        for (size_t i = 0; i < table->heads[hash_list].list_length; i++)
        {
            alignas(32) char text_to_check[32] = "";
            strncpy(text_to_check, node->word->word_text, node->word->word_len);
            __m256i node_text = _mm256_load_si256((__m256i*)text_to_check);
            __m256i cmp = _mm256_cmpeq_epi8(text_to_find, node_text);
            int cmp_mask = (int) _mm256_movemask_epi8(cmp);
            if (cmp_mask == -1) 
            {
                entry[j] = true;
                break; 
            }

            node = node->next_node;
        }
    }
}

void Check_Mass_Entry_AVX_STRCMPAVX(Hash_Table* table, const Word* words, bool* entry, long amount)
{
    for (long i = 0; i < amount/4; i++)
    {
        Check_Entry_AVX_STRCMPAVX(table, words + 4*i, entry + 4*i);
    }

    long i = (amount/4)*4;

    while (i < amount)
    {
        entry[i] = Check_Entry(table, &words[i]);
        i++;
    }
}

bool Check_List_Entry_AVX(Hash_Table_Node* node, const size_t list_length, const Word* word)
{
    __m256i text_to_find = *word->avx_text;
    bool entry = false;

    for (size_t i = 0; i < list_length; i++)
    {
        __m256i node_text = *node->word->avx_text;
        __m256i cmp = _mm256_cmpeq_epi8(text_to_find, node_text);
        int cmp_mask = (int) _mm256_movemask_epi8(cmp);
        if (cmp_mask == -1) 
        {
            entry = true;
            break; 
        }

        node = node->next_node;
    }

    return entry;
}

void Check_Entry_AVX_STRCMPAVX_NO_STRCPY(Hash_Table* table, const Word words[4], bool entry[4])
{
    __m256i avx_hashes = Hash_Polynom_AVX(words);
    long long* hashes = (long long*) &avx_hashes;
    for (int i = 0; i < 4; i++)
    {
        hashes[i] = ((long long*) &avx_hashes)[i];
    }


    for (long j = 0; j < 4; j++)
    {
        long hash_list = hashes[j]%table->hash_amount;
        Hash_Table_Node* node = table->heads[hash_list].nodes;

        entry[j] = Check_List_Entry_AVX(node, table->heads[hash_list].list_length, &words[j]);
    }
}

void Check_Mass_Entry_AVX_STRCMPAVX_NO_STRCPY(Hash_Table* table, const Word* words, bool* entry, long amount)
{
    for (long i = 0; i < amount/4; i++)
    {
        Check_Entry_AVX_STRCMPAVX_NO_STRCPY(table, words + 4*i, entry + 4*i);
    }

    long i = (amount/4)*4;

    while (i < amount)
    {
        entry[i] = Check_Entry(table, &words[i]);
        i++;
    }
}

__m256i Hash_Polynom_AVX_aaa(const Word** words)
{
    __m256i pow_k = _mm256_set1_epi64x(1);
    const __m256i k = _mm256_set1_epi64x((long)31);
    const __m256i words_lengths = _mm256_set_epi64x(words[3]->word_len, words[2]->word_len, words[1]->word_len, words[0]->word_len);
    __m256i hashes = _mm256_set1_epi64x(0);
    __m256i letter_num = _mm256_set1_epi64x(0);
    const __m256i just_ones = _mm256_set1_epi64x(1);
    __m256i letters = _mm256_set_epi64x(words[3]->word_text[0], words[2]->word_text[0], words[1]->word_text[0], words[0]->word_text[0]);

    long max_len = 0;
    for (int j = 0; j < 4; j ++)
    {
        if (words[j]->word_len > max_len) max_len = words[j]->word_len;
    }

    for (int j = 0; j < max_len; j ++)
    {
        __m256i cur_letter_term = _mm256_mul_epi32(pow_k, letters);
        hashes = _mm256_add_epi64(hashes, cur_letter_term);
        pow_k = _mm256_mul_epi32(pow_k, k);

        __m256i cmp = _mm256_cmpeq_epi64(letter_num, words_lengths);
        letter_num = _mm256_add_epi64(letter_num, _mm256_add_epi64(just_ones, cmp));
        long* letter_num_array = (long*) &letter_num;
        letters = _mm256_set_epi64x(words[3]->word_text[letter_num_array[3]], words[2]->word_text[letter_num_array[2]], words[1]->word_text[letter_num_array[1]], words[0]->word_text[letter_num_array[0]]);
    }

    return hashes;
}


bool Check_Entry_ASM_hash_STRCMPAVX_NOSTRCPY(const Hash_Table* table, Word* word)
{
    long hash_list = Asm_Hash_Polynom(word)%table->hash_amount;
    Hash_Table_Node* node = table->heads[hash_list].nodes;
    bool entry = Check_List_Entry_AVX(node, table->heads[hash_list].list_length, word);

    return entry;
}


long CRC32_Hash(const Word* word)
{
    long hash = 0;
    const char* text = word->word_text;
    asm(
        R"(
            .intel_syntax noprefix
            xor rax, rax
            crc32q rax, qword ptr [%1 + 0x00]
            crc32q rax, qword ptr [%1 + 0x08]
            crc32q rax, qword ptr [%1 + 0x10]
            mov %1, rax
            .att_syntax prefix
        )"
        :"=r"(hash)
        :"r"(text)
        :"rax");
    //printf("%ld\n", hash);
    return hash;
}

bool Check_Entry_only_STRCMPAVX_NOSTRCPY(const Hash_Table* table, Word* word)
{
    long hash_list = ((*table->hash_function)(word))%table->hash_amount;
    Hash_Table_Node* node = table->heads[hash_list].nodes;
    bool entry = Check_List_Entry_AVX(node, table->heads[hash_list].list_length, word);

    return entry;
}

bool Check_Entry_ASM_CRC32_hash_STRCMPAVX_NOSTRCPY(const Hash_Table* table, Word* word)
{
    long hash_list = CRC32asm(word)%table->hash_amount;
    Hash_Table_Node* node = table->heads[hash_list].nodes;
    bool entry = Check_List_Entry_AVX(node, table->heads[hash_list].list_length, word);

    return entry;
}

//------------------------------------------------------------------------------------------------------------------------------------
void Word_Dtor(Word* word)
{
    free(word->avx_text);
    free(word->word_text);
    word->word_len = 0;
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

long Hash_Just_One(const Word* word)
{
    return 1;
}

long Hash_Ascii(const Word* word)
{
    return (long)word->word_text[0];
}

long Hash_Strlen(const Word* word)
{
    return word->word_len;
}

long Hash_Ascii_Sum(const Word* word)
{
    long sum = 0;
    for (long i = 0; i < word->word_len; i++)
    {
        sum += (long) word->word_text[i];
    }

    return sum;
}

long ROL(long num, int shift) {return (num << shift) | (num >> (sizeof(long) - shift));}
long Hash_Rol(const Word* word)
{
    long hash = 0;

    for (int i = 0; i < word->word_len; i++)
    {
        hash = ROL(hash, 1) ^ word->word_text[i];
    }

    return hash;
}

long ROR(long num, int shift) {return (num >> shift) | (num << (sizeof(long) - shift));}
long Hash_Ror(const Word* word)
{
    long hash = 0;

    for (int i = 0; i < word->word_len; i++)
    {
        hash = ROR(hash, 1) ^ word->word_text[i];
    }

    return hash;
}

long Hash_Polynom(const Word* word)
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