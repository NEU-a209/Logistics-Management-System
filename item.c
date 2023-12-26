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
#include <stdlib.h>


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

// Update the addStorageInfo function to add a new node to the linked list
error_code addStorageInfo(struct Item *item, struct StorageInfo storageInfo) {
    // Create a new node
    struct StorageInfoNode *newNode = malloc(sizeof(struct StorageInfoNode));
    if (newNode == NULL) {
        // Handle memory allocation error
        return ERR_UNABLE_TO_HANDLE;
    }

    // Initialize the new node
    newNode->storageInfo = storageInfo;
    newNode->next = NULL;

    // Add the new node to the linked list
    if (item->storageInfoList == NULL) {
        // If the list is empty, set the new node as the head
        item->storageInfoList = newNode;
    } else {
        // Otherwise, find the last node and append the new node
        struct StorageInfoNode *lastNode = item->storageInfoList;
        while (lastNode->next != NULL) {
            lastNode = lastNode->next;
        }
        lastNode->next = newNode;
    }

    // Increment the storage info index (optional, if needed)
    item->currentStorageInfoIndex++;

    return SUCCEEDED;
}
