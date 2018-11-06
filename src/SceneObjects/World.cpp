
#include <fstream>    //for file saving
#include "../Utilities/Constants.h"
#include "../Utilities/Maths.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Point2D.h"
#include "../Utilities/Normal.h"
#include "AmbientOccluder.h"
#include "../Utilities/Ray.h"
#include "World.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Directional.h"
#include "PointLight.h"
#include "../Misc./MultipleObjects.h"
#include "../Misc./RayCast.h"
#include "../Misc./Whitted.h"
#include "../Misc./Pinhole.h"
#include "../Misc./Multijittered.h"
#include "GeometricObject.h"
#include "../Utilities/Reflective.h"
#include "../Utilities/Phong.h"
#include "../Utilities/PerfectSpecular.h"
#include "../Utilities/Transparent.h"
#include "../Utilities/Material.h"
#include "../Utilities/Matte.h"
#include "Instance.h"

#include <iostream>
using namespace std;

World::World(){
  vp = ViewPlane();
  background_color = black;
//  tracer_ptr = new MultipleObjects();
  pixels.resize(vp.hres * vp.vres);
  //ambient_ptr = new Ambient();
//  tracer_ptr = new RayCast(this);
  tracer_ptr = new Whitted(this);
    //lights
//  Ambient* ambient_ptr = new Ambient;
//  ambient_ptr->scale_radiance(0.6);
//  set_ambient_light(ambient_ptr);

  int num_samples = 30;     //samples to use for the sampling

  Multijittered* sampler_ptr = new Multijittered(num_samples);
  AmbientOccluder* ambient_ptr = new AmbientOccluder;
  ambient_ptr->scale_radiance(.5);
  ambient_ptr->set_sampler(sampler_ptr);
  set_ambient_light(ambient_ptr);
//  Directional* directional_ptr = new Directional;
//  directional_ptr->set_direction(0, 0, -1);
//  directional_ptr->set_ls(1.1);
//  add_light(directional_ptr);
  PointLight* pointlight_ptr = new PointLight(0,-5,10);
  pointlight_ptr->scale_radiance(2);
//  pointlight_ptr->set_direction(0, 0, -1);
//  pointlight_ptr->set_ls(1.1);
  add_light(pointlight_ptr);

  vp.set_hres(300);
  vp.set_vres(300);
  vp.set_s(1.2);
  vp.set_gamma(1.0);
  pixels.resize(vp.hres * vp.vres); //resize pixels array again
  vp.set_sampler(sampler_ptr);
  vp.set_max_depth(15);

  //set up camera
  Pinhole* pinhole_ptr = new Pinhole;
  //  pinhole_ptr->set_eye(60, 30, 170);
  //  pinhole_ptr->set_lookat(-60,-180, 40);
  pinhole_ptr->set_eye(-20, 10, 0);
  pinhole_ptr->set_lookat(0, 30, 0);
  pinhole_ptr->set_view_distance(30);
  pinhole_ptr->set_exposure_time(1);
  //  pingole_ptr->set_vpd()
  pinhole_ptr->compute_uvw();
  set_camera(pinhole_ptr);
}

