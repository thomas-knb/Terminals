# Terminals

Création, visualisation et optimisation d'un réseau de terminaux

## Contenu

Ce programme est divisé en 2 parties : la création et la visualisation du réseau (C++), et l'optimisation du réseau (Python).

## Configuration

La bibliothèque SFML est requise pour compiler le premier programme ("terminals"). Exécutez la commande suivante pour l'installer si besoin.

```bash
sudo apt-get install libsfml-dev
```

Vous pouvez ensuite compiler le programme.

```bash
make
```

Vous pouvez désormais exécuter le programme avec la commande suivante.

```bash
./terminals
```

Le programme va vous retourner les matrices de connexion Y et Z dans le terminal. Vous pouvez les utiliser pour remplacer les valeurs par défaut contenues dans le deuxième programme ("solver.py").

La bibliothèque RBFOpt est requise pour exécuter ce dernier. Exécutez la commande suivante pour l'installer si besoin.

```bash
sudo pip install rbfopt
```

Vous pouvez ensuite exécuter le programme avec la commande suivante.

```bash
python2.7 solver.py
```