#include <stdio.h>
#include<stdlib.h>
#include "contact.h"
#include "file.h"

int main() 
{
    AddressBook book; //struct variable
    //initialize(&book);    //fun call

    book.fptr = fopen("addressbook.csv","r+");

    if(book.fptr == NULL)
    {
        printf("Error in opening the file\n");
        return 0;
    }

    loadContactsFromFile(&book);

    do            //to dispaly the menu infinitely
    {
        // display the menu
        printf("Display the Menu : \n");
        printf(" 1.Create Contact\n 2.Search Contact\n 3.Edit contact\n 4.Delete contact\n 5.List Contacts\n 6.Exit\n");

        int option;
        printf("Enter the choice : ");
        scanf("%d",&option);    //read choice from the user

        switch(option)
       {
        case 1: printf("Select create contact\n");
                createContact(&book);
                break;
        case 2: printf("Select search contact\n");
                searchContact(&book);
                break;
        case 3: printf("Select edit contact\n");
                editContact(&book);
                break;
        case 4: printf("Select delete contact\n");
                deleteContact(&book);
                break;
        case 5: printf("Select list contact\n");
                listContacts(&book);
                break;
        case 6: printf("Select Exit\n");
                char choice;
                printf("Do you want to save the data to the file(y/n): ");
                scanf(" %c",&choice);
                if(choice=='y')
                {
                   saveAndExit(&book);
                }
                else
                {
                    printf("Exit from the program without saving\n");
                    //free(book.fptr);
                    exit(0);
                }
                
                break;
        }
    }while(1);
   
}
