# Sujet du TP : 
## Introduction :
L’objectif de ce travail est de compléter l’initiation aux notions abordées pendant les séances
de cours du module autour de l’intérêt d’utiliser des heuristiques et/ou des métaheuristiques
lorsque le problème à résoudre est “difficile”.\
Pour cela vous allez travailler en équipe.  
Une équipe est, par définition, composée de plusieurs individus. Il ne s’agit pas d’un travail
individuel mais bien d’une collaboration qui doit notamment contribuer à renforcer vos compétences
organisationnelles au sein d’un groupe.

## Description du problème
En informatique théorique, le problème de couverture par ensembles (Set Cover problem en
anglais) est un problème d’algorithmique particulièrement important car c’est l’un des 21 problèmes
NP-complets de Karp.\
Étant donné un univers U constitué des éléments {1, 2, ...,m} et une collection S de n sousensembles
de U, où chaque sous-ensemble j de S est associé à un poids positif cj , le problème
de la couverture d’ensemble consiste à trouver une sous-collection de S dont l’union est égale
à U et dont la somme des poids est minimale.\
Le problème peut être modélisé de la manière suivante. Considérons une matrice binaire A =
(aij) de taille m × n où aij = 1 si et seulement si l’élément i appartient au sous-ensemble j.
En utilisant des variables binaires xj , telles que xj = 1 si et seulement si le sous-ensemble
j est sélectionné, le problème de la couverture d’ensembles peut être modélisé de la manière
suivante : \
![image](https://github.com/user-attachments/assets/b12c75a9-ac5b-4457-934b-c6716ca740e2)\
Dans ce modèle, la fonction objective vise à minimiser le poids total de tous les sous-ensembles
sélectionnés. La contrainte (2) garantit que chaque élément i appartient à au moins un sousensemble
sélectionné.

## Travail attendu - tâches à réaliser
Le but de ce projet est de développer une approche basée sur les principes des métaheuristiques
pour résoudre ce problème. Afin d’atteindre cet objectif, il faut développer les algorithmes
suivants :\
- Une procédure de lecture des données ; Les données sont accessibles via le lien suivant
https://people.brunel.ac.uk/~mastjjb/jeb/orlib/scpinfo.html
- Une procédure de construction d’une solution réalisable ;
- Une procédure de vérification de la faisabilité d’une solution ;
- Différentes recherches locales :Ajouter un sous-ensemble ; Retirer un sous-ensemble ; Échanger
deux sous-ensembles ;
- Développer une approche basée sur les procédures précédentes (VNS ou Tabou Search).

La complexité des structures de données utilisées et des différents sous-programmes de l’algorithme
doit être estimée et expliquée. De plus, il est nécessaire de fournir des tableaux de
résultats. Ces tableaux doivent permettre de comparer la valeur de la solution initiale, les valeurs
des solutions obtenues après les procédures de recherche locale (LS) et la valeur de la
solution obtenue par l’approche métaheuristique. Enfin, les tableaux doivent contenir les temps
CPU en secondes nécessaires pour atteindre chaque valeur de solution.

# Notre équipe : 
__Bouagila Ghazi__, __Galfano Nathan__ et __Crinchon Mathis__
