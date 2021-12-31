/* 随机产生100个数,采用数据的方式进行排序(冒泡法排序) */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    printf("随机产生100个数,采用数据的方式进行排序(冒泡法排序)\n");
    printf("按下Enter键开始运行\n");
    getchar();

    int a[100];
    int i,j,t;
    srandom(time(NULL));   //初始化随机数种子
    for (i=0; i<100; i++)
        a[i] = random();   //获取100个随机数
       
    for (i=0; i<100; i++)   //冒泡法排序
        for (j=0; j<i; j++)
            if (a[i] < a[j])
            {
                t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
    for (i=0; i<100; i++)  //输出结果
        printf("%d\n", a[i]);
   
    //system("pause");   Windows操作系统下请务必将这一行注释"//"去掉！！！   
    return 0;
}