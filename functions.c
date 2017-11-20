/*****************************************************************
 //
 //  NAME:        Joaquin Torres
 //
 //  HOMEWORK:    Programming Assignment 2
 //
 //  CLASS:       ICS 355
 //
 //  INSTRUCTOR:  Dan Clark
 //
 //  DATE:        November 19, 2017
 //
 //  FILE:        functions.c
 //
 //  DESCRIPTION:
 //   This file contains all of the functions used in the process
 //   of creating a financial calculator program.
 //
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"
#include "record.h"
#include <time.h>

/*****************************************************************
 //
 //  Function name: convertToPounds
 //
 //  DESCRIPTION:   This function will convert an inputted amount into pounds
 //                 based on the type of currency it was originally.
 //
 //  Parameters:    input (float) : formatted number to only include the value
 //                 of the currency, not the type.
 //
 //                 type (char) : contains the type of currency being converted,
 //                 where 'd' is dollars and 'e' is euros.
 //
 //
 //  Return values:  value : the pound value of the inputted currency.
 //
 ****************************************************************/

float convertToPounds (float input, char type)
{
    float value = 0;
    
    if (type == 'd')
    {
        
        value = input * 0.75;
        
    }
    else if (type == 'e')
    {
        
        value = input * 0.89;
        
    }
    
    return value;
}

/*****************************************************************
 //
 //  Function name: convertToDollars
 //
 //  DESCRIPTION:   This function will convert an inputted amount into dollars
 //                 based on the type of currency it was originally.
 //
 //  Parameters:    input (float) : formatted number to only include the value
 //                 of the currency, not the type.
 //
 //                 type (char) : contains the type of currency being converted,
 //                 where 'p' is pounds and 'e' is euros.
 //
 //
 //  Return values:  value : the dollar value of the inputted currency.
 //
 ****************************************************************/

float convertToDollars (float input, char type)
{
    float value = 0;
    
    if (type == 'p')
    {
        
        value = input * 1.33;
    
    }
    else if (type == 'e')
    {
    
        value = input * 1.18;
    
    }
    
    return value;
}

/*****************************************************************
 //
 //  Function name: convertToEuros
 //
 //  DESCRIPTION:   This function will convert an inputted amount into euros
 //                 based on the type of currency it was originally.
 //
 //  Parameters:    input (float) : formatted number to only include the value
 //                 of the currency, not the type.
 //
 //                 type (char) : contains the type of currency being converted,
 //                 where 'd' is dollars and 'p' is pounds.
 //
 //
 //  Return values:  value : the euro value of the inputted currency.
 //
 ****************************************************************/

float convertToEuros (float input, char type)
{
    float value = 0;
    
    if (type == 'p')
    {
    
        value = input * 1.12;
    
    }
    else if (type == 'd')
    {
    
        value = input * 0.85;
        
    }
    
    return value;

}

/*****************************************************************
 //
 //  Function name: findRecord
 //
 //  DESCRIPTION:   This function will find a record based on its account number
 //                 and return its position in the account array.
 //
 //  Parameters:    accarray (struct record []) : contains the list of accounts.
 //
 //                 inaccountno (int) : contains the account number of the record
 //                 to be found.
 //
 //                 numusers (int) : contains the number of users in the database.
 //
 //
 //  Return values:  count (int) : returns the position in the account array at
 //                  that holds the account number initially inputted. If the account
 //                  was not found or the list was empty, then the function returns 0.
 //
 ****************************************************************/

int findRecord (struct record accarray[], int inaccountno, int numusers)
{
    struct record current[100];
    
    for (int i = 0; i < 100; i++)
        current[i] = accarray[i];
    int found = 0;
    int count = 0;

    if (current[count].accountno == '0')
    {
        printf("\nList empty\n");
    }

    while (count < numusers && found == 0)
    {
        if (current[count].accountno == inaccountno)
        {
        
            printf("\nFound user %s with account number: %d\nBalance: $%.2f\n", current[count].name, current[count].accountno, current[count].balance);
            found = 1;

        }

        count++;

    }
    
    if (found == 0)
    {
        count = found;
    }
    
    return count;
    
}

/*****************************************************************
 //
 //  Function name: findRecord
 //
 //  DESCRIPTION:   This function will find a record based on its account number
 //                 and return its position in the account array.
 //
 //  Parameters:    accarray (struct record []) : contains the list of accounts.
 //
 //                 inaccountno (int) : contains the account number of the record
 //                 to be found.
 //
 //                 numusers (int) : contains the number of users in the database.
 //
 //
 //  Return values:  0 : username not found
 //                 -1 : username found, but password incorrect
 //                  1 : username found and password correct
 ****************************************************************/

