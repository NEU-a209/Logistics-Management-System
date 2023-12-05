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
#include <stdbool.h>

#define INITIAL_INDEX              0
#define DEFAULT_PAUSING_MODE       true
#define SHOW_INSTRUCTIONS_ON_PAUSE true

enum OPERATION {
    ADD_ITEM,
    REMOVE_ITEM,
    MODIFY_ITEM,
    PRINT_ALL_ITEMS,
    ADD_REPOSITORY,
    REMOVE_REPOSITORY,
    PRINT_ALL_REPOSITORY,
    TOGGLE_PAUSING,
    EXIT_PROGRAM
};

enum ERROR_CODE {
    SUCCEEDED,
    ERR_NOT_FOUND,
    PRINTER_ON_FIRE
};


void printMenu();

void printAllItems();

void printAllRepositories();

int addItem(struct Item item);

int removeItem(struct Item *item);

int removeItemByIndex(int itemIndex);

struct Item *getItemByIndex(int itemIndex);

int addRepository(struct Repository repository);

int removeRepository(struct Repository *repository);

int removeRepositoryByIndex(int repositoryIndex);

struct Repository *getRepositoryByIndex(int repositoryIndex);

void pauseProgram();

#endif //LOGISTICS_MANAGEMENT_SYSTEM_SERVER_H
