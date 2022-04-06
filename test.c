#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <raylib.h>
#include "mobius.h"

#define NUM_GENS 2

static mobius gens[NUM_GENS];
static mobius gen_inverses[NUM_GENS];
static complex double gen_centers0[NUM_GENS];
static complex double gen_centers1[NUM_GENS];
static double gen_radii0[NUM_GENS];
static double gen_radii1[NUM_GENS];
static complex double gen_params0[NUM_GENS];
static complex double gen_params1[NUM_GENS];
static Color gen_colors[NUM_GENS] = {RED, BLUE};
static Color gen_inverse_colors[NUM_GENS] = {GREEN, ORANGE};
static int display;
static int screen_width;
static int screen_height;

static void initialize_gens(void){
	int i;

	for(i = 0; i < NUM_GENS; i++){
		gens[i] = mobius_circle_pair(gen_centers0[i], gen_radii0[i], gen_centers1[i], gen_radii1[i], gen_params0[i], gen_params1[i]);
		gen_inverses[i] = mobius_inverse(gens[i]);
	}
}

static void initialize(void){
	complex double P;
	double r;
	complex double Q;
	double s;

	gen_centers0[0] = -1.0;
	gen_radii0[0] = 1.0;
	gen_centers1[0] = 1.0;
	gen_radii1[0] = 1.0;
	gen_params0[0] = 0;
	gen_params1[0] = I;
	gen_centers0[1] = -I;
	gen_radii0[1] = sqrt(2.0) - 1.0;
	gen_centers1[1] = I;
	gen_radii1[1] = sqrt(2.0) - 1.0;
	gen_params0[1] = 0;
	gen_params1[1] = 1;
	initialize_gens();

	screen_width = 480;
	screen_height = 600;

	InitWindow(screen_width, screen_height, "Fractal test");
	display = GetCurrentMonitor();
	screen_width = GetMonitorWidth(display);
	screen_height = GetMonitorHeight(display);
	SetWindowSize(screen_width, screen_height);
	ToggleFullscreen();
}

static Vector2 get_complex_pos(complex double x){
	Vector2 out;

	out.x = (creal(x) + 2.0)/4.0*screen_height + (screen_width - screen_height)/2.0;
	out.y = (2.0 - cimag(x))/4.0*screen_height;

	return out;
}

static void draw_complex_circle(complex double center, double radius, Color c){
	Vector2 screen_center;

	screen_center = get_complex_pos(center);
	DrawCircle(round(screen_center.x), round(screen_center.y), radius*screen_height/4.0, c);
}

static void draw_fractal_recursive(int depth, complex double center, double radius, mobius current_word, int last_gen, Color c){
	int i;
	mobius next_word;
	complex double new_center;
	double new_radius;

	if(depth <= 0){
		mobius_circle_image(current_word, center, radius, &new_center, &new_radius);
		draw_complex_circle(new_center, new_radius, c);
		return;
	}

	for(i = 0; i < NUM_GENS; i++){
		if(last_gen == -i - 1){
			continue;
		}
		next_word = compose_mobius(gens[i], current_word);
		draw_fractal_recursive(depth - 1, center, radius, next_word, i + 1, c);
	}

	for(i = 0; i < NUM_GENS; i++){
		if(last_gen == i + 1){
			continue;
		}
		next_word = compose_mobius(gen_inverses[i], current_word);
		draw_fractal_recursive(depth - 1, center, radius, next_word, -i - 1, c);
	}
}

static void draw_fractal(int depth){
	int i;

	for(i = 0; i < NUM_GENS; i++){
		draw_fractal_recursive(depth - 1, gen_centers0[i], gen_radii0[i], (mobius) {1, 0, 0, 1}, -i - 1, gen_colors[i]);
	}

	for(i = 0; i < NUM_GENS; i++){
		draw_fractal_recursive(depth - 1, gen_centers1[i], gen_radii1[i], (mobius) {1, 0, 0, 1}, i + 1, gen_inverse_colors[i]);
	}
}

int main(int argc, char **argv){
	int i;

	initialize();
	while(!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(BLACK);
		for(i = 1; i < 10; i++){
			draw_fractal(i);
		}
		EndDrawing();
	}

	CloseWindow();

	return 0;
}

