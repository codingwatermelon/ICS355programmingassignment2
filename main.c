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
 //  FILE:        main.c
 //
 //  DESCRIPTION:
 //   This file contains the driver for the usage of functions in
 //   the functions.c file. It also contains the UI main menu as well
 //   as the MD5 hashing algorithm.
 //
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "prototypes.h"
#include "record.h"
#include <regex.h>
#include <string.h>
#include <math.h>
#include <time.h>

/*****************************************************************
 //
 //  Function name: md5 functions
 //
 //  DESCRIPTION:   These functions (all the way down to main) are
 //                 actually the functions that implement the MD5
 //                 hashing algorithm. I've included the source in
 //                 the one page summary.
 //
 //  Parameters:    -
 //
 //  Return values:  -
 //
 ****************************************************************/

typedef union uwb{
    unsigned w;
    unsigned char b[4];
}MD5union;

typedef unsigned DigestArray[4];
unsigned func0( unsigned abcd[] ){
    return ( abcd[1] & abcd[2]) | (~abcd[1] & abcd[3]);}

unsigned func1( unsigned abcd[] ){
    return ( abcd[3] & abcd[1]) | (~abcd[3] & abcd[2]);}

unsigned func2( unsigned abcd[] ){
    return  abcd[1] ^ abcd[2] ^ abcd[3];}

unsigned func3( unsigned abcd[] ){
    return abcd[2] ^ (abcd[1] |~ abcd[3]);}

typedef unsigned (*DgstFctn)(unsigned a[]);

unsigned *calctable( unsigned *k)
{
    double s, pwr;
    int i;
    
    pwr = pow( 2, 32);
    for (i=0; i<64; i++) {
        s = fabs(sin(1+i));
        k[i] = (unsigned)( s * pwr );
    }
    return k;
}

/*Rotate Left r by N bits
 or
 We can directly hardcode below table but as i explained above we are opting
 generic code so shifting the bit manually.
 r[ 0..15] := {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22}
 r[16..31] := {5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20}
 r[32..47] := {4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23}
 r[48..63] := {6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21}
 */
unsigned rol( unsigned r, short N )
{
    unsigned  mask1 = (1<<N) -1;
    return ((r>>(32-N)) & mask1) | ((r<<N) & ~mask1);
}

unsigned *md5( const char *msg, int mlen)
{
    /*Initialize Digest Array as A , B, C, D */
    static DigestArray h0 = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476 };
    static DgstFctn ff[] = { &func0, &func1, &func2, &func3 };
    static short M[] = { 1, 5, 3, 7 };
    static short O[] = { 0, 1, 5, 0 };
    static short rot0[] = { 7,12,17,22};
    static short rot1[] = { 5, 9,14,20};
    static short rot2[] = { 4,11,16,23};
    static short rot3[] = { 6,10,15,21};
    static short *rots[] = {rot0, rot1, rot2, rot3 };
    static unsigned kspace[64];
    static unsigned *k;
    
    static DigestArray h;
    DigestArray abcd;
    DgstFctn fctn;
    short m, o, g;
    unsigned f;
    short *rotn;
    union {
        unsigned w[16];
        char     b[64];
    }mm;
    int os = 0;
    int grp, grps, q, p;
    unsigned char *msg2;
    
    if (k==NULL) k= calctable(kspace);
    
    for (q=0; q<4; q++) h[q] = h0[q];   // initialize
    
    {
        grps  = 1 + (mlen+8)/64;
        msg2 = malloc( 64*grps);
        memcpy( msg2, msg, mlen);
        msg2[mlen] = (unsigned char)0x80;
        q = mlen + 1;
        while (q < 64*grps){ msg2[q] = 0; q++ ; }
        {
            MD5union u;
            u.w = 8*mlen;
            q -= 8;
            memcpy(msg2+q, &u.w, 4 );
        }
    }
    
    for (grp=0; grp<grps; grp++)
    {
        memcpy( mm.b, msg2+os, 64);
        for(q=0;q<4;q++) abcd[q] = h[q];
        for (p = 0; p<4; p++) {
            fctn = ff[p];
            rotn = rots[p];
            m = M[p]; o= O[p];
            for (q=0; q<16; q++) {
                g = (m*q + o) % 16;
                f = abcd[1] + rol( abcd[0]+ fctn(abcd) + k[q+16*p] + mm.w[g], rotn[q%4]);
                
                abcd[0] = abcd[3];
                abcd[3] = abcd[2];
                abcd[2] = abcd[1];
                abcd[1] = f;
            }
        }
        for (p=0; p<4; p++)
            h[p] += abcd[p];
        os += 64;
    }
    return h;
}

/*****************************************************************
 //
 //  Function name: main
 //
 //  DESCRIPTION:   This function contains the UI and functions calls to
 //                 create a financial calculator program.
 //
 //  Parameters:    none
 //
 //  Return values:  0
 //
 ****************************************************************/

