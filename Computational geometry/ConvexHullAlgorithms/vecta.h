#ifndef VECTA_H
#define VECTA_H
#include <cmath>
#include <utility>

#ifdef GSQR
#undef GSQR
#endif
#define GSQR(x) ((x)*(x))

namespace vecta  {
	const double PI = 3.14159265358979;

	typedef double Number;

	template <typename N = Number>
	class vec2d  {
	private:
		void cp(N xx, N yy)  { x = xx;  y = yy; }
	public:
		N x, y;
		vec2d(const N x = 0, const N y = 0)  { cp(x, y); }
		template <class aN>
		vec2d(const vec2d<aN>& q)  { cp(q.x, q.y); }
		template <class aN>
		vec2d<N>& operator= (const vec2d<aN>& q)  { cp(q.x, q.y);  return *this; }
		template <class aN>
		vec2d<N>& operator+= (const vec2d<aN>& q)  { x += q.x;  y += q.y;  return *this; }
		template <class aN>
		vec2d<N>& operator-= (const vec2d<aN>& q)  { x -= q.x;  y -= q.y;  return *this; }
		template <class aN>
		vec2d<N>& operator*= (const aN c)  { x *= c;  y *= c;  return *this; }
		template <class aN>
		vec2d<N>& operator/= (const aN c)  { x /= c;  y /= c;  return *this; }
		template <class aN>
		vec2d<N>& operator&= (const aN a)  { return *this = cos(a)**this + sin(a)*~*this; }
		template <class aN>
		vec2d<N>& operator&= (const vec2d<aN>& q)  {
			N t = x*q.x - y*q.y;
			y = x*q.y + y*q.x;
			x = t;
			return *this;
		}
		template <class aN>
		vec2d<N>& operator/= (const vec2d<aN>& q)  {
			Number t = GSQR(q.x) + GSQR(q.y), xx = q.x / t, yy = q.y / t;
			t = x*xx + y*yy;
			y = y*xx - x*yy;
			x = t;
			return *this;
		}
	};

	//-----------------------------------------------------------------------

	template <typename N> class vec3d;

	class quatrn  {
	private:
		void cp(Number rr, Number xx, Number yy, Number zz)  { r = rr;  x = xx;  y = yy;  z = zz; }
	public:
		Number r, x, y, z;
		quatrn(const Number r = 0, const Number x = 0, const Number y = 0, const Number z = 0)  { cp(r, x, y, z); }
		quatrn(const quatrn& q)  { cp(q.r, q.x, q.y, q.z); }
		quatrn& operator= (const quatrn& q)  { cp(q.r, q.x, q.y, q.z);  return *this; }
		quatrn& operator*= (const quatrn& q)  {
			cp(q.r*r - q.x*x - q.y*y - q.z*z,
				q.r*x + q.x*r + q.y*z - q.z*y,
				q.r*y + q.y*r + q.z*x - q.x*z,
				q.r*z + q.z*r + q.x*y - q.y*x);
			return *this;
		}
		template <class aN>
		quatrn(const Number a, const vec3d<aN>& p)  {
			Number d = len(p), s = sin(a / 2) / d;
			cp(cos(a / 2), s*p.x, s*p.y, s*p.z);
		}
	};

	template <typename N = Number>
	class vec3d  {
	private:
		void cp(N xx, N yy, N zz)  { x = xx;  y = yy;  z = zz; }
	public:
		N x, y, z;
		vec3d(const N x = 0, const N y = 0, const N z = 0)  { cp(x, y, z); }
		template <class aN>
		vec3d(const vec3d<aN>& q)  { cp(q.x, q.y, q.z); }
		template <class aN>
		vec3d<N>& operator= (const vec3d<aN>& q)  { cp(q.x, q.y, q.z);  return *this; }
		template <class aN>
		vec3d<N>& operator+= (const vec3d<aN>& q)  { x += q.x;  y += q.y;  z += q.z;  return *this; }
		template <class aN>
		vec3d<N>& operator-= (const vec3d<aN>& q)  { x -= q.x;  y -= q.y;  z -= q.z;  return *this; }
		template <class aN>
		vec3d<N>& operator*= (const aN c)  { x *= c;  y *= c;  z *= c;  return *this; }
		template <class aN>
		vec3d<N>& operator/= (const aN c)  { x /= c;  y /= c;  z /= c;  return *this; }
		template <class aN>
		vec3d<N>& operator^= (const vec3d<aN>& q)  { cp(y*q.z - q.y*z, z*q.x - q.z*x, x*q.y - q.x*y);  return *this; }
		vec3d<N>& operator&= (const quatrn& q)  {
			Number p1 = (q.r - q.z)*(q.r + q.z), p2 = (q.x - q.y)*(q.x + q.y),
				ab = q.r*q.x, ac = q.r*q.y, ad = q.r*q.z,
				bc = q.x*q.y, bd = q.x*q.z, cd = q.y*q.z,
				xx = x, yy = y;
			x = (p1 + p2)  *xx + 2 * (bc - ad)*yy + 2 * (bd + ac)         *z,
				y = 2 * (bc + ad)*xx + (p1 - p2)  *yy + 2 * (cd - ab)         *z;
			z = 2 * (bd - ac)*xx + 2 * (cd + ab)*yy + (4 * GSQR(q.r) - 2 * p1 - 1)*z;
			return *this;
		}
		template <class aN>
		vec3d<N>& operator&= (const std::pair< aN, vec3d<aN> >& p)  {
			return *this &= quatrn(p.first, p.second);
		}
	};
		

