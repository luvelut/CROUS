#include "projet_fct.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLEETUD 20

/* Programme : projet_fct.c
 * Auteurs : MOMMALIER Victor, VELUT Lucile et PONCET Clara.
 * Date : 15/12/2019
 * Finalité : Gérer les demandes de logements du CROUS */

//-----
//CHARGEMENT DES LOGEMENTS DANS UN TABLEAU
//-----

Adresse  fchargeAdresse(FILE *fe)
/*Nom : fchargeAdresse
 * Finalité : Charge les adresses des cités dans un tableau.
 * Description générale : Reçoit le fichier contenant les informations sur les cités, charge les adresses des cités dans un tableau et renvoie ce tableau.
 * Variables : adresse		variable structurée
 * 			   fe			Fichier à lire */

{
    Adresse adresse;
    fscanf(fe,"%d", &adresse.NumRue);
    fscanf(fe,"%s", adresse.NomRue);
    fscanf(fe,"%d", &adresse.CodePost);

    return adresse;
}


int fChargeLgments(Logements *tLogements, int TAILLELOG)
/* Nom : fChargeLgments
 * Finalité : Charge les informations concernant les logements dans un tableau.
 * Description générale : Reçoit un pointeur sur le tableau tLogement, lit le fichier contenant les informations sur les cités, charge les informations dans le tableau, appelle à la fonction fchargeAdresse et renvoie la taille du tableau.
 * Variables : *tLogement	Pointeur sur le tableau contenant les informations des logements
 * 			   fe			Fichier à lire
 * 			   Log			logement (variable structurée Logements)
 * 			   IdLogement	identifiant du logement
 *             Nom_cite		nom de la cité étudiante
 *  		   adresse		adresse du logement (variable structurée Adresse)
 * 			   adapte		A si adapté ( et P sinon ??????? (pas sur))
 * 			   typeLogement	C chambre, S studio, T1 ou T2
 * 			   disponibilite D si disponible, I sinon
 * 			   idEtudiant	identifiant de l'étudiant
 * 			   n			Taille du tableau
 * 			   i 			compteur*/
{
    FILE *fe;
    Logements Log;

    fe=fopen("logements.txt","r");
    if(fe==NULL) {printf("Pb ouverture fichier Logements"); exit(1);}

    int n,i=0;
    fscanf(fe,"%d", &n);
    for (i = 0; i < n; ++i)
    {
        if(i==TAILLELOG)
        {
            Logements* nouvTLog;
            TAILLELOG=TAILLELOG+5;
            nouvTLog=(Logements*)realloc(tLogements, (TAILLELOG)*sizeof(Logements));
            if(nouvTLog==NULL) {printf("Pb realloc du tableau de logements\n"); fclose(fe); exit(1);}
            else {tLogements=nouvTLog; printf("realloc effectuée\n");}
        }
        fscanf(fe,"%s %s", Log.IdLogement, Log.Nom_cite);
        Log.adresse=fchargeAdresse(fe);
        fscanf(fe,"%s %s %s", &Log.adapte, Log.typeLogement, &Log.disponibilite);
        if(Log.disponibilite == 'I')
            fscanf(fe," %s", Log.IdEtudiant);
        tLogements[i]=Log;
    }
    fclose(fe);
    return  n;
}

//-----
//TRI DES LOGEMENTS PAR NOM DE LA CITE
//-----

int RecherchePourTri(Logements tLogements[],int nbLogeMax)
/* Nom : RecherchePourTri
 * Finalité :Recherche le rang du tableau tLogements pour lequel la fonction tri devra permuter avec une autre valeur.
 * Description générale : Reçoit le tableau tLogement et sa taille logique, compare les noms de cité, retourne le rang quand le nom du tableau trouvé est plus petit (dans l'ordre alphabétique) que celui du rang.
 * Variables : tLogements tableau contenant les logements
 * 				nbLogeMax taille logique du tableau
 * 				i 		  compteur
 * 				rang	  rang
*/
{int i, rang=0;
    for(i=1;i<nbLogeMax;i++)
        if(strcmp(tLogements[i].Nom_cite,tLogements[rang].Nom_cite)<0) rang=i;
    return rang;}

void Permute(Logements tLogements[], int rang)
/* Nom : Permute
 * Finalité : Echange la valeur du tableau d'un rang avec celle d'un autre rang.
 * Description générale : Reçoit le tableau tLogement et le rang de la valeur à permuter, utilise une variable temporaire pour permuter les deux valeurs. 
 * Variables :  tLogements   tableau contenant les logements
 * 				nbLogeMax    taille logique du tableau
 * 				temp		 variable temporaire
 * 				rang	     rang
*/
{Logements temp;
    temp=tLogements[0];
    tLogements[0]=tLogements[rang];
    tLogements[rang]=temp;
}

void tri(Logements tLogements[],int nbLogeMax)
/* Nom : tri
 * Finalité : Tri le tableau tLogements en fonction du nom de cité.
 * Description générale : Reçoit le tableau tLogement et sa taille logique, appelle les fonctions recherchePourTri et Permute, passe à la valeur suivante en se rappellant elle même.
 * Variables : tLogements   tableau contenant les logements
 * 			   nbLogeMax    taille logique du tableau
 * 				rang	     rang
*/
{
    if(nbLogeMax==1) return;
    int rang;
    rang=RecherchePourTri(tLogements,nbLogeMax);
    Permute(tLogements,rang);
    tri(tLogements+1,nbLogeMax-1);
}

