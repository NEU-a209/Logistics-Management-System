//
// Created by Kalen Suen on 2023/12/7.
//

#ifndef LOGISTICS_MANAGEMENT_SYSTEM_GLOBAL_DECLARATIONS_H
#define LOGISTICS_MANAGEMENT_SYSTEM_GLOBAL_DECLARATIONS_H

#include "time.h"

#define MAX_ITEM_NUM              8192
#define MAX_ITEM_NAME_LENGTH      64
#define MAX_STORAGE_INFO_NUM      16

#define INVALID_INDEX (-1)

#define error_code int

enum TYPE {
    NORMAL,
    FRAGILE,
    REFRIGERATION
};

enum ERROR_CODE {
    SUCCEEDED,
    ERR_NOT_FOUND,
    ERR_UNABLE_TO_HANDLE,
    ERR_DATA_OVERFLOW,
    ERR_PRINTER_ON_FIRE
};

struct StorageInfo {
    struct Repository *repository;
    time_t timeIn;
    time_t timeOut;
};

struct Item {
    int index;
    int inventoryIndex;
    time_t timeCreated;
    char name[MAX_ITEM_NAME_LENGTH];
    int type;
    bool isRemoved;
    struct Repository *currentRepository;
    struct StorageInfo storageInfo[MAX_STORAGE_INFO_NUM];
    int currentStorageInfoIndex;
};

void printItem(struct Item *item);

#endif //LOGISTICS_MANAGEMENT_SYSTEM_GLOBAL_DECLARATIONS_H