int authenticate (struct record accarray[], int numusers, char username[], char hashedpassword[], int * currSession)
{
    struct record current[100];
    
    for (int i = 0; i < 100; i++)
        current[i] = accarray[i];
    int authenticate = 0;
    int count = 0;

    while (count < numusers && authenticate == 0)
    {
        //if username is in database
        if (strcmp(current[count].username, username) == 0)
        {
            if (strcmp(current[count].hashedpw, hashedpassword) == 0)
            {
                
                //username correct, password correct
                authenticate = 1;
                * currSession = current[count].accountno;
            
            }
            else
            {
                
                //username correct, password incorrect
                authenticate = -1;
                
            }
        }
        
        count++;
        
    }
    
    if (authenticate == 0)
        count = authenticate;
    
    return authenticate;
    
}

/*****************************************************************
 //
 //  Function name: printAll
 //
 //  DESCRIPTION:   This function will print all the records currently held
 //                 in the database.
 //
 //  Parameters:    accarray (struct record []) : contains the list of accounts.
 //
 //                 numusers (int) : contains the number of users in the database.
 //
 //
 //  Return values:  none
 //
 ****************************************************************/

void printAll (struct record accarray[], int numusers)
{
    struct record * current;
    current = accarray;
    int count = 0;
    
    if (current == NULL)
    {
        
        printf("\nList empty\n");
    
    }
    
    while (count < numusers)
    {
        
        printf("\nRecord Number: %d\nAccount Number: %d\nName: %s\nBalance: $%.2f\n", count + 1, current[count].accountno, current[count].name, current[count].balance);
        count++;
        
    }
}

/*****************************************************************
 //
 //  Function name: readFile
 //
 //  DESCRIPTION:   This function will read the database file and store
 //                 its values in the account array.
 //
 //  Parameters:    accarray (struct record []) : contains the list of accounts.
 //
 //                 numuser (int) : contains the number of users in the database.
 //
 //                 filename (char []) : the file to be read
 //
 //  Return values:  returnValue : 0 if successful, -1 if file not found
 //
 ****************************************************************/

int readfile(struct record accarray[], int * numuser, char filename[])
{
    FILE * inputFile = fopen(filename, "r");
    
    char input[300];
    int returnValue = 0;
    int user = 0;
    *numuser = 0;
    int lineCount = 1;
    
    if (inputFile != NULL)
    {
        while(!feof(inputFile) || lineCount == 7)
        {
            if(lineCount == 1)          //accountnumber
            {
                
                fgets(input, sizeof(input), inputFile);
                accarray[user].accountno = atoi(input);
                lineCount++;
                
            }
            else if (lineCount == 2)    //name
            {
                
                fgets(input, sizeof(input), inputFile);
                strcpy(accarray[user].name, input);
                lineCount++;
                
            }
            else if (lineCount == 3)    //balance
            {
                
                fgets(input, sizeof(input), inputFile);
                accarray[user].balance = atof(input);
                lineCount++;
            }
            else if (lineCount == 4)    //username
            {
                
                fgets(input, sizeof(input), inputFile);
                strcpy(accarray[user].username, input);
                lineCount++;
                
            }
            else if (lineCount == 5)    //salt
            {
                
                fgets(input, sizeof(input), inputFile);
                strcpy(accarray[user].salt, input);
                lineCount++;
                
            }
            else if (lineCount == 6)    //hashedpw
            {
                
                fgets(input, sizeof(input), inputFile);
                strcpy(accarray[user].hashedpw, input);
                lineCount++;
                
            }
            else
            {
                
                accarray[user].name[strlen(accarray[user].name) - 1] = '\0';
                accarray[user].username[strlen(accarray[user].username) - 1] = '\0';
                accarray[user].salt[strlen(accarray[user].salt) - 1] = '\0';
                
                if (!feof(inputFile))
                    accarray[user].hashedpw[strlen(accarray[user].hashedpw) - 1] = '\0';
                
                lineCount = 1;
                user++;
                * numuser = * numuser + 1;
                
            }
            
        }
        
        fclose(inputFile);
        
    }
    else
    {
        
        returnValue = -1;
        
    }
    
    return returnValue;
    
}

/*****************************************************************
 //
 //  Function name: writeFile
 //
 //  DESCRIPTION:   This function will write to the database file and store
 //                 the values of the account array in.
 //
 //  Parameters:    accarray (struct record []) : contains the list of accounts.
 //
 //                 numuser (int) : contains the number of users in the database.
 //
 //                 filename (char []) : the file to be written to
 //
 //  Return values:  returnValue : 0 if successful, -1 if file not found
 //
 ****************************************************************/

