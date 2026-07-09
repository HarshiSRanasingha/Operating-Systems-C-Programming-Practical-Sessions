==========================Q1==============================

echo "enter a operation: (type number)"
echo "1. Addition"
echo "2. Substraction"
echo "3. Multiplication"
echo "4. Division"
read op

echo "enter two numbers: "
read n1
read n2

sum=$(($n1+$n2))
sub=$(($n1-$n2))
mul=$(($n1*$n2))
div=$(($n1/$n2))

if [ "$op" -eq 1 ];
then
echo "addition of $n1 and $n2 is $sum"
elif [ "$op" -eq 2 ];
then
echo "subtraction between $n1 and $n2 is $sub"
elif [ "$op" -eq 3 ];
then
echo "multiplication between $n1 and $n2 is $mul"
else
echo "division between $n1 and $n2 is $div"
fi


------output------
bash test.sh
enter a operation: (type number)
1. Addition
2. Substraction
3. Multiplication
4. Division
1
enter two numbers:
23
45
addition of 23 and 45 is 68



==============================================================
echo "enter two numbers: "
read n1
read n2

echo "enter a operation: (type number) :  "
echo "1. Addition"
echo "2. Substraction"
echo "3. Multiplication"
echo "4. Division"
read op

sum=$(($n1+$n2))
sub=$(($n1-$n2))
mul=$(($n1*$n2))
div=$(($n1/$n2))

	case $op in
	1)echo "addition of $n1 and $n2 is $sum";;
	2)echo "subtraction between $n1 and $n2 is $sub";;
	3)echo "multiplication between $n1 and $n2 is $mul";;
	4)echo "division between $n1 and $n2 is $div";;
	*)echo "Invalid input";;
	esac
	
	
-------output--------	
bash test.sh
enter two numbers:
23
12
enter a operation: (type number) :
1. Addition
2. Substraction
3. Multiplication
4. Division
3
multiplication between 23 and 12 is 276



============================================================
