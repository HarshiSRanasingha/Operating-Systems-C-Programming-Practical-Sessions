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
if
echo "addition of $n1 and $n2 is $sum"
echo "subtraction between $n1 and $n2 is $sub"