int main(int argc, const char * argv[])
{
    struct record accdb[100];
    int accountno = 0;
    int option = 0;
    int auth = 0;
    int recordno = 0;
    int numusers;
    int temp = 0;
    int count = 0;
    int currSession = 0;
    int currRecordno = 0;
    char optionbuff[20], accountnobuff[20], amtBuf[50], conv[50], nameBuf[50], usernameBuf[50], passwordBuf[50], saltBuf[20];
    //for adding records
    char name[30], username[30], salt[30], password[30];
    
    char inUsername[50];
    char inPassword[50];
    char inSalt[50];
    char hashedinPassword[100];
    char buffer[20];
    
    readfile(accdb, &numusers, "accdb.txt");
    
    printf("Welcome to UHICS355FinProgram v2.0. Please login.\n");
    
    //implement too many pw requests error
    while (auth == 0)
    {
        memset(inUsername, 0, sizeof(inUsername));
        printf("Username: ");
        
        fgets(inUsername, sizeof(inUsername), stdin);
        inUsername[strlen(inUsername) - 1] = '\0';
        
        memset(inPassword, 0, sizeof(inPassword));
        printf("Password: ");
        
        fgets(inPassword, sizeof(inPassword), stdin);
        inPassword[strlen(inPassword) - 1] = '\0';
        
        while (count < numusers)
        {
            if (strcmp(accdb[count].username, inUsername) == 0)
            {
                for (int i = 0; i < strlen(accdb[count].salt); i++)
                {
                    //store salt from db into currsession salt
                    snprintf(saltBuf, sizeof(saltBuf), "%c", accdb[count].salt[i]);
                    strcat(inSalt, saltBuf);
                
                }
            }
            
            count++;
        
        }
        
        //salts password
        strcat(inPassword, inSalt);
        
        //hash password+salt
        int j,k;
        //printf("Input String to be Encrypted using MD5 : \n\t%s", inPassword);
        unsigned *d = md5(inPassword, strlen(inPassword));
        MD5union u;
        //printf("\n\n\nThe MD5 code for input string is : \n");
        //printf("\t= ");
        
        memset(hashedinPassword, 0, sizeof(hashedinPassword));
        
        for (j=0; j<4; j++){
            
            u.w = d[j];
            
            for (k=0; k<4; k++)
            {
                //store hashed pw into array
                //printf("%02x",u.b[k]);
                snprintf(buffer, sizeof(buffer), "%02x", u.b[k]);
                strcat(hashedinPassword, buffer);

            }
        }
        
        if (authenticate(accdb, numusers, inUsername, hashedinPassword, &currSession) == 1)
        {
            
            printf("\nSuccessfully authenticated. Hello %s!\n", inUsername);
            auth = 1;
        
        }
        else if (authenticate(accdb, numusers, inUsername, hashedinPassword, &currSession) == -1)
        {
         
            printf("\nIncorrect password. Try again.\n");
        
        }
        else
        {
            
            printf("\nUsername not found. Try again.\n");
        
        }
    }
    
    //begin menu
    
    printf("\nWelcome to the financial database for UH ICS 355.\nHere, you can update and view user account balances in the record. Please note, at this time, we can only accept values of USD ($), UK Pound (£), and Euro (€).\n");
    
    while (option != 8)
    {
        
        printf("\n*--------------------------------*\n");
        printf("Main Menu\n");
        printf("1) Withdraw money from an account\n");
        printf("2) Deposit money to an account\n");
        printf("3) Transfer money from one account to another\n");
        printf("4) Print all records\n");
        printf("5) Currency conversion\n");
        printf("6) Add user to database\n");
        printf("7) Delete user from database\n");
        printf("8) Exit");
        printf("\n*--------------------------------*\n");
        printf("\nPlease select one of the options using its number: ");
        
        fgets(optionbuff, sizeof(optionbuff), stdin);
        option = atoi(optionbuff);
        
        if (option < 1 || option > 8)
        {
            printf("\nPlease enter a number from 1 to 8.\n");
        }
        
        if (option == 1)        //withdraw money
        {
            printf("\nEnter the number of the account which you want to withdraw money from: ");
            fgets(accountnobuff, sizeof (accountnobuff), stdin);
            accountno = atoi(accountnobuff);
            
            recordno = findRecord(accdb, accountno, numusers);
            
            if (recordno != 0)
            {
            
                printf("\nEnter the amount of money you would like to withdraw from this account, indicating the type of currency in front of the amount (e.g. $3150.02, £10.52, etc.): ");
                fgets(amtBuf, sizeof(amtBuf), stdin);
                //parses the raw input and strips the currency type and will convert if necessary
                parseInput(accdb, recordno - 1, accountno, amtBuf, 'w');
            
            }
            else
            {
                
                printf("\nError: Couldn't find an existing record with that account number.\n");
            
            }
        }
        if (option == 2)   //deposit money
        {
            printf("\nEnter the number of the account which you want to deposit money to: ");
            fgets(accountnobuff, sizeof (accountnobuff), stdin);
            accountno = atoi(accountnobuff);
            
            recordno = findRecord(accdb, accountno, numusers);
            
            if (recordno != 0)
            {
                
                printf("\nEnter the amount of money you would like to deposit into this account, indicating the type of currency in front of the amount (e.g. $3150.02, £10.52, etc.): ");
                fgets(amtBuf, sizeof(amtBuf), stdin);
                parseInput(accdb, recordno - 1, accountno, amtBuf, 'd');
                
            }
            else
            {
                
                printf("\nError: Couldn't find an existing record with that account number.\n");
            
            }
        }
        if (option == 3)   //transfer money
        {
            //grab user accountno from login (currSession)
            printf("\nEnter the number of the account which you want to transfer money to: ");
            fgets(accountnobuff, sizeof (accountnobuff), stdin);
            accountno = atoi(accountnobuff);
            
            recordno = findRecord(accdb, accountno, numusers);
            currRecordno = findRecord(accdb, currSession, numusers);
            
            if (recordno != 0)
            {
                char temp[50];
                memset(temp, 0, sizeof(temp));
                
                printf("\nEnter the amount of money you would like to transfer into this account, indicating the type of currency in front of the amount (e.g. $3150.02, £10.52, etc.): ");
                fgets(amtBuf, sizeof(amtBuf), stdin);
                strcpy(temp, amtBuf);
                parseInput(accdb, currRecordno - 1, currSession, amtBuf, 'w');
                parseInput(accdb, recordno - 1, accountno, temp, 'd');
                
            }
            else
            {
                
                printf("\nError: Couldn't find an existing record with that account number.\n");
                
            }

        
        }
        if (option == 4)   //print all records
        {
            
            printAll(accdb, numusers);
  
        }
        if (option == 5)   //currency conversion
        {
            
            printf("\nEnter the currency you'd like to convert (e.g. $3150.02, £10.52, etc.): ");
            fgets(conv, sizeof(conv), stdin);
            parseInput(accdb, recordno, accountno, conv, 'c');
            
        }
        if (option == 6 && currSession == 12345)   //add user
        {
            
            printf("\nEnter the account number of the record: ");
            fgets(accountnobuff, sizeof(accountnobuff), stdin);
            accountno = atoi(accountnobuff);
            
            printf("\nEnter the name of the account holder: ");
            fgets(nameBuf, sizeof(nameBuf), stdin);
            strcpy(name, nameBuf);
            name[strlen(name) - 1] = '\0';
            
            printf("\nEnter the username of the account: ");
            fgets(usernameBuf, sizeof(nameBuf), stdin);
            strcpy(username, usernameBuf);
            username[strlen(username) - 1] = '\0';
            
            printf("\nEnter the password for the account: ");
            fgets(passwordBuf, sizeof(passwordBuf), stdin);
            strcpy(password, passwordBuf);
            password[strlen(password) - 1] = '\0';
            
            //lazy coding
            //generate salt
            srand(time(NULL));
            int r;
            r = rand() % 10000000;
             
            snprintf(salt, sizeof(salt), "%d", r);
            
            //salts password
            strcat(password, salt);
            
            //hash password+salt
            int l,m;
            //printf("Input String to be Encrypted using MD5 : \n\t%s", password);
            unsigned *e = md5(password, strlen(password));
            MD5union y;
            //printf("\n\n\nThe MD5 code for input string is : \n");
            //printf("\t= ");
            
            memset(hashedinPassword, 0, sizeof(hashedinPassword));
            memset(buffer, 0, sizeof(buffer));
            
            for (l=0; l<4; l++){
                
                y.w = e[l];
                
                for (m=0; m<4; m++)
                {
                    //store hashed pw into array
                    //printf("%02x",y.b[m]);
                    snprintf(buffer, sizeof(buffer), "%02x", y.b[m]);
                    strcat(hashedinPassword, buffer);
                    
                }
            }
            
            if (addRecord(accdb, accountno, name, username, salt, hashedinPassword, &numusers) == -1)
            {
                
                printf("\nError: Account already exists\n");
                
            }
            else
            {
                
                printf("\nSuccess: Account added\n");
                printf("\nNew accounts automatically come with $100.00. Go wild!\n");
                
            }
        }
        else if (currSession != 12345 && option != 8)
        {
            
            printf("\nError: Insufficient permissions. Only administrators may add accounts.\n");
            
        }
        if (option == 7 && currSession == 12345)   //delete user
        {
            
            printf("\nEnter the account number of the record to delete: ");
            fgets(accountnobuff, sizeof(accountnobuff), stdin);
            accountno = atoi(accountnobuff);
            
            if (accountno != 12345)
            {
            
                temp = deleteRecord(accdb, accountno, &numusers);
           
            }
            else
            {
                
                printf("\nYou can't delete the administrator account!");
            
            }
            
            if (temp == -2)
            {
                
                printf("\nError: List is empty\n");
                
            }
            else if (temp == -1)
            {
                
                printf("\nError: Record not found, account doesn't exist\n");
                
            }
            else
            {
                
                printf("\nSuccess: Record deleted\n");
                
            }
            
            temp = 0;
            
        }
        else if (currSession != 12345 && option != 8)
        {
            
            printf("\nError: Insufficient permissions. Only administrators may delete accounts.\n");
            
        }
        
    }
    
    writefile(accdb, numusers, "accdb.txt");
    
    return 0;

}
