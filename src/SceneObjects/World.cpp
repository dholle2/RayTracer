
#include <fstream>    //for file saving
#include "../Utilities/Constants.h"
#include "../Utilities/Maths.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Point2D.h"
#include "../Utilities/Normal.h"

#include "../Utilities/Ray.h"
#include "World.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Directional.h"
#include "../Misc./MultipleObjects.h"
#include "../Misc./Pinhole.h"
#include "../Misc./Multijittered.h"

#include <iostream>
using namespace std;

World::World(){
  vp = ViewPlane();
  background_color = black;
  tracer_ptr = new MultipleObjects();
  pixels.resize(vp.hres * vp.vres);
}


void
World::build(void){
  background_color = black;
  tracer_ptr = new MultipleObjects(this);
  int num_samples = 10;     //samples to use for the sampling
  vp.set_hres(200);
  vp.set_vres(200);
  vp.set_s(0.8);
  vp.set_gamma(1.0);
  pixels.resize(vp.hres * vp.vres); //resize pixels array again
  vp.set_sampler(new Multijittered(num_samples));

  //set up camera
  Pinhole* pinhole_ptr = new Pinhole;
  pinhole_ptr->set_eye(300, 400, 500);
  pinhole_ptr->set_eye(300, 400, 500);
  pinhole_ptr->set_eye(300, 400, 500);
  pinhole_ptr->set_eye(300, 400, 500);
  set_camera(pinhole_ptr);
//add sphere
  Sphere* sphere_ptr = new Sphere;
  sphere_ptr->set_center(15, 10, 20);
  sphere_ptr->set_radius(10.0);
  sphere_ptr->set_color(1,0,0);
//  sphere_ptr->set_material(Matte);
  add_object(sphere_ptr);

  Sphere* sphere_ptr2 = new Sphere;
  sphere_ptr2->set_center(16, 40, 30);
  sphere_ptr2->set_radius(30.0);
  sphere_ptr2->set_color(.5,0,0);
//  sphere_ptr2->set_material(Matte);
  add_object(sphere_ptr2);

//add plane
  Plane* plane_ptr = new Plane(Point3D(0,-20,20), Normal(15,5,-5));
  plane_ptr->set_color(0,0,1);
//  plane_ptr->set_material(Matte);
  add_object(plane_ptr);

  //add triangle
    Triangle* triangle_ptr = new Triangle(Point3D(-30,0,20), Point3D(0,0,20), Point3D(0,40,40));
    triangle_ptr->set_color(1,1,1);
//    triangle_ptr->set_material(Matte);
    add_object(triangle_ptr);
}

void
World::add_object(GeometricObject* object_ptr){
  objects.push_back(object_ptr);
}

void
World::set_camera(Camera* camera){
  camera_ptr = camera;
}


  ShadeRec
  World::hit_bare_bones_objects(const Ray& ray){
    ShadeRec sr(*this);
    double  t;
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
  //      sr.material_ptr = objects[j]->get_material();
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
      cout << "Color: " << pixel_color.r << pixel_color.g << pixel_color.b << endl;
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
      cout << "Color: " << pixel_color.r << pixel_color.g << pixel_color.b << endl;
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
    int idx = (column * vp.hres) + row;
    pixels[idx] = pixel_color;
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
