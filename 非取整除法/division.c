#include <stdio.h>
#include <stdlib.h>
#define IS_END_ZERO 0 //若除尽末尾是否输出0

int main()
{
	int dividend, divisor, quotient, remainder;
	unsigned int precision = 6, isRound = 0;
	printf("请输入被除数、除数、输出精度、是否四舍五入(0/1)：");
	scanf("%d %d %u %u", &dividend, &divisor, &precision, &isRound);
	if (divisor == 0 || precision & 0xF << 30)					//除数为0和控制精度范围
		exit(-1);

	char* decimal = NULL;
	if ((decimal = (char*)calloc(precision + 1, sizeof(char))) == NULL)
	{
		printf("memory allocated failed!");
		exit(-1);
	}

	quotient = dividend / divisor;
	remainder = dividend % divisor;
	if (quotient < 0)
		divisor *= -1;											//结果为负数的处理
	for (unsigned i = 0; i < precision + 1; i++)
	{
		remainder *= 10;
		decimal[i] = remainder / divisor;
		remainder %= divisor;

		if (!IS_END_ZERO && remainder == 0)						//除尽时末尾不保留0的处理
		{
			if (i < precision)
				precision = i + 1;
			break;
		}
	}

	if (isRound && decimal[precision] > 4)						//四舍五入
	{
		int i = 0;
		do {
			if (i != 0)
				decimal[precision - i] = 0;						//将为10的上一位置0
			i++;
			precision - i + 1
				? decimal[precision - i]++
				: quotient++;									//舍入整数位
		} while (decimal[precision - i] == 10);					//进位后为10则继续进位
	}

	printf("%d", quotient);
	if (precision != 0)
		putchar('.');
	for (unsigned i = 0; i < precision; i++)
	{
		printf("%d", decimal[i]);
	}

	free(decimal);
	decimal = NULL;

	return 0;
}