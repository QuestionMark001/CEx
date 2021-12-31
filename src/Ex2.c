/* 自动判断每个同学的等级 */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("随机产生100个同学的分数(20~100)，并自动判断每个同学的等级\n");
    printf("按下Enter键开始运行\n");
    getchar();


    for (int i = 0; i < 100; i++)
    {
        printf("%d", rand() % 81 +20);
    }

    //system("pause");   Windows操作系统下请务必将这一行注释"//"去掉！！！
    return 0;

}