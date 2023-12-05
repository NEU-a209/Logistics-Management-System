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

#include "server.h"
#include "item.h"
#include "repository.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>

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
        if (isPausingRequired && !isExitTriggered) pauseProgram();
    }
    return 0;
}

void printMenu() {
    printf("物流信息管理系统\n");
    printf("1: 添加货物\n");
    printf("2: 删除货物\n");
    printf("3: 修改货物\n");
    printf("4: 查看所有货物\n");
    printf("5: 退出程序\n");
    printf("请选择需要的操作：");
}

void printAllItems() {

}

void printAllRepositories() {

}

int addItem(struct Item item) {
    return currentItemIndex;
}

int removeItem(struct Item *item) {
    return SUCCEEDED;
}

int removeItemByIndex(int itemIndex) {
    if (itemIndex > currentItemIndex)
        return ERR_NOT_FOUND;
    return SUCCEEDED;
}

struct Item *getItemByIndex(int itemIndex) {

}

int addRepository(struct Repository repository) {
    return SUCCEEDED;
}

int removeRepository(struct Repository *repository) {
    return SUCCEEDED;
}

int removeRepositoryByIndex(int repositoryIndex) {
    if (repositoryIndex > currentRepositoryIndex)
        return ERR_NOT_FOUND;
    return SUCCEEDED;
}

struct Repository *getRepositoryByIndex(int repositoryIndex) {

}

void pauseProgram() {
    if (SHOW_INSTRUCTIONS_ON_PAUSE)
        printf("按任意键继续...");

    getchar();
    getchar();
}