//-----
//CHARGEMENT DES ETUDIANTS EN TABLEAU DE POINTEURS
//-----

Etudiant lireEtud(FILE *fe)
/* Nom : lireEtud
 * Finalité : Lire les informations concernant un étudiant.
 * Description générale : Reçoit un pointeur le fichier contenant les informations sur les étudiants, lit ces informations et renvoie la variable étudiant.
 * Variables :
 * 			   fe			Fichier à lire
 * 			   etud			étudiant (variable structurée)
 * 			   IdEtudiant	identifiant de l'étudiant
 * 			   civilite		Civilité de l'étudiant (Mme ou Mr)
 * 			   nom 			Nom de l'étudiant
 *             prenom		Prenom de l'étudiant
 * 			   boursier		N si pas boursier B si boursier
 *             echelon		numéro de l'échelon
 *             handicape    H si handicape V sinon*/
{

    Etudiant etud;
    etud.echelon=-1;

    fscanf(fe,"%s %s %s %s %c ", etud.IdEtudiant, etud.civilite, etud.nom, etud.prenom, &etud.boursier);
    if (etud.boursier =='B')
    {fscanf(fe,"%d", &etud.echelon);
        fscanf(fe,"%*c%c", &etud.handicape);}
    else fscanf(fe,"%c", &etud.handicape);

    return etud;
}


int fchargeEtudiant(Etudiant *Tetud[], int nbEtud)
/* Nom : fchargeEtudiant
 * Finalité : Charge les informations concernant les étudiants dans un tableau.
 * Description générale : Reçoit un pointeur sur le tableau TEtud, lit le fichier contenant les informations sur les étudiants, appelle la fonction lireEtud, alloue les espaces nécessaires et renvoie la taille du tableau rempli.
 * Variables :
 * 			   fe			Fichier à lire
 * 			   **Tetud		Pointeur sur le tableau à remplir
 * 			   *etud		tableau d'étudiants (variable structurée)
 * 			   nbEtud		Taille max du tableau
 * 			   i 			Compteur (taille finale du tableau)
 * 			   n 			Taille logique du tableau */
{
    FILE *fe;
    int i=0,n;
    Etudiant *etud;
    fe=fopen("etudiants.txt","r");
    if (fe==NULL){ printf("Probleme ouverture fichier\n"); return -1;}

    etud=(Etudiant*)malloc(sizeof(Etudiant));
    if(etud==NULL){printf("Pb malloc Etudiants"); fclose(fe); exit(1);}
    *etud=lireEtud(fe);

    while(feof(fe)==0)
    {
        if(i==nbEtud) {printf("Prob taille\n"); fclose(fe); return -2;}
        Tetud[i]=etud;
        i++;
        etud=(Etudiant*)malloc(sizeof(Etudiant));
        if(etud==NULL){printf("Pb malloc Etudiants"); fclose(fe); exit(1);}
        *etud=lireEtud(fe);
    }

    fclose(fe);
    return i;
}

//-----
//CHARGEMENT DES DEMANDES DANS UNE LSITE CHAÎNEE
//-----

Liste ListeVide(Liste d)
/* Nom : ListeVide
 * Finalité : Initialise une liste chaînée vide.
 * Description générale : Reçoit une liste de demandes, retourne NULL.
 * Variables : d    pointeur sur une liste chaînée de demandes
*/
{
    return NULL;
}

Liste InsertionEnTete(Liste listeDemande, DemandeEnAttente d)
/* Nom : InsertionEnTete
 * Finalité : Ajoute un maillon en tête d'une liste chaînée
 * Description générale : Reçoit une liste de demandes et une demande, crée un nouveau maillon, y stocke la demande et l'adresse du futur deuxième maillon, renvoit l'adresse du nouveau maillon pour le placer en tête de liste.
 * Variables : m    pointeur sur un maillon d'une liste de demandes
 *             d    demande
 *             listeDemande    pointeur sur une liste chaînée de demandes
*/
{
    Maillon* m;
    m=(Maillon*)malloc(sizeof(Maillon));
    if(m==NULL){printf("Pb malloc"); exit(1);}
    m->demande=d;
    m->suivant=listeDemande;
    return m;
}

Liste InsertionTriee(Liste listeDemande, DemandeEnAttente d)
/* Nom : InsertionTriée
 * Finalité : Ajoute un maillon dans une liste chaînée triée par échelon.
 * Description générale : Reçoit une liste de demandes et une demande, parcours la liste en comparant l'échelon de la demande, appelle InsertionEnTete si besoin, se rappelle elle-même, renvoit l'adresse de la liste.
 * Variables : m    pointeur sur un maillon d'une liste de demandes
 *             d    demande
 *             listeDemande    pointeur sur liste chaînée de demandes
*/
{
    if(listeDemande==NULL) return InsertionEnTete(listeDemande,d);
    if(d.echelon>=listeDemande->demande.echelon) return InsertionEnTete(listeDemande, d);
    listeDemande->suivant=InsertionTriee(listeDemande->suivant,d);
    return listeDemande;
}

