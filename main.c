/*
 * THIS FILE IS CREATED UNDER THE COOPERATION OF NEU-a209.
 * GITHUB ORGANIZATION LINK:
 * https://github.com/NEU-a209
 *
 * GITHUB REPOSITORY LINK:
 * https://github.com/NEU-a209/Logistics-Management-System
 *
 * Created by Kalen Suen on 2023/12/04.
 *
 * CODE PRINCIPLES:
 * 1. NO MAGIC NUMBERS.
 * 2. DECLARATIONS AND DEFINITIONS SHOULD BE SPLIT.
 * 3. PROPER INDENTS.
 * 4. SPACE REQUIRED AROUND OPERATORS.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>


#define MAX_REPOSITORY_NAME_LENGTH  64
#define MAX_REPOSITORY_CONNECTIONS  16
#define MAX_ITEM_NAME_LENGTH        64
#define MAX_STORAGE_INFO_NUM        16
#define MAX_ITEM_NUM                8192
#define MAX_REPOSITORY_NUM          512

#define TYPE_NUM 3

#define INITIAL_INDEX        0
#define DEFAULT_PAUSING_MODE true


enum TYPE {
    NORMAL,
    FRAGILE,
    REFRIGERATION
};

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
    ERR_REPOSITORY_NOT_FOUND,
    ERR_ITEM_NOT_FOUND,
    ERR_NO_CONNECTION_FOUND
};


struct Repository;
struct Connection;
struct StorageInfo;
struct Item;

struct Connection {
    double transportationTime[TYPE_NUM];
    struct Repository *destination;
};

struct Repository {
    int index;
    char name[MAX_REPOSITORY_NAME_LENGTH];
    struct Connection connections[MAX_REPOSITORY_CONNECTIONS];
};

struct StorageInfo {
    struct Repository *repository;
    int timeIn;
    int timeOut;
};

struct Item {
    int index;
    int timeCreated;
    char name[MAX_ITEM_NAME_LENGTH];
    int type;
    struct Repository *currentRepository;
    struct StorageInfo storageInfo[MAX_STORAGE_INFO_NUM];
};


void printMenu();

void printAllItems();

void printAllRepositories();

struct Item constructItem();

struct Repository constructRepository();

int addItem(struct Item item);

int removeItem(struct Item *item);

int removeItemByIndex(int itemIndex);

struct Item *getItemByIndex(int itemIndex);

int addRepository(struct Repository repository);

int removeRepository(struct Repository *repository);

int removeRepositoryByIndex(int repositoryIndex);

struct Repository *getRepositoryByIndex(int repositoryIndex);

void pauseProgram();


struct Item items[MAX_ITEM_NUM];
struct Repository repositories[MAX_REPOSITORY_NUM];

int currentItemIndex = INITIAL_INDEX;
int currentRepositoryIndex = INITIAL_INDEX;


int main(void) {
    bool isExitTriggered = false;
    bool isPausingRequired = DEFAULT_PAUSING_MODE;
    while (!isExitTriggered) {
        printMenu();

        int operation;
        scanf("%d", &operation); // NOLINT(*-err34-c)

        struct Item item;
        struct Repository repository;

        struct Item *itemPointer;
        struct Repository *repositoryPointer;

        int itemIndex;
        int repositoryIndex;

        switch (operation) {
            case ADD_ITEM:
                item = constructItem();
                itemIndex = addItem(item);
                break;
            case REMOVE_ITEM:
                scanf("%d", &itemIndex); // NOLINT(*-err34-c)
                itemPointer = getItemByIndex(itemIndex);
                removeItem(itemPointer);
                break;
            case MODIFY_ITEM:
                scanf("%d", &itemIndex); // NOLINT(*-err34-c)
                item = constructItem();
                *getItemByIndex(itemIndex) = item;
                break;
            case PRINT_ALL_ITEMS:
                printAllItems();
                break;
            case EXIT_PROGRAM:
                isExitTriggered = true;
                break;
            case ADD_REPOSITORY:
                repository = constructRepository();
                repositoryIndex = addRepository(repository);
                break;
            case REMOVE_REPOSITORY:
                scanf("%d", &repositoryIndex); // NOLINT(*-err34-c)
                repositoryPointer = getRepositoryByIndex(repositoryIndex);
                removeRepository(repositoryPointer);
                break;
            case PRINT_ALL_REPOSITORY:
                printAllRepositories();
                break;
            case TOGGLE_PAUSING:
                isPausingRequired = !isPausingRequired;
                break;
            default:
                break;
        }
        if (isPausingRequired) pauseProgram();
    }
}

void printMenu() {
    printf("欢迎来到物流信息管理系统……\n");
    printf("1: 添加货物\n");
    printf("2: 删除货物\n");
    printf("3: 修改货物\n");
    printf("4: 查看所有货物\n");
    printf("5: 退出程序\n");
    printf("请选择需要的操作：\n");
}