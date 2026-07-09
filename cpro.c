cpro.c

gcc   cpro.c   -o  cpro
./cpro

#include <stdio.h>

int main() {
    printf("Hello!\n");

    char name[50];
    int age;
    char grade;
    float gpa;

    printf("What is your name? ");
    scanf("%49s", name);

    printf("Enter your age: ");
    scanf("%d", &age);

    printf("Enter your grade: ");
    scanf(" %c", &grade);

    printf("Enter GPA: ");
    scanf("%f", &gpa);

    printf("\n--- Student Details ---\n");
    printf("Name : %s\n", name);
    printf("Age  : %d\n", age);
    printf("Grade: %c\n", grade);
    printf("GPA  : %.2f\n", gpa);

    return 0;
}

Hello!
What is your name? John
Enter your age: 20
Enter your grade: A
Enter GPA: 3.75

--- Student Details ---
Name : John
Age  : 20
Grade: A
GPA  : 3.75

========================================================
#include <stdio.h>

int main()
{
    int a, b, sum, sub, mul;
    float div;

    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);

    sum = a + b;
    sub = a - b;
    mul = a * b;
    div = (float)a / b;

    printf("sum : %d\n", sum);
    printf("sub : %d\n", sub);
    printf("mul : %d\n", mul);
    printf("div : %.2f\n", div);

    return 0;
}

Enter two numbers: 10 4
sum : 14
sub : 6
mul : 40
div : 2.50

==========================================================

#include <stdio.h>

int main() {
    int a, b;
    char op;

    printf("Enter expression (eg. 5+3): ");
    scanf("%d%c%d", &a, &op, &b);

    if (op == '+')
        printf("result = %d\n", a + b);

    else if (op == '-')
        printf("result = %d\n", a - b);

    else if (op == '*')
        printf("result = %d\n", a * b);

    else if (op == '/')
        printf("result = %.2f\n", (float)a / b);

    else
        printf("Invalid operator\n");

    return 0;
}

Enter expression (eg. 5+3): 5+3
result = 8

============================================================

#include <stdio.h>

int main() {

    for (int i = 1; i <= 5; i++) {
        printf("%d\n", i);
    }

    return 0;
}

1
2
3
4
5

=============================================================

#include <stdio.h>

int main() {

    int n, i = 1;

    printf("Enter a number: ");
    scanf("%d", &n);

    while (i <= n) {
        printf("%d\n", i);
        i++;
    }

    return 0;
}

Enter a number: 5
1
2
3
4
5

===============================================================

#include <stdio.h>

int main() {

    int a, b;
    char op;

    printf("Enter two numbers:\n");
    scanf("%d %d", &a, &b);

    printf("Enter Operator:\n");
    scanf(" %c", &op);

    switch (op) {

        case '+':
            printf("Result = %d\n", a + b);
            break;

        case '-':
            printf("Result = %d\n", a - b);
            break;

        case '*':
            printf("Result = %d\n", a * b);
            break;

        case '/':
            printf("Result = %.2f\n", (float)a / b);
            break;

        default:
            printf("Invalid operator\n");
    }

    return 0;
}


	Enter two numbers:
	 23
	 2
	Enter Operator:
	 *
	 46





