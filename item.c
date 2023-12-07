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


#include "item.h"
#include "globalDeclarations.h"

struct Item constructItem(time_t timeCreated) {
    struct Item item = {};

    // inquire user to input info here
    // and to construct a item object

    return item;
}

void printItem(struct Item *item) {
    if (item->isRemoved) {
        return;
    }
    // print info about item
}

error_code addStorageInfo(struct Item *item, struct StorageInfo storageInfo) {
    if (item->currentStorageInfoIndex == MAX_STORAGE_INFO_NUM) return ERR_DATA_OVERFLOW;
    item->storageInfo[item->currentStorageInfoIndex++] = storageInfo;
    return SUCCEEDED;
}