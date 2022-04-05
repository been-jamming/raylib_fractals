#include <complex.h>
#include <math.h>
#include "mobius.h"

mobius compose_mobius(mobius x, mobius y){
	complex double new_a, new_b, new_c, new_d;

	new_a = x.a*y.a + x.b*y.c;
	new_b = x.a*y.b + x.b*y.d;
	new_c = x.c*y.a + x.d*y.c;
	new_d = x.c*y.b + x.d*y.d;

	return (mobius) {new_a, new_b, new_c, new_d};
}

complex_vec2 apply_mobius_vec(mobius T, complex_vec2 v){
	complex double new_x, new_y;

	new_x = T.a*v.x + T.b*v.y;
	new_y = T.c*v.x + T.d*v.y;

	return (complex_vec2) {new_x, new_y};
}

complex double apply_mobius(mobius T, complex double z){
	return (T.a*z + T.b)/(T.c*z + T.d);
}

complex double mobius_determinant(mobius T){
	return T.a*T.d - T.b*T.c;
}

static complex double square_root(complex double z){
	double r;

	r = cabs(z);
	return sqrt(r)*(z + r)/cabs(z + r);
}

mobius normalize_mobius(mobius T){
	complex double det;
	complex double det_root;

	det = mobius_determinant(T);
	det_root = square_root(det);
	return (mobius) {T.a/det_root, T.b/det_root, T.c/det_root, T.d/det_root};
}

mobius mobius_inverse(mobius T){
	return (mobius) {T.d, -T.b, -T.c, T.a};
}

complex double mobius_trace(mobius T){
	return (T.a + T.d)/square_root(mobius_determinant(T));
}

complex_vec2 mobius_fixed(mobius T){
	complex double discr;
	complex double root;
	complex double fix0;
	complex double fix1;

	discr = (T.d - T.a)*(T.d - T.a) - 4*T.b*T.c;
	root = square_root(discr);
	fix0 = ((T.a - T.d) + root)/(2*T.c);
	fix1 = ((T.a - T.d) - root)/(2*T.c);

	return (complex_vec2) {fix0, fix1};
}

void mobius_circle_image(mobius T, complex double P, double P_rad, complex double *Q, double *Q_rad){
	complex double z;

	z = P - P_rad*P_rad/conj(T.d/T.c + P);
	*Q = apply_mobius(T, z);
	*Q_rad = cabs(*Q - apply_mobius(T, P + P_rad));
}

mobius mobius_circle_pair(complex double p, double r, complex double q, double s, complex double u, complex double v){
	complex double a, b, c, d;

	a = s*u + q*conj(v);
	b = -s*u*p + s*r*v - q*p*conj(v) + r*q*conj(u);
	c = conj(v);
	d = -p*conj(v) + r*conj(u);

	return (mobius) {a, b, c, d};
}

