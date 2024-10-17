#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "contact.h"
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    addressBook->fptr=fopen("addressbook.csv","w");
    fprintf(addressBook->fptr, "#%d#\n" , addressBook->contactCount);
    //run loop
    for(int i=0;i<addressBook->contactCount;i++)
    {
        //remove any trailing new line charcters
        addressBook->contacts[i].name[strcspn(addressBook->contacts[i].name, "\n")] = 0;
        addressBook->contacts[i].phone[strcspn(addressBook->contacts[i].phone, "\n")] = 0;
        addressBook->contacts[i].email[strcspn(addressBook->contacts[i].email, "\n")] = 0;
        
        //store the data and remove any leading spaces present
        char *name = addressBook->contacts[i].name;
        name += strspn(name, " ");
        char *phone = addressBook->contacts[i].phone;
        phone += strspn(phone, " ");
        char *email = addressBook->contacts[i].email;
        email += strspn(email, " ");
    
        fprintf(addressBook->fptr, "%s, %s, %s\n" , addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);  

    }
    fclose(addressBook->fptr);
    printf("Contact saved successfully\n");
    
}

void loadContactsFromFile(AddressBook *addressBook) {
    char str[200]; 

    // Read the first line to get the contact count, assuming the format #num#
    fscanf(addressBook->fptr, "%s", str);
        
    // store the number between the hash signs by converting the string to integer using atoi

    int num = atoi(strtok(str + 1, "#"));  // Skips the first '#' and tokenizes until next '#'

    // Set the contact count in the address book
    addressBook->contactCount = num;

    // Allocate memory for contacts
    addressBook->contacts = malloc(num * sizeof(Contact));

    if (addressBook->contacts == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    // Clear the input buffer
    int c;
    while ((c = fgetc(addressBook->fptr)) != '\n' && c != EOF);

    // Read each contact from the file
    for (int i = 0; i < num; i++)
    {
        // Read a full line into str
        fgets(str, sizeof(str), addressBook->fptr);
        
        /*if (fgets(str, sizeof(str), addressBook->fptr) == NULL) {
            printf("Error reading contact data.\n");
            free(addressBook->contacts); // Free allocated memory if there's an error
            return;
        }*/

        // Remove leading and trailing spaces from the line
        char *p=str;
        while(*p==' ')
          p++; //to find any leading space is present if yes skip that portion
        char *q=p+strlen(p)-1;   //to move to last charcter of the string and removing leading spaces then removing the trailing spaces
        while(*q==' ')
           *q--='\0';

        // Tokenize the line by commas to extract name, phone, and email
        char *name = strtok(p, ",");
        char *phone = strtok(NULL, ",");
        char *email = strtok(NULL, ",");

        // Remove leading and trailing spaces from name, phone, and email
        name += strspn(name, " ");
        name[strcspn(name, "\n")] = 0;
        phone += strspn(phone, " ");
        phone[strcspn(phone, "\n")] = 0;
        email += strspn(email, " ");
        email[strcspn(email, "\n")] = 0;

        // Copy the name, phone, and email to the contact structure
        strcpy(addressBook->contacts[i].name, name);
        strcpy(addressBook->contacts[i].phone, phone);
        strcpy(addressBook->contacts[i].email, email);
    }
}