int writefile(struct record accarray[], int numuser, char filename[])
{
    int user = 0;
    int returnValue = 0;
    
    FILE * inputFile = fopen(filename, "w");
    
    if (inputFile != NULL)
    {
        if (numuser > 0)
        {
            for (user = 0; user < numuser; user++)
            {
                
                fprintf(inputFile,"%d\n%s\n%.2f\n%s\n%s\n%s\n", accarray[user].accountno, accarray[user].name, accarray[user].balance, accarray[user].username, accarray[user].salt, accarray[user].hashedpw);
                
            }
            
            fclose(inputFile);
            
        }
        else
        {
            
            returnValue = -1;
            fclose(inputFile);
            
        }
    }
    else
    {
        
        returnValue = -1;
        
    }
    
    return returnValue;

}

/*****************************************************************
 //
 //  Function name: addRecord
 //
 //  DESCRIPTION:   This function will take the address of the array which holds
 //                 the records and add a record to it based on the given parameters.
 //
 //  Parameters:    accarray (struct record []) : array which holds existing
 //                 records
 //
 //                 inaccountno (int) : inputted integer that specifies the account number
 //                 field in the record
 //
 //                 inname (char []) : inputted string which specifies the name field in
 //                 the record
 //
 //                 inusername (char []) : inputted string which specifies the
 //                 username field in the record
 //
 //                 insalt (char []) : inputted string which specifies the salt field
 //                 in the record (used for hashing).
 //
 //                 inpassword (char []) : inputted string which specifies the password
 //                 field in the record.
 //
 //                 numuser (int *) : pointer to number of users in the db
 //
 //  Return values:  -1 : record already exists in the database, therefore cannot be added
 //                   0 : record successfully added to the database
 //
 ****************************************************************/

int addRecord (struct record accarray[], int inaccountno, char inname[], char inusername[], char insalt[], char inpassword[], int * numuser)
{
    
    //srand(time(NULL));
    int returnValue;
    //int r;
    
    returnValue = 0;
    //generates random number between 0 to 10000000
    //r = rand() % 10000000;
    
    for (int i = 0; i < *numuser; i++)
    {
        if (accarray[i].accountno == inaccountno)
        {
            
            //account already exists
            returnValue = -1;
            
        }
    }
    
    if (returnValue == 0)
    {
        
        accarray[*numuser].accountno = inaccountno;
        strcpy(accarray[*numuser].name, inname);
        strcpy(accarray[*numuser].username, inusername);
        strcpy(accarray[*numuser].hashedpw, inpassword);
        accarray[*numuser].balance = 100.00;
        //snprintf(accarray[*numuser].salt, sizeof(accarray[*numuser].salt), "%d", r);
        strcpy(accarray[*numuser].salt, insalt);
        accarray[*numuser].next = NULL;

        * numuser = * numuser + 1;
    
    }
    
    return returnValue;
    
}

/*****************************************************************
 //
 //  Function name: deleteRecord
 //
 //  DESCRIPTION:   This function will take the array of records and delete the
 //                 record specified by the given account number
 //
 //  Parameters:    accarray (struct record []) : array of existing records
 //
 //                 inaccountno (int) : inputted integer that specifies the account number
 //                 field in the record
 //
 //                 numuser (int *) : pointer to number of users in the db
 //
 //  Return values:  -1 : record was not found
 //                   0 : record successfully added to the database
 //
 ****************************************************************/

int deleteRecord(struct record accarray[], int inaccountno, int * numuser)
{

    int returnValue;
    int found;
    int count;

    returnValue = 0;
    found = 0;
    count = 0;

    while(count < * numuser && found == 0)
    {
        if (accarray[count].accountno == inaccountno)
        {
            for (int i = count; i < * numuser; i++)
            {
    
                accarray[i] = accarray[i+1];
                
            }
                    
            found = 1;
            returnValue = 0;
            count++;
                    
        }
        else
        {

            count++;
            
        }
    }
    
    if(found == 0 && returnValue != -2)
    {
        
        returnValue = -1;
        
    }
    else
    {
        
        * numuser = * numuser - 1;
        
    }
    
    return returnValue;
    
}

/*****************************************************************
 //
 //  Function name: parseInput
 //
 //  DESCRIPTION:   This function will take a string and format it according
 //                 to the currency it needs to be converted to. It will also store
 //                 the value into the account array.
 //
 //  Parameters:    accarray (struct record []) : contains the list of accounts.
 //
 //                 recordno (int) : the record number returned from findRecord
 //
 //                 accountno (int) : the account number to deposit or withdraw to
 //
 //                 input (char []) : the string to parse
 //
 //                 opt (char) : the option, 'd' for deposit, 'w' to withdraw, or 'c'
 //                 to convert
 //
 //  Return values:  none
 //
 ****************************************************************/

