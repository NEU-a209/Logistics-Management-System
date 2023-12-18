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
#include "globalDeclarations.h"
#include "utilities.h"

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

struct Item items[MAX_ITEM_NUM];
struct Repository repositories[MAX_REPOSITORY_NUM];

int currentItemIndex = 2;
int currentRepositoryIndex = INITIAL_INDEX;

time_t timeStamp = NON_REALISTIC_TIMESTAMP;

int main(void) {
    // login();

    int currentMenuIndex = MAIN;

    bool isExitTriggered = false;
    while (!isExitTriggered) {
        refreshTimestamp();

        switch (currentMenuIndex) {
            case MAIN:
                currentMenuIndex = mainMenu();
                break;
            case ITEM:
                currentMenuIndex = itemMenu();
                break;
            case REPOSITORY:
                currentMenuIndex = repositoryMenu();
                break;
            case ORDER:
                currentMenuIndex = orderMenu();
                break;
        }
        isExitTriggered = (currentMenuIndex == EXIT);

        // if (isPausingRequired && !isExitTriggered)
    }
    return 0;
}

void printHeader() {
    printf("        ┌--------------------------------------┐\n");
    printf("            # Logistics Management System #      \n");
    printf("        └--------------------------------------┘\n\n");
}

void login() {
    char id[128] = {0};
    char password[128] = {0};

    printHeader();
    bool isPasswordCorrect = false;
    do {
        printf("Account：");
        scanf("%s", id);
        printf("Password：");
        scanf("%s", password);
        if (strcmp(id, "admin") == 0 && strcmp(password, "123456") == 0) {
            isPasswordCorrect = true;
        } else {
            printf("Your account name or password is wrong! \n");
            printf("Reenter your account and password. \n");
        }
    } while (!isPasswordCorrect);
    printf("\n\n\n\n\n");
}


int mainMenu() {
    printMainMenu();

    int operation;
    inputInteger(&operation);
    switch (operation) {
        case ITEM_MANAGEMENT:
            return ITEM;
        case REPOSITORY_MANAGEMENT:
            return REPOSITORY;
        case ORDER_MANAGEMENT:
            return ORDER;
        case EXIT_PROGRAM:
            return EXIT;
        case -1:
            saveData();
            return MAIN;
    }
}

int itemMenu() {

    struct Item item;

    int itemIndex;
    int repositoryIndex;

    printItemMenu();

    int operation;
    inputInteger(&operation);
    switch (operation) {
        case ADD_ITEM:
            item = constructItem(timeStamp);
            itemIndex = addItem(item);
            return ITEM;
        case DELETE_ITEM:
            inputInteger(&itemIndex);
            removeItemByIndex(itemIndex);
            return ITEM;
        case MODIFY_ITEM:
            inputInteger(&itemIndex);
            item = constructItem(items[itemIndex].timeCreated);
            *getItemByIndex(itemIndex) = item;
            return ITEM;
        case PRINT_ALL_ITEMS:
            printAllItems();
            return ITEM;
        case ADD_TO_REPOSITORY:
            inputInteger(&itemIndex);
            inputInteger(&repositoryIndex);
            addToRepository(&items[itemIndex], getRepositoryByIndex(repositoryIndex));
            return ITEM;
        case RETURN_FROM_ITEM:
            return MAIN;
        default:
            return MAIN;
    }
    pauseProgram();
    printf("\n");
}

int repositoryMenu() {

    struct Repository repository;

    int repositoryIndex;

    printRepositoryMenu();

    int operation;
    inputInteger(&operation);
    switch (operation) {
        case ADD_REPOSITORY:
            repository = constructRepository(timeStamp);
            repositoryIndex = addRepository(repository);
            pauseProgram();
            return REPOSITORY;
        case REMOVE_REPOSITORY:
            inputInteger(&repositoryIndex);
            removeRepositoryByIndex(repositoryIndex);
            pauseProgram();
            return REPOSITORY;
        case PRINT_ALL_REPOSITORY:
            printAllRepositories();
            pauseProgram();
            return REPOSITORY;
        case RETURN_FROM_REPOSITORY:
            return MAIN;
    }
    printf("\n");
}

int orderMenu() {
    pauseProgram();
}

void printMainMenu() {
    printf("\n");
    printHeader();
    printf("        ┌-------------------------------┐\n");
    printf("               #物流管理运输系统#\n");
    printf("\n");
    printf("              [0] 物品管理系统\n");
    printf("              [1] 仓储管理系统\n");
    printf("              [2] 订单管理系统\n");
    printf("              [3] 退出系统\n");
    printf("\n");
    printf("        └-------------------------------┘\n");
    printf("请选择需要的操作：");
}

void printRepositoryMenu() {
    printf("\n");
    printHeader();
    printf("        ┌-------------------------------┐\n");
    printf("               #物流管理运输系统#\n");
    printf("\n");
    printf("              [0] 增加仓库\n");
    printf("              [1] 删除仓库\n");
    printf("              [2] 修改仓库\n");
    printf("              [3] 查看所有仓库\n");
    printf("              [4] 返回主菜单\n");
    printf("\n");
    printf("        └-------------------------------┘\n");
    printf("请选择需要的操作：");
}

