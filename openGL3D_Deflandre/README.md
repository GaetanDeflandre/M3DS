TP2: OpenGL
===========


## Auteur

 - Gaëtan DEFLANDRE
 
 
## Doit contenir :
- ce que vous n'avez pas fait (et pourquoi).
- difficultés rencontrées.
- commentaires éventuels sur le TP (points à éclaircir, longueur du
  sujet, etc).


### Question 7

Sur la projection calculer par OpenGL, on peut voir en plus des faces
rouge et bleu du premier plan (ce sont normalement les seules
visibles), on voit également les faces verte et cyan du tétraèdre.

En effet, si l'on ne prècis rien aux shaders, tous les fragments sont
tracé. Les derniers fragments sont tracé et la couleur du pixel tracé
remplace la précédente sans prendre en compte la profondeur. C'est le
cas dans notre exemple avec les faces verte et cyan.

![Tétraèdre sans prendre en compte la profondeur dans les shaders](media/snapshot/capture_0000.png)


La profondeur des calculé en fonction de la normale de la camera très
loin = 0 sur la camera = -1 shhhh
