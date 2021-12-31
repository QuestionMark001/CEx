/* 二进制转换为十进制 */
/* 在Linux下用gcc编译请使用gcc Ex6.1.c -lm -o Ex6.1命令 */
#include <stdio.h>
//#include <stdlib.h>   //Windows操作系统下请务必将这一行注释"//"去掉！！！
#include <math.h>

int convertBinaryToDecimal(long long n);
 
int main()
{
    printf("二进制到十进制转换器\n");
    printf("按下Enter键开始运行\n");
    getchar();

    long long n;
    printf("输入一个二进制数: ");
    scanf("%lld", &n);
    printf("二进制数 %lld 转换为十进制为 %d\n", n, convertBinaryToDecimal(n));

    //system("pause");   Windows操作系统下请务必将这一行注释"//"去掉！！！
    return 0;
}
 
int convertBinaryToDecimal(long long n)
{
    int decimalNumber = 0, i = 0, remainder;
    while (n!=0)
    {
        remainder = n%10;
        n /= 10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }
    return decimalNumber;
}