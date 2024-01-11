/*
* Nom: Projet final INF1900
* Arman Lidder : 2174916  - Hamza Boukaftane : 2183376
* Loic Nguemegne-Temena : 2180845 - Jonathan Arrobas-Gilbert: 2120128
* Equipe #57-#58

Ceci est le fichier main de l'ensemble du projet. Nous avons implementer une machine a etat permettant de choisir 
sur quel parcours nous voulons commencer. Si on choisi le parcours B, on rentre automatiquement dans le parcours S
apres que nous avons fini le parcous B.
Voici la table d'etats :

+------------+----------------+---------------+-----------+
|    Etat    |     Entree     | Prochain etat |  Sortie   |
+------------+----------------+---------------+-----------+
| PARCOURS S | BOUTTON APPUYE | PARCOURS A    | LED VERT  |
| PARCOURS A | BOUTTON APPUYE | PARCOURS B    | LED ROUGE |
| PARCOURS B | BOUTTON APPUYE | PARCOURS S    | LED AMBRE |
+------------+----------------+---------------+-----------+

Apres qu'on a le parcours voulu avec la bonne LED, il faut appuyer le bouton poussoir integre sur la carte
afin de confirmer notre choix.

Le programme joue une chanson a la fin apres le stationnement du robot.
*/

#include "selectRoute.h"
#include "FollowLineTrajetA.h"
#include "FollowLineTrajetB.h"
#include "targetSVisitor.h"


volatile bool isRouteS = false;
volatile bool timerDone = false;

ISR(TIMER1_COMPA_vect)
{
    TCNT1 = 0;
    if (isRouteS)
        timerDone = true;
    else
    {
        Timer timerBInterruption;
        timerBInterruption.stopTimer();
        Motor motorInterruption(FORWARD, FORWARD, ZERO, ZERO);
        adjustMotor(motorInterruption);
    }
}

int main()
{
    int route = selectRoute();
    switch (route)
    {
    case 0:
        followRouteA();
        break;
    case 1:
        followRouteB();
    case 2:
        isRouteS = true;
        followRouteS();
        Sound music;
        music.playGodfather();
        break;
    }
    return 0;
}