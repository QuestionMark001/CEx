/* 十进制转换为二进制 */
/* 在Linux下用gcc编译请使用gcc Ex6.2.c -lm -o Ex6.2命令 */
#include <stdio.h>
//#include <stdlib.h>   //Windows操作系统下请务必将这一行注释"//"去掉！！！
#include <math.h>

long long convertDecimalToBinary(int n);
 
int main()
{
    printf("十进制到二进制转换器\n");
    printf("按下Enter键开始运行\n");
    getchar();

    int n;
    printf("输入一个十进制数: ");
    scanf("%d", &n);
    printf("十进制数 %d 转换为二进制位 %lld\n", n, convertDecimalToBinary(n));
    
    //system("pause");   Windows操作系统下请务必将这一行注释"//"去掉！！！
    return 0;
}
 
long long convertDecimalToBinary(int n)
{
    long long binaryNumber = 0;
    int remainder, i = 1, step = 1;
 
    while (n!=0)
    {
        remainder = n%2;
        printf("Step %d: %d/2, 余数 = %d, 商 = %d\n", step++, n, remainder, n/2);
        n /= 2;
        binaryNumber += remainder*i;
        i *= 10;
    }
    return binaryNumber;
}