void
World::buildMirror(void){
  background_color = black;
//  tracer_ptr = new MultipleObjects(this);

  Grid* grid_ptr = new Grid;

  Phong* phong_ptr1 = new Phong;
  phong_ptr1->set_ks(1.2);
  phong_ptr1->set_cs(0,0,1);
  phong_ptr1->set_exp(2);
  phong_ptr1->set_ka(0.5);
  phong_ptr1->set_cd(0,1,0);  //green
  phong_ptr1->set_kd(0.8);

  Phong* phong_ptr2 = new Phong;
  phong_ptr2->set_ks(1.2);
  phong_ptr2->set_cs(0,0,1);
  phong_ptr2->set_exp(2);
  phong_ptr2->set_ka(0.5);
  phong_ptr2->set_cd(1,0,0);  //red
  phong_ptr2->set_kd(0.8);

  Phong* phong_ptr3 = new Phong;
  phong_ptr3->set_ks(1.2);
  phong_ptr3->set_cs(0,0,1);
  phong_ptr3->set_exp(2);
  phong_ptr3->set_ka(0.5);
  phong_ptr3->set_cd(1,1,0);  //yellow
  phong_ptr3->set_kd(0.8);


                                              //Mirror
Reflective* reflect_ptr1 = new Reflective;
reflect_ptr1->set_ka(.25);
reflect_ptr1->set_kd(.5);
reflect_ptr1->set_cd(.8,.8,.8);  //greyish
reflect_ptr1->set_ks(.15);
reflect_ptr1->set_exp(100);
reflect_ptr1->set_kr(.75);
reflect_ptr1->set_cr(1,1,1);  //reflect white

                                              //Transparent
Transparent* glass_ptr1 = new Transparent;
glass_ptr1->set_ks(.9);
glass_ptr1->set_exp(1000);
glass_ptr1->set_ior(1);
glass_ptr1->set_kr(.1);
glass_ptr1->set_kt(.9);

  //add sphere
  Sphere* sphere_ptr0 = new Sphere;
  sphere_ptr0->set_center(10, 10, 10);
  sphere_ptr0->set_radius(10.0);
  sphere_ptr0->set_material(glass_ptr1);
//  add_object(sphere_ptr);
  grid_ptr->add_object(sphere_ptr0);

  Sphere* sphere_ptr1 = new Sphere;
  sphere_ptr1->set_center(-15, 60, 10);
  sphere_ptr1->set_radius(10.0);
  sphere_ptr1->set_material(phong_ptr1);
//  add_object(sphere_ptr);
  grid_ptr->add_object(sphere_ptr1);

  Sphere* sphere_ptr2 = new Sphere;
  sphere_ptr2->set_center(16, 40, 30);
  sphere_ptr2->set_radius(30.0);
  sphere_ptr2->set_material(reflect_ptr1);
//  add_object(sphere_ptr2);
  grid_ptr->add_object(sphere_ptr2);

  Sphere* sphere_ptr3 = new Sphere;
  sphere_ptr3->set_center(30, 20, 40);
  sphere_ptr3->set_radius(20.0);
  sphere_ptr3->set_material(phong_ptr3);
//  add_object(sphere_ptr3);
  grid_ptr->add_object(sphere_ptr3);

//call after grid is done being added to
  grid_ptr->setup_cells();
  add_object(grid_ptr);

} //end reflective

void
World::buildReflective(void){
  background_color = black;
//  tracer_ptr = new MultipleObjects(this);

  Grid* grid_ptr = new Grid;
                                            //reflective
  Phong* phong_ptr1 = new Phong;
  phong_ptr1->set_ks(1.2);
  phong_ptr1->set_cs(0,0,1);
  phong_ptr1->set_exp(2);
  phong_ptr1->set_ka(0.5);
  phong_ptr1->set_cd(0,1,0);  //green
  phong_ptr1->set_kd(0.8);

  Phong* phong_ptr2 = new Phong;
  phong_ptr2->set_ks(1.2);
  phong_ptr2->set_cs(0,0,1);
  phong_ptr2->set_exp(2);
  phong_ptr2->set_ka(0.5);
  phong_ptr2->set_cd(1,0,0);  //red
  phong_ptr2->set_kd(0.8);

  Phong* phong_ptr3 = new Phong;
  phong_ptr3->set_ks(1.2);
  phong_ptr3->set_cs(0,0,1);
  phong_ptr3->set_exp(2);
  phong_ptr3->set_ka(0.5);
  phong_ptr3->set_cd(1,1,0);  //yellow
  phong_ptr3->set_kd(0.8);

  //add sphere
  Sphere* sphere_ptr = new Sphere;
  sphere_ptr->set_center(15, 10, 10);
  sphere_ptr->set_radius(10.0);
  sphere_ptr->set_material(phong_ptr3);
//  add_object(sphere_ptr);
  grid_ptr->add_object(sphere_ptr);

  Sphere* sphere_ptr2 = new Sphere;
  sphere_ptr2->set_center(16, 40, 30);
  sphere_ptr2->set_radius(30.0);
  sphere_ptr2->set_material(phong_ptr1);
//  add_object(sphere_ptr2);
  grid_ptr->add_object(sphere_ptr2);

  Sphere* sphere_ptr3 = new Sphere;
  sphere_ptr3->set_center(20, 20, 30);
  sphere_ptr3->set_radius(20.0);
  sphere_ptr3->set_material(phong_ptr2);
//  add_object(sphere_ptr3);
  grid_ptr->add_object(sphere_ptr3);

//call after grid is done being added to
  grid_ptr->setup_cells();
  add_object(grid_ptr);

/*
//add plane
  Plane* plane_ptr = new Plane(Point3D(30,30,30), Normal(0,5,5));
  plane_ptr->set_color(0,0,1);
  plane_ptr->set_material(phong_ptr3);
  add_object(plane_ptr);
*/

  //add triangle
  /*
    Triangle* triangle_ptr = new Triangle(Point3D(15,10,20), Point3D(10,10,0), Point3D(0,20,30));
    triangle_ptr->set_material(phong_ptr2);
    add_object(triangle_ptr);
*/
} //end reflective

