#ifndef __TRANSPARENT__
#define __TRANSPARENT__

#include "Phong.h"
#include "PerfectSpecular.h"
#include "PerfectTransmitter.h"


class Transparent: public Phong {
	public:

    		Transparent(void);
/*
    		Transparent(const Transparent& Transparent);

    		virtual Transparent*
    		clone(void)const = 0;

    		Transparent&
    		operator= (const Transparent& rhs);
*/
    		virtual
    		~Transparent(void);

    		virtual RGBColor
    		shade(ShadeRec& sr);


        void
        set_kt(float k);
        void
        set_ior(float i);
        void
        set_kr(const float k);
        void
        set_cr(const RGBColor& c);
        void
        set_cr(const float r, const float g, const float b);
        void
        set_cr(const float c);


	private:

		PerfectSpecular* 	reflective_brdf;
		PerfectTransmitter* specular_btdf;
};

#endif


inline void
Transparent::set_kt(float k) {
	specular_btdf->set_kt(k);
}

inline void
Transparent::set_ior(float i) {
	specular_btdf->set_ior(i);
}

// -------------------------------------------------------------- set_kr

inline void
Transparent::set_kr(const float k) {
  reflective_brdf->set_kr(k);
}


// -------------------------------------------------------------- set_cr

inline void
Transparent::set_cr(const RGBColor& c) {
  reflective_brdf->set_cr(c);
}


// ---------------------------------------------------------------- set_cr

inline void
Transparent::set_cr(const float r, const float g, const float b) {
  reflective_brdf->set_cr(r,g,b);
}


// ---------------------------------------------------------------- set_cr

inline void
Transparent::set_cr(const float c) {
  reflective_brdf->set_cr(c);
}