Liste fChargeDemande(Liste listeDemande)
/* Nom : fChargeDemande
 * Finalité : Remplit une liste chaînée de demandes à partir d'un fichier.
 * Description générale : Reçoit une liste de demandes, ouvre un fichier, lit le fichier et les stocke en faisant appelle à InsertionTriee, renvoit l'adresse de la liste de demandes.
 * Variables : listeDemande    pointeur sur liste chaînée de demandes
 *             fdemande    pointeur sur le fichier de demandes
 *             d      pointeur sur une demande
*/
{
    FILE *fdemande;
    fdemande=fopen("demandesEnAttente.txt","r");
    if(fdemande==NULL){printf("Probleme ouverture fichier\n"); return NULL;}
    DemandeEnAttente *d;
    d=(DemandeEnAttente*)malloc(sizeof(DemandeEnAttente));
    if(d==NULL) {printf("pb malloc\n"); fclose(fdemande); exit(1);}
    fscanf(fdemande,"%s %s %d %s %s", d->IdDemande, d->IdEtudiant, &(d->echelon), d->Nom_cite, d->typeLogement);

    while(feof(fdemande)==0)
    {
        listeDemande=InsertionTriee(listeDemande, *d);
        fscanf(fdemande,"%s %s %d %s %s", d->IdDemande, d->IdEtudiant, &(d->echelon), d->Nom_cite, d->typeLogement);
    }
    fclose(fdemande);
    return listeDemande;
}

//-----
//AFFICHAGES
//-----

void fAffichage(Logements tLogements[], int nbmax)
/* Nom : fAffichage
 * Finalité : Affiche la liste des logements disponibles triés par cité
 * Description générale : Reçoit le tableau tLogement et la taille de ce tableau, affiche.
 * Variables : *tLogement	Pointeur sur le tableau contenant les informations des logements
 * 			   nbmax		taille du tableau
 * 			   IdLogement	identifiant du logement
 *             Nom_cite		nom de la cité étudiante
 *  		   adresse		adresse du logement (variable structurée Adresse)
 * 			   adapte		A si adapté et P sinon
 * 			   typeLogement	C chambre, S studio, T1 ou T2
 * 			   disponibilite D si disponible, I sinon
 * 			   i 			compteur*/
{	int i;
    printf("\n****\nLogements disponibles :\n****\n");
    for (i=0; i < nbmax ; ++i)
    {
        if(tLogements[i].disponibilite=='D')
            printf("%s %s %d %s %d %c %s\n", tLogements[i].IdLogement, tLogements[i].Nom_cite, tLogements[i].adresse.NumRue, tLogements[i].adresse.NomRue, tLogements[i].adresse.CodePost, tLogements[i].adapte, tLogements[i].typeLogement);
    }
}


void fAffEtud(Etudiant* etud[], int nbmax)
/* Nom : fAffEtud
 * Finalité : Affiche la liste des étudiants
 * Description générale : Reçoit le tableau de pointeurs sur les étudiants, affiche la liste des étudiants dans le système. 
 * Variables : nbmax 		Taille logique du tableau
 * 			   **etud		Tableau de pointeurs sur étudiants (variable structurée)
 * 			   IdEtudiant	identifiant de l'étudiant
 * 			   civilite		Civilité de l'étudiant (Mme ou Mr)
 * 			   nom 			Nom de l'étudiant
 *             prenom		Prenom de l'étudiant
 * 			   boursier		N si non-boursier B si boursier
 *             echelon		numéro de l'échelon (-1 si non-boursier)
 *             handicape    H si handicape V sinon
 * 			   i			compteur
*/
{
    int i;
    printf("\n****\nEtudiants enregistrés :\n****\n");
    for (i = 0; i < nbmax; ++i) {
        printf("%s %s %s %s %c ", etud[i]->IdEtudiant, etud[i]->civilite, etud[i]->nom, etud[i]->prenom, etud[i]->boursier);
        if(etud[i]->boursier=='B')
            printf("%d ", etud[i]->echelon);
        printf("%c\n", etud[i]->handicape);
    }
}

int fRechEtud(Etudiant* etud[], int nbmax, char *IdRech, int *trouve)    
/* Nom : fRechEtud
 * Finalité : Recherche le rang (ou rang d'insertion) d'un étudiant 
 * Description générale : Reçoit le tableau de pointeurs sur étudiants, sa taille logique, l'identifiant de l'étudiant recherché/à insérer, le pointeur trouve. Parcourt le tableau, modifie trouve si l'étudiant est trouvé, renvoit son rang (ou rang d'insertion).
 * Variables : nbmax        Taille logique du tableau
 *             *etud        Tableau d'étudiants (variable structurée)
 *             *IdRech      Identifiant à rechercher/insérer
 *             i            compteur
 *             trouve       pointeur sur la variable qui indique si l'étudiant est dans le tableau (1) ou non (0)
*/
{
    int cmp, i;
    *trouve=0;
    for (i = 0; i < nbmax; ++i)
    {
        cmp=strcmp(etud[i]->IdEtudiant,IdRech);
        if(cmp>=0)
        {if(cmp==0)
                *trouve=1;
            return i;}
    }
    return i;
}