void
World::buildDiffuse(void){
  background_color = black;

//  Grid* grid_ptr = new Grid;
/*
  //add sphere
  Matte* matte_ptr1 = new Matte;
  matte_ptr1->set_ka(0.5);
  matte_ptr1->set_cd(0,1,0);  //green
  matte_ptr1->set_kd(0.8);

  Matte* matte_ptr2 = new Matte;
  matte_ptr2->set_ka(0.5);
  matte_ptr2->set_cd(1,0,0);  //red
  matte_ptr2->set_kd(0.8);

  Matte* matte_ptr3 = new Matte;
  matte_ptr3->set_ka(0.5);
  matte_ptr3->set_cd(1,1,0);  //yellow
  matte_ptr3->set_kd(0.8);

  //add sphere
  Sphere* sphere_ptr = new Sphere;
  sphere_ptr->set_center(15, 10, 10);
  sphere_ptr->set_radius(10.0);
  sphere_ptr->set_material(matte_ptr3);
//  add_object(sphere_ptr);
  grid_ptr->add_object(sphere_ptr);

  Sphere* sphere_ptr2 = new Sphere;
  sphere_ptr2->set_center(16, 40, 30);
  sphere_ptr2->set_radius(30.0);
  sphere_ptr2->set_material(matte_ptr1);
//  add_object(sphere_ptr2);
  grid_ptr->add_object(sphere_ptr2);

  Sphere* sphere_ptr3 = new Sphere;
  sphere_ptr3->set_center(20, 20, 30);
  sphere_ptr3->set_radius(    Sphere* sphere_ptrLoop = new Sphere;20.0);
  sphere_ptr3->set_material(matte_ptr2);
//  add_object(sphere_ptr3);
  grid_ptr->add_object(sphere_ptr3);

*/


Pinhole* pinhole_ptr = new Pinhole;
//  pinhole_ptr->set_eye(60, 30, 170);
//  pinhole_ptr->set_lookat(-60,-180, 40);
pinhole_ptr->set_eye(3, 3, 3);
pinhole_ptr->set_lookat(0, 0, 0);
pinhole_ptr->set_view_distance(1);
pinhole_ptr->set_exposure_time(1);
//  pingole_ptr->set_vpd()
pinhole_ptr->compute_uvw();
set_camera(pinhole_ptr);


/*
  int num_spheres = 5;
  for(int x = 0; x < num_spheres; x++){
    Matte* matte_ptrLoop = new Matte;
    matte_ptrLoop->set_ka(0.25);
    matte_ptrLoop->set_cd( (double)((rand()%10) / 10.0), (double)((rand()%10) / 10.0), (double)((rand()%10) / 10.0));  //yellow
    matte_ptrLoop->set_kd(0.75);

    Sphere* sphere_ptrLoop = new Sphere;
    sphere_ptrLoop->set_center(50 - (rand() % 10) * (rand() % 10) * (rand() % 10), 20 - (rand() % 10) * (rand() % 10) * (rand() % 10),
      30 - (rand() % 10) * (rand() % 10) * (rand() % 10));
    sphere_ptrLoop->set_radius(10.0);
    sphere_ptrLoop->set_material(matte_ptrLoop);

    grid_ptr->add_object(sphere_ptrLoop);
  }

  Matte* matte_ptrPLY = new Matte;
  matte_ptrPLY->set_ka(0.25);
  matte_ptrPLY->set_cd(0,1,0);  //yellow
  matte_ptrPLY->set_kd(0.75);
  string file_name = "";

  Grid* grid_ptr = new Grid(new Mesh);
  grid_ptr->read_flat_triangles(file_name);
*/
//  grid_ptr->set_material(matte_ptrPLY);
//  grid_ptr->setup_cells();
//  add_object(grid_ptr);

  /*
      Triangle* triangle_ptr = new Triangle(Point3D(-30,0,20), Point3D(0,0,20), Point3D(0,40,40));
      triangle_ptr->set_material(matte_ptr1);
      add_object(triangle_ptr);
  */

}


