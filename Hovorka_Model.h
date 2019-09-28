//
// Created by Francesco_D'Ambrosio on 26/09/2019.
//

#include "Constant.h"

#ifndef DIABETS_THESIS_HOVORKA_MODEL_H
#define DIABETS_THESIS_HOVORKA_MODEL_H

void hovorka_IGDynamics_prev(float FVr_temp[I_D], float Initial_Conditions[NUM_DATA][4], int fin);

void meal_disturbance2(float meal_abs[NUM_DATA][1], float Initial_Conditions[NUM_DATA][4], float t_max_G, float A_G);
#endif //DIABETS_THESIS_HOVORKA_MODEL_H
