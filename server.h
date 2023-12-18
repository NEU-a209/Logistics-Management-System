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
#define MAX_TOKEN_NUM              2048

enum MANU_INDEX {
    MAIN,
    ITEM,
    REPOSITORY,
    ORDER,
    EXIT
};

enum MAIN_MANU_OPERATIONS {
    ITEM_MANAGEMENT,
    REPOSITORY_MANAGEMENT,
    ORDER_MANAGEMENT,
    EXIT_PROGRAM,
};

enum ITEM_MANAGEMENT {
    ADD_ITEM,
    DELETE_ITEM,
    MODIFY_ITEM,
    ADD_TO_REPOSITORY,
    PRINT_ALL_ITEMS,
    RETURN_FROM_ITEM
};

enum REPOSITORY_MANAGEMENT {
    ADD_REPOSITORY,
    REMOVE_REPOSITORY,
    PRINT_ALL_REPOSITORY,
    REMOVE_FROM_REPOSITORY,
    RETURN_FROM_REPOSITORY
};

bool verify();

void printHeader();

void clearScreen();

void getToken();

void login();

void printMainMenu();

void printItemMenu();

void printRepositoryMenu();

int mainMenu();

int itemMenu();

int repositoryMenu();

int orderMenu();

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

error_code addToRepository(struct Item *item, struct Repository *repo);

error_code removeFromRepository(struct Item *item);

error_code refreshTimestamp();

error_code saveData();

void clearScreen();

error_code loadData();

error_code clearAllData();

unsigned int customHash(const char *text);

void getToken();

bool verifyToken(const char *text);

error_code addToken();

#endif //LOGISTICS_MANAGEMENT_SYSTEM_SERVER_H
