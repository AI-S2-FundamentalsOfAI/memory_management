# Memory Management in C++ door middel van het implementeren van een string-based Hash Map


(c) 2024 Hogeschool Utrecht<br>
Auteurs: David Isaacs Paternostro en Nick Roumimper

* Studentnummer:
* Naam:
* Datum:

## Inleiding
In deze opdracht gaan we zelf een HashMap implementeren. De bedoelde werking hiervan zal worden behandeld tijdens een van de komende colleges, 
Echter, conceptueel kun je dit datatype zien als een opzoektabel: gegeven een key, vertalen we die key naar een geëncodeerde variant ervan (een hash), 
wat ons een positie geeft om een waarde (value) mee terug te geven. Als je dat in de oren klinkt als een dictionary-achtig object in het gebruik, 
dan heb je goed opgelet.

Belangrijke hint: de exit code van het programma is bij de eerste uitvoering geen 0 (lees: er gaat dus iets mis). Pas als alle tests slagen en je code 
draait eindigt het programma met een 0! Dit is een voorwaarde voor een geldige inlevering.

## Relevante bronnen

De oplettende lezer zal zien dat de termen hash table en hash map allebei gebruikt worden, er zijn kleine technische verschillen maar voor deze 
opdracht kan je die negeren.

### Hash maps
- https://www.youtube.com/watch?v=FsfRsGFHuv4&t=320s
- https://en.wikipedia.org/wiki/Hash_table
- https://en.wikipedia.org/wiki/Hash_function
- https://martin.ankerl.com/2022/08/27/hashmap-bench-01/

### C++ 
- https://cplusplus.com/doc/tutorial/pointers/
- https://cplusplus.com/doc/tutorial/dynamic/
- https://cplusplus.com/doc/tutorial/structures/


## Vooronderzoek
In deze opdracht spelen eigenlijk drie uitdagingen centraal
1. We moeten bewuste keuzes maken bij onze implementatie voor onze Hash map
2. We gaan handmatig geheugen dynamisch alloceren op de heap en weer vrijgeven
3. We gaan voor het eerst objecten maken in C++

Voor onderdeel 1 vragen we van jullie om in eigen woorden de volgende keuzes te verantwoorden:

- **Kies je methode voor collision resolution**, open addressing of met separate chaining. Verklaar je keuze.
- **Kies je load factor**, je kan initieel kiezen voor een vaste grootte voor m (aantal buckets), maar je kan voor extra uitdaging ook kijken naar een dynamische grootte.
- **Kies je hashfunction**, verwerk in je antwoord de woorden **Uniformiteit en Effeciëntie**, maak sowieso een keuze voor een hashfunctie die je begrijpt en denkt te kunnen implementeren.


## Implementatie
In deze opdracht is al een boel voor je opgezet. Het is aan jou om bij de plekken waar nog TODO staat te zorgen dat je werkende code implementeert.


## Aanpak
Het is belangrijk bij deze opdracht dat je bewuste keuzes maakt, er wordt van jullie gevraagd code te voorzien van commentaar. Op basis van dit 
commentaar kunnen de docenten beoordelen of je de opdracht goed begrepen hebt. De belangrijkste regels om te commenten zijn die waar je geheugen 
dynamisch alloceert of weer vrij maakt. Verder laten we het aan jou over om te bepalen wat handig is om te voorzien van commentaar. Het is altijd jouw 
verantwoordelijkheid om te zorgen dat anderen (incluis je toekomstige zelf) jouw code goed begrijpen.
<br>
Daarnaast zijn er testfuncties voor jullie geschreven. Deze testen verschillende situaties af. De tests moeten allemaal slagen op één na **"test_create_and_delete_hashmap"**. 
Deze testfunctie is wat apart, het is vrij lastig om een test te schrijven die voor alle platformen goed checkt of je geheugen weer is vrijgegeven. 
Wanneer de code na het printen van "after deletion" nog steeds keys print dan weet je dat je hashmap niet juist is gedelete.


## Experiment
Een van de tests **"test_random_keys**" is een opzet om te kijken hoe efficiënt je implementatie is. Dit is een stresstest maar ook een opzetje om je
eigen experiment op te zetten of bijvoorbeeld te vergelijken met je klasgenoten.

