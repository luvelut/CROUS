#include <stdio.h>

typedef struct
{
    int NumRue;
    char NomRue[25];
    int CodePost;
} Adresse;

typedef struct
{
    char IdEtudiant[6];
    char civilite[4];
    char nom[20];
    char prenom[10];
    char boursier;
    int echelon;
    char handicape;
} Etudiant;

typedef struct
{
    char IdLogement[6];
    char Nom_cite[50];
    Adresse adresse;
    char adapte;
    char typeLogement[3];
    char  disponibilite;
    char IdEtudiant[6];

} Logements;

typedef struct
{
    char IdDemande[6];
    char IdEtudiant[6];
    int echelon;
    char Nom_cite[50];
    char typeLogement[3];
} DemandeEnAttente;

typedef struct liste        
{DemandeEnAttente demande;
struct liste *suivant;} Maillon, *Liste;

Adresse  fchargeAdresse(FILE *fe);
int fChargeLgments(Logements *tLogement, int TAILLELOG);
int RecherchePourTri(Logements tLogements[],int nbLogeMax);
void Permute(Logements tLogements[], int rang);
void tri(Logements tLogements[],int nbLogeMax);
Etudiant lireEtud(FILE *fe);
int fchargeEtudiant(Etudiant *Tetud[], int nbEtud);
void fAffichage(Logements tLogements[], int nbmax);
int fRechEtud(Etudiant* etud[], int nbmax, char *IdRech, int *trouve);
void fAffichOccupes(Logements tLogements[], Etudiant *Tetud[], int nbLogeMax, int nbEtudMax);
Liste ListeVide(Liste d);
Liste InsertionEnTete(Liste listeDemande, DemandeEnAttente d);
Liste InsertionTriee(Liste listeDemande, DemandeEnAttente d);
Liste fChargeDemande(Liste listeDemande);
void AffichListeDem(Liste l);
DemandeEnAttente lireDem(FILE *fe);
int fChargeDemandeTab(DemandeEnAttente *Tdem[], int nbDem);
void AffichDem(DemandeEnAttente *Tdem[], int nbDem);
Etudiant* fSaisieEtud(char *IdRech);
void fRechListeDem(Liste l, char *IdDemande, int *rechDem);
Liste fSaisieDemande(Etudiant *Tetud[], int *nbEtudMax, Liste listeDemande);
void TraitementDemandes(Logements *tLogements, int nbLogeMax, Liste listeDemande, Etudiant **tetud, int nbEtudMax, DemandeEnAttente *d, int *stop);
int fRechEchelon(Liste l, char *IdDemande);
Liste SuppressionTriee(Liste listeDemande, DemandeEnAttente d);
Liste SuppressionEnTete(Liste l);
Logements Liberation(Logements tLogements[], int *nbLogeMax);
void sauvegardeLogements(Logements tLogements[],int nbLogeMax);
void LectSauvLogements(Logements tLogements[],int nbLogeMax);
void SauvegardeEtud(Etudiant **etud, int n);
void SauvegardeDem(Liste l, FILE* fs);

void ftest();
