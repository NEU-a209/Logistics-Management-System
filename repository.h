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

#define MAX_REPOSITORY_NAME_LENGTH  64
#define MAX_REPOSITORY_CONNECTIONS  16
#define MAX_REPOSITORY_NUM          512

#define TYPE_NUM 3

struct Connection {
    double transportationTime[TYPE_NUM];
    struct Repository *destination;
};

struct Repository {
    int index;
    char name[MAX_REPOSITORY_NAME_LENGTH];
    struct Connection connections[MAX_REPOSITORY_CONNECTIONS];
};


struct Repository constructRepository();

#endif //LOGISTICS_MANAGEMENT_SYSTEM_REPOSITORY_H
