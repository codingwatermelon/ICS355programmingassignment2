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
 //  FILE:        record.h
 //
 //  DESCRIPTION:
 //   This file contains the record definition for the account
 //   array structure.
 //
 ****************************************************************/

#ifndef record_h
#define record_h

#include <stdio.h>

struct record
{
    int              accountno;
    char             name[25];
    float            balance;
    char             username[25];
    char             salt[100];
    char             hashedpw[100];
    struct record* next;
    
};
#endif /* record_h */
