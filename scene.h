#if 0
/**
	This is a simple shape class. 
*/
#endif

#ifndef SCENE_H
#define SCENE_H

#include <stddef.h>
#include <stdlib.h>

#include "mesh.h"

typedef struct {
	int cntMesh;
	Mesh ** meshes;
} Scene;

extern const size_t scene_size;

#if 0
	/**
		This function allocates and init mesh instance with given shapecount.
	*/
#endif
Scene * alloc_scene(const unsigned int meshcount);

#if 0
	/**
		This function frees all memory from using shape.
	*/
#endif
void free_scene(Scene *scene);


#if 0
	/**
		multiplies every mesh of scene coords with given matrix like transform or roation one
	*/
#endif
void mat_mul_scene(Scene * scene, const Mat3 * matrix);
#if 0
	/**
		scales scene
	*/
#endif
void scale_scene(Scene * scene, const float scalex, const float scaley, const float scalez );

#if 0
	/**
		translate scene
	*/
#endif
void translate_scene(Scene * scene, const float tx, const float ty, const float tz );

#endif