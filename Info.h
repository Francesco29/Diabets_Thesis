//
// Created by Francesco_D'Ambrosio on 25/09/2019.
//
#include "Constant.h"

#ifndef DIABETS_THESIS_INFO_H
#define DIABETS_THESIS_INFO_H

struct S_struct
{
    int FVr_bound[1][I_D];
    int I_lentol;

    int FVr_x[NUM_DATA][1];
    int FVr_x_lim_up;
    int FVr_x_lim_lo;
    float FVr_y[NUM_DATA][1];
    float FVr_y_lim_up;
    float FVr_y_lim_lo;
    int FVr_n;

    int FVr_xte[Delta_t_prevision][1];
    int FVr_xte_lim_up;
    int FVr_xte_lim_lo;
    float FVr_yte[Delta_t_prevision][1];
    float FVr_yte_lim_up;
    float FVr_yte_lim_lo;
    int FVr_nte;

    int I_NP;
    float F_weight;
    float F_CR;
    int ID;
    int FVr_minbound[1][I_D];
    int FVr_maxbound[1][I_D];
    int I_bnd_constr;
    int I_itermax;
    float F_VTR;
    int I_strategy;
    int I_refresh;
    int I_plotting;
} Info;

// This procedure contains the value of structure
void structure_data(float Data_Train[NUM_DATA][2], float Data_Test[Delta_t_prevision][2]);

#endif //DIABETS_THESIS_INFO_H