void fAffichOccupes(Logements tLogements[], Etudiant *Tetud[], int nbLogeMax, int nbEtudMax)
/* Nom : fAffichOccupes
 * Finalité : Affiche la liste des logements occupés en mentionnant l'identité de l'étudiant qui l'occupe
 * Description générale : Reçoit le tableau des logements, le tableau de pointeurs sur les étudiants, leur taille logique. Parcourt le tableau pour trouver les logements occupés, les affiche, appelle la fonction fRechEtud pour pouvoir afficher l'identité de l'étudiant occupant le logement.
 * Variables : tLogements[] Tableau des logements
 *             **Tetud      Tableau de pointeurs sur étudiants
 *             nbLogeMax    Taille logique du tableau de logements
 *             nbEtudMax    Taille logique du tableau de pointeurs des étudiants
 *             i            compteur
 *             rang         rang de l'étudiant
 *             trouve       variable indiquant si l'étudiant est dans le tableau ou non
*/
{
    int rang, trouve;
    printf("\n****\nLogements occupés :\n****\n");
    for (int i = 0; i < nbLogeMax; ++i)
    {
        if (tLogements[i].disponibilite!='D')
        {printf("%s %s %s ", tLogements[i].IdLogement, tLogements[i].Nom_cite, tLogements[i].IdEtudiant);
            rang=fRechEtud(Tetud,nbEtudMax,tLogements[i].IdEtudiant,&trouve);
            printf("%s %s\n",Tetud[rang]->nom, Tetud[rang]->prenom);}
    }
}

void AffichListeDem(Liste l)
/* Nom : fAffichListeDem
 * Finalité : Affiche la liste des demandes en attente
 * Description générale : Reçoit le pointeur sur la liste des demandes, affiche la première demande puis fait un appel récursif pour afficher le reste de la liste.
 * Variables : l pointeur sur la liste chaînée des demandes
*/
{
    if(l==NULL) return;
    printf("%s %s %d %s %s\n",l->demande.IdDemande,l->demande.IdEtudiant,l->demande.echelon,l->demande.Nom_cite,l->demande.typeLogement);
    AffichListeDem(l->suivant);
}

//-----
//TRAITEMENT DES DEMANDES
//-----

void TraitementDemandes(Logements *tLogements, int nbLogeMax, Liste listeDemande, Etudiant **tetud, int nbEtudMax, DemandeEnAttente *d, int *stop)
/* Nom : TraitementDemandes
 * Finalité : Si possible, attribue un logement à un étudiant ayant fait une demande.
 * Description générale : Reçoit le tableau des logements, le tableau de pointeurs sur les étudiants, leur taille logique, le pointeur sur la liste des demandes, un pointeur sur une demande. Parcourt le tableau des logements pour en trouver un disponible et correspondant à la demande, effectue les changements nécessaires si l'attribution d'un logement est possible, fais un appel récursif pour traiter toutes les demandes.
 * Variables : tLogements[] Tableau des logements
 *             l            pointeur sur la liste chaînée des demandes
 *             **tetud      Tableau de pointeurs sur étudiants
 *             nbLogeMax    Taille logique du tableau de logements
 *             nbEtudMax    Taille logique du tableau de pointeurs des étudiants
 *             d            pointeur sur une demande
 *             i            compteur
 *             rang         rang de l'étudiant
 *             trouve       variable indiquant si l'étudiant est dans le tableau ou non
*/
{int i, trouve=1, rang;

    if(listeDemande==NULL) {*stop=1; return;}

    for (i=0;i<nbLogeMax;i++)
    {if (tLogements[i].disponibilite=='D' && strcmp(listeDemande->demande.Nom_cite,tLogements[i].Nom_cite)==0 && (strcmp(tLogements[i].typeLogement,listeDemande->demande.typeLogement)==0))
        {rang=fRechEtud(tetud, nbEtudMax, listeDemande->demande.IdEtudiant, &trouve);
            if ((tetud[rang]->handicape=='H' && tLogements[i].adapte=='A') || tetud[rang]->handicape=='V')
                {tLogements[i].disponibilite='I';
                strcpy(tLogements[i].IdEtudiant,listeDemande->demande.IdEtudiant);
                strcpy(d->IdDemande,listeDemande->demande.IdDemande);
                d->echelon=listeDemande->demande.echelon;
                return;
                }
        }
    }

    TraitementDemandes(tLogements, nbLogeMax, listeDemande->suivant, tetud, nbEtudMax, d, stop);
}

//-----
//SAISIE D'UNE NOUVELLE DEMANDE
//-----

