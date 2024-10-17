#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"


void listContacts(AddressBook *addressBook) 
{
     
    int i;
    for(i=0;i<addressBook->contactCount;i++)
    {
       printf("Name  : %-15s\t", addressBook->contacts[i].name);
       printf("Phone : %-15s\t",addressBook->contacts[i].phone);
       printf("Email : %-15s\n",addressBook->contacts[i].email);
       
    
      
    }
         

}



/*void initialize(AddressBook *addressBook) 
{
    //Initialize the contact count as zero

    addressBook->contactCount=0;

    //function call

    populateAddressBook(addressBook);
}*/

void saveAndExit(AddressBook *addressBook) 
{
   saveContactsToFile(addressBook); 
}


void createContact(AddressBook *addressBook) 
{
    // Clear the input buffer to remove leftover newline characters

      int c;
      while ((c=getchar())!= '\n'&& c != EOF); 
     
    
    //Read name ,phone number and email Id from the user.
    //Name validation is not required check whether the phonenumber and email present in the contact if yes printf error else update the contact list
    
    //addressBook->contacts = realloc(addressBook->contacts,addressBook->contactCount+1 * sizeof(Contact));
    addressBook->contacts = realloc(addressBook->contacts, (addressBook->contactCount + 1) * sizeof(Contact));


    char name[50];
    printf("Enter the name to be Added : ");
    fgets(name,sizeof(name),stdin);
    
    //fscanf(stdin, "%[^,],", name);

     // Remove trailing newline character if present
    name[strcspn(name, "\n")] = 0;
   
    //Read the phone number 

    char phone[50];
    printf("Enter the phone to be Added : ");
    fgets(phone,sizeof(phone),stdin);

    // Remove trailing newline character if present
    phone[strcspn(phone, "\n")] = 0;

    char new_phone[50];

    //Initially check for the validation of phone number
    
    int found1=0;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(phone,addressBook->contacts[i].phone)==0)
        {
            found1=1;
            break;
        }
    }
    if(found1==1)
    {
        printf("Phone number already present in the contact\n");
        printf("Read new phone number from the user : \n");
        while(found1==1)
        {
            char new_phone[50];
            printf("Enter the phone to be replaced : ");
            fgets(new_phone,sizeof(new_phone),stdin);
            // Remove trailing newline character if present
            new_phone[strcspn(new_phone, "\n")] = 0;
            
            found1=0;
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strcmp(new_phone,addressBook->contacts[i].phone)==0)
                {
                    found1=1;
                    printf("Phone number already present in the contact\n");
                    break;
                }
            }
           strcpy(addressBook->contacts[addressBook->contactCount].phone,new_phone);
        }

    }
    else
    {
        strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
    }
    
    //Read the Email.Id

    char email[50];
    printf("Enter the email to be Added : ");
    fgets(email,sizeof(email),stdin);

    // Remove trailing newline character if present
    email[strcspn(email, "\n")] = 0;

    char new_email[50];

    //Check for the validation of Email.Id
    
    int found2=0;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(email,addressBook->contacts[i].email)==0)
        {
            found2=1;
            break;
        }
    }
    if(found2==1)
    {
        printf("Email Id already present in the contact\n");
        printf("Read new email id from the user : \n");
        while(found2==1)
        {
            char new_email[50];
            printf("Enter the email to be replaced : ");
            fgets(new_email,sizeof(new_email),stdin);
            // Remove trailing newline character if present
            new_email[strcspn(new_email, "\n")] = 0;
            
            found2=0;
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strcmp(new_email,addressBook->contacts[i].email)==0)
                {
                    found2=1;
                    printf("Email Id already present in the contact\n");
                    break;
                }
            }
        strcpy(addressBook->contacts[addressBook->contactCount].email,new_email);
        strcpy(addressBook->contacts[addressBook->contactCount].name,name);
        addressBook->contactCount++;
        }

        
        
    }
    else
    {
       strcpy(addressBook->contacts[addressBook->contactCount].email,email);
       strcpy(addressBook->contacts[addressBook->contactCount].name,name);
       addressBook->contactCount++;
    }
   // addressBook->contacts = realloc(addressBook->contacts, (addressBook->contactCount + 1) * sizeof(Contact));

}

