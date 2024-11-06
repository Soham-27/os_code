#!/bin/bash

fileExists(){
    [ -e Address_book.txt ]
}

displayFileError(){
    echo "Address bokk is not created "
}

initAddressBook(){
    if ! fileExists;
    then
    touch Address_book.txt
    printf "| Name | Email | Phone Number | Address |\n" > Address_book.txt

    fi
}

main(){
    initAddressBook
    while true ; do  
     printf "\nWelcome to Address Book\n"
        printf "1. Create Address Book\n"
        printf "2. View Address Book\n"
        printf "3. Insert Record\n"
        printf "4. Delete Record\n"
        printf "5. Search Record\n"
        printf "6. Update Record\n"
        printf "7. Exit\n"
        read -p "Enter Choice: " choice

    case $choice in 
    1) if ! fileExists ; then 
            initAddressBook
            echo "Address Book Created"
        else
            echo "Address book already exists"
        fi;;
    2) 
        if ! fileExists; then
            displayFileError
        else 
            if [ -s Address_book.txt ];
            then
            cat Address_book.txt
            else
            echo "Address book is empty"
            fi ;
        fi;;

    3) 
        if ! fileExists ; then
            displayFileError
        else 
            read -p "Enter your name :" name
            read -p "Enter your email :" email
            read -p "Enter you Phone Number :" Phone_Number
            read -p "Enter Address :" Address
            printf "| %s | %s | %s | %s |\n" "$name,$email,$Phone_Number,$Address">>Address_book.txt
            echo "Record Added"
        fi ;;
    

    4)  if ! fileExists ; then
            displayFileError
        else  
            read -p "enter name to delete " name
            if grep -qi  "$name" Address_book.txt ; then 
            sed -i "/$(echo "$name" | sed 's/[^^]/[&]/g; s/\^/\\^/g')/d" Address_book.txt
            echo "record deleted"

            else 
            echo "no record deleted "

            fi
        fi ;;

     5)  if ! fileExists ; then
            displayFileError
            else  
            read -p "enter name to search " name
            if grep -i  "$name" Address_book.txt ; then 
            echo "record found"
            else 
            echo "no record deleted "

            fi
        fi ;;
    
     6) if ! fileExists ; then
            displayFileError
        else  
            read -p "enter name to update " name
            if grep -qi  "$name" Address_book.txt ; then 
            sed -i "/$(echo "$name" | sed 's/[^^]/[&]/g; s/\^/\\^/g')/d" Address_book.txt
            read -p "Enter your email :" email
            read -p "Enter your Phone Number : " Phone_Number
            read -p "Enter your Address : " Address;
            printf "| %s | %s | %s | %s |\n" "$name" "$email" "$phone" "$address" >> Address_Book.txt
            echo "Record updated."

            else 
            echo "no record updated "

            fi
        fi ;;

    7) exit ;;
    *) 

    esac
    done
}
main