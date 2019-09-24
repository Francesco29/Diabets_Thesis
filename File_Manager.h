//
// Created by Francesco_D'Ambrosio on 21/09/2019.
//

#include <stdio.h>
#include <stdlib.h>

#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H


#define NCAR 100
#define NUM_DATA 285

// This function reads data from a file
void load_data(FILE *fp, float Matrix_loaded[NUM_DATA][8]);
// This fucntion modify the ins basal column (colomn1); then it produces a matrix with only four column:
// glucose - ins basal - ins - cho
// The Matrix of interest is Initial_Conditions because contain the column with correct values of ins basal.
void column_of_interest(float Matrix_loaded[NUM_DATA][8], float Initial_Conditions[NUM_DATA][4]);

#endif /*FILE_MANAGER_H*/
