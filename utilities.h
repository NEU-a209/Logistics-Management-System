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


#ifndef LOGISTICS_MANAGEMENT_SYSTEM_UTILITIES_H
#define LOGISTICS_MANAGEMENT_SYSTEM_UTILITIES_H

#include "globalDeclarations.h"

struct DictTree {
    struct Item *item;
    struct DictTree *subTrees[38];
};

error_code addItemToDictionaryTree(struct Item *item, struct DictTree *dictTree);

struct DictTree *getTreeByString(const char *name, struct DictTree *dictionaryTree);

int asciiToDictionaryTreeIndex(char ascii);

void printTimestamp(time_t time);

void inputInteger(int *num);

#endif //LOGISTICS_MANAGEMENT_SYSTEM_UTILITIES_H
