#include "scene_builder.h"


typedef struct {
    Vec2 *charPos;
	ColorRGB *color;
	Texture *texture;
} __r_render_txt_ctx_t;

static void __rf_text_render_func(float const * const x, float const * const y, void *data)
{
    __r_render_txt_ctx_t *ctx = data;
    Vec2 *charPos = ctx->charPos;
	ColorRGB *color = ctx->color;
	Texture *texture = ctx->texture;
    long used_x = charPos->x + *x;
    long used_y = ceilf((float)texture->height - charPos->y - *y);

	ArrayError err = crgb_array2D_set(texture->buffer, used_x, used_y, color);
	(void)(err);
}

static Texture* __sceneb_create_text_tex(float glyphDetail, unsigned char const * const text, ColorRGB *txtColor )
{
	RFProvider* provider = get_default_provider();

    RFCtx rf_ctx;
    rfont_init(&rf_ctx, provider);

	RFGlyphMeta meta;
	rfont_get_meta_str( &rf_ctx, &meta, text, glyphDetail);
	
	Vec2 charPos = {0.f, -meta.yOffsetChar};

	unsigned int width = meta.alignedCharBox.xMax;
	unsigned int height = meta.alignedCharBox.yMax;

	Texture *texture = texture_new(width, height);
	ColorRGB clearcolor = { 1.f, 0.f, 1.f };
	texture_clear(texture, &clearcolor);
	__r_render_txt_ctx_t renderCtx = {&charPos, txtColor, texture}; 

	rfont_raster_text(&rf_ctx, text, glyphDetail, __rf_text_render_func, &renderCtx);
	//save_texture_normalized_ppm(texture, "test_glyph_tex.ppm");
	return texture;
}

static Mesh* __Rendererext_quad(TextureCache *texCache, float txtSize, float glyphDetail, unsigned char const * const text, ColorRGB *txtColor )
{
	Texture *texture = __sceneb_create_text_tex(glyphDetail, text, txtColor);
	
	int texId = texture_cache_register(texCache, texture);

	float txtunit_w = (float)texture->width * 0.01 * txtSize;
	float txtunit_h = (float)texture->height * 0.01 * txtSize;
	float whalf = txtunit_w * 0.5f;
	float hhalf = txtunit_h * 0.5f;
	const Vec3 lb = {-whalf, -hhalf, 0.f};
	const Vec3 rb = {whalf, -hhalf, 0.f};
	const Vec3 lt = {-whalf, hhalf, 0.f};
	const Vec3 rt = {whalf, hhalf, 0.f};

	return create_quad3_textured(&lb, &rb, &lt, &rt, texId);
}