void
World::buildMesh(void){
  background_color = black;
//  tracer_ptr = new MultipleObjects(this);





  Phong* phong_ptr1 = new Phong;
  phong_ptr1->set_ks(.7);
  phong_ptr1->set_cs(0,0,1);
  phong_ptr1->set_exp(2);
  phong_ptr1->set_ka(0.5);
  phong_ptr1->set_cd(0,1,0);  //green
  phong_ptr1->set_kd(0.8);

  string file_name = "teapot.obj";
  Grid* grid_ptr = new Grid(new Mesh);
  grid_ptr->read_flat_triangles(file_name);
  grid_ptr->set_material(phong_ptr1);
  grid_ptr->setup_cells();

  double xcenter = grid_ptr->get_bounding_box().x0 - grid_ptr->get_bounding_box().x1;
  double ycenter = grid_ptr->get_bounding_box().y0 - grid_ptr->get_bounding_box().y1;
  double zcenter = grid_ptr->get_bounding_box().z0 - grid_ptr->get_bounding_box().z1;

  Instance* instance_ptr = new Instance;
  instance_ptr->set_object(grid_ptr);
  instance_ptr->scale(1.2);

/*
  BBox objBox = instance_ptr.get_bounding_box
*/
  Pinhole* pinhole_ptr = new Pinhole;
  //  pinhole_ptr->set_eye(60, 30, 170);
  //  pinhole_ptr->set_lookat(-60,-180, 40);
//  pinhole_ptr->set_eye(3, 12, -5);
  pinhole_ptr->set_eye(3 , 4, -3);
  pinhole_ptr->set_lookat(xcenter, ycenter, zcenter);
  pinhole_ptr->set_view_distance(25);
  pinhole_ptr->set_exposure_time(1);
  //  pingole_ptr->set_vpd()
  pinhole_ptr->compute_uvw();
  set_camera(pinhole_ptr);

//  add_object(grid_ptr);

  add_object(instance_ptr);



//  add_object(grid_ptr);


} //end mesh


void
World::add_object(GeometricObject* object_ptr){
  objects.push_back(object_ptr);
}

void
World::add_light(Light* light_ptr){
  lights.push_back(light_ptr);
}

