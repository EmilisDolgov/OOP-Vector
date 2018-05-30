# OOP-Vector

# [v1.0](https://github.com/EmilisDolgov/OOP-Vector/releases/tag/1.0)

 * Palygintos Vector ir std::vector push_back funkcijos
 * Eksperimentas pakartotas su flagais
 * Trečioje užduotyje panaudotas Vector ir palygintas

Vector vs std::vector

 |Konteinerio dydis|10000|100000|1000000|10000000|
 |---|---|---|---|---|
 |Vector|0.000663891|0.0036386s|0.0280456s|0.37947s|
 |std::vector|0.018062s|0.0734953s|0.852324s|7.27299s|
 
Vector vs std::vector (O1 flagas)

 |Konteinerio dydis|10000|100000|1000000|10000000|
 |---|---|---|---|---|
 |Vector|0.00030336s|0.00435967s|0.036241s|0.31678s|
 |std::vector|0.00796499s|0.0982569s|0.961401s|10.21s|
 
Vector vs std::vector (O2 flagas)

 |Konteinerio dydis|10000|100000|1000000|10000000|
 |---|---|---|---|---|
 |Vector|0.000403625s|0.00402388s|0.0301461s|0.382363s|
 |std::vector|0.00991272s|0.0828482s|0.816418s|10.3513s|

Vector vs std::vector (O3 flagas)

 |Konteinerio dydis|10000|100000|1000000|10000000|
 |---|---|---|---|---|
 |Vector|0.000757332s|0.00415402s|0.0355131s|0.327405s|
 |std::vector|0.0195417s|0.0859851s|0.918084s|10.0678s|
 
Vector

 |Konteinerio dydis|10|100|1000|10000|100000|
 |---|---|---|---|---|---|
 |Pirma strategija|0.00186765s|0.0103018s|0.0706055s|0.704054s|6.64594s|
 |Antra strategija|0.00151381s|0.00574292s|0.0608135s|0.613784s|5.80709s|
 
std::vector

 |Konteinerio dydis|10|100|1000|10000|100000|
 |---|---|---|---|---|---|
 |Pirma strategija|0.00141653s|0.00717012s|0.0547775s|0.545008s|5.18568s|
 |Antra strategija|0.000847784s|0.00481321s|0.0243874s|0.234436s|2.36744s|

 
 

 
