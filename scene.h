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
	mesh_t ** meshes;
} scene_t;

extern const size_t scene_size;

#if 0
	/**
		This function allocates and init mesh instance with given shapecount.
	*/
#endif
scene_t * alloc_scene(const unsigned int meshcount);

#if 0
	/**
		This function frees all memory from using shape.
	*/
#endif
void free_scene(scene_t *scene);


#if 0
	/**
		multiplies every mesh of scene coords with given matrix like transform or roation one
	*/
#endif
void mat_mul_scene(scene_t * scene, const mat3_t * matrix);
#if 0
	/**
		scales scene
	*/
#endif
void scale_scene(scene_t * scene, const float scalex, const float scaley, const float scalez );

#if 0
	/**
		translate scene
	*/
#endif
void translate_scene(scene_t * scene, const float tx, const float ty, const float tz );

#endif