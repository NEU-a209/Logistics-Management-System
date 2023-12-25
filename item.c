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
#include "utilities.h"
#include "repository.h"

#include <stdio.h>


struct Item constructItem(time_t timeCreated) {
    struct Item item = {};

    printf("Enter the item name: ");
    scanf("%s", item.name);
    puts("");


    printf("Enter the item type: ");
    inputInteger(&item.type);
    puts("");

    printf("Enter the item price: ");
    inputInteger(&item.price);
    puts("");

    printf("Enter the item quantity: ");
    inputInteger(&item.quantity);
    puts("");

    // inquire user to input info here
    // and to construct an item object

    return item;
}

void printItem(struct Item *item) {
    if (item->isRemoved) {
        return;
    }
    printf("%-10s%-6d%-6d%-6d%-8s\n\n", item->name, item->index, item->type, item->price, item->currentRepository->name);

}

error_code addStorageInfo(struct Item *item, struct StorageInfo storageInfo) {
    if (item->currentStorageInfoIndex == MAX_STORAGE_INFO_NUM) return ERR_DATA_OVERFLOW;
    item->storageInfo[item->currentStorageInfoIndex++] = storageInfo;
    return SUCCEEDED;
}