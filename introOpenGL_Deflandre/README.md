Intro OpenGL
============

## Auteur

 - DEFLANDRE Gaëtan


## Doit contenir :

 - ce que vous n'avez pas fait (et pourquoi).
 - difficultés rencontrées.
 - commentaires éventuels sur le TP (points à éclaircir, longueur du sujet, etc). 


## Réponses aux question

### Question 7

TODO: vérifier

Le rôle d'un VBO.  
Le rôle d'un VAO.  
Le Program Shader est le programme qui rassemble les deux bout de code GLSL, le vertex 
shader et le fragment shader, (après compilation et linkage), pour pouvoir les utilisés 
dans un programme C++.

### Question 10

Pour retrouver les triangles précédents, il faut tracer les nouveaux sommets dans l'ordre
suivant:
 - v0
 - v3
 - v2
 - v5
 - v1
 - v4

### Question 12

En effet, les indices de GL_ELEMENT_ARRAY_BUFFER influt uniquement sur l'attribut position // TODO vérifier les color dans les 2 tableau

### Question 13

On a la même couleur pour les deux sommets des triangles qui se touche car leurs sommets
ont le même indice, la couleur associée au sommet d'incide 2 est la couleur d'indice 2 dans
le tableau de couleurs.

### Question 26