Scene * 
scene_create_test() {
	Vec3 center;
	const float sidelen = .3f;
	uint32_t cntMesh = 42;
	Scene * scene = alloc_scene(cntMesh);
	scene->meshes[40] = create_raster(6.f);
	scene->meshes[41] = create_point_raster();
	scene->meshes[29] = createsphere(0.2f, 28, 28);
	translate_mesh(scene->meshes[29], -2.f, .0f, -1.f);
	scene->meshes[30] = createsphere(0.1f, 28, 28);
	translate_mesh(scene->meshes[30], -3.5f, .0f, -1.f);
	scene->meshes[31] = createsphere(0.3f, 28, 28);
	translate_mesh(scene->meshes[31], -2.f, .0f, -1.f);
	scene->meshes[32] = createsphere(0.5f, 28, 28);
	translate_mesh(scene->meshes[32], -2.f, .0f, 2.f);
	scene->meshes[33] = createsphere(0.2f, 28, 28);
	translate_mesh(scene->meshes[33], -1.5f, .0f, 15.f);
	scene->meshes[34] = createsphere(0.8f, 28, 28);
	translate_mesh(scene->meshes[34], -1.f, .0f, 1.f);
	scene->meshes[35] = createsphere(0.5f, 28, 28);
	translate_mesh(scene->meshes[35], 1.f, .0f, 1.5f);
	scene->meshes[36] = createsphere(0.4f, 28, 28);
	translate_mesh(scene->meshes[36], 1.5f, .0f, 1.5f);
	scene->meshes[37] = createsphere(0.5f, 28, 28);
	translate_mesh(scene->meshes[37], 2.f, .0f, 1.5f);
	scene->meshes[38] = createsphere(0.4f, 28, 28);
	translate_mesh(scene->meshes[38], 1.f, .0f, 2.f);
	scene->meshes[39] = createsphere(0.5f, 10, 10);
	translate_mesh(scene->meshes[39], 2.f, .0f, 2.f);
	
	scene->meshes[27] = createsphere(0.5f, 10, 10);
	scene->meshes[28] = createsphere(0.5f, 10, 10);
	scale_mesh(scene->meshes[28], 1.f, .1f, 1.f);
	translate_mesh(scene->meshes[27], -4.5f, .0f, 0.f);
	translate_mesh(scene->meshes[28], 5.5f, .0f, 0.f);

	center = (Vec3) { 0.0f, 0.0f, 0.0f };
	scene->meshes[0] = create_cube3_center(&center, sidelen);//create_raster(2.f);
	center = (Vec3) { -0.5f, 0.0f, 0.0f };
	scene->meshes[1] = create_cube3_center(&center, sidelen);//create_raster(2.f);
	center = (Vec3) { 0.5f, 0.0f, 0.0f };
	scene->meshes[2] = create_cube3_center(&center, sidelen);//create_raster(2.f);
    
	center = (Vec3) { 0.0f, -0.5f, 0.0f };
	scene->meshes[3] = create_cube3_center(&center, sidelen);//create_raster(2.f);
	center = (Vec3) { -0.5f, -0.5f, 0.0f };
	scene->meshes[4] = create_cube3_center(&center, sidelen);//create_raster(2.f);
	center = (Vec3) { 0.5f, -0.5f, 0.0f };
	scene->meshes[5] = create_cube3_center(&center, sidelen);//create_raster(2.f);
	
	center = (Vec3) { 0.0f, 0.5f, 0.0f };
	scene->meshes[6] = create_cube3_center(&center, sidelen);//create_raster(2.f);
	center = (Vec3) { -0.5f, 0.5f, 0.0f };
	scene->meshes[7] = create_cube3_center(&center, sidelen);//create_raster(2.f);
	center = (Vec3) { 0.5f, 0.5f, 0.0f };
	scene->meshes[8] = create_cube3_center(&center, sidelen);//create_raster(2.f);
	
	center = (Vec3) { 0.0f, 0.0f, 0.5f };
	scene->meshes[9] = create_cube3_center(&center, sidelen);//create_raster(2.f);
	center = (Vec3) { -0.5f, 0.0f, 0.5f };
	scene->meshes[10] = create_cube3_center(&center, sidelen);//create_raster(2.f);
	center = (Vec3) { 0.5f, 0.0f, 0.5f };
	scene->meshes[11] = create_cube3_center(&center, sidelen);//create_raster(2.f);
    
	center = (Vec3) { 0.0f, -0.5f, 0.5f };
	scene->meshes[12] = create_cube3_center(&center, sidelen);//create_raster(2.f);
	center = (Vec3) { -0.5f, -0.5f, 0.5f };
	scene->meshes[13] = create_cube3_center(&center, sidelen);//create_raster(2.f);
	center = (Vec3) { 0.5f, -0.5f, 0.5f };
	scene->meshes[14] = create_cube3_center(&center, sidelen);//create_raster(2.f);
	
	center = (Vec3) { 0.0f, 0.5f, 0.5f };
	scene->meshes[15] = create_cube3_center(&center, sidelen);//create_raster(2.f);
	center = (Vec3) { -0.5f, 0.5f, 0.5f };
	scene->meshes[16] = create_cube3_center(&center, sidelen);//create_raster(2.f);
	center = (Vec3) { 0.5f, 0.5f, 0.5f };
	scene->meshes[17] = create_cube3_center(&center, sidelen);//create_raster(2.f);
	
	center = (Vec3) { 0.0f, 0.0f, -0.5f };
	scene->meshes[18] = create_cube3_center(&center, sidelen);//create_raster(2.f);
	center = (Vec3) { -0.5f, 0.0f, -0.5f };
	scene->meshes[19] = create_cube3_center(&center, sidelen);//create_raster(2.f);
	center = (Vec3) { 0.5f, 0.0f, -0.5f };
	scene->meshes[20] = create_cube3_center(&center, sidelen);//create_raster(2.f);
    
	center = (Vec3) { 0.0f, -0.5f, -0.5f };
	scene->meshes[21] = create_cube3_center(&center, sidelen);//create_raster(2.f);
	center = (Vec3) { -0.5f, -0.5f, -0.5f };
	scene->meshes[22] = create_cube3_center(&center, sidelen);//create_raster(2.f);
	center = (Vec3) { 0.5f, -0.5f, -0.5f };
	scene->meshes[23] = create_cube3_center(&center, sidelen);//create_raster(2.f);
	
	center = (Vec3) { 0.0f, 0.5f, -0.5f };
	scene->meshes[24] = create_cube3_center(&center, sidelen);//create_raster(2.f);
	center = (Vec3) { -0.5f, 0.5f, -0.5f };
	scene->meshes[25] = create_cube3_center(&center, sidelen);//create_raster(2.f);
	center = (Vec3) { 0.5f, 0.5f, -0.5f };
	scene->meshes[26] = create_cube3_center(&center, sidelen);//create_raster(2.f);
	
	for ( uint32_t curMesh = 0; curMesh < cntMesh; curMesh++ )
	{
		mesh_create_bbox(scene->meshes[curMesh]);
	}

	return scene;
	
}

