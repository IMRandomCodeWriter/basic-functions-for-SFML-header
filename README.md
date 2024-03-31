# **Basic functions for SFML**
## description
Its the header that includes the basic functions for SFML, they are not included in SFML by default, but is very useful in many projects. Just include "BasFun.h" in your project, all functions are placed in "bf" namespace.
## All functions and their description
### Vectors functions(Vector2 and Vector3):
+ distance - calculates distance;
+ magnitude - calculates magnitude;
+ normalize - can normalize 1 vector or can calculate normalized direction of 2 vectors;
+ dot - calculates dot product of vectors;
+ angle - calculates angle between vectors;
### Shapes functions(all 2d shapes):
+ realCenter - calculates shape or vertex array center in global space;
+ centerOrigin - set rect or circle origin to center;
+ isCollide - checks if rect collide with rect, rect collide with circle(circle and rect origin must be in center) or convex shape collide with convex shape;
+ contains - accurately determines if a shape contains a point, used for circles and convex shapes;
+ uni_isCollide - the universal colliding function, can check the colliding of any shape, is used to check collide of convex shapes, circles may be inaccurate if they are large and contain a small number of points;


## Extra
+ You can see the settings at the top of the file, they can disable unnecessary parts of the code 
+ There is a quick distance function, it is just a distance function without using a template and a square root, so it is not accurate, but maybe in some cases you can use it
+ I know some of functions haven't got good optimization and may not work properly
+ I also know that most likely no one but me will use it, but maybe someone will need it