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

#ifndef LOGISTICS_MANAGEMENT_SYSTEM_REPOSITORY_H
#define LOGISTICS_MANAGEMENT_SYSTEM_REPOSITORY_H

#include "stdbool.h"
#include "globalDeclarations.h"

#define MAX_REPOSITORY_NAME_LENGTH  64
#define MAX_REPOSITORY_CONNECTIONS  16
#define MAX_REPOSITORY_NUM          512
#define MAX_INVENTORY_SIZE          1024

#define TYPE_NUM 3


struct Connection {
    double transportationTime[TYPE_NUM];
    struct Repository *destination;
};

struct Repository {
    int index;
    time_t timeCreated;
    int itemQuantity;
    char name[MAX_REPOSITORY_NAME_LENGTH];
    bool isRemoved;
    struct Connection connections[MAX_REPOSITORY_CONNECTIONS];
    struct Item *inventory[MAX_INVENTORY_SIZE];
    int currentInventoryIndex;
};


struct Repository constructRepository(time_t time);

void printRepository(struct Repository *repository);

error_code addItemToRepository(struct Item *item, struct Repository *repo);

void printInventory(struct Repository *repository);

#endif //LOGISTICS_MANAGEMENT_SYSTEM_REPOSITORY_H
