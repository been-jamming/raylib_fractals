typedef struct complex_vec2 complex_vec2;

struct complex_vec2{
	complex double x;
	complex double y;
};

typedef struct mobius mobius;

struct mobius{
	complex double a;
	complex double b;
	complex double c;
	complex double d;
};

mobius compose_mobius(mobius x, mobius y);
complex_vec2 apply_mobius_vec(mobius T, complex_vec2 v);
complex double apply_mobius(mobius T, complex double z);
complex double mobius_determinant(mobius T);
static complex double square_root(complex double z);
mobius normalize_mobius(mobius T);
mobius mobius_inverse(mobius T);
complex double mobius_trace(mobius T);
complex_vec2 mobius_fixed(mobius T);
void mobius_circle_image(mobius T, complex double P, double P_rad, complex double *Q, double *Q_rad);
mobius mobius_circle_pair(complex double p, double r, complex double q, double s, complex double u, complex double v);

