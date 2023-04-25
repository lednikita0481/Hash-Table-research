OUTPUT_FILE_NAME = main

CC = g++
CFLAGS = -mavx2 -msse3 -O3 -fno-omit-frame-pointer -no-pie -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -D_DEBUG -D_EJUDGE_CLIENT_SIDE


SRC_DIR = ./src/
OBJ_DIR = ./obj/

SRCC = Hash_Tables.cpp File_String.cpp main.cpp 
SRC_ASM = asm_hash_func.s CRC32.s
OBJ = $(patsubst %.cpp, $(OBJ_DIR)%.o, $(SRCC))
OBJ_ASM = $(patsubst %.s, $(OBJ_DIR)%.o, $(SRC_ASM))

all: just_do_it

just_do_it: $(OBJ) $(OBJ_ASM)
				$(CC) $(CFLAGS) $^ -o $(OUTPUT_FILE_NAME)
				./main

$(OBJ_DIR)%.o: $(SRC_DIR)%.s
				mkdir -p obj
				nasm -f elf64 $^ -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
				mkdir -p obj
				$(CC) $(IFLAGS) $(CFLAGS) -c $^ -o $@

clear:
				rm -f $(OBJ_DIR)*.o