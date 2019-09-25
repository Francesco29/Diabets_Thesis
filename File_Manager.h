//
// Created by Francesco_D'Ambrosio on 21/09/2019.
//

#include "Constant.h"

#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

// This function reads data from a file
void load_data(FILE *fp, float Matrix_loaded[NUM_DATA][8]);

// This function modify the ins basal column (colomn1); then it produces a matrix with only four column:
// glucose - ins basal - ins - cho
// The Matrix of interest is Initial_Conditions because contain the column with correct values of ins basal.
void column_of_interest(float Matrix_loaded[NUM_DATA][8], float Initial_Conditions[NUM_DATA][4]);

// This function contains: Data_Train, Data_Test, IC_Train and IC_Test
void matrices_of_interest(float Initial_Conditions[NUM_DATA][4], float Data_Train[NUM_DATA][2], float Data_Test[Delta_t_prevision][2], float IC_train[NUM_DATA][4], float IC_test[Delta_t_prevision][4]);


#endif /*FILE_MANAGER_H*/
