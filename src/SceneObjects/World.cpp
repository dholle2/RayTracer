
#include <fstream>    //for file saving
#include "../Utilities/Constants.h"

#include "../Utilities/Vector3D.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Normal.h"

#include "../Utilities/Ray.h"
#include "World.h"
#include "Sphere.h"
#include "Plane.h"
#include "../Misc./Camera.h"
#include "../Misc./MultipleObjects.h"

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
  vp.set_hres(200);
  vp.set_vres(200);
  vp.set_s(1.0);
  vp.set_gamma(1.0);
  pixels.resize(vp.hres * vp.vres); //resize pixels array again

  background_color = black;
  tracer_ptr = new MultipleObjects(this);

  Sphere* sphere_ptr = new Sphere;
  sphere_ptr->set_center(0, -25, 0);
  sphere_ptr->set_radius(85.0);
  sphere_ptr->set_color(1,0,0);
  add_object(sphere_ptr);

  Plane* plane_ptr = new Plane(Point3D(0,0,0), Normal(0,1,1));
  plane_ptr->set_color(0,0,1);
  add_object(plane_ptr);
}

void
World::add_object(GeometricObject* object_ptr){
  objects.push_back(object_ptr);
}

  ShadeRec
  World::hit_bare_bones_objects(const Ray& ray){
    ShadeRec sr(*this);
    double  t;
    double  tmin = 10000.0; //kHugeValue
    double  num_objects = objects.size();

    for(int j = 0; j < num_objects; j++){
      if(objects[j]->hit(ray, t, sr) && (t < tmin)){
        sr.hit_an_object = true;
        tmin = t;
        sr.color = objects[j]->get_color();
      }
    }
    return sr;
  }

void
World::render_scene(void){
  RGBColor pixel_color;
  Ray ray;
  double zw = 100.0;
  double x,y;

//  open_window(vp.hres, vp.vres);  //what is this function

//populate the pixel array
  for(int r = 0; r < vp.vres; r++){ //vertical
    for(int c = 0; c <= vp.hres; c++){  //horizontal
      x = vp.s * (c - 0.5 * (vp.hres - 1.0));
      y = vp.s * (r - 0.5 * (vp.vres - 1.0));


      ray.o = Point3D(x, y, zw);
      pixel_color = tracer_ptr->trace_ray(ray);   //ray tracing!
      cout << pixel_color.r << pixel_color.g << pixel_color.b << endl;
      display_pixel(r, c, pixel_color);           //put pixel in list!
    }
  }//end fors



  cout << "all pixels printed" << endl;


//save image
  string fileName = "coolImage";
  save_image(fileName);
}

void
World::display_pixel(const int row,
                    const int column,
                    const RGBColor& pixel_color){


//    RGBColor tempColor;
    int idx = (column * vp.hres) + row;
//    tempColor.r = std::fmin(pixel_color.r, 1);
//    tempColor.g = std::fmin(pixel_color.g, 1);
//    tempColor.b = std::fmin(pixel_color.b, 1);

//    m_pixels[new_index] = tempColor;
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
