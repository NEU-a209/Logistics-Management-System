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

#include <stdio.h>
#include <stdbool.h>
#include <time.h>

struct Item items[MAX_ITEM_NUM];
struct Repository repositories[MAX_REPOSITORY_NUM];

int currentItemIndex = INITIAL_INDEX;
int currentRepositoryIndex = INITIAL_INDEX;

time_t timeStamp = NON_REALISTIC_TIMESTAMP;

int main(void) {
    bool isExitTriggered = false;
    bool isPausingRequired = DEFAULT_PAUSING_MODE;
    while (!isExitTriggered) {
        printMenu();

        int operation;
        inputInteger(&operation);

        struct Item item;
        struct Repository repository;

        struct Item *itemPointer;
        struct Repository *repositoryPointer;

        int itemIndex;
        int repositoryIndex;

        switch (operation) {
            case ADD_ITEM:
                item = constructItem(timeStamp);
                itemIndex = addItem(item);
                break;
            case DELETE_ITEM:
                inputInteger(&itemIndex);
                removeItemByIndex(itemIndex);
                break;
            case MODIFY_ITEM:
                inputInteger(&itemIndex);
                item = constructItem(items[itemIndex].timeCreated);
                *getItemByIndex(itemIndex) = item;
                break;
            case PRINT_ALL_ITEMS:
                printAllItems();
                break;
            case EXIT_PROGRAM:
                isExitTriggered = true;
                break;
            case ADD_REPOSITORY:
                repository = constructRepository(timeStamp);
                repositoryIndex = addRepository(repository);
                break;
            case REMOVE_REPOSITORY:
                inputInteger(&repositoryIndex);
                removeRepositoryByIndex(repositoryIndex);
                break;
            case PRINT_ALL_REPOSITORY:
                printAllRepositories();
                break;
            case TOGGLE_PAUSING:
                isPausingRequired = !isPausingRequired;
                break;
            case ADD_TO_REPOSITORY:
                inputInteger(&itemIndex);
                inputInteger(&repositoryIndex);
                addToRepository(&items[itemIndex], &repositories[repositoryIndex]);
                break;
            case REMOVE_FROM_REPOSITORY:
                inputInteger(&itemIndex);

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
    for (int i = 0; i < currentItemIndex; ++i) {
        if (items[i].isRemoved) continue;
        printItem(&items[i]);
    }
}

void printAllRepositories() {
    for (int i = 0; i < currentRepositoryIndex; ++i) {
        if (repositories[i].isRemoved) continue;
        printRepository(&repositories[i]);
    }
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

void inputInteger(int *num) {
    while (true) {
        if (scanf("%d", num) == 1) { // NOLINT(*-err34-c)
            break;
        } else {
            while (getchar() != '\n');
            printf("Invalid input. Please enter a number.\n");
        }
    }
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