void searchContact(AddressBook *addressBook) 
{
    // Clear the input buffer to remove leftover newline characters

    int c;
    while ((c=getchar())!= '\n' && c != EOF);
     
     //read the name from the user

     char name[50];
     printf("Enter the name to be searched : ");
     fgets(name,sizeof(name),stdin);

    //strtok(name,"\n");
    // Remove trailing newline character if present
    name[strcspn(name, "\n")] = 0;

    //Search for name in Contacts[]
     
     int found=0;
     for(int i=0;i<addressBook->contactCount;i++)
     {
        if(strcmp(name,addressBook->contacts[i].name)==0)
        {
            found=1;
            printf("Name found in the contact\n");
            printf("Name  :%s\t",addressBook->contacts[i].name);
            printf("Phone :%s\t",addressBook->contacts[i].phone);
            printf("Email :%s\t",addressBook->contacts[i].email);
            printf("\n");
            
        }
     }
     if(found==0)
     {
        printf("Name not found in the contact\n");
     }
     
}

void editContact(AddressBook *addressBook) 
{
    // Clear the input buffer to remove leftover newline characters

    int c;
    while ((c=getchar()) != '\n' && c != EOF) ;
     
     //read the name from the user

     char name[50];
     printf("Enter the name to be searched : ");
     fgets(name,sizeof(name),stdin);

    // Remove trailing newline character if present
    name[strcspn(name, "\n")] = 0;

    //Search for name in Contacts[] if found edit the contacts and read the new info from the user
    
    int found=0;
    int index;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(name,addressBook->contacts[i].name)==0)
        {
            found=1;
            index=i;
            char name_replace[50];
            printf("Enter the name to be replaced : ");
            fgets(name_replace,sizeof(name_replace),stdin);

            char phone_replace[50];
            printf("Enter the phone to be replaced : ");
            fgets(phone_replace,sizeof(phone_replace),stdin);

            char email_replace[50];
            printf("Enter the email to be replaced : ");
            fgets(email_replace,sizeof(email_replace),stdin);

            // Remove trailing newline character if present
            name_replace[strcspn(name_replace, "\n")] = 0;
            // Remove trailing newline character if present
            phone_replace[strcspn(phone_replace, "\n")] = 0;
            // Remove trailing newline character if present
            email_replace[strcspn(email_replace, "\n")] = 0;

            printf("Name  :%s\t",strcpy(addressBook->contacts[index].name,name_replace));
            printf("Phone :%s\t",strcpy(addressBook->contacts[index].phone,phone_replace));
            printf("Email :%s\t",strcpy(addressBook->contacts[index].email,email_replace));
            printf("\n");

        }
     }
     if(found==0)
     {
        printf("Name not found in the contact\n"); 
     }

}

void deleteContact(AddressBook *addressBook) 
{
    // Clear the input buffer to remove leftover newline characters

    int c;
    while ((c=getchar())!= '\n' && c != EOF);
     
     //read the name from the user

    char name[50];
     printf("Enter the name to be searched : ");
    fgets(name,sizeof(name),stdin);

    //fscanf(stdin, "%[^,]", name);

    // Remove trailing newline character if present
    name[strcspn(name, "\n")] = 0;

    //Search whether the contact is present if yes delete the contact

    int found=0;
    int index=-1;
    
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(name,addressBook->contacts[i].name)==0)
        {
            found=1;                         //contact is found
            index=i;                         //find the index at which the contact is present
            break;
        }
    }
    
    //if the contact is found then replace the contact with the next contact

    if(found)
    {
        for(int i=index;i<addressBook->contactCount-1;i++)
        {
            addressBook->contacts[i]=addressBook->contacts[i+1];
        }
        addressBook->contactCount--;    //decrement the contact count
        addressBook->contacts = realloc(addressBook->contacts,addressBook->contactCount * sizeof(Contact));


    }
   
   //if not found print the contact is not found

   else
   {
     printf("Contact not found\n");
   }
    
}


