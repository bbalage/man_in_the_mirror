# man_in_the_mirror
This is a hand-in project for the University subject Computer Graphics created with OpenGL.

In the project, a basic reflection making technique is used to mirror a man and the player. There is only one room, with a text, a randomly walking man and the player controlling another person.

Download links for textures and models are in the textures/textures.urls and models/models.urls files. Each link should begin a download.

Usage:
Use the h button to show help!
If you use it, the program would provide you the following information:
Use W,A,S,D to move around.
Use the mouse to look around.
Use the + and the - keys to increase and decrease light in the scene.

What is specifically created in the project:
Self-made models for the man and map. The models were created in Blender. The map is a simple 6*6 field of concrete and brick boundaries. There is also a "painting", which is actually a simple text, included to be mirrored in the screen.
The man walks around randomly, and the leg movement is animated. A small up and down movement is added to its whole body to make the walk a little more realistic. Otherwise, head and arms are not moved.
The player is controlling another man with different textures in first person view. His walk animation is all the same.
There is a semi-transparent block in the wall representing a mirror. On its other side, the real models are copied and transformed to simulate a mirror effect.

The reflection making:
Reflection is generated a little differently with each model.
The bounds (walls, floors and ceilings) are reflected as a model, all of their vertices transformed and copied. These are small models, consisting of two triangles and do not move. Due to this, transformation is simple and is only done once.
With the painting, there is a simple trick used: It is transformed without being rotated. This achives the effect of looking at a text from behind, in which case the text looks exactly like if seen in a mirror.
The moving man and player are reflected dynamically, their reflection objects created at each display. Models are not reflected in the OpenGL program, but were mirrored in Blender. The models used in the reflection are different: they were pre-mirrored in Blender (In the current version, only the body and head is pre-mirrored).
The help message is shown as a texture preview. This way it could be formated more easily.

Note on the design:
The models and textures of the man and the player are intentionally grotesque and are meant to be horroristic (their textures are cloth pictures, like if they were dolls). This is due to the game idea the project was based on, but which bear no relevance to the project itself.
