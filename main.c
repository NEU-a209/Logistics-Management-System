//
// Created by Kalen Suen on 2023/12/4.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define MAX_REPOSITORY_NAME_LENGTH  64
#define MAX_REPOSITORY_CONNECTIONS  16
#define MAX_ITEM_NAME_LENGTH        64
#define MAX_STORAGE_INFO_NUM        16
#define MAX_ITEM_NUM                8192
#define MAX_REPOSITORY_NUM          512

#define TYPE_NUM 3

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

int addItem(struct Item item);

int removeItem(struct Item *item);

int removeItemByIndex(int itemIndex);

struct Item *getItemByIndex(int itemIndex);

int addRepository(struct Repository repository);

int removeRepository(struct Repository *repository);

int removeRepositoryByIndex(int repositoryIndex);

struct Repository *getRepositoryByIndex(int repositoryIndex);


struct Item items[MAX_ITEM_NUM];
struct Repository repositories[MAX_REPOSITORY_NUM];

int currentItemIndex = 0;
int currentRepositoryIndex = 0;

int main(void) {
    bool isExitTriggered = false;
    while (!isExitTriggered) {
        printMenu();

        int operation;
        scanf("%d", &operation); // NOLINT(*-err34-c)

        switch (operation) {
            case ADD_ITEM:
                break;
            case REMOVE_ITEM:
                break;
            case MODIFY_ITEM:
                break;
            case PRINT_ALL_ITEMS:
                break;
            case EXIT_PROGRAM:
                isExitTriggered = true;
                break;
            case ADD_REPOSITORY:
                break;
            case REMOVE_REPOSITORY:
                break;
            case PRINT_ALL_REPOSITORY:
                break;
            default:
                break;
        }
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