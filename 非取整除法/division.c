#include <stdio.h>
#include <stdlib.h>
#define IS_END_ZERO 1 //若除尽末尾是否输出0
//精度上限2^30-1位，约10亿位
int main()
{
	int dividend, divisor, quotient, remainder;
	unsigned int precision = 6, isRound = 0;
	printf("请输入被除数、除数、输出精度、是否四舍五入(0/1)：");
	scanf("%d %d %u %u", &dividend, &divisor, &precision, &isRound);
	if (divisor == 0 || precision & 0xF << 30)					//除数为0和控制精度范围
		exit(-1);


	char* decimal = NULL;							//创建变长数组，多一位用于四舍五入，使用char储存一位数以节省空间
	if ((decimal = (char*)calloc(precision + 1, sizeof(char))) == NULL) {
		printf("memory allocated failed!");
		exit(-1);
	}

	quotient = dividend / divisor;
	remainder = dividend % divisor;
	if (quotient < 0)divisor *= -1;								//商为负数的处理
	for (unsigned i = 0; i < precision + 1; i++) {
		remainder *= 10;										/****核心步骤****/
		decimal[i] = remainder / divisor;						/****核心步骤****/
		remainder %= divisor;									/****核心步骤****/

		if (!IS_END_ZERO && remainder == 0) {					/***除尽时末尾不保留0的处理***/
			if (precision != i)									//判断除尽时数组长度是否 不能 刚好容纳最后一位非0数
				precision = i + 1;
			break;
		}
	}

	/***四舍五入***/
	if (isRound && decimal[precision] > 4) {
		int i = 0;
		do {
			if (i)decimal[precision - i] = 0;					//将为10的上一位置0
			i++;
			precision - i + 1
				? decimal[precision - i]++
				: quotient++;									//舍入整数位
		} while (decimal[precision - i] == 10);					//进位后为10则继续进位
	}

	printf("%d", quotient);
	if (precision != 0)
		putchar('.');
	for (unsigned i = 0; i < precision; i++) {
		printf("%d", decimal[i]);
	}

	free(decimal);
	decimal = NULL;

	return 0;
}