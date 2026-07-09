a). 
echo " enter 4 digit number : "
read n

b).
echo " enter 4 digit number : "
read n

function sum(){
         digit = 0 
         sum = 0
         
		 while [ $1 -gt 0 ];
		 do
		   digit = $(($1 % 10))
		   sum = $(($sum + $digit))
		   num = $(($1/10))
		 done
		 
		 echo "Digit sum : $sum  "
}

sum $num


c).
echo " Enter 4 digit number : "
read num

function sum(){
         digit = 0 
         sum = 0
         
		 while [ $1 -gt 0 ];
		 do
		   digit = $(($1 % 10))
		   sum = $(($sum + $digit))
		   num = $(($1/10))
		 done
		 
		 echo "Digit sum : $sum  "
}

sum $num

function reverse(){
        digit = 0 
		
		echo "reverse order : "
		
		while [ $1 -gt 0 ];
		 do
		   digit = $(($1 % 10))
		   echo " $digit "
		   num = $(($1/10))
		 done
}

reverse $num		 
		 
