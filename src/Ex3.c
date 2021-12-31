/* 牛顿迭代法求解超越方程 x*sin(x)=1
*  在Linux下用gcc编译请使用gcc Ex3.c -lm -o Ex3命令
*/
# include <stdio.h>
# include <math.h>
# define eps 1e-6

int main(void)
{
    printf("牛顿迭代法求解超越方程 x*sin(x)=1\n");
    printf("按下Enter键开始运行\n");
    getchar();
    
    float x0, x1;

    x0 = 1.0;
    x1 = (1 + x0*x0*cos(x0)) / (sin(x0) + x0*cos(x0));

    do
    {
        x0 = x1;
        x1 = (1 + x0*x0*cos(x0)) / (sin(x0) + x0*cos(x0));
    }while(fabs(x0 - x1) > eps);

    printf("%f\n", x1);

    //system("pause");   Windows操作系统下请务必将这一行注释"//"去掉！！！
    return 0;
}