Etudiant* fSaisieEtud(char *IdRech) // Saisie un nouvel étudiant en recevant déjà son ID
/* Nom : fSaisieEtud
 * Finalité : Saisi un nouvel étudiant
 * Description générale : Reçoit l'identifiant de l'étudiant à insérer, lit les informations le concernant, renvoit ces informations dans un pointeur sur Etudiant.
 * Variables : *IdRech      Identifiant à rechercher/insérer
 *             etud         pointeur sur Etudiant
*/
{
    Etudiant* etud;
    etud=(Etudiant*)malloc(sizeof(Etudiant));
    if(etud==NULL){printf("Pb malloc"); exit(1);}
    etud->echelon=-1;
    strcpy(etud->IdEtudiant,IdRech);
    printf("Saisir la civilité de l'étudiant, son nom et son prénom :");
    scanf("%s %s %s",etud->civilite,etud->nom,etud->prenom);
    while(strcmp(etud->civilite,"Mme")!=0 && strcmp(etud->civilite,"M")!=0)
        {printf("Erreur de saisie de la civilité.\n");
        printf("Saisir la civilité de l'étudiant :");
        scanf("%s",etud->civilite);}
    printf("Si l'étudiant est boursier, tapez B, sinon tapez N :");
    scanf(" %c", &etud->boursier);
    while(etud->boursier!='B' && etud->boursier!='N')
        {printf("Erreur, cette valeur n'est pas valide.\n");
        printf("Si l'étudiant est boursier, tapez B, sinon tapez N :");
        scanf(" %c", &etud->boursier);
        }
    if (etud->boursier=='B')
            {printf("Saisir l'échelon de bourse de l'étudiant :");
            scanf("%d", &etud->echelon);
            while (etud->echelon<1 || etud->echelon>7)
                {printf("Erreur, cette valeur n'est pas valide. L'échelon doit être compris entre 1 et 7 inclus.\n");
                printf("Saisir l'échelon de bourse de l'étudiant :");
                scanf("%d", &etud->echelon);}
            }
    printf("Si l'étudiant est handicapé, tapez H, sinon tapez V :");
    scanf(" %c", &etud->handicape);
    while (etud->handicape != 'H' && etud->handicape != 'V')
        {printf("Erreur, cette valeur n'est pas valide.\n");
        printf("Si l'étudiant est handicapé, tapez H, sinon tapez V :");
        scanf(" %c", &etud->handicape);}
    return etud;
}

void fRechListeDem(Liste l, char *IdDemande, int *rechDem)
/* Nom : fRechListeDem
 * Finalité : Recherche récursive d'une demande dans une liste en fonction de son identifiant
 * Description générale : Reçoit le pointeur sur la liste de demandes, l'identifiant de la demande à rechercher et le pointeur sur la variable indiquant si la demande se trouve dans la liste. Modifie cette variable si la demande est trouvée, fait un appel récursif pour parcourir le reste de la liste sinon.
 * Variables : l        pointeur sur la lsite de demandes
 *             *IdDemande      Identifiant à rechercher
 *             rechDem       pointeur sur la variable qui indique si la demande est dans la liste (1) ou non (0)
*/
{
    if(l==NULL) return;
    if(strcmp(l->demande.IdDemande,IdDemande)==0) {*rechDem=1;return;}
    else fRechListeDem(l->suivant,IdDemande,rechDem);
}

Liste fSaisieDemande(Etudiant *Tetud[], int *nbEtudMax, Liste listeDemande)
/* Nom : fSaisieDemande
 * Finalité : Saisie d'une nouvelle demande (et d'un nouvel étudiant si besoin)
 * Description générale : Reçoit le tableau de pointeurs sur les étudiants, sa taille logique, le pointeur sur la liste des demandes. Lit l'identifiant étudiant, appelle fRechEtud pour savoir s'il existe et son rang d'insertion si non, appelle fSaisieEtud et insère le nouvel étudiant si besoin. Lit l'identifiant de la demande, vérifie qu'elle n'existe pas déjà, lit les autres informations, appelle InsertionTriee pour insérer la demande au bon endroit dans la liste chaînée, renvoit l'adresse de la liste.
 * Variables : **Tetud      Tableau de pointeurs sur étudiants
 *             nbEtudMax    Taille logique du tableau de pointeurs des étudiants
 *             listeDemande pointeur sur la liste chaînée de demandes
 *             etud         pointeur sur un étudiant
 *             dem          pointeur sur une demande
 *             i            compteur
 *             rang         rang de l'étudiant
 *             trouve       variable indiquant si l'étudiant est dans le tableau (1) ou non (0)
 *             rechDem      pointeur sur la variable qui indique si la demande est dans la liste (1) ou non (0)
*/
{
    int rang, i, trouve, rechDem=0;
    Etudiant* etud;
    etud=(Etudiant*)malloc(sizeof(Etudiant));
    if(etud==NULL){printf("Pb malloc"); exit(1);}
    DemandeEnAttente* dem;
    dem=(DemandeEnAttente*)malloc(sizeof(DemandeEnAttente));
    if(dem==NULL){printf("Pb malloc"); exit(1);}
    printf("\nSaisir l'identifiant de l'étudiant :");
    scanf("%s",etud->IdEtudiant);
    rang=fRechEtud(Tetud,*nbEtudMax,etud->IdEtudiant,&trouve);
    if (trouve==0)
    {etud=fSaisieEtud(etud->IdEtudiant);
        rang=fRechEtud(Tetud,*nbEtudMax,etud->IdEtudiant,&trouve);
        for(i=*nbEtudMax;i>rang;i--)
            Tetud[i]=Tetud[i-1];
        Tetud[rang]=etud;
        *nbEtudMax=*nbEtudMax+1;
        fAffEtud(Tetud,*nbEtudMax);}
    else etud=Tetud[rang];
    printf("Saisir l'identifiant de la demande :");
    scanf("%s", dem->IdDemande);
    fRechListeDem(listeDemande, dem->IdDemande, &rechDem);
    if(rechDem==1) {printf("La demande existe déjà.\n");exit(1);}
    strcpy(dem->IdEtudiant,etud->IdEtudiant);
    dem->echelon=etud->echelon;
    printf("Saisir le nom de la cité et le type du logement demandé :");
    scanf("%s %s", dem->Nom_cite, dem->typeLogement);
    listeDemande=InsertionTriee(listeDemande,*dem);
    return listeDemande;
}

