i=1
j=0
max=20000
sp="/-\|"
printf "\033[0;31m"
echo -n "Loading... "
echo -n ' '
while [ $j -lt $max ]
do
    printf "\b${sp:i++%${#sp}:1}"
    j=$(($j+1))
done

