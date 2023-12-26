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
unsigned int tokens[MAX_TOKEN_NUM];


int currentItemIndex = INITIAL_INDEX;
int currentRepositoryIndex = INITIAL_INDEX;
int currentTokenIndex = INITIAL_INDEX;

time_t timeStamp = NON_REALISTIC_TIMESTAMP;

int main(void) {
    loadData();

/*
    printf("1: 登陆\n2: 注册\n输入你的选择: ");
    int operation = 0;
    inputInteger(&operation);
    if (operation == 1) login();
    else if (operation == 2) {
        getToken();
        login();
    }
    puts("");*/


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

    saveData();
    return 0;
}

void printHeader() {
    printf("        ┌--------------------------------------┐\n");
    printf("            # Logistics Management System #      \n");
    printf("        └--------------------------------------┘\n\n");
}

error_code addToken(const char *ch) {
    if (currentItemIndex == MAX_TOKEN_NUM)
        return ERR_DATA_OVERFLOW;
    unsigned int hashedToken = customHash(ch);
    tokens[currentTokenIndex++] = hashedToken;
    return SUCCEEDED;
}

bool verifyToken(const char *ch) {
    unsigned int hashToken = customHash(ch);
    for (int i = 0; i < currentTokenIndex; ++i) {
        if (tokens[i] == hashToken) return true;
    }
    return false;
}

void getToken() {
    printHeader();
    int num;
    srand(time(0));   //防止伪随机数 时间复杂度
    char node[7];     //node[6]='\0';
    char node_[7];
    char eng[36] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                    'Y', 'Z', '0', '1', '2', '3', '4', '5',
                    '6', '7', '8', '9'};
    for (int i = 0; i < 6; i++) {
        num = rand() % 34;
        node[i] = eng[num];  //验证码
    }
    node[6] = '\0';     //解决bug

    printf("你的Token为:%s    ", node);

    printf("请输入验你的Token:");
    scanf("%s", node_);
    if (strcmp(node, node_) == 0) {
        printf("注册成功，请记住你的Token!!!\n");
        addToken(node);
    } else {
        printf("注册失败!!!\n");
    }
}

bool verify() {
    int num;
    srand(time(0));   //防止伪随机数 时间复杂度
    char node[7];     //node[6]='\0';
    char node_[7];
    char eng[62] = {'A', 'B', 'C', 'D', 'E', 'F', 'G',
                    'H', 'I', 'J', 'K', 'L', 'M', 'N',
                    'O', 'P', 'Q', 'R', 'S', 'T', 'U',
                    'V', 'W', 'X', 'Y', 'Z', '0', '1',
                    '2', '3', '4', '5', '6', '7', '8',
                    '9', 'a', 'b', 'c', 'd', 'e', 'f',
                    'g', 'h', 'i', 'j', 'k', 'l', 'm',
                    'n', 'o', 'p', 'q', 'r', 's', 't',
                    'u', 'v', 'w', 'x', 'y', 'z'};
    for (int i = 0; i < 6; i++) {
        num = rand() % 60;
        node[i] = eng[num];  //验证码
    }
    node[6] = '\0';     //解决bug

    printf("验证码为:%s    ", node);

    printf("请输入验证码:");
    scanf("%s", node_);
    if (strcmp(node, node_) == 0) {
        printf("验证成功!!!\n");
        return true;
    } else {
        printf("验证失败!!!\n");
        return false;
    }
}