//-----
//SUPPRESSION D'UNE DEMANDE
//-----

int fRechEchelon(Liste l, char *IdDemande)
/* Nom : fRechEchelon
 * Finalité : Recherche l'échelon de l'étudiant d'une demande donnée.
 * Description générale : Reçoit la liste des demandes en attente et l'identifiant de la demande à traiter. Compare l'IdDemande de la liste et celui cherché pour trouver la bonne demande dans le tableau. Renvoit l'échelon de cette demande.
 * Variables : l			     Liste à traiter
 * 				IdDemande		 Demande à rechercher */
{
    if(l==NULL) return -10;
    if(strcmp(l->demande.IdDemande,IdDemande)==0) return l->demande.echelon;
    else return fRechEchelon(l->suivant,IdDemande);
}

Liste SuppressionTriee(Liste listeDemande, DemandeEnAttente d)
/* Nom : SuppressionTriee
 * Finalité : Supprime une demande en attente.
 * Description générale : La liste à traîter et la demande à annuler. Procède à la suppression de cette demande dans le tableau ( en appellant la fonction SuppressionEnTete) et retourne la nouvelle liste.
 * Variables : listeDemande     Liste à traiter
 *             d                demande à supprimer
*/
{
    if(listeDemande==NULL)return listeDemande;
    if(d.echelon>listeDemande->demande.echelon)
        return listeDemande;
    if(d.echelon==listeDemande->demande.echelon && strcmp(d.IdDemande,listeDemande->demande.IdDemande)==0)
        return SuppressionEnTete(listeDemande);
    listeDemande->suivant=SuppressionTriee(listeDemande->suivant,d);
    return listeDemande;
}


Liste SuppressionEnTete(Liste l)
/* Nom : SuppressionEnTete
 * Finalité : Supprime une demande en attente qui est en tête de liste.
 * Description générale : Reçoit la liste. Procède à la suppression de la première demande de la liste et retourne la nouvelle liste.
 * Variables : l            Liste à traiter
 *             m            Nouvelle liste
*/
{
    Liste m;
    m=l->suivant;
    free(l);
    return m;
}

//-----
//LIBERATION D'UN LOGEMENT
//-----

Logements Liberation(Logements tLogements[], int *nbLogeMax)
/* Nom : Liberation
 * Finalité : Libère un logement
 * Description générale : Reçoit le tableau des logements et le pointeur sur sa taille logique. Lit l'identifiant du logement à supprimer, recherche sa position, change sa disponibilité puis retourne le tableau. 
 * Variables : *nbLogMax 	Taille logique du tableau
 * 			   TLogements[]	Tableau de logements(variable structurée)
 * 			   IdLogement	identifiant du Logement
 * 			   i			compteur
 * 			   Log			Logement à libérer
*/
{
    char choix='o';
    Logements Log;
    int i;
    printf("\nSaisir le logement à libérer : ");
    scanf("%s",Log.IdLogement);
    for(i=0;i<*nbLogeMax;i++)
        if(strcmp(tLogements[i].IdLogement,Log.IdLogement)==0)
        {tLogements[i].disponibilite='D';
            return *tLogements;}
    printf("\nLogement introuvable\n");
    return *tLogements;
}

//-----
//SAUVEGARDE DES LOGEMENTS DANS UN FICHIER BINAIRE
//-----

void sauvegardeLogements(Logements tLogements[],int nbLogeMax)
/* Nom :   sauvegardeLogements
 * Finalité : Sauvegarde le tableau des logements dans un fichier binaire.
 * Description générale : Reçoit le tableau des logements et sa taille, copie le tableau dans un fichier binaire "sauvLog.txt".
 * Variables : nbLogMax 	Taille logique du tableau
 * 			   TLogements[]	Tableau de logements(variable structurée)
 * 				fs			fichier de sauvegarde "sauvLog.txt"
*/
{
    FILE *fs;
    fs=fopen("sauvLog.txt","wb");
    if(fs==NULL){printf("Pb ouverture du fichier");exit(1);}
    fwrite(&nbLogeMax,sizeof(int),1,fs);
    fwrite(tLogements,sizeof(Logements),nbLogeMax,fs);
    fclose(fs);
}

void LectSauvLogements(Logements tLogements[],int nbLogeMax)
/* Nom :   LectSauvLogements
 * Finalité : Restaure le fichier binaire de sauvegarde pour pouvoir le lire et vérifier si la sauvegarde a bien fonctionné.
 * Description générale : Reçoit le tableau des logements et sa taille, lit le fichier binaire et l'affiche à l'écran.
 * Variables : nbLogMax 	Taille logique du tableau
 * 			   TLogements[]	Tableau de logements(variable structurée)
 * 				fe			fichier de sauvegarde "sauvLog.txt"
 * 				i 			compteur
*/
{
    FILE *fe;
    int i;
    fe=fopen("sauvLog.txt","rb");
    if(fe==NULL){printf("Pb ouverture du fichier");exit(1);}
    fread(&nbLogeMax,sizeof(int),1,fe);
    fread(tLogements,sizeof(Logements),nbLogeMax,fe);
    printf("\nFichier binaire restauré :\n\n");
    printf("%d",nbLogeMax);
    for(i=0;i<nbLogeMax;i++)
    {printf("\n%s %s %d %s %d %c %s %c",tLogements[i].IdLogement,tLogements[i].Nom_cite,tLogements[i].adresse.NumRue,tLogements[i].adresse.NomRue,tLogements[i].adresse.CodePost,tLogements[i].adapte,tLogements[i].typeLogement,tLogements[i].disponibilite);
        if(tLogements[i].disponibilite=='I')
            printf("%s",tLogements[i].IdEtudiant);
    }
    fclose(fe);
}

