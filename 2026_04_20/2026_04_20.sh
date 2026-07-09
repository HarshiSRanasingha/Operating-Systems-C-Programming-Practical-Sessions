==================================Question 01================================

-----------------------------i-----------------------------
vi 20th.sh

####################################
echo " ----- find factorial----- "
echo "enter  n: "
read n

function factorial() {
		fact=1
			for ((i=1; i<=$1; i++))
				do
				  ((fact*=i))
				done
	  echo "factorial of $1 is $fact"
}
factorial $n


bash 20th.sh

		----- find factorial-----
		enter  n:
		3
		factorial of 3 is 6
#####################################

factorial() {
    n=$1
    fact=1

    while [ $n -gt 1 ]
    do
        fact=$((fact * n))
        n=$((n - 1))
    done

    echo $fact
}

---------------------------ii-----------------------------
################################
echo " ----- find nCr ----- "
echo "enter  n: "
read n
echo "enter  r: "
read r

function factorial() {
		fact=1
			for ((i=1; i<=$1; i++))
				do
				  ((fact*=i))
				done
	  echo "factorial of $1 is $fact"
}
factorial $n


function nCr(){
   
	factn = $((factorial $1))
    factr = $((factorial $2))
	factnr = $((factorial $(($1 - $2))))
	factndivr = $((factnr * factr))
      nCr = $(($factn / $factndivr))
	  
	   echo "nCr is $nCr"
}
nCr $n $r

#################################

nCr() {
    n=$1
    r=$2

    fn=$(factorial $n)
    fr=$(factorial $r)
    fnr=$(factorial $((n - r)))

    echo $(( fn / (fr * fnr) ))
}

--------------------------iii---------------------------

while true
do
    echo "Enter value of n:"
    read n

    echo "Enter value of r:"
    read r

    if [ $n -lt $r ]; then
        echo "Invalid input: n must be greater than or equal to r. Please re-enter values."
    else
        break
    fi
done

----------------------------iv----------------------------

result=$(nCr $n $r)
echo "nCr = $result"