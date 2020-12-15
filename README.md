# CROUS    (2019)
[ C ] Gestion des logements du CROUS

## PRESENTATION

Projet réalisé dans le cadre de la matière "structures de données" de la première année de DUT Informatique.  
Comme l'indique l'intitulé de la matière, l'objectifs était de manipuler des structures C plus ou moins complexes,  
pour arriver à réaliser une application console fonctionnel.

## EQUIPE

Victor MOMMALIER  
Clara PONCET  
Lucile VELUT  

## FONCTIONNALITES

#### Chargement, tri et affichage des logements

Le programme récupère les données depuis le fichier logements.txt, les charge dans un tableau, tri ce tableau grâce à un tri par permutation récursif, puis affiche ces données en deux listes distinctes : les logements disponibles d’une part (Affichage) et les logements occupés de l’autre (AffichOccupes). Toutes les fonctions nécessaires fonctionnent.
Chargement et affichage des étudiants
Le programme lit le fichier etudiants.txt et charge les données de ce fichier en conservant leur ordre dans un tableau de pointeurs. Ce tableau est ensuite affiché. Toutes les fonctions nécessaires fonctionnent.

#### Chargement et affichage des demandes en attente

Le programme lit les demandes en attente depuis le fichier demandesEnAttente.txt et classe les données dans une liste chaînée en les triant par échelon décroissant. Cette liste est ensuite affichée grâce à une fonction d’affichage récursive. Toutes les fonctions nécessaires fonctionnent.

#### Saisie d’une nouvelle demande et d’un nouvel étudiant si besoin

Cette fonctionnalité lit un identifiant étudiant. Si cet étudiant n’existe pas, il est lu et ajouté au bon endroit dans le tableau de pointeurs des étudiants. Les autres informations de la demandes sont ensuite lues avant d’être ajoutée dans la liste de manière à conserver le tri. Il y a également une fonction de recherche permettant de vérifier que la demande n’existe pas déjà. La fonction de saisie d’un nouvel étudiant comporte des contrôles de saisie dans des boucles qui permettent à l’utilisateur de corriger ses erreurs sans avoir à relancer le programme. Toutes les fonctions nécessaires fonctionnent.

#### Traitement des demandes

Cette fonction parcourt la liste chaînée des demandes et pour chaque demande, parcourt le tableau des logements afin de trouver un logement correspondant à la demande. Si une attribution est possible, les changements nécessaires sont effectués et la demande est supprimée. Elle se trouve dans une boucle ce qui garantit que toutes les attributions possibles sont effectuées. Toutes les fonctions nécessaires fonctionnent.

#### Annulation d’une demande
Le programme demande à l’utilisateur l’identifiant de la demande à supprimer et effectue la suppression sans affecter l’ordre des autres maillons de la liste chaînée. Pour cela, il utilise une fonction de recherche afin d’associer le bon échelon à la demande à supprimer. Toutes les fonctions nécessaires fonctionnent.
Libération d’un logement
L’utilisateur renseigne l’identifiant du logement à supprimer. La fonction de libération change sa disponibilité si le logement existe. Sinon, un message d’erreur est affiché. La mise à disposition d’un logement entraine le traitement des demandes afin d’attribuer ce logement à un étudiant si cela est possible. Toutes les fonctions nécessaires fonctionnent.

#### Sauvegarde des logements

Le programme sauvegarde le tableau comprenant tous les logements dans un fichier binaire sauvLog.txt. Ce fichier binaire peut être lu grâce à la fonction lectSauvLogements afin de vérifier que la sauvegarde a été effectuée sans accroc. Toutes les fonctions nécessaires fonctionnent.

#### Sauvegarde des étudiants

Le tableau de pointeurs des étudiants est sauvegardé dans un fichier texte sauvEtud.txt en reprenant la même structure que le fichier etudiants.txt initial. Toutes les fonctions nécessaires fonctionnent.

#### Sauvegarde des demandes

La liste chaînée est sauvegardée dans le fichier sauvDem.txt grâce à une fonction récursive. Ce fichier reprend la même structure que le fichier demandesEnAttente.txt initial. Toutes les fonctions nécessaires fonctionnent.

#### Menu

La fonction appelante globale comprend un menu qui permet à l’utilisateur de choisir quelle action il veut effectuer et dans quel ordre. Le menu est dans une boucle ce qui permet de faire plusieurs actions à la suite sans avoir à relancer le programme. Il contient aussi une option permettant de quitter le programme. Ce menu ne fonctionne que lorsque qu’un entier lui est envoyé. Lorsqu’il reçoit un autre type de variable, le menu tourne à l’infini.
