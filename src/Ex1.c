/* 九九乘法表 */
#include <stdio.h>
//#include <stdlib.h>   //Windows操作系统下请务必将这一行注释去掉！！！

int main(void)
{
    printf("九九乘法表\n");
    printf("按下Enter键开始运行\n");
    getchar();

    int x,y;

    for (x = 1; x <= 9; x++)
    {
        for (y = 1; y <= x; y++)
        {
            printf("%d*%d=%-5d",y,x,x*y);
        }
        printf("\n");
        
    }
    
    //system("pause");   Windows操作系统下请务必将这一行注释去掉！！！
    return 0;

}