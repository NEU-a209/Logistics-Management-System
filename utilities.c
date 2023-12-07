/*
 * THIS FILE IS CREATED UNDER THE COOPERATION OF NEU-a209.
 * GITHUB ORGANIZATION LINK:
 * https://github.com/NEU-a209
 *
 * GITHUB REPOSITORY LINK:
 * https://github.com/NEU-a209/Logistics-Management-System
 *
 * Created by Kalen Suen on 2023/12/07.
 */

#include "time.h"
#include "globalDeclarations.h"
#include "utilities.h"

#include "stdio.h"
#include "ctype.h"
#include "stdlib.h"

error_code addItemToDictionaryTree(const struct Item *item, struct DictionaryTree *dictionaryTree) {
    for (int i = 0; i < MAX_ITEM_NAME_LENGTH, item->name[i] != '\0'; ++i) {
        int index = asciiToDictionaryTreeIndex(item->name[i]);
        if (dictionaryTree->subTrees[index]) {
            dictionaryTree = dictionaryTree->subTrees[index];
        } else {
            struct DictionaryTree *newSubTree = malloc(sizeof(struct DictionaryTree));
            if (!newSubTree) {
                return ERR_UNABLE_TO_HANDLE;
            }
            newSubTree->item = NULL;  // Initialize item to NULL
            for (int j = 0; j < 38; ++j) {
                newSubTree->subTrees[j] = NULL;
            }
            dictionaryTree->subTrees[index] = newSubTree;
            dictionaryTree = newSubTree;
        }
    }
    dictionaryTree->item = item;
    return SUCCEEDED;
}

struct DictionaryTree *getTreeByString(const char *name, struct DictionaryTree *dictionaryTree) {
    for (int i = 0; i < MAX_ITEM_NAME_LENGTH, name[i] != '\0'; ++i) {
        int index = asciiToDictionaryTreeIndex(name[i]);
        if (dictionaryTree->subTrees[index] == NULL)
            return (struct DictionaryTree *) NULL;
        dictionaryTree = dictionaryTree->subTrees[index];
    }
    return dictionaryTree;
}

int asciiToDictionaryTreeIndex(char ascii) {
    if (isdigit(ascii)) return ascii - '0';
    if (ascii == ' ') return 37;
    if (isupper(ascii)) tolower(ascii);
    return ascii - 'a' + 10;
}

void printTimestamp(time_t time) {
    struct tm *localTime = localtime(&time);

    printf("当前时间: %s\n", asctime(localTime));
}