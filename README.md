# Projet1_LINFO1252 - Groupe 7-2

Ce projet a été réalisé dans le cadre du cours LINFO1252 - Systèmes informatiques. Voici le lien vers le [repository GitHub](https://github.com/EthSamson/Projet1_LINFO1252).

L'objectif est de tester et de comparer les algorithmes de synchronisation des threads, pour ensuite afficher les résultats à travers des graphes.

## Pré-requis

Pour le bon fonctionnement du code, vous aurez besoin de télécharger plusieurs librairies et packages :

- Python3
- Numpy (python)
- Matplotlib (python)
- Pandas (python)
- GCC
- Make

L'ensemble du projet a été réalisé pour une machine possédant 6 coeurs.

## Contenu du projet

*< img >* : contient l'ensemble des graphes réalisés par les tests au format *.pdf* et *.png*.

*< Makefile >* : Makefile principale qui automatise l'ensemble des tests du projet.

*< graph_philo.py, graph_prodcons.py ,graph_readwrite.py, graph_tas_tatas.py >* : traîtent les fichiers *.csv* pour créer les graphes.

*< task1 >* :
- *< stats >* : contient les fichiers *.csv* qui regroupe les temps mesurés par les tests.
- *< Makefile >* : le sous-Makfile qui permet d'automatiser les actions de la tâche 1.
- *< Script1_1,2,3.sh >* : les scripts bash qui permettent l'encodage des fichiers *.csv*.
- *< task1_1.c >* : regroupe les fonctions de mise en ouvres du problème des philosophes.
- *< task1_2.c >* : regroupe les fonctions de mise en ouvres du problème des producteurs-consommateurs.
- *< task1_3.c >* : regroupe les fonctions de mise en ouvres du problème des lecteurs-écrivains.

*< task2 >* :
- *< stats >* : contient les fichiers *.csv* qui regroupe les temps mesurés par les tests.
- *< Makefile >* : sous-Makfile qui permet d'automatiser les actions de la tâche 2.
- *< Script_philo,prodcons,readwrite,tas,tatas.sh >* : les scripts bash qui permettent l'encodage des fichiers *.csv*.
- *< my_mutex.c/my_mutex.h >* : regroupe les fonctions nécessaire à la création d'un verrou par attente active et d'une interface mutex grâce à l'assembleur en ligne.
- *< my_sem.c/my_sem.h >* :  regoupe les fonctions nécessaire à la création d'une interface sémaphore.
- *< philo.c >* : adaptation du problème des philosophes avec les primitives d'attente active.
- *< prodcons.c >* : adaptation du problème des producteurs-consommateurs avec les primitives d'attente active.
- *< readwrite.c >* : adaptation du problème des lecteurs-écrivains avec les primitives d'attente active.
- *< task2_1.c >* : regroupe les fonctions de mise en oeuvre de l'algorithme test-and-set.
- *< task2_3.c >* : regroupe les fonctions de mise en oeuvre de l'algorithme test-and-test-and-set.


## Utilisation du Makefile

Le projet contient un Makefile pour faciliter l'exécution des différents tests.
Les commandes à effectuer dans le terminal sont répertoriées ci-dessous :

### Lancement des tests :

- Pour afficher l'ensemble des graphes. Cette commande va aussi lancer les tests de performance et créer le fichier *.csv* de l'algorithme correspondant si celui-ci est n'est pas présent : 
```
$ make allGraph
```

- Pour lancer les tests de performance et générer les fichiers *.csv* pour l'ensemble de la tâche 1 et 2 respectivement :
```
$ make allScript1
```
```
$ make allScript2
```

- Pour afficher le graphe d'un problème en particulier et générer le fichier *.csv* correspondant si besoin :
```
$ make Gphilo
```
```
$ make Gprodcons
```
```
$ make Greadwrite
```
```
$ make Gtastatas
```

### Commande clean et mrproper :

- Pour supprimer les fichiers d'exécution de la tâche 1 et 2 respectivement :
```
$ make clean1
```
```
$ make clean2
```

- Pour supprimer les fichiers *.csv* et les fichiers d'exécution de la tâche 1 et 2 respectivement :
```
$ make mrproper1
```
```
$ make mrproper2
```

## Auteurs

- **Ethan Samson** - 79021600
- **Louis Ridelle** - 65481700