Scene * 
scene_create_raster(const float linelen){
	Scene * scene = alloc_scene(1);
	scene->meshes[0] = create_raster(linelen);
	return scene;
}

Scene * 
scene_create_triangle(){
	const Vec3  p1 = {-.5f, -.5f, 0.5f},
		    p2 = {.5f, -.5f, 0.5f},
			p3 = {0.f, .5f, -0.5f};

	Scene * scene = alloc_scene(1);
	scene->meshes[0] = create_triangle3(&p1,&p2,&p3);
	
	mesh_create_bbox(scene->meshes[0]);
	mesh_color_by_bbox(scene->meshes[0]);
	
	return scene;
}

Scene *
scene_create_tree(){
	Scene * scene = alloc_scene(1);
	const float radius = 0.2f;
	const int cntelements = 20; 
	const float height = 2.5f; 
	const int longs = 10;
	const float scaleend = 0.85f; //1.0 nothing scaled and scaleend = 0.0 max
	scene->meshes[0] = createpath(radius, cntelements, height, longs, scaleend);
	return scene;
}

Scene * scene_create_Textureest() 
{
	const Vec3 _center = {0.f, 0.f, 0.f};
	const Vec3 * center = &_center;
	
	Scene * scene = alloc_scene(1);
	
	scene->meshes[0] = create_cube3_center(center, 0.25f);
	
	Vec2 lttex = {0.f, 0.f};
	Vec2 lbtex = {0.f, 1.f};
	Vec2 rttex = {1.f, 0.f};
	Vec2 rbtex = {1.f, 1.f};

	for (unsigned int i = 0; i < scene->meshes[0]->cntShapes; ++i){

		shape_set_texture(scene->meshes[0]->shapes[i++], 0.f, &lbtex, &rbtex, &lttex);
		shape_set_texture(scene->meshes[0]->shapes[i], 0.f, &lttex, &rbtex, &rttex);

	}
	
	return scene;
}