void
World::set_camera(Camera* camera){
  camera_ptr = camera;
}
/*
void
World::set_ambient_light(Ambient* ambient){
  ambient_ptr = ambient;
}
*/
void
World::set_ambient_light(Light* ambient){
  ambient_ptr = ambient;
}


  ShadeRec
  World::hit_bare_bones_objects(const Ray& ray){
    ShadeRec sr(*this);
    double  t;//	objects.erase (objects.begin(), objects.end());
    double  tmin = 10000.0; //kHugeValue
    double  num_objects = objects.size();

    for(int j = 0; j < num_objects; j++){
      if(objects[j]->hit(ray, t, sr) && (t < tmin) ){
        sr.hit_an_object = true;
        tmin = t;
        sr.color = objects[j]->get_color();
      }
    }
    return sr;
  }

  ShadeRec
  World::hit_objects(const Ray& ray){
    ShadeRec sr(*this);
    double t;
    Normal normal;
    Point3D local_hit_point;
    float tmin = 10000; //kHugeValue
    int num_objects = objects.size();

    for(int j = 0; j < num_objects; j++){
      if(objects[j]->hit(ray, t, sr) && (t < tmin)){
        sr.hit_an_object = true;
        tmin = t;
        sr.material_ptr = objects[j]->get_material(); //get material
        sr.hit_point = ray.o + t * ray.d;
        normal = sr.normal;
        local_hit_point = sr.local_hit_point;
      }
    }//end for

    if(sr.hit_an_object){
      sr.t = tmin;
      sr.normal = normal;
      sr.local_hit_point = local_hit_point;
    }

    return sr;
  }

void
World::render_scene_ortho(void){
  RGBColor pixel_color;
  Ray ray;
  double zw = 0;
  double x,y;
//populate the pixel array
  for(int r = 0; r < vp.vres; r++){ //vertical
    for(int c = 0; c <= vp.hres; c++){  //horizontal

      x = vp.s * (c - 0.5 * (vp.hres - 1.0));
      y = vp.s * (r - 0.5 * (vp.vres - 1.0));


      ray.o = Point3D(x, y, zw);
      pixel_color = tracer_ptr->trace_ray(ray);   //ray tracing!
  //    cout << "Color: " << pixel_color.r << pixel_color.g << pixel_color.b << endl;
      display_pixel(r, c, pixel_color);           //put pixel in list!
    }
  }//end fors


  cout << "all pixels printed" << endl;


//save image
  string fileName = "orthographic";
  save_image(fileName);
}//end render

void
World::render_scene_multijittered(void){
  RGBColor pixel_color;
  Ray ray;
  double zw = 0;
  double x,y;
  //int samples = vp.sampler_ptr->num_samples;
  //int n = (int) sqrt((float) samples); //10 samples
  Point2D sp;
  Point2D pp;
//populate the pixel array
  for(int r = 0; r < vp.vres; r++){ //vertical
    for(int c = 0; c <= vp.hres; c++){  //horizontal
      pixel_color = black;

  //    for(int p = 0; p < n; p++){
        for (int q=0; q< vp.num_samples; q++){
          sp = vp.sampler_ptr->sample_unit_square();
          pp.x = vp.s * (c - 0.5 * vp.hres + sp.x);
          pp.y = vp.s * (r - 0.5 * vp.vres + sp.y);
          ray.o = Point3D(pp.x, pp.y, zw);
          pixel_color += tracer_ptr->trace_ray(ray);
        }
      pixel_color /= vp.num_samples;
//      cout << "Color: " << pixel_color.r << pixel_color.g << pixel_color.b << endl;
      display_pixel(r, c, pixel_color);           //put pixel in list!
    }
  }//end fors



  cout << "all pixels printed" << endl;


//save image
  string fileName = "jittering";
  save_image(fileName);
}

void
World::render_scene_perspective(void){

  RGBColor pixel_color;
  Ray ray;
  ray.o = Point3D(0.0, 0.0, -30.0); //last param is "eye" dist from vp
//populate the pixel array
  for(int r = 0; r < vp.vres; r++){ //vertical
    for(int c = 0; c <= vp.hres; c++){  //horizontal
      ray.d = Vector3D(vp.s * (c - 0.5 * (vp.hres - 1.0)),
        vp.s * (r - 0.5 * (vp.vres - 1.0)), 200);    //last is eye dist from screen
      ray.d.normalize();
      pixel_color = tracer_ptr->trace_ray(ray);
  //    cout << "Color: " << pixel_color.r << pixel_color.g << pixel_color.b << endl;
      display_pixel(r, c, pixel_color);           //put pixel in list!
    }
  }//end fors
  cout << "all pixels printed" << endl;

//save image
  string fileName = "Perspective";
  save_image(fileName);
}//end render


