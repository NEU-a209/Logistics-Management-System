/*
 * THIS FILE IS CREATED UNDER THE COOPERATION OF NEU-a209.
 * GITHUB ORGANIZATION LINK:
 * https://github.com/NEU-a209
 *
 * GITHUB REPOSITORY LINK:
 * https://github.com/NEU-a209/Logistics-Management-System
 *
 * Created by Kalen Suen on 2023/12/05.
 */

#ifndef LOGISTICS_MANAGEMENT_SYSTEM_SERVER_H
#define LOGISTICS_MANAGEMENT_SYSTEM_SERVER_H

#include "item.h"
#include "repository.h"
#include "globalDeclarations.h"
#include <stdbool.h>


#define INITIAL_INDEX              0
#define DEFAULT_PAUSING_MODE       true
#define SHOW_INSTRUCTIONS_ON_PAUSE true
#define NON_REALISTIC_TIMESTAMP    1000


enum OPERATION {
    ADD_ITEM,
    DELETE_ITEM,
    MODIFY_ITEM,
    PRINT_ALL_ITEMS,
    ADD_REPOSITORY,
    REMOVE_REPOSITORY,
    PRINT_ALL_REPOSITORY,
    TOGGLE_PAUSING,
    ADD_TO_REPOSITORY,
    REMOVE_FROM_REPOSITORY,
    EXIT_PROGRAM
};



void printMenu();

void printAllItems();

void printAllRepositories();

int addItem(struct Item item);

error_code removeItem(struct Item *item);

error_code removeItemByIndex(int itemIndex);

struct Item *getItemByIndex(int itemIndex);

int addRepository(struct Repository repository);

error_code removeRepository(struct Repository *repository);

error_code removeRepositoryByIndex(int repositoryIndex);

struct Repository *getRepositoryByIndex(int repositoryIndex);

void pauseProgram();

void inputInteger(int *num);

error_code addToRepository(struct Item *item, struct Repository *repo);

error_code removeFromRepository(struct Item *item);

error_code refreshTimestamp();

#endif //LOGISTICS_MANAGEMENT_SYSTEM_SERVER_H
