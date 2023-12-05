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

#define MAX_ITEM_NUM              8192
#define MAX_ITEM_NAME_LENGTH      64
#define MAX_STORAGE_INFO_NUM      16


enum TYPE {
    NORMAL,
    FRAGILE,
    REFRIGERATION
};


struct StorageInfo {
    struct Repository *repository;
    int timeIn;
    int timeOut;
};

struct Item {
    int index;
    int timeCreated;
    char name[MAX_ITEM_NAME_LENGTH];
    int type;
    struct Repository *currentRepository;
    struct StorageInfo storageInfo[MAX_STORAGE_INFO_NUM];
};

struct Item constructItem();

#endif //LOGISTICS_MANAGEMENT_SYSTEM_ITEM_H
