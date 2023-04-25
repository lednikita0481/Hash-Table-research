# Laboratory work. Hash functions research and Hash table optimisation.

## Goals:
- To implement a hash table
- To test several hash functions for distribution uniformity
- To research the hash table and implement at least 3 optimisations different ways

## Tools
Laptop Honor Magicbook 15 with AMD Ryzen™ 5 5500U, Linux Mint x64 OS, perf, g++ compiler, NASM assembly.

## Theory reference
**Hash table** is a data structure. It stores all its elements as a pair of key and value. Key is a unique number for value indexing. 
Hash table has several lists, in wich data is stored. List number is calculated with **hash function**. It takes the key and return the list number, in wich we store the value.

If hash function returns a number of already used list for a new value, **collision** occures. Such situations can be handled different ways. I used chain method.
The idea of it is that elements with the same hash are stored in linked list:
<img src="Optimisation/graphs/hash table.jpeg">

If we use good hash function, it returns different list number for different keys, so data becomes distributed uniformly across the table. In this way, 
hash table becomes a useful instrument to insert or find a value quickly. First part of my work is exactly researching some different hash functions.

## Part 1. Hash functions research

To show the result in undestandable form, I will make graphs of the dependance of the collisions amount on list number fo every of analyzed function.
<img src="No optimisation/graphs/graphs.png">

### 1. Returns 1
You can hardly ever imagine hash function worse then this. It vanishes all the sence of hash table. Was implemented only for educational purposes.
~~~C++
long Hash_Just_One(const Word* word)
{
    return 1;
}
~~~

### 2. First letter ASCII code
This function returns just the ASCII code of the first letter. Really bad function.
~~~C++
long Hash_Ascii(const Word* word)
{
    return (long)word->word_text[0];
}
~~~