//-----
//SAUVEGARDE DES ETUDIANTS DANS UN FICHIER
//-----

void SauvegardeEtud(Etudiant **etud, int n)
/* Nom : SauvegardeEtud
 * Finalité : Sauvegarde le tableau d'étudiants.
 * Description générale :Reçoit le tableau de pointeurs des étudiants et sa taille, copie le tableau dans un fichier "sauvEtud.txt".
 * Variables : **etud 	Tableau de pointeurs sur les étudiants
 * 				n 		Taille logique du tableau
 * 				fs 		fichier "sauvEtud.txt"
 * 				i		compteur
*/
{
    int i;
    FILE *fs;
    fs=fopen("sauvEtud.txt","w");
    if(fs==NULL) {printf("Erreur ouverture fichier de sauvegarde"); exit(1);}
    for (i = 0; i < n; ++i)
    {fprintf(fs,"%s %s %s %s %c ", etud[i]->IdEtudiant, etud[i]->civilite, etud[i]->nom, etud[i]->prenom, etud[i]->boursier);
        if(etud[i]->boursier=='B')
            fprintf(fs,"%d ", etud[i]->echelon);
        fprintf(fs,"%c\n", etud[i]->handicape);
    }
    fclose(fs);
}

//-----
//SAUVEGARDE DES DEMANDES DANS UN FICHIER
//-----

void SauvegardeDem(Liste l, FILE* fs)
/* Nom :  SauvegardeDem
 * Finalité : Sauvegarde la liste chaînée des demandes.
 * Description générale : Reçoit la liste des demandes et le fichier de sauvegarde, copie la liste dans un fichier "sauvDem.txt".
 * Variables :	l 	Liste chaînée (liste des demandes)
 * 				fs	Fichier de sauvegarde
*/
{
    if(l==NULL) return;
    fprintf(fs,"%s %s %d %s %s\n",l->demande.IdDemande,l->demande.IdEtudiant,l->demande.echelon,l->demande.Nom_cite,l->demande.typeLogement);
    SauvegardeDem(l->suivant, fs);
}

//-----
//FONCTION GLOBALE
//-----