Scene * scene_create_text_quad(TextureCache *texCache, float txtSize, float glyphDetail, unsigned char const * const text, ColorRGB *txtColor)
{

	//Mesh* __Rendererext_quad(TextureCache *texCache, float glyphDetail, (unsigned char const * const)text, ColorRGB *txtColor);

	Scene * scene = alloc_scene(3);
	scene->meshes[1] = __Rendererext_quad(texCache, txtSize, glyphDetail, text, txtColor);

	scene->meshes[2] = __Rendererext_quad(texCache, 0.25, 120.f, (unsigned char const * const)"text 2 :D", txtColor);

	translate_mesh(scene->meshes[2], 0.f, -0.5f, 0.f);

	Vec3 center = { 0.f, 0.f, -1.5f };
	scene->meshes[0] = create_cube3_center(&center, 1.f);

	return scene;
	/*


	float txtunit_w = (float)texWidth * 0.01 * size;
	float txtunit_h = (float)texHeight * 0.01 * size;
	float whalf = txtunit_w * 0.5f;
	float hhalf = txtunit_h * 0.5f;
	const Vec3 lb = {-whalf, -hhalf, 0.f};
	const Vec3 rb = {whalf, -hhalf, 0.f};
	const Vec3 lt = {-whalf, hhalf, 0.f};
	const Vec3 rt = {whalf, hhalf, 0.f};
	
	Scene * scene = alloc_scene(2);

	scene->meshes[1] = create_quad3_textured(&lb, &rb, &lt, &rt, 0);

	Vec3 center = { 0.f, 0.f, -1.5f };
	scene->meshes[0] = create_cube3_center(&center, 1.f);

	return scene;*/
}

Scene * scene_create_texture_quad(unsigned int texWidth, unsigned int texHeight, float scalex, float scaley) 
{
	const Vec3 lb = {-1.f, -1.f, 0.f};
	const Vec3 rb = {1.f, -1.f, 0.f};
	const Vec3 lt = {-1.f, 1.f, 0.f};
	const Vec3 rt = {1.f, 1.f, 0.f};
	
	Scene * scene = alloc_scene(2);
	//create_quad3(const Vec3 *lb, const Vec3 *rb, const Vec3 *lt, const Vec3 *rt)
	scene->meshes[1] = create_quad3_textured(&lb, &rb, &lt, &rt, 0);;//create_cube3_center(center, 0.25f);
	
	float aspect = (float)texHeight / (float)texWidth;

	scale_mesh(scene->meshes[1], 1.f * scalex, aspect *scaley, 1.f );

	Vec3 center = { 0.f, 0.f, -1.5f };
	scene->meshes[0] = create_cube3_center(&center, 1.f);

	return scene;
}

