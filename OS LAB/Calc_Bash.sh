#!/bin/bash
echo "Enter 1st num :"
read a
echo "Enter 2nd num :"
read b
c=1
res=0
while [ $c=1 ]
do
        echo "Add/Sub/Mul/Div"
        echo "Enter :"
        read ch
        case $ch in
                1)res=`echo $a + $b | bc`
                 ;;
                2)res=`echo $a - $b | bc`
                ;;
                3)res=`echo $a \* $b | bc`
                ;;
                4)res=`echo $a / $b | bc`
                ;;
                *)echo "enter valid choice :";;
        esac

        echo "Res: $res"
        echo "Continue?1/0"
        read c
        if [ $c != 1 ];
        then
                exit
        fi
done
