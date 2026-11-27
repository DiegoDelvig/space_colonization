# Space Colonization (C / SDL2)

Implémentation 2D de l'algorithme de **space colonization** en C, avec affichage SDL2. Un ensemble de points « attracteurs » est semé au hasard dans la fenêtre, et une structure de nœuds pousse progressivement vers eux, à la manière d'une branche ou d'une racine.

## L'algorithme

À chaque itération :

1. **Association** : chaque attracteur trouve le nœud le plus proche de lui. Si ce nœud est à moins de `DI` (distance d'influence), l'attracteur l'« attire ».
2. **Croissance** : pour chaque nœud attiré, on additionne les directions unitaires vers ses attracteurs, on normalise la somme, et on crée un nouveau nœud à distance `D_STEP` dans cette direction.
3. **Élimination** : tout attracteur situé à moins de `DK` d'un nœud est supprimé (il a été « atteint »).

La simulation se stabilise quand il ne reste plus d'attracteur à portée.

## Structure du projet

| Fichier | Rôle |
|---|---|
| `main.c` | Initialisation SDL, boucle principale, logique de l'algorithme, rendu |
| `vec2.h` / `vec2.c` | Vecteur 2D (`vec2_t`) : addition, soustraction, échelle, norme, distance, normalisation, position aléatoire |
| `points.h` / `points.c` | Tableau dynamique de points (`points_t`) : création, ajout (avec `realloc`), suppression par échange avec le dernier, destruction |
| `draw.h` / `draw.c` | Primitives de dessin SDL : couleur, disque plein, ligne |
| `app.h` / `app.c` | Première version de l'algorithme, organisée par nœud. Elle n'est plus utilisée par `main.c`, qui applique désormais le schéma « par attracteur » |

## Dépendances

- Un compilateur C (gcc ou clang)
- SDL2 (bibliothèque et en-têtes de développement)

Sur Ubuntu / Debian :

```bash
sudo apt install build-essential libsdl2-dev
```

## Compilation

Depuis le dossier contenant les sources :

```bash
gcc -Wall -Wextra -std=c11 -O2 \
    main.c vec2.c points.c draw.c app.c \
    $(sdl2-config --cflags --libs) -lm \
    -o space_colonization
```

Le projet a été développé sous Eclipse CDT ; les fichiers peuvent aussi y être importés tels quels (pensez à lier `SDL2` et `m`).

## Exécution

```bash
./space_colonization
```

Fermer la fenêtre arrête le programme.

## Paramètres

Les constantes se règlent en haut de `main.c` :

| Constante | Rôle | Valeur actuelle |
|---|---|---|
| `WIDTH`, `HEIGHT` | Taille de la fenêtre | 600 × 600 |
| `attractorsCapacity` | Nombre d'attracteurs générés | 20 |
| `D_STEP` | Longueur d'un pas de croissance | 5.0 |
| `DI` | Distance d'influence d'un attracteur | 200.0 |
| `DK` | Distance de suppression d'un attracteur | 8.0 |
| `RADIUS` | Rayon d'affichage des points | 3.0 |

Quelques repères : `DK` doit rester petit devant `DI`, sinon les attracteurs disparaissent d'un coup. Un `DI` trop faible laisse des attracteurs hors de portée, qui ne seront jamais atteints.

## Notes sur la mémoire

- `points_create` / `points_destroy` doivent toujours être appariés : `points_destroy` libère à la fois le tableau `items` et la structure.
- `points_add` peut réallouer `items` : ne conservez jamais de pointeur vers `items[i]` à travers un appel à `points_add`, copiez le `point_t` par valeur.
- `points_remove` échange l'élément supprimé avec le dernier. En parcourant une liste pour supprimer, itérez à l'envers.

## Pistes d'évolution

- [ ] Champ `parent` dans `point_t` et tracé des branches avec `draw_lineBetweenTwoPoints`
- [ ] Racine placée en bas au centre de la fenêtre
- [ ] Rayons distincts pour les attracteurs et les nœuds
- [ ] Nettoyage ou suppression de `app.c` / `app.h`
- [ ] Contrôle de la vitesse et réinitialisation au clavier
- [ ] Accélération de la recherche du nœud le plus proche (grille spatiale) pour de grands nombres d'attracteurs

## Licence

MIT
