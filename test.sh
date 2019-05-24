#!/bin/bash

app="$1"
dire="$2"

for file in $dire/*.in; do
    file_out="${file:0:-3}.out"
    file_err="${file:0:-3}.err"
    file_out_tst="$file.out.tst"
    file_err_tst="$file.err.tst"
    
    printf "Testing against %s\n" "$file"
    
    e_code3=$( valgrind --error-exitcode=15 --leak-check=full --show-leak-kinds=all -q  ./$app < $file > $file_out_tst 2> $file_err_tst )
    e_code3=$?
    diff -a "$file_out_tst" "$file_out"
    e_code=$?
    diff -a "$file_err_tst" "$file_err" 
    e_code2=$?
    
    if [ $e_code != 0 ] || [ $e_code2 != 0 ] || [ $e_code3 == 15 ] ; then
        printf "TEST FAIL!\n"
    else
        printf "TEST OK\n"
    
    fi
    
    rm $file_out_tst
    rm $file_err_tst
        
done

exit 0