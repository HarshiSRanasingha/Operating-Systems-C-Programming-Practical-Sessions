================================Q1=================================

vi first.c

	#include <stdio.h>
	int main(){
		printf("Hello World\n");
		return 0;
	}

gcc first.c -o first
./first

	Hello World


================================Q2=================================

vi first.c

	#include <stdio.h>
	int main(){
		int age = 20;
		float height = 5.8;
		char grade = 'A';
		char name[] = "ABC";

		printf("Age = %d\n", age);
		printf("Height = %.2f\n", height);
		printf("Grade = %c\n", grade);
		printf("Name = %s\n", name);
		return 0;
	}



gcc first.c -o first
./first

	Age = 20
	Height = 5.80
	Grade = A
	Name = ABC
	

================================Q3=================================

vi first.c

	#include <stdio.h>
	int main(){
		int a,b,sum;

		printf("Enter two numbers \n");
		scanf("%d %d", &a, &b);

		sum = a + b;
		printf("sum = %d\n", sum);
		return 0;
	}

	

gcc first.c -o first
./first

	Enter two numbers
	3
	4
	sum = 7

================================Q4=================================

vi first.c

	#include <stdio.h>
	int main(){
		int a,b,sum,sub,mul;
		float div;

		printf("Enter two numbers \n");
		scanf("%d %d", &a, &b);

		sum = a + b;
		sub = a - b;
		mul = a * b;
		div = a / b;

		printf("sum = %d\n", sum);
		printf("sub = %d\n", sub);
		printf("mul = %d\n", mul);
		printf("div = %.2f\n", div);
		return 0;
	}
		

gcc first.c -o first
./first

	Enter two numbers
	23
	45
	sum = 68
	sub = -22
	mul = 1035
	div = 0.00
	
================================Q5=================================

vi first.c

	#include <stdio.h>
	int main(){
		int num;

		printf("Enter a number \n");
		scanf("%d", &num);

		if (num % 2 == 0)
		printf("even \n");
		else
		printf("odd \n");

		return 0;
	}
	

gcc first.c -o first
./first

	Enter a number
	45
	odd
		

================================Q6=================================

vi first.c

	#include <stdio.h>
	int main(){
		int a,b;
		char op;

		printf("Enter expression (eg.5+3): ");
		scanf("%d %c %d", &a, &op, &b);

		if (op == '+')
		printf("result= %d\n", a + b);
		else if (op == '-')
		printf("result= %d\n", a - b);
		else if (op == '*')
		printf("result= %d\n", a * b);
		else
		printf("invalid");
		return 0;
	}
	

gcc first.c -o first
./first

	Enter expression (eg.5+3): 5+6
	result= 11
	
	
================================Q7=================================

vi first.c

	#include <stdio.h>
	int main(){

		for (int i = 1; i <= 5; i++){
		printf("%d\n", i);
		}

		return 0;
	}


gcc first.c -o first
./first

	1
	2
	3
	4
	5
	
================================Q8=================================

vi first.c

	#include <stdio.h>
	int main(){

		int n, i = 1;
		printf("Enter a number: ");
		scanf("%d", &n);

		while (i <= n){
		printf("%d\n", i);
		i++;
		}

		return 0;
	}


gcc first.c -o first
./first

	Enter a number: 5
		1
		2
		3
		4
		5


================================Q9=================================

vi first.c

	#include <stdio.h>
	int main(){

		int a, b;
		char op;

		printf("Enter two numbers:\n ");
		scanf("%d %d", &a, &b);

		printf("Enter Operator:\n ");
		scanf(" %c", &op);

		switch (op){
			case '+':
			printf("%d\n", a + b);
			break;
			case '-':
			printf("%d\n", a - b);
			break;
			case '*':
			printf("%d\n", a * b);
			break;
			case '/':
			printf("%d\n", a / b);
			break;
			default:
			printf("invalid\n");
		}

		return 0;
	}


gcc first.c -o first
./first

	Enter two numbers:
	 23
	 2
	Enter Operator:
	 *
	 46
	