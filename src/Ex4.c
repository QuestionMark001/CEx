/* 圆周率的估算 */
#include <stdio.h>
//#include <stdlib.h>   //Windows操作系统下请务必将这一行注释"//"去掉！！！
#include <math.h>

int main(void)
{
    printf("圆周率的估算\n");
    printf("按下Enter键开始运行\n");
    getchar();

    int s;
    float n,t,pi;
    t=1,pi=0;n=1.0;s=1;

    while(fabs(t)>1e-6)
    {
        pi=pi+t;
        n=n+2;
        s=-s;
        t=s/n;
    }

    pi=pi*4;

    printf("pi=%10.6f\n",pi);

    //system("pause");   Windows操作系统下请务必将这一行注释"//"去掉！！！
    return 0;

}