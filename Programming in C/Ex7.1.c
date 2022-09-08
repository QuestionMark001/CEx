/* 函数功能: 用迭代法计算n!
 * 函数入口参数： 整形变量n表示结成的阶数
 * 函数返回值： 返回n!的值
 */
#include<stdio.h>

long Fact(int n)
{
	int i;
	long result = 1;
	for (i = 2;i <= n;i++) 
	{
		result *= i;
	}

	return result;
}

int main()
{
	int m;
	long ret;
	printf("Input m:");
	scanf("%d",&m);
	ret = Fact(m);
	printf("%d = %ld\n",m,ret);
	return 0;
}