void parseInput (struct record accarray[], int recordno, int accountno, char input[], char opt)
{
    
    float amt;
    
    if (input[0] == '$')
    {
        int i = 0;
        
        /*strip $ from input*/
        while (input[i] != '\0')
        {
            
            input[i] = input[i + 1];
            i++;
            
        }
        
        i = 0;
        
        amt = atof(input);
        
        if (opt == 'c')
        {
            
            printf("\n$%.2f converts to £%.2f or €%.2f\n", amt, convertToPounds(amt, 'd'), convertToEuros(amt, 'd'));
        
        }
        
        if (amt > accarray[recordno].balance && opt == 'w')
        {
            
            printf("Error: The amount attempted to withdraw exceeds the amount available in the account.");
        
        }
        else if ((amt <= accarray[recordno].balance || opt == 'd') && opt != 'c')
        {
            if (opt == 'd') {
            
                printf("\nDepositing $%.2f to account %d\n", amt, accountno);
                accarray[recordno].balance = accarray[recordno].balance + amt;
            
            }
            else {
        
                printf("\nWithdrawing $%.2f from account %d\n", amt, accountno);
                accarray[recordno].balance = accarray[recordno].balance - amt;
            
            }
            
            printf("New Balance: $%.2f\n", accarray[recordno].balance);
            
        }
        
    }
    /*strip pound symbol from input if unicode matches pound symbol*/
    else if (input[0] == '\xc2')
    {
        int i = 0;
        
        for (int j = 0; j < 2; j++)
        {
            while (input[i] != '\0')
            {
                
                input[i] = input[i + 1];
                i++;
                
            }
            
            i = 0;
            
        }
        
        amt = atof(input);
        
        if (opt == 'd' || opt == 'w')
        {
        
            printf("\n£%.2f converts to $%.2f", amt, convertToDollars(amt, 'p'));
            amt = convertToDollars(amt, 'p');
            
        }
        
        if (opt == 'c')
        {
            printf("\n£%.2f converts to $%.2f or €%.2f\n", amt, convertToDollars(amt, 'p'), convertToEuros(amt, 'p'));
        }
        
        if (amt > accarray[recordno].balance && opt == 'w')
        {
          
            printf("Error: The amount attempted to withdraw exceeds the amount available in the account.");
            
        }
        else if ((amt <= accarray[recordno].balance || opt == 'd') && opt != 'c')
        {
            
            if (opt == 'd') {
                
                printf("\nDepositing $%.2f to account %d\n", amt, accountno);
                accarray[recordno].balance = accarray[recordno].balance + amt;
                
            }
            else {
               
                printf("\nWithdrawing $%.2f from account %d\n", amt, accountno);
                accarray[recordno].balance = accarray[recordno].balance - amt;
            
            }
            
            printf("New Balance: $%.2f\n", accarray[recordno].balance);
            
        }
    }
    /*strip euro symbol from input if unicode matches euro symbol*/
    else if (input[0] == '\xe2' && input[1] == '\x82' && input[2] == '\xac')
    {
        
        int i = 0;
        
        for (int j = 0; j < 3; j++)
        {
            while (input[i] != '\0')
            {
                
                input[i] = input[i + 1];
                i++;
                
            }
            
            i = 0;
        
        }
        
        amt = atof(input);
        
        if (opt == 'd' || opt == 'w')
        {
            
            printf("\n€%.2f converts to $%.2f", amt, convertToDollars(amt, 'e'));
            amt = convertToDollars(amt, 'e');
            
        }
        
        if (opt == 'c')
        {
            printf("\n€%.2f converts to $%.2f or £%.2f\n", amt, convertToDollars(amt, 'e'), convertToPounds(amt, 'e'));
        }
        
        if (amt > accarray[recordno].balance && opt == 'w')
        {
           
            printf("Error: The amount attempted to withdraw exceeds the amount available in the account.");
            
        }
        else if ((amt <= accarray[recordno].balance || opt == 'd') && opt != 'c')
        {
            
            if (opt == 'd') {
                
                printf("\nDepositing $%.2f to account %d\n", amt, accountno);
                accarray[recordno].balance = accarray[recordno].balance + amt;
                
            }
            else {
             
                printf("\nWithdrawing $%.2f from account %d\n", amt, accountno);
                accarray[recordno].balance = accarray[recordno].balance - amt;
           
            }
            
            printf("New Balance: $%.2f\n", accarray[recordno].balance);
            
        }
        
    }
    else
    {
     
        printf("\nError: You've entered in an invalid currency type. Please enter the amount you'd like to withdraw with the type of currency in front of the amount. This database will only accept $, £, and €\n");
    
    }
}