Scene * 
scene_create_test_all(float distance){
	Scene * scene = alloc_scene(9);
	Vec3 center = { 0.f, 0.f, 0.f };
	scene->meshes[0] = create_cube3_center(&center, .2f);

	mesh_create_bbox(scene->meshes[0]);
	mesh_color_by_bbox(scene->meshes[0]);
	
	scene->meshes[1] = createsphere(0.2f, 50, 50);
	translate_mesh(scene->meshes[1], 0.f, 0.f, distance);
	
	mesh_create_bbox(scene->meshes[1]);
	mesh_color_by_bbox(scene->meshes[1]);
	
	scene->meshes[2] = createcylinder(0.2f, .3f, 30, 30, true, true);
	translate_mesh(scene->meshes[2], 0.f, 0.f, -distance);
	
	mesh_create_bbox(scene->meshes[2]);
	mesh_color_by_bbox(scene->meshes[2]);
	
	scene->meshes[3] = createcone(0.2f, .3f, 10, true);
	translate_mesh(scene->meshes[3], -distance, 0.f, 0.f);
	
	mesh_create_bbox(scene->meshes[3]);
	mesh_color_by_bbox(scene->meshes[3]);
	
	center = (Vec3){ distance, 0.f, 0.f };
	scene->meshes[4] = create_square_block(&center, 0.2f, 0.25f, 0.3f, 1, 2, 3);
	
	mesh_create_bbox(scene->meshes[4]);
	mesh_color_by_bbox(scene->meshes[4]);
	
	center = (Vec3){ distance, 0.f, distance };
	scene->meshes[5] = create_square_block(&center, 0.2f, 0.3f, 0.25f, 1, 3, 2);
	
	mesh_create_bbox(scene->meshes[5]);
	mesh_color_by_bbox(scene->meshes[5]);
	
	center = (Vec3){ -distance, 0.f, distance };
	scene->meshes[6] = create_square_block(&center, 0.25f, 0.2f, 0.3f, 2, 1, 3);
	
	mesh_create_bbox(scene->meshes[6]);
	mesh_color_by_bbox(scene->meshes[6]);
	
	center = (Vec3){ distance, 0.f, -distance };
	scene->meshes[7] = create_square_block(&center, 0.25f, 0.3f, 0.2f, 2, 3, 1);
	
	mesh_create_bbox(scene->meshes[7]);
	mesh_color_by_bbox(scene->meshes[7]);
	
	scene->meshes[8] = createsphere(0.2f, 50, 50);

	Mat3 * rotx_mat = create_rot_x_mat(225.f);
	mat_mul_mesh(scene->meshes[8], rotx_mat);
	free(rotx_mat);
	translate_mesh(scene->meshes[8], -distance, 0.f, -distance );
	mesh_create_bbox(scene->meshes[8]);

	return scene;
}

Scene * 
scene_create_test_point_raster() {
	unsigned int meshes = 1;
	Scene * scene = alloc_scene(meshes);
	//scene->meshes[--meshes] = create_raster(6.f);
	scene->meshes[--meshes] = create_point_raster();
	
	mesh_create_bbox(scene->meshes[meshes]);
	mesh_color_by_bbox(scene->meshes[meshes]);
	
	return scene;
}

Scene * 
scene_create_test_cube() {
	Scene * scene = alloc_scene(1);
	Vec3 center = { 0.f, 0.f, 0.f };
	scene->meshes[0] = create_cube3_center(&center, .5f);
	mesh_create_bbox(scene->meshes[0]);
	mesh_color_by_bbox(scene->meshes[0]);
	
	Mat3 * rotx_mat = create_rot_x_mat(45.f);
	mat_mul_mesh(scene->meshes[0], rotx_mat);
	free(rotx_mat);
	
	return scene;
}

