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
 //  FILE:        prototypes.h
 //
 //  DESCRIPTION:
 //   This file contains the prototypes for the functions in functions.c
 //
 ****************************************************************/

#ifndef prototypes_h
#define prototypes_h

#include <stdio.h>
#include "record.h"

float convertToPounds (float, char);
float convertToDollars (float, char);
float convertToEuros (float, char);
int readfile(struct record [], int *, char []);
int writefile(struct record [], int, char []);
int findRecord(struct record [], int, int);
int deleteRecord(struct record [], int, int *);
int addRecord(struct record[], int, char [], char [], char [], char [], int *);
int authenticate(struct record [], int, char [], char [], int *);
void printAll (struct record [], int);
void parseInput (struct record[], int, int, char [], char);

//md5 hash functions


#endif /* prototypes_h */
