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


#include "repository.h"
#include "globalDeclarations.h"
#include "stdio.h"

struct Repository constructRepository(time_t timeCreated) {
    struct Repository repo = {};

    // inquire user to input info here
    // and to construct a repo object

    return repo;
}

void printRepository(struct Repository *repository) {
    if (repository->isRemoved) {
        return;
    }
    // print info about repository
}

int addItemToRepository(struct Item *item, struct Repository *repository) {
    if (repository->currentInventoryIndex == MAX_INVENTORY_SIZE) return ERR_DATA_OVERFLOW;

    repository->inventory[repository->currentInventoryIndex++] = item;
    item->inventoryIndex = repository->currentInventoryIndex - 1;

    return SUCCEEDED;
}

void printInventory(struct Repository *repository) {
    for (int i = 0; i < repository->currentInventoryIndex; ++i) {
        if (repository->inventory[i]->isRemoved) continue;
        printItem(repository->inventory[i]);
    }
}
