mkdir lower1  lower2  merged  upper  work

echo "I'm from lower1" > lower1/in_lower1.txt
echo "I'm from lower1" > lower1/in_lower.txt
echo "I'm from lower1" > lower1/in_both.txt

echo "I'm from lower2" > lower2/in_lower2.txt
echo "I'm from lower2" > lower2/in_lower.txt
echo "I'm from lower2" > lower2/in_both.txt

echo "I'm from upper" > upper/in_upper.txt
echo "I'm from upper" > upper/in_both.txt

mount -t overlay overlay -o lowerdir=./lower1:./lower2,upperdir=./upper,workdir=./work ./merged
