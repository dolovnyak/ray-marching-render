#include "config_cl.h"

t_vector3d  get_cam_ray(int x, int y, t_camera camera, int width, int height)
{
	float3  canvas_cell;
    float3  r;

    float cell_x = x * camera.aspect_ratio / width;
    float cell_y = y / (float)height;
	x -= width / 2;
    y -= height / 2;
    canvas_cell = camera.transform + camera.transform.local.forward * camera
    		.min_distance + camera.transform.local.right * x + camera
    		.transform.local.up * y;
//    canvas_cell = (t_vector3d){
//    	camera.pos.x + camera.local_z.x * camera.min_distance +
//    	camera.local_x.x * x + camera.local_y.x * y,
//		camera.pos.y + camera.local_z.y * camera.min_distance +
//		camera.local_x.y * x + camera.local_y.y * y,
//		camera.pos.z + camera.local_z.z * camera.min_distance +
//		camera.local_x.z * x + camera.local_y.z * y};
	r = normalize(canvas_cell);
    return (t_vector3d)(r.x, r.y, r.z);
}
