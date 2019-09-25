//
// Created by Francesco_D'Ambrosio on 20/09/2019.
//

#include "File_Manager.h"
#include "Info.h"

// int  Delta_t_prevision = 12;


int main() {
    int i = 0;
    int j = 0;
    //char filename[NCAR];
    //printf("Inserisci nome file dati: ");
    //scanf("%s", filename);
    //FILE *fp = fopen(filename, "r");
    FILE *fp = fopen(("C:\\Users\\franc\\Desktop\\Tesi\\db_04_05.dat"), "r");

    float Matrix_loaded[NUM_DATA][8];
    float Initial_Conditions[NUM_DATA][4];
    float Data_Train[NUM_DATA][2];
    float Data_Test[Delta_t_prevision][2];
    float IC_train[NUM_DATA][4];
    float IC_test[Delta_t_prevision][4];

    load_data(fp, Matrix_loaded);
    column_of_interest(Matrix_loaded, Initial_Conditions);
    matrices_of_interest(Initial_Conditions, Data_Train, Data_Test, IC_train, IC_test);
    structure_data(Data_Train, Data_Test);

    return 0;
}