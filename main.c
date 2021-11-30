//
//  main.c
//  IMS_CO2
//
//  Created by Jakub Kachlik and Ondrej Dacer on 08/12/2019.
//

#include <stdio.h>
#include <string.h>

#define M3_NA_HEKTAR 966
#define AKRU_NA_HEKTAR 2.471
#define STROMU_NA_AKR 700

#define PRIROZENE_ZALESNENI_JEHLICNANY 2357 //(ha)
#define PRIROZENE_ZALESNENI_LISTNATE 1718 //(ha)

#define JEHLICNANY_2018 1862445 //(ha)
#define LISTNATE_2018 711706 //(ha)

#define TEZBA_JEHLICNANY_2019 24212510 //(m3)
#define TEZBA_JEHLICNANY_2020 22500000 //(m3)
#define TEZBA_JEHLICNANY_2021 21000000 //(m3)
#define TEZBA_JEHLICNANY_2022 19000000 //(m3)
#define TEZBA_JEHLICNANY_2023 17000000 //(m3)

#define TEZBA_JEHLICNANY_STANDART 15066146 //(m3)
#define TEZBA_LISTNATE 1476275 //(m3)

#define PRUMERNY_VEK 51.2 //let

#define ZACATEK_SIMULACE 2018 //rok
#define DELKA_PROJEKTU 12 //let


//funkce, ktera provadi zakladni upravy promenne aktualniho roku a prumerneho veku stromu
void cycleChange(int *rok, float *prumerny_vek, int *celkem_lesy, int *umele_zalesneni ){
    *rok=*rok+1;
    *prumerny_vek = ((*celkem_lesy * *prumerny_vek) + (*umele_zalesneni * 1)) / (*celkem_lesy + *umele_zalesneni);
    return;
}

// funkce, zarizujici vstupy od uzivatele
void inputFunction(double *listnate_pomer, double *jehlicnate_pomer, int *umele_zalesneni, int *rok){
        printf("ROK %d\n",*rok);
        printf("------------------------------------------------------\n");
           int tmp;
           printf("Procento zasazených listnatých stromů v roce %d: ", *rok);
           scanf("%d", &tmp);
           *listnate_pomer = tmp;
           *jehlicnate_pomer = 100 - *listnate_pomer;
           printf("Počet hektarů nového lesa v roce %d: ", *rok);
           scanf("%d", &tmp);
           *umele_zalesneni = tmp;
}

//funkce, upravujici mnozstvi absorbovaneho CO2 vzhledem k prumernemu veku stromu
void ageChanger(float *prumerny_vek, double *absorpce_jehlicnany, double *absorpce_listnate){
    if (*prumerny_vek < 10){
        *absorpce_jehlicnany = 2;
        *absorpce_listnate = 0.45;
    }
    else if (*prumerny_vek < 15){
        *absorpce_jehlicnany = 4;
        *absorpce_listnate = 0.684;

    }
    else if (*prumerny_vek < 20){
        *absorpce_jehlicnany = 5.5;
        *absorpce_listnate = 0.912;

    }
    else if (*prumerny_vek < 25){
        *absorpce_jehlicnany = 6;
        *absorpce_listnate = 1.14;

    }
    else if (*prumerny_vek < 30){
        *absorpce_jehlicnany = 6.8;
        *absorpce_listnate = 1.20;

    }
    else if (*prumerny_vek < 35){
        *absorpce_jehlicnany = 7.3;
        *absorpce_listnate = 1.27;

    }
    else if (*prumerny_vek < 40){
        *absorpce_jehlicnany = 7.7;
        *absorpce_listnate = 1.34;

    }
    else if (*prumerny_vek < 45){
        *absorpce_jehlicnany = 8.1;
        *absorpce_listnate = 1.41;

    }
    else if (*prumerny_vek < 50){
        *absorpce_jehlicnany = 8.5;
        *absorpce_listnate = 1.48;

    }
    else if (*prumerny_vek < 55){
        *absorpce_jehlicnany = 8.5;
        *absorpce_listnate = 1.55;

    }
    else if (*prumerny_vek < 60){
        *absorpce_jehlicnany = 8.3;
        *absorpce_listnate = 1.62;

    }
    else if (*prumerny_vek < 65){
        *absorpce_jehlicnany = 8.1;
        *absorpce_listnate = 1.69;

    }
    else if (*prumerny_vek < 70){
        *absorpce_jehlicnany = 7.9;
        *absorpce_listnate = 1.75;

    }
}


//funkce, upravujici velikost tezby jehlicnatych stromu vzhledem k ustupujici kurovcove kalamite
void tezbaChanger(int *rok, int *tezba_jehlicnate){
    if (*rok == 2019) {
        *tezba_jehlicnate  = TEZBA_JEHLICNANY_2019 / M3_NA_HEKTAR;
    }
    else if (*rok == 2020) {
        *tezba_jehlicnate  = TEZBA_JEHLICNANY_2020 / M3_NA_HEKTAR;
    }
    else if (*rok == 2021) {
        *tezba_jehlicnate  = TEZBA_JEHLICNANY_2021 / M3_NA_HEKTAR;
    }
    else if (*rok == 2022) {
        *tezba_jehlicnate  = TEZBA_JEHLICNANY_2022 / M3_NA_HEKTAR;
    }
    else if (*rok == 2023) {
        *tezba_jehlicnate  = TEZBA_JEHLICNANY_2023 / M3_NA_HEKTAR;
    }
    else {
        *tezba_jehlicnate = TEZBA_JEHLICNANY_STANDART / M3_NA_HEKTAR;
    }
}


