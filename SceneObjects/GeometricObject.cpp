#include "Constants.h"
#include "Material.h"
#include "GeometricObject.h"


  GeometricObject::GeometricObject(void)
  : color(black)
  {}

  GeometricObject::GeometricObject(const GeometricObject& object)
  : color(object.color)
  {}

  GeometricObject::~GeometricObject(void);
  {}

  void
  GeometricObject::add_object(GeometricObject* object_ptr);
  {}
