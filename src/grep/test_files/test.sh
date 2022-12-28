#!/bin/bash

./../s21_grep bla bla.txt blabla.txt > res_S21.txt
grep bla bla.txt blabla.txt > res.txt
echo "No options testing: "
LEN=$(diff res.txt res_S21.txt | wc -l)
if [ $LEN == 0 ]; then 
    echo "\033[32mSUCCESS\033[0m"
else
    echo "\033[41mFAIL\033[0m"
fi

./../s21_grep -e bla bla.txt blabla.txt > res_S21.txt
grep -e bla bla.txt blabla.txt > res.txt
echo "-e options testing:"
LEN=$(diff res.txt res_S21.txt | wc -l)
if [ $LEN == 0 ]; then 
    echo "\033[32mSUCCESS\033[0m"
else
    echo "\033[41mFAIL\033[0m"
fi

./../s21_grep -i pattern.txt bla.txt blabla.txt > res_S21.txt
grep -i pattern.txt bla.txt blabla.txt > res.txt
echo "-i options testing: "
LEN=$(diff res.txt res_S21.txt | wc -l)
if [ $LEN == 0 ]; then 
    echo "\033[32mSUCCESS\033[0m"
else
    echo "\033[41mFAIL\033[0m"
fi

./../s21_grep -v pattern.txt bla.txt blabla.txt > res_S21.txt
grep -v pattern.txt bla.txt blabla.txt > res.txt
echo "-v options testing: "
LEN=$(diff res.txt res_S21.txt | wc -l)
if [ $LEN == 0 ]; then 
    echo "\033[32mSUCCESS\033[0m"
else
    echo "\033[41mFAIL\033[0m"
fi

./../s21_grep -c bla bla.txt blabla.txt > res_S21.txt
grep -c bla bla.txt blabla.txt > res.txt
echo "-c options testing: "
LEN=$(diff res.txt res_S21.txt | wc -l)
if [ $LEN == 0 ]; then 
    echo "\033[32mSUCCESS\033[0m"
else
    echo "\033[41mFAIL\033[0m"
fi

./../s21_grep -l bla bla.txt blabla.txt > res_S21.txt
grep -l bla bla.txt blabla.txt > res.txt
echo "-l options testing:"
LEN=$(diff res.txt res_S21.txt | wc -l)
if [ $LEN == 0 ]; then 
    echo "\033[32mSUCCESS\033[0m"
else
    echo "\033[41mFAIL\033[0m"
fi

./../s21_grep -n bla bla.txt blabla.txt > res_S21.txt
grep -n bla bla.txt blabla.txt > res.txt
echo "-n options testing:"
LEN=$(diff res.txt res_S21.txt | wc -l)
if [ $LEN == 0 ]; then 
    echo "\033[32mSUCCESS\033[0m"
else
    echo "\033[41mFAIL\033[0m"
fi

./../s21_grep -s bla bla.txt no.txt > res_S21.txt
grep -s bla bla.txt no.txt > res.txt
echo "-s options testing:"
LEN=$(diff res.txt res_S21.txt | wc -l)
if [ $LEN == 0 ]; then 
    echo "\033[32mSUCCESS\033[0m"
else
    echo "\033[41mFAIL\033[0m"
fi

rm res_S21.txt res.txt
