//
// Created by Kalen Suen on 2023/12/4.
//
#include <stdio.h>
/*主界面
添加货物
查看货物，
删除货物
修改货物
货物出库
两个注意事项:1.订单不存在问题.2.订单重复问题
*/


/*
typedef struct
{
    char id[15];
    char 
    
} goods;*/

int main(void) {
    int operation1;
    printf("欢迎来到物流信息管理系统……\n");
    printf("1 添加货物\n");
    printf("2 删除货物\n");
    printf("3 修改货物\n");
    printf("4 查看所有货物\n");
    printf("5 \n");
    printf("请选择需要的操作：\n");

    scanf("%d", &operation1);
}
/*
    switch(operation1)
    {
        case 1:
            add();
            break;
        case 2:
            delete();
            break;
        case 3:
            modify();
            break;
        case 4:
            check();
            break;
        case 5:
            


    }
    */