void login() {
    char token[128] = {0};

    printHeader();
    bool isPasswordCorrect = false;
    do {
        printf("Token：");
        scanf("%s", token);

        if (verifyToken(token)) {
            if (verify()) {
                isPasswordCorrect = true;
            }
        } else {
            printf("Your Token is wrong! \n");
            printf("Reenter your Token. \n");
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
        case -2:
            loadData();
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
            int repoIndex = 0;
            printf("Enter the item repository index: ");
            inputInteger(&repoIndex);
            puts("");
            addToRepository(&item, getRepositoryByIndex(repoIndex), timeStamp);
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
            pauseProgram();
            return ITEM;
        case ADD_TO_REPOSITORY:
            printf("Enter the item index to transfer: ");
            inputInteger(&itemIndex);
            puts("");
            printf("Enter the target repository index: ");
            inputInteger(&repositoryIndex);
            puts("");
            addToRepository(getItemByIndex(itemIndex),
                            getRepositoryByIndex(repositoryIndex),
                            timeStamp);

            return ITEM;
        case RETURN_FROM_ITEM:
            return MAIN;
        default:
            return ITEM;
    }
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
            repository.index = repositoryIndex;
            pauseProgram();
            return REPOSITORY;
        case REMOVE_REPOSITORY:
            printf("Enter repository index to remove: ");
            inputInteger(&repositoryIndex);
            puts("");
            removeRepositoryByIndex(repositoryIndex);
            pauseProgram();
            return REPOSITORY;
        case PRINT_ALL_REPOSITORY:
            printAllRepositories();
            pauseProgram();
            return REPOSITORY;
        case PRINT_REPOSITORY_ITEMS:
            printf("Enter repository index to display: ");
            inputInteger(&repositoryIndex);
            puts("");
            printRepositoryItems(getRepositoryByIndex(repositoryIndex));
            pauseProgram();
            return REPOSITORY;
        case RETURN_FROM_REPOSITORY:
            return MAIN;
    }
    printf("\n");
}

