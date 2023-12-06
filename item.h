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


#ifndef LOGISTICS_MANAGEMENT_SYSTEM_ITEM_H
#define LOGISTICS_MANAGEMENT_SYSTEM_ITEM_H

#include "stdbool.h"
#include "globalDeclarations.h"


struct Item constructItem(time_t time);

error_code addStorageInfo(struct Item *item, struct StorageInfo storageInfo);

#endif //LOGISTICS_MANAGEMENT_SYSTEM_ITEM_H