Scene * scene_create_polys() {
	Scene *poly_scene = alloc_scene(6);
	

	Vec3 points[8] = { {.5f, .0f, .0f} , { .5f, 1.0f, .0f}, { .0f, 1.0f, .0f}  , { .0f, 1.4f, .0f}, 
						 {1.4f, 1.4f, .0f}, { 1.4f, 1.0f, .0f}, { 0.9f, 1.0f, .0f}, { .9f, .0f, .0f}};


	poly_scene->meshes[0] = create_polygon3(points, 8);
	

	Vec3 points2[14] = { {0.f, .0f, .0f} , { .0f, .8f, .0f}, { .2f, 1.1f, .0f}  , { .3f, 1.4f, .0f}, 
						 {.5f, 1.1f, .0f}, { .8f, 0.9f, .0f}, { 1.f, 1.2f, .0f}, { 1.0f, 0.7f, .0f},
						 { 0.7f, 0.6f, .0f}, { 1.0f, 0.4f, .0f}, { 0.7f, .0f, .0f}, { .5f, .2f, .0f},
						 { .3f, .0f, .0f}, { 0.2f, 0.2f, .0f}};

	poly_scene->meshes[1] = create_polygon3(points2, 14);
	

	Vec3 points3[10] = { {0.f, .0f, .0f} , { .0f, 1.1f, .0f}, { .3f, .8f, .0f}  , { .6f, 1.1f, .0f}, 
						 {.4f, .6f, .0f}, { .1f, 0.9f, .0f}, { .1f, .3f, .0f}, { .4f, .5f, .0f},
						 { 0.6f, 0.1f, .0f}, { .3f, 0.3f, .0f}};


	poly_scene->meshes[2] = create_polygon3(points3, 10);
	
	

	Vec3 points4[22] = {	{1.f, .0f, .0f}, { .0f, .0f, .0f }, { .0f, 1.f, .0f}  , { 1.f, 1.f, .0f}, 
						 	{1.f, .2f, .0f}, { .2f, 0.2f, .0f}, { .2f, .8f, .0f}, { .8f, .8f, .0f}, { .8f, .4f, .0f},
						 	{ 0.4f, 0.4f, .0f}, { .4f, 0.6f, .0f} ,{.5f, .6f, .0f} , { .5f, .5f, .0f}, { .7f, .5f, .0f}, 
						 	{.7f, .7f, .0f}, { .3f, .7f, .0f}, { .3f, .3f, .0f}, { .9f, .3f, .0f},
						 	{ 0.9f, 0.9f, .0f}, { .1f, 0.9f, .0f}, { 0.1f, 0.1f, .0f}, { 1.f, 0.1f, .0f}
						};


	poly_scene->meshes[3] = create_polygon3(points4, 22);
	

	Vec3 points5[10] = { {0.1f, .0f, .0f} , { .3f, .3f, .0f}, { .0f, .4f, .0f}  , { .3f, .5f, .0f}, 
						   {.5f, .8f, .0f}, { .7f, 0.5f, .0f}, { 1.f, .4f, .0f}, { .7f, .3f, .0f},
						   { 0.9f, 0.0f, .0f}, { .5f, 0.2f, .0f}};


	poly_scene->meshes[4] = create_polygon3(points5, 10);
	

	Vec3 points6[46] = {  {.0f, 1.1f, .0f}, { .1f, 1.4f, .0f }, { .4f, 1.6f, .0f}  , { .9f, 1.7f, .0f}, 
						 	{1.4f, 1.6f, .0f}, { 1.7f, 1.4f, .0f}, { 1.8f, 1.1f, .0f},   { 1.7f, .8f, .0f}, { 1.6f, .5f, .0f},
						 	{1.7f, .4f, .0f}, { 1.5f, .3f, .0f}, { 1.4f, .4f, .0f} ,   { 1.2f, .4f, .0f}, { 1.3f, .2f, .0f}, 
						 	{1.2f, .0f, .0f}, { 1.1f, .2f, .0f},  { 1.f, .0f, .0f},   { .9000002f, .2f, .0f},
						 	{.9000002f, .3f, .0f}, { 1.000002f, 0.5f, .0f}, { 1.1000002f, 0.6f, .0f}, { 1.5f, 0.7f, .0f},
							{1.3f, 0.9f, .0f}, { 1.f, .7f, .0f }, { 1.1f, .6f, .0f}  , { 1.f, .5f, .0f}, { .9f, .6f, .0f}, 
						 	{0.8f, .5000003f, .0f}, { .7f, 0.6000003f, .0f}, { .8f, .7f, .0f},   { .5f, .9f, .0f}, { .3f, .7f, .0f},
						 	{.7f, .6f, .0f}, { .8f, 0.5f, .0f}, {.9f, .3f, .0f} ,   { .9f, .2f, .0f}, { .8f, .0f, .0f}, 
						 	{.7f, .2f, .0f}, { .6f, .0f, .0f},  { .5f, .2f, .0f},   { .6f, .4f, .0f}, { .4f, .4f, .0f}, 
						 	{.3f, .3f, .0f}, { .1f, 0.4f, .0f}, { 0.2f, 0.5f, .0f}, { .1f, 0.8f, .0f}};


	poly_scene->meshes[5] = create_polygon3(points6, 46);
	

	ColorRGB color = { 1.f, 0.f, 0.f };
	mesh_set_color(poly_scene->meshes[0], &color);
	mesh_set_color(poly_scene->meshes[1], &color);
	mesh_set_color(poly_scene->meshes[2], &color);
	mesh_set_color(poly_scene->meshes[3], &color);
	mesh_set_color(poly_scene->meshes[4], &color);
	color = (ColorRGB ){ 0.f, 0.f, 1.f };
	mesh_set_color(poly_scene->meshes[5], &color);


	translate_mesh(poly_scene->meshes[0], -5.5, 1.7f, 0.f);
	translate_mesh(poly_scene->meshes[1], -1, 1.7f, 0.f);
	translate_mesh(poly_scene->meshes[2], .5, 1.7f, 0.f);
	translate_mesh(poly_scene->meshes[3], .5, -2.0f, 0.f);
	translate_mesh(poly_scene->meshes[4], -1.5f, -2.0f, 0.f);
	translate_mesh(poly_scene->meshes[5], -.7f, -0.5f, 0.1f);
	
	scale_mesh(poly_scene->meshes[0], 0.3f, .6f, 1.f);

	return poly_scene;

}

