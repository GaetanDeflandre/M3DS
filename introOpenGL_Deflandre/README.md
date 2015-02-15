Intro OpenGL
============

## Auteur

 - DEFLANDRE Gaëtan


## Difficultés rencontrées

Première petite difficulté sur la compréhension du VBO et VAO. Ils
sont, maintenant, compris après une relecture du cours.  
Sinon, quelles difficultés pour mettre en place la première animation
avec la variable *coeff* et aussi pour mettre en place la texture. Ces
problèmes ont été rapidement résolu.


## Réponses aux questions


### Question 7

#### Le VBO
Le VBO (Vertex Buffer Object) est la mémoire sur le serveur OpenGL. Le
Program Shader ne peut pas utiliser directement la mémoire classique,
il faut donc copier les morceaux de mémoire qui nous intéresse dans le
VBO (positions, couleurs, textures...). Après, les shaders auront
accès au VBO. Cela permet à OpenGL d'utiliser la mémoire de la carte
graphique par exemple.

#### Le VAO
Le rôle du VAO est d'indiquer la valeur des attributs du vertex
shader. Il lie les valeurs dans le VBO avec les attributs du vertex
shader.

#### Le Program Shader
Le Program Shader est l'assemblage des deux codes GLSL, le vertex
shader et le fragment shader, (après compilation et linkage). Il
positionne chaque sommet et donne la couleur de chaque pixel, en
fonction des valeurs écrites dans le VBO et des attributs *uniform*.


### Question 10

Pour retrouver les triangles précédents, il faut tracer les nouveaux
sommets dans l'ordre suivant:
 - v0
 - v3
 - v2
 - v5
 - v1
 - v4


### Question 12

En effet, les indices de GL_ELEMENT_ARRAY_BUFFER influent uniquement
sur l'attribut position.  Les couleurs sont dans l'ordre du vecteur
*trianglePosition*.


### Question 13

On a la même couleur pour les deux sommets des triangles qui se
touchent car leurs sommets ont le même indice, la couleur associée au
sommet d'incide 2 est la couleur d'indice 2 dans le tableau de
couleurs.


### Question 18

Le nombre de sommets n'a pas n'importance pour le VAO ou le program
shader, il ne faut pas les modifier. On n'a pas besoin de modifier
l'initialisation du VBO, car la copie des sommets dans le VBO est
effectuée après l'initialisation des sommets.