void
World::display_pixel(const int row,
                    const int column,
                    const RGBColor& pixel_color){

    RGBColor mapped_color;
    if(pixel_color.r > 1.0 || pixel_color.g > 1.0 || pixel_color.b > 1.0){

      mapped_color = clamp_to_color(pixel_color);
    }else{
      mapped_color = max_to_one(pixel_color);
    }
    if(vp.gamma != 1.0){
      mapped_color = mapped_color.powc(vp.inv_gamma);
    }

    int idx = (column * vp.hres) + row;
    pixels[idx] = mapped_color;
}

void World::save_image(const std::string& outputFile) const {
  const int image_size = vp.vres * vp.hres * 4;
  const int headers_size = 14 + 40;
  const int filesize = image_size + headers_size;
  const int pixelsPerMeter = 2835;

  unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0};
  //size of the file in bytes
  bmpfileheader[ 2] = (unsigned char)(filesize);
  bmpfileheader[ 3] = (unsigned char)(filesize>>8);
  bmpfileheader[ 4] = (unsigned char)(filesize>>16);
  bmpfileheader[ 5] = (unsigned char)(filesize>>24);

  unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0};
  //width of the image in bytes
  bmpinfoheader[ 4] = (unsigned char)(vp.hres);
  bmpinfoheader[ 5] = (unsigned char)(vp.hres>>8);
  bmpinfoheader[ 6] = (unsigned char)(vp.hres>>16);
  bmpinfoheader[ 7] = (unsigned char)(vp.hres>>24);

  //height of the image in bytes
  bmpinfoheader[ 8] = (unsigned char)(vp.vres);
  bmpinfoheader[ 9] = (unsigned char)(vp.vres>>8);
  bmpinfoheader[10] = (unsigned char)(vp.vres>>16);
  bmpinfoheader[11] = (unsigned char)(vp.vres>>24);

  // Size image in bytes
  bmpinfoheader[21] = (unsigned char)(image_size);
  bmpinfoheader[22] = (unsigned char)(image_size>>8);
  bmpinfoheader[23] = (unsigned char)(image_size>>16);
  bmpinfoheader[24] = (unsigned char)(image_size>>24);

  bmpinfoheader[25] = (unsigned char)(pixelsPerMeter);
  bmpinfoheader[26] = (unsigned char)(pixelsPerMeter>>8);
  bmpinfoheader[27] = (unsigned char)(pixelsPerMeter>>16);
  bmpinfoheader[28] = (unsigned char)(pixelsPerMeter>>24);

  bmpinfoheader[29] = (unsigned char)(pixelsPerMeter);
  bmpinfoheader[30] = (unsigned char)(pixelsPerMeter>>8);
  bmpinfoheader[31] = (unsigned char)(pixelsPerMeter>>16);
  bmpinfoheader[32] = (unsigned char)(pixelsPerMeter>>24);

  FILE *file = fopen(outputFile.c_str(), "wb");//write-binary

  fwrite(bmpfileheader,1,14, file);
  fwrite(bmpinfoheader,1,40, file);

  for (int i = 0; i < pixels.size(); ++i){
      const RGBColor pixel = pixels[i];
      unsigned char color[3] = {
          (int) (pixel.b * 255),
          (int) (pixel.g * 255),
          (int) (pixel.r * 255)
      };
      fwrite(color, 1, 3, file);
  }
  fclose(file);
}




//handle gamut


RGBColor
World::clamp_to_color(const RGBColor& raw_color){
    RGBColor c(raw_color);

    if(raw_color.r > 1.0){
      c.r = 1.0;
    }
    if(raw_color.g > 1.0){
      c.g = 1.0;
    }
    if(raw_color.b > 1.0){
      c.b = 1.0;
    }

    return c;
}

  RGBColor
  World::max_to_one(const RGBColor& c){
    float max_value = max(c.r, max(c.g, c.b));

    if(max_value > 1.0){
      return (c / max_value);
    }else{
      return c;
    }
  }