static void scene_itoa(int value, char* str, int bufflen)
{
	snprintf(str, bufflen, "%d", value);
}

Scene * 
scene_create_waterfall_diagram(TextureCache *texCache, float *_array, uint32_t _rows, uint32_t _cols) {
	Scene * scene = alloc_scene(7 + _cols + _cols + _rows + _rows);
	uint32_t cntMesh = 0;
	//scene->meshes[0] = create_raster(5.f);
	//scene->meshes[cntMesh++] = create_point_raster();
	scene->meshes[cntMesh] = create_hmap_from_array(_array, _rows, _cols);
	
	Mesh *map = scene->meshes[cntMesh++];
	scale_mesh(map, 0.5f, 1.0f, 0.2f);
	mesh_create_bbox(map);
	mesh_color_by_bbox2(map);
	
	char buffer[20];
	Mat3 * roty_mat = create_rot_y_mat(180.f);
	Mat3 * rotx_mat = create_rot_x_mat(90.f);
	ColorRGB txtCol = { 1.f, 1.f, 1.f };

	ColorRGB line_col = { .5f, .5f, .5f };
	for(unsigned int shape = 0; shape < map->cntShapes; ++shape){
		Shape * curshape = map->shapes[shape];
		if ( curshape->cntVertex == 2 ) {
			set_shape_color(curshape, &line_col);
		}
	}

	BBox *bbox = &map->bbox;
	line_col = (ColorRGB){ .5f, .5f, .5f };
	if (bbox->created) {
		Vec3 *bbmin = &bbox->min;
		Vec3 *bbmax = &bbox->max;

		Vec3 start, end;
		vec3_set_values(&start, bbmin->x, bbmin->y, bbmin->z);
		vec3_set_values(&end, bbmin->x, 1.f, bbmin->z);
		
		scene->meshes[cntMesh] = create_line3(&start, &end);
		mesh_set_color (scene->meshes[cntMesh++], &line_col);

		vec3_set_values(&start, bbmax->x, bbmin->y, bbmin->z);
		vec3_set_values(&end, bbmax->x, 1.f, bbmin->z);
		
		scene->meshes[cntMesh] = create_line3(&start, &end);
		mesh_set_color (scene->meshes[cntMesh++], &line_col);

		vec3_set_values(&start, bbmin->x, bbmin->y, bbmax->z);
		vec3_set_values(&end, bbmin->x, 1.f, bbmax->z);
		
		scene->meshes[cntMesh] = create_line3(&start, &end);
		mesh_set_color (scene->meshes[cntMesh++], &line_col);


		vec3_set_values(&start, bbmax->x, bbmin->y, bbmax->z);
		vec3_set_values(&end, bbmax->x, 1.f, bbmax->z);

		scene->meshes[cntMesh] = create_line3(&start, &end);
		mesh_set_color (scene->meshes[cntMesh++], &line_col);

		//map->shapes[cnt_shape++] = create_shape_line3(&lb, &rb);
		//map->shapes[cnt_shape++] = create_shape_line3(&lb, &lt);
		Shape* first_h_line = map->shapes[0];
		Shape* first_v_line = map->shapes[1];
		Vec3 h_vec, v_vec;
		vec3_sub_dest(&h_vec, &first_h_line->vertices[1]->vec, &first_h_line->vertices[0]->vec);
		vec3_sub_dest(&v_vec, &first_v_line->vertices[1]->vec, &first_v_line->vertices[0]->vec);
		
		float axis_offset = 0.2f;
		//x Axis 
		vec3_set_values(&start, bbmin->x, 0.f, bbmin->z - axis_offset);
		vec3_set_values(&end, bbmax->x, 0.f, bbmin->z - axis_offset);

		scene->meshes[cntMesh] = create_line3(&start, &end);
		mesh_set_color (scene->meshes[cntMesh++], &line_col);

		float axis_step_len = .05f;
		for (uint32_t cur_col = 0; cur_col < _cols; cur_col++) {
			float cur_x = bbmin->x + (h_vec.x * cur_col);
			float base_z = bbmin->z - axis_offset;
			vec3_set_values(&start, cur_x, 0.f, base_z - axis_step_len);
			vec3_set_values(&end, cur_x, 0.f, base_z + 2.f*axis_step_len);

			scene->meshes[cntMesh] = create_line3(&start, &end);
			mesh_set_color (scene->meshes[cntMesh++], &line_col);

			start.z -= 0.2f;
			//scene->meshes[cntMesh] = create_point3(&start);
			//mesh_set_color (scene->meshes[cntMesh++], &line_col);
			//itoa(cur_col + 1, buffer, 10);
			scene_itoa(cur_col + 1, buffer, 20);
			//printf("converted: %s\n", buffer);
			scene->meshes[cntMesh] = __Rendererext_quad(texCache, 0.25, 80.f, (unsigned char const * const)buffer, &txtCol);
			mat_mul_mesh(scene->meshes[cntMesh], roty_mat);
			mat_mul_mesh(scene->meshes[cntMesh], rotx_mat);
			translate_mesh(scene->meshes[cntMesh++], start.x, start.y, start.z);
			
		}
		

		//z Axis 
		vec3_set_values(&start, bbmin->x - axis_offset, 0.f, bbmin->z);
		vec3_set_values(&end, bbmin->x - axis_offset, 0.f, bbmax->z);

		scene->meshes[cntMesh] = create_line3(&start, &end);
		mesh_set_color (scene->meshes[cntMesh++], &line_col);

		for (uint32_t cur_row = 0; cur_row < _rows; cur_row++) {
			float cur_z = bbmin->z - (v_vec.z * cur_row);
			float base_x = bbmin->x - axis_offset;
			vec3_set_values(&start, base_x - axis_step_len, 0.f, cur_z);
			vec3_set_values(&end, base_x + 2.f*axis_step_len, 0.f,cur_z);

			scene->meshes[cntMesh] = create_line3(&start, &end);
			mesh_set_color (scene->meshes[cntMesh++], &line_col);

			start.x -= 0.2f;
			//scene->meshes[cntMesh] = create_point3(&start);
			//mesh_set_color (scene->meshes[cntMesh++], &line_col);
			//itoa(cur_row + 1, buffer, 10);
			scene_itoa(cur_row + 1, buffer, 20);
			//printf("converted: %s\n", buffer);
			scene->meshes[cntMesh] = __Rendererext_quad(texCache, 0.25, 80.f, (unsigned char const * const)buffer, &txtCol);
			mat_mul_mesh(scene->meshes[cntMesh], roty_mat);
			mat_mul_mesh(scene->meshes[cntMesh], rotx_mat);
			translate_mesh(scene->meshes[cntMesh++], start.x, start.y, start.z);
		}
		
	}

	free(rotx_mat);
	free(roty_mat);

	return scene;
}