// funkce, menici hodnoty lesu na nove ziskane vypocty
void changeCounter(int *listnate, int *tezba_jehlicnate, int *tezba_listnate, int *jehlicnany, int *celkem_lesy, int *umele_zalesneni, double *jehlicnate_pomer, double *listnate_pomer, double *absorpce_jehlicnany, double *absorpce_listnate, float *co2){
    *listnate = *listnate + PRIROZENE_ZALESNENI_LISTNATE - *tezba_listnate + ((*umele_zalesneni * *listnate_pomer) / 100);
           *jehlicnany = *jehlicnany + PRIROZENE_ZALESNENI_JEHLICNANY - *tezba_jehlicnate + ((*umele_zalesneni * *jehlicnate_pomer) / 100);
           *celkem_lesy = *listnate + *jehlicnany;
          
           // CO2 prepocitana na strom * prumerny vek * pocet jehl/list * absorpce dle veku
           *co2 = (STROMU_NA_AKR * AKRU_NA_HEKTAR * (*jehlicnany * *absorpce_jehlicnany)) / 1000000000 + (STROMU_NA_AKR * AKRU_NA_HEKTAR *(*listnate * *absorpce_listnate)) / 1000000000;
}


//funkce pro vypis ziskanych hodnot a statistik
void changesPrinter(int *rok, int *listnate, int *jehlicnany, int * umele_zalesneni, double * listnate_pomer, double *jehlicnate_pomer, int *tezba_listnate, int *tezba_jehlicnate, float *co2){
    printf("------------------------------------------------------\n");
    printf("Nový poměr stromů (listnaté : jehličnaté) pro rok %d = %.2d %% : %.2d %%\n",*rok ,*listnate*100/(*listnate+*jehlicnany),*jehlicnany*100/(*listnate+*jehlicnany));
    printf("------------------------------------------------------\n");
    printf("Umělé zalesnění jehličnatých lesů (ha): +%.0f\n", ((*umele_zalesneni * *jehlicnate_pomer) / 100));
    printf("Přirozené zalesnění jehličnatých lesů (ha): +%d\n", PRIROZENE_ZALESNENI_JEHLICNANY);
    printf("Vykáceno jehličnanů (ha): -%d\n", *tezba_jehlicnate);
    printf("Jehličnaté lesy (ha): %d\n", *jehlicnany);
    printf("------------------------------------------------------\n");
    printf("Umělé zalesnění listnatých lesů (ha): +%.0f\n", ((*umele_zalesneni * *listnate_pomer) / 100));
    printf("Přirozené zalesnění listnatých lesů (ha): +%d\n", PRIROZENE_ZALESNENI_LISTNATE);
    printf("Vykáceno listnáčů (ha): -%d\n", *tezba_listnate);
    printf("Listnaté lesy (ha): %d\n", *listnate);
    printf("------------------------------------------------------\n");
    printf("Produkce CO2 (megatun): 103,88\n");
    printf("Absorbováno našimi lesy CO2 (megatun): %.2f (%.2f %%)\n", *co2, 100 * *co2 / 103.88);
    printf("------------------------------------------------------\n\n");
}





int main(int argc, const char * argv[]) {

    if (argc==2 && !strcmp(argv[1], "help")) {
        printf("1. argument - procentuální rozložení listnáčů\n2. argument - procentuální rozložení jehličnanů\n3. argument - kolik každý rok zasadíme nových hektarů lesa\n4. argument - kolikrát se bude sázení opakovat (počet let)\n");
        return 0;
    }

    int jehlicnany = JEHLICNANY_2018;
    int listnate = LISTNATE_2018;
    int rok = ZACATEK_SIMULACE;
    float prumerny_vek = PRUMERNY_VEK;
    double listnate_pomer, jehlicnate_pomer;
    int celkem_lesy = jehlicnany + listnate;
    int tezba_jehlicnate,  umele_zalesneni;
    int tezba_listnate = TEZBA_LISTNATE / M3_NA_HEKTAR;
    double absorpce_jehlicnany, absorpce_listnate;
    float co2 = 0;
    
    printf("\nROK 2018\n------------------------------------------------------\nJehličnaté lesy (ha): %d\nListnaté lesy (ha): %d\n\n", jehlicnany, listnate);
   


    for (int i = 0; i < DELKA_PROJEKTU; i++) {
        cycleChange(&rok, &prumerny_vek, &celkem_lesy, &umele_zalesneni);
        inputFunction(&listnate_pomer, &jehlicnate_pomer, &umele_zalesneni, &rok);
        ageChanger(&prumerny_vek, &absorpce_jehlicnany, &absorpce_listnate);
        tezbaChanger(&rok, &tezba_jehlicnate);
        changeCounter(&listnate, &tezba_jehlicnate, &tezba_listnate, &jehlicnany, &celkem_lesy, &umele_zalesneni, &jehlicnate_pomer, &listnate_pomer, &absorpce_jehlicnany, &absorpce_listnate, &co2);
        changesPrinter(&rok, &listnate, &jehlicnany, &umele_zalesneni, &listnate_pomer, &jehlicnate_pomer, &tezba_listnate, &tezba_jehlicnate, &co2);

    }
    
    return 0;
}