int orderMenu() {
    printf("输入物品id以查询物流信息: ");
    int itemID;
    inputInteger(&itemID);
    printStorageInfoList(getItemByIndex(itemID)->storageInfoList);
    pauseProgram();
    return MAIN;
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
    printf("              [2] 列出仓库\n");
    printf("              [3] 查看仓库\n");
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

    // todo: print the current repository index of the displayed item

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
    printf("\n        ┌------------------------------------┐\n");
    printf("         序号 名称       编号   物品数量   创建时间\n\n");
    for (int i = 0; i < currentRepositoryIndex; ++i) {
        if (repositories[i].isRemoved) continue;
        printf("         %d   ", i);
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

error_code addToRepository(struct Item *item, struct Repository *repo, time_t time) {
    if (item->isRemoved || repo->isRemoved) return ERR_NOT_FOUND;

    if (item->currentRepository != NULL) {
        removeFromRepository(item);
    }

    item->currentRepository = repo;
    item->currentRepository->itemQuantity += 1;

    error_code errorCode = addItemToRepository(item, repo);
    if (errorCode != SUCCEEDED) return errorCode;

    if (time != -1) {
        struct StorageInfo storageInfo = {};
        storageInfo.repository = repo;
        storageInfo.timeIn = time;

        addStorageInfo(item, storageInfo);
    }

    return SUCCEEDED;
}

error_code removeFromRepository(struct Item *item) {
    if (item->isRemoved) return ERR_NOT_FOUND;

    item->currentRepository->inventory[item->inventoryIndex] = NULL;

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
        return ERR_UNABLE_TO_HANDLE;
    }

    // Saving repositories
    fprintf(file, "%d\n", currentRepositoryIndex);
    for (int i = 0; i < currentRepositoryIndex; ++i) {
        struct Repository *pRepository = getRepositoryByIndex(i);
        fprintf(file, "%s %ld %d\n", pRepository->name, pRepository->timeCreated, (int) pRepository->isRemoved);
    }

    // Saving items
    fprintf(file, "%d\n", currentItemIndex);
    for (int i = 0; i < currentItemIndex; ++i) {
        struct Item *pItem = getItemByIndex(i);
        fprintf(file, "%s %d %d %d %d %d\n", pItem->name, pItem->type, pItem->price, pItem->quantity, pItem->isRemoved,
                pItem->currentRepository->index);

        // Save StorageInfo linked list for each item
        fprintf(file, "%d\n", pItem->currentStorageInfoIndex);
        struct StorageInfoNode *storageInfoNode = pItem->storageInfoList;
        while (storageInfoNode != NULL) {
            fprintf(file, "%d %ld ", storageInfoNode->storageInfo.repository->index,
                    storageInfoNode->storageInfo.timeIn);
            storageInfoNode = storageInfoNode->next;
        }
        fprintf(file, "\n");
    }

    // Saving hashed tokens
    fprintf(file, "%d\n", currentTokenIndex);
    for (int i = 0; i < currentTokenIndex; ++i) {
        fprintf(file, "%ud\n", tokens[i]);
    }

    fclose(file);
    return SUCCEEDED;
}

error_code loadData() {
    clearAllData();

    FILE *file = fopen("data.dat", "r");
    if (file == NULL) {
        // Handle file opening error
        perror("Error opening file\n");
        return ERR_UNABLE_TO_HANDLE;
    }

    int numItems = 0;
    int numRepos = 0;
    int numTokens = 0;

    // Loading repositories
    fscanf(file, "%d\n", &numRepos);
    for (int i = 0; i < numRepos; ++i) {
        struct Repository repository = {};
        fscanf(file, "%s %ld", repository.name, &repository.timeCreated);
        int isRemoved;
        fscanf(file, "%d", &isRemoved);
        repository.isRemoved = (bool) isRemoved;
        repository.index = i;

        addRepository(repository);
    }

    // Loading items
    fscanf(file, "%d\n", &numItems);
    for (int i = 0; i < numItems; ++i) {
        struct Item item = {};
        int currentRepoIndex = 0;
        fscanf(file, "%s %d %d %d %d %d", item.name, &item.type, &item.price, &item.quantity, &item.isRemoved,
               &currentRepoIndex);

        item.currentRepository = getRepositoryByIndex(currentRepoIndex);
        // Load StorageInfo linked list for each item
        int numStorageInfo;
        fscanf(file, "%d", &numStorageInfo);
        for (int j = 0; j < numStorageInfo; ++j) {
            struct StorageInfo storageInfo = {};
            int repoIndex = 0;
            fscanf(file, "%d %ld", &repoIndex, &storageInfo.timeIn);
            storageInfo.repository = getRepositoryByIndex(repoIndex);
            addStorageInfo(&item, storageInfo);
        }

        addToRepository(&item, getRepositoryByIndex(item.currentRepository->index), -1);
        addItem(item);
    }

    // Loading tokens
    fscanf(file, "%d\n", &numTokens);
    for (int i = 0; i < numTokens; ++i) {
        fscanf(file, "%ud", &tokens[currentTokenIndex++]);
    }

    fclose(file);
    return SUCCEEDED;
}

void clearScreen() {
    for (int i = 0; i < 20; ++i) {
        puts("");
    }
}

error_code clearAllData() {
    currentItemIndex = INITIAL_INDEX;
    currentRepositoryIndex = INITIAL_INDEX;
    currentTokenIndex = INITIAL_INDEX;
    return SUCCEEDED;
}

unsigned int customHash(const char *text) {
    unsigned int hash = 0;
    while (*text != '\0') {
        hash = (hash * 281 ^ *text * 997) & 0xFFFFFFFF;
        text++;
    }
    return hash;
}

// todo: add titles and stuff
void printRepositoryItems(struct Repository *repository) {
    for (int i = 0; i < repository->currentInventoryIndex; ++i) {
        if (repository->inventory[i] != NULL)
            printItem(repository->inventory[i]);
    }
}

// Function to print the linked list of StorageInfo nodes
void printStorageInfoList(struct StorageInfoNode *storageInfoNode) {
    printf("Storage Information:\n");

    while (storageInfoNode != NULL) {
        printf("Repository: %s, Time In: %lld\n",
               storageInfoNode->storageInfo.repository->name,
               (long long) storageInfoNode->storageInfo.timeIn);

        storageInfoNode = storageInfoNode->next;
    }
}