void printItemMenu() {
    printf("\n");
    printHeader();
    printf("        ┌-------------------------------┐\n");
    printf("               #物流管理运输系统#\n");
    printf("\n");
    printf("              [0] 增加物品\n");
    printf("              [1] 删除物品\n");
    printf("              [2] 修改物品\n");
    printf("              [3] 转移物品\n");
    printf("              [4] 查看所有物品\n");
    printf("              [5] 返回主菜单\n");
    printf("\n");
    printf("        └-------------------------------┘\n");
    printf("请选择需要的操作：");
}

void printAllItems() {
    printHeader();
    printf("\n        ┌-------------------------------┐\n");
    printf("         序号 名称       编号   类型   价格\n\n");
    for (int i = 0; i < currentItemIndex; ++i) {
        if (items[i].isRemoved) continue;
        printf("         %d   ", i);
        printItem(&items[i]);
    }
    printf("        └-------------------------------┘\n");
    printf("共%d条结果\n\n", currentItemIndex);
}

void printAllRepositories() {
    printHeader();
    printf("\n      ┌------------------------------------┐\n");
    printf("         序号 名称       编号   物品数量   创建时间\n\n");
    for (int i = 0; i < currentRepositoryIndex; ++i) {
        if (repositories[i].isRemoved) continue;
        printf("%d   ", i);
        printRepository(&repositories[i]);
    }
    printf("        └------------------------------------┘\n");
    printf("共%d条结果\n\n", currentItemIndex);
}

int addItem(struct Item item) {
    items[currentItemIndex++] = item;
    return currentItemIndex - 1; // return the index of the newly-added item
}

/*
 * in order to keep each item's index unchanged
 * and to avoid massive cost during deletion
 * and to keep code simple
 *
 * when deleting an item, we only mark the item as 'deleted'
 */

error_code removeItem(struct Item *item) {
    removeFromRepository(item);

    item->isRemoved = true;

    return SUCCEEDED;
}

error_code removeItemByIndex(int itemIndex) {
    if (itemIndex > currentItemIndex)
        return ERR_NOT_FOUND;

    removeItem(&items[itemIndex]);

    return SUCCEEDED;
}

struct Item *getItemByIndex(int itemIndex) {
    return &items[itemIndex];
}

int addRepository(struct Repository repository) {
    repositories[currentRepositoryIndex++] = repository;
    return currentRepositoryIndex - 1; // return the index of the newly-added repo
}

error_code removeRepository(struct Repository *repository) {
    repository->isRemoved = true;

    for (int i = 0; i < repository->currentInventoryIndex; ++i) {
        removeItem(repository->inventory[i]);
    }

    return SUCCEEDED;
}

error_code removeRepositoryByIndex(int repositoryIndex) {
    if (repositoryIndex > currentRepositoryIndex)
        return ERR_NOT_FOUND;

    removeRepository(&repositories[repositoryIndex]);

    return SUCCEEDED;
}

struct Repository *getRepositoryByIndex(int repositoryIndex) {
    return &repositories[repositoryIndex];
}

void pauseProgram() {
    if (SHOW_INSTRUCTIONS_ON_PAUSE)
        printf("按任意键继续...");

    getchar();
    getchar();
}

error_code addToRepository(struct Item *item, struct Repository *repo) {
    if (item->isRemoved || repo->isRemoved) return ERR_NOT_FOUND;

    if (item->currentRepository != NULL) {
        removeFromRepository(item);
    }

    item->currentRepository = repo;
    item->currentRepository->itemQuantity += 1;

    error_code errorCode = addItemToRepository(item, repo);
    if (errorCode != SUCCEEDED) return errorCode;

    struct StorageInfo storageInfo = {};
    storageInfo.repository = repo;
    storageInfo.timeIn = timeStamp;
    storageInfo.timeOut = NON_REALISTIC_TIMESTAMP;

    addStorageInfo(item, storageInfo);

    return SUCCEEDED;
}

error_code removeFromRepository(struct Item *item) {
    if (item->isRemoved) return ERR_NOT_FOUND;

    item->currentRepository->inventory[item->inventoryIndex] = NULL;
    item->storageInfo[item->currentStorageInfoIndex - 1].timeOut = timeStamp;

    item->currentRepository->itemQuantity -= 1;

    item->currentRepository = NULL;
    item->inventoryIndex = INVALID_INDEX;
    return SUCCEEDED;
}

error_code refreshTimestamp() {
    time(&timeStamp);
    return SUCCEEDED;
}

error_code saveData() {
    FILE *file = fopen("data.dat", "w");
    if (file == NULL) {
        // Handle file opening error
        perror("Error opening file\n");
        exit(EXIT_FAILURE);
    }

    // Saving items
    fprintf(file, "%d\n", currentItemIndex);
    for (int i = 0; i < currentItemIndex; ++i) {
        struct Item *pItem = getItemByIndex(i);
        fprintf(file, "%s %d %d %d\n", pItem->name, pItem->type, pItem->price, pItem->quantity);
    }

    // Saving repositories
    fprintf(file, "%d\n", currentRepositoryIndex);
    for (int i = 0; i < currentRepositoryIndex; ++i) {
        struct Repository *pRepository = getRepositoryByIndex(i);
        // todo: implement connection function
        fprintf(file, "%s %ld\n", pRepository->name, pRepository->timeCreated);
    }

    fclose(file);
    return SUCCEEDED;
}

error_code loadData() {

    return SUCCEEDED;
}

void clearScreen() {
    for (int i = 0; i < 20; ++i) {
        puts("");
    }
}

error_code clearAllData() {
    currentItemIndex = 0;
    currentRepositoryIndex = 0;
    return SUCCEEDED;
}