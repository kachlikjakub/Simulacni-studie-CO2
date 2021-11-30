# Simulační studie CO2
Autoři: Jakub Kachlík a Ondřej Dacer

Semestrální projekt 2019/2020 předmětu Modelování a simulace: Uhlíková stopa v zemědělství, lesnictví a zpracovatelském průmyslu.

Program počítá přibližnou rozlohu lesů (*ha*) v České republice v průběhu let a jejich vliv na absorbci CO2, vzhledem k průměrným statickým hodnotám produkce z minulých let. V každé iteraci program požaduje 2 vstupy: 
- podíl nově vysázených listnatých stromů (*%*)
- množství zasazených lesů (*ha*)

Program je ukončen po 12 cyklech (letech).
### Spuštění:
Pro překlad:
```sh
make
```
Pro spuštění:
```sh
make run
```

Pro dokončení jednotlivých cyklů je nutné vždy zadat dvojici údajů o poměru a počtu zasazených stromů. Simulační model je ukončen po 12 iteracích, jejichž průběh a rozdíly můžeme sledovat na standartním výstupu.

### Výstup:
Po spuštění programu:

```
ROK 2018
------------------------------------------------------
Jehličnaté lesy (ha): 1862445
Listnaté lesy (ha): 711706

ROK 2019
------------------------------------------------------
Procento zasazených listnatých stromů v roce 2019: INPUT
Počet hektarů nového lesa v roce 2019: INPUT
```
Po zadání vstupů (např. 50 a 10 000) dojde k výpočtu hodnot pro následující rok.
```
------------------------------------------------------
Nový poměr stromů (listnaté : jehličnaté) pro rok 2019 = 27 % : 72 %
------------------------------------------------------
Umělé zalesnění jehličnatých lesů (ha): +5000
Přirozené zalesnění jehličnatých lesů (ha): +2357
Vykáceno jehličnanů (ha): -25064
Jehličnaté lesy (ha): 1844738
------------------------------------------------------
Umělé zalesnění listnatých lesů (ha): +5000
Přirozené zalesnění listnatých lesů (ha): +1718
Vykáceno listnáčů (ha): -1528
Listnaté lesy (ha): 716896
------------------------------------------------------
Produkce CO2 (megatun): 103,88
Absorbováno našimi lesy CO2 (megatun): 29.04 (27.96 %)
------------------------------------------------------
```
A následuje další iterace vyžadující uživatelský vstup.