	// ------------------------ declarations

	template <typename N>
	Number len(const vec2d<N>& p);

	template <typename N>
	Number dir(const vec2d<N>& p);

	template <typename N>
	vec2d<> unit(const vec2d<N>& p);

	template <typename N>
	vec2d<N> operator- (const vec2d<N>& p);

	template <typename N>
	vec2d<N> operator! (const vec2d<N>& p);

	template <typename N>
	vec2d<N> operator~ (const vec2d<N>& p);

	template <typename N1, typename N2>
	vec2d<N1> operator+ (const vec2d<N1>& p, const vec2d<N2>& q);

	template <typename N1, typename N2>
	vec2d<N1> operator- (const vec2d<N1>& p, const vec2d<N2>& q);

	template <typename N1, typename N2>
	vec2d<N2> operator* (const N1 c, const vec2d<N2>& q);

	template <typename N1, typename N2>
	vec2d<N1> operator* (const vec2d<N1>& p, const N2 c);

	template <typename N1, typename N2>
	vec2d<N1> operator/ (const vec2d<N1>& p, const N2 c);

	template <typename N1, typename N2>
	N1 operator* (const vec2d<N1>& p, const vec2d<N2>& q);

	template <typename N1, typename N2>
	N1 operator^ (const vec2d<N1>& p, const vec2d<N2>& q);

	template <typename N>
	N norm(const vec2d<N>& p);

	template <typename N1, typename N2>
	bool operator== (const vec2d<N1>& p, const vec2d<N2>& q);

	template <typename N1, typename N2>
	bool operator!= (const vec2d<N1>& p, const vec2d<N2>& q);

	template <typename N1, typename N2>
	bool operator< (const vec2d<N1>& p, const vec2d<N2>& q);

	template <typename N1, typename N2>
	bool operator<= (const vec2d<N1>& p, const vec2d<N2>& q);

	template <typename N1, typename N2>
	bool operator|| (const vec2d<N1>& p, const vec2d<N2>& q);

	template <typename N1, typename N2>
	bool operator>= (const vec2d<N1>& p, const vec2d<N2>& q);

	template <typename N1, typename N2>
	bool operator> (const vec2d<N1>& p, const vec2d<N2>& q);

	template <typename N1, typename N2>
	Number angle(const vec2d<N1>& u, const vec2d<N2>& v);

	template <typename N1, typename N2>
	vec2d<N1> operator& (const vec2d<N1>& p, const N2 & a);

	template <typename N1, typename N2>
	vec2d<N1> operator& (const vec2d<N1>& p, const vec2d<N2>& q);

	template <typename N1, typename N2>
	vec2d<N1> operator/ (const vec2d<N1>& p, const vec2d<N2>& q);

	vec2d<> polar(const Number r, const Number a);

	//----------------------------

	quatrn operator* (const quatrn& b, const quatrn& a);

	//----------------------------

	template <typename N>
	vec3d<N> operator- (const vec3d<N>& p);

	template <typename N1, typename N2>
	vec3d<N1> operator+ (const vec3d<N1>& p, const vec3d<N2>& q);

	template <typename N1, typename N2>
	vec3d<N1> operator- (const vec3d<N1>& p, const vec3d<N2>& q);

	template <typename N1, typename N2>
	vec3d<N2> operator* (const N1 c, const vec3d<N2>& q);

	template <typename N1, typename N2>
	vec3d<N1> operator* (const vec3d<N1>& p, const N2 c);

	template <typename N1, typename N2>
	vec3d<N1> operator/ (const vec3d<N1>& p, const N2 c);

	template <typename N1, typename N2>
	N1 operator* (const vec3d<N1>& p, const vec3d<N2>& q);

	template <typename N1, typename N2>
	vec3d<N1> operator^ (const vec3d<N1>& p, const vec3d<N2>& q);

	template <typename N>
	std::pair < vec3d<N>, vec3d<N> > operator~ (const vec3d<N>& p);

	template <typename N>
	N norm(const vec3d<N>& p);

	template <typename N>
	Number len(const vec3d<N>& p);

	template <typename N>
	vec3d<> unit(const vec3d<N>& p);

	template <typename N1, typename N2>
	bool operator== (const vec3d<N1>& p, const vec3d<N2>& q);

	template <typename N1, typename N2>
	bool operator!= (const vec3d<N1>& p, const vec3d<N2>& q);

	template <typename N1, typename N2>
	bool operator|| (const vec3d<N1>& p, const vec3d<N2>& q);

	template <typename N1, typename N2>
	Number angle(const vec3d<N1>& u, const vec3d<N2>& v);

	template <typename N>
	vec3d<N> operator& (const vec3d<N>& a, const quatrn& q);

	template <typename N1, typename N2>
	vec3d<N1> operator& (const vec3d<N1>& u, const std::pair< N2, vec3d<N2> >& p);

	template <typename N1, typename N2>
	std::pair<Number, quatrn> operator/ (const vec3d<N1>& u, const vec3d<N2>& v);
}
#undef GSQR
#endif