void ftest(void)
{
    //CHARGEMENT ETUDIANTS
    Etudiant **tetud;
    tetud=(Etudiant**)malloc(sizeof(Etudiant)*TAILLEETUD);
    if(tetud==NULL){printf("Pb malloc"); exit(1);}
    int nbEtudMax;
    nbEtudMax=fchargeEtudiant(tetud, TAILLEETUD);

    //CHARGEMENT LOGEMENTS
    int nbLogeMax;
    int TAILLELOG=20;
    Logements *tLogements;
    tLogements=(Logements*)malloc(TAILLELOG*sizeof(Logements));
    if(tLogements==NULL){printf("Pb malloc Logements"); exit(1);}
    nbLogeMax=fChargeLgments(tLogements,TAILLELOG);
    tri(tLogements,nbLogeMax);

    //CHARGEMENT DEMANDES
    Liste listeDemande;
    listeDemande=ListeVide(listeDemande);
    listeDemande=fChargeDemande(listeDemande);


    //MENU

    int  choix=1;

    while (choix!=11)
    {
        printf("\n**************\n");
        printf("1- Affichage des logements \n");
        printf("2- Affichage des étudiants \n");
        printf("3- Affichage des demandes en attentes \n");
        printf("4- Enregistrement d'une nouvelle demande (avec la saisie d'un nouvel étudiants si celui-ci n'existe pas) \n");
        printf("5- Mise à jour des demandes en attentes \n");
        printf("6- Annulation d'une demandes \n");
        printf("7- Libération d'un logement \n");
        printf("8- Sauvegarde des logements \n");
        printf("9- Sauvegarde des étudiants \n");
        printf("10- Sauvegarde des demandes en attentes \n");
        printf("11- Quitter le programme");
        printf("");

        while (choix == 1 || choix == 2 || choix == 3 || choix == 4 || choix == 5 || choix == 6 || choix == 7 || choix == 8 || choix == 9 || choix == 10)
        {
            printf("\n**************\nSaisir votre choix: \n");
            scanf("%d", &choix);
            printf("**************\n");

            if (choix!=1 && choix!=2 && choix!=3 && choix!=4 && choix!=5 && choix!=6 && choix!=7 && choix!=8 && choix!=9 && choix!=10 && choix!=11)
            {
                while(choix!=1 && choix!=2 && choix!=3 && choix!=4 && choix!=5 && choix!=6 && choix!=7 && choix!=8 && choix!=9 && choix!=10 && choix!=11)
                {
                    printf("Votre choix n'est pas disponible veuillez le ressaisir :\n");
                    scanf("%d", &choix);
                }
            }

            if (choix == 1) //AFFICHAGE DES LOGEMENTS DISPONIBLES ET OCCUPES
            {
                fAffichage(tLogements, nbLogeMax);
                fAffichOccupes(tLogements, tetud, nbLogeMax, nbEtudMax);
            }

            if (choix == 2) //AFFICHAGE DES ETUDIANTS
                fAffEtud(tetud, nbEtudMax);

            if (choix == 3) //AFFICHAGE DES DEMANDES
            {
                printf("\n****\nDemandes en attente :\n****\n");
                AffichListeDem(listeDemande);
            }

            if (choix == 4) //SAISIE D'UNE NOUVELLE DEMANDE
            {
                char choix='o';
                while (choix == 'o')
                {
                    fSaisieDemande(tetud, &nbEtudMax, listeDemande);
                    AffichListeDem(listeDemande);
                    printf("Souhaitez vous saisir une autre demande ? (o/n)");
                    scanf("%*c%c", &choix);
                    while (choix != 'o' && choix !='n')
                    {
                        printf("Choix non reconnu veuillez recommencer :");
                        scanf("%*c%c", &choix);
                    }

                }
            }

            if (choix == 5) //TRAITEMENT DES DEMANDES
            {
                int stop=0;
                DemandeEnAttente *dem;
                dem=(DemandeEnAttente*)malloc(sizeof(DemandeEnAttente));
                fAffichage(tLogements, nbLogeMax);
                printf("\n***\n");
                AffichListeDem(listeDemande);
                while(stop!=1)
                    {TraitementDemandes(tLogements, nbLogeMax, listeDemande, tetud, nbEtudMax, dem, &stop);
                    listeDemande=SuppressionTriee(listeDemande,*dem);}
                printf("\n*** RESULTAT ***\n");
                fAffichage(tLogements, nbLogeMax);
                printf("\n****\nDemandes en attente :\n****\n");
                AffichListeDem(listeDemande);
            }

            if (choix == 6) //ANNULATION D'UNE DEMANDE
            {
                char choix='o';
                while(choix == 'o') {
                    DemandeEnAttente d;
                    printf("Saisir l'identifiant de la demande à annuler : ");
                    scanf("%s", d.IdDemande);
                    d.echelon = fRechEchelon(listeDemande, d.IdDemande);
                    listeDemande = SuppressionTriee(listeDemande, d);
                    printf("\n****\nDemandes en attente après suppression:\n****\n");
                    AffichListeDem(listeDemande);

                    printf("Souhaitez vous faire une autre annulation ? (o/n)");
                    scanf("%*c%c", &choix);
                    while (choix != 'o' && choix !='n')
                    {
                        printf("Caractère non reconnu, recommencer");
                        scanf("%*c%c", &choix);
                    }

                }
            }

            if (choix == 7) //LIBERATION D'UN LOGEMENT
            {
                char choix='o';
                while (choix == 'o')
                {
                    int stop=0;
                    DemandeEnAttente *dem;
                    dem=(DemandeEnAttente*)malloc(sizeof(DemandeEnAttente));
                    *tLogements = Liberation(tLogements, &nbLogeMax);
                    printf("\n*** RESULTAT APRES LIBERATION ***\n");
                    fAffichage(tLogements, nbLogeMax);
                    while(stop!=1)
                        {TraitementDemandes(tLogements, nbLogeMax, listeDemande, tetud, nbEtudMax, dem, &stop);
                        listeDemande=SuppressionTriee(listeDemande,*dem);}
                    printf("\n\n*** RESULTAT APRES TRAITEMENT DES DEMANDES ***\n");
                    fAffichage(tLogements, nbLogeMax);
                    printf("\n****\nDemandes en attente :\n****\n");
                    AffichListeDem(listeDemande);
                    printf("Voulez vous faire une autre libération de logement ? (o/n)");
                    scanf("%*c%c", &choix);
                    while (choix != 'o' && choix != 'n') 
                    {
                        printf("Choix non reconnu veuillez recommencer :");
                        scanf("%*c%c", &choix);
                    }
                }
            }

            if (choix == 8) //SAUVEGARDE DES LOGEMENTS
            {
                sauvegardeLogements(tLogements,nbLogeMax);
                printf("Sauvegarde réussie !\n");
                //LectSauvLogements(tLogements,nbLogeMax); //Fonction test permettant de restaurer et afficher le fichier binaire créé
            }

            if (choix == 9) //SAUVEGARDE DES ETUDIANTS
            {
                SauvegardeEtud(tetud, nbEtudMax);
                printf("Sauvegarde réussie !\n");
            }

            if(choix == 10) //SAUVEGARDE DES DEMANDES
            {
                FILE *fs;
                fs = fopen("sauvDem.txt", "w");
                if (fs == NULL)
                {
                    printf("Erreur ouverture fichier de sauvegarde");
                    exit(1);
                }
                SauvegardeDem(listeDemande, fs);
                printf("Sauvegarde réussie !\n");
                fclose(fs);
            }

        }

    }

    //LIBERATION DES ESPACES MEMOIRES

    for(int i = 0; i < nbEtudMax; ++i)
    {
        free(tetud[i]);
    }
    free(tLogements);

}
