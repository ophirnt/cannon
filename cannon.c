#import "stdio.h"
#import "math.h"
#import "time.h" //For calculating elapsed time 

typedef int bool;
#define true 1 
#define false 0


/* System constants & Debug miscellania */

#define SCALE_FACTOR 0.001
#define CIRC_SCALE_FACTOR 0.005
#define DEBUG false


/* Debug function */

//void show(const char *format, ...){
//	if(DEBUG) { printf(*format, ...); }
//}

/*  */

/** Main structs & functions **/


/* Defining the Fortress's struct and functions */
struct Circle {

	double x_0, y_0, radius;

} fortress;


// Returns wether or not the point (x,y) belongs to the circle.
bool belongsTo(double *x, double *y){

	return (*x - fortress.x_0)*(*x - fortress.x_0) + (*y - fortress.y_0)*(*y - fortress.y_0) <= fortress.radius*fortress.radius;  

}


/*	*/

/* Defining the Cannon's struct and functions */

struct LineOfSight {

	double x_0, y_0, angle, spread;

} cannon;

// Given a vector defined by x and y, returns its angle in relation to the x axis
double getAngle(double x, double y){
	
	double angle;
	angle = acos( ( x/( pow( x * x + y * y,0.5) ) ) );

	if(x < 0 && y < 0) { return (2*(M_PI - angle) + angle); } //Third quad.
	else if(x > 0 && y < 0) { return (2*M_PI - angle); } //Fourth quad.
	else { return angle; } //Defaults

}


// Determines if the point is within the area of sight of the cannon, or not
bool isHit(double *x, double *y){
	
	double vector_angle = getAngle( (*x) - cannon.x_0, (*y) - cannon.y_0);
	double hspread = cannon.spread/2; // stores half the spread value for performance reasons

	return (vector_angle >= cannon.angle - hspread && vector_angle <= cannon.angle + hspread);
}


/*  */

/* Main iteration */

struct Iteration {

	double x_i, y_i, x_begin, y_begin, x_end, y_end;
	double length, area_grid, total_area;

} iterate;


// Iterates over a circunscribed square in relation to the fortress's circle

void scan(){ 

	iterate.length = 2 * fortress.radius * SCALE_FACTOR;
	iterate.area_grid = iterate.length * iterate.length;
	iterate.total_area = 0.0;

	iterate.x_begin = fortress.x_0 - fortress.radius;
	iterate.x_end = fortress.x_0 + fortress.radius;
	iterate.y_end = fortress.y_0 - fortress.radius;
	iterate.y_i = fortress.y_0 + fortress.radius;

	while (iterate.y_i >= iterate.y_end){

		iterate.x_i = iterate.x_begin;

		while (iterate.x_i <= iterate.x_end){

			if(DEBUG) { printf("y: %lf x: %lf", iterate.y_i, iterate.x_i); }

			if( belongsTo( &(iterate.x_i), &(iterate.y_i) ) && isHit ( &(iterate.x_i), &(iterate.y_i) ) ) {
				iterate.total_area += iterate.area_grid;
				if(DEBUG) { printf("Total area so far: %lf", iterate.total_area); }
			}

			iterate.x_i += iterate.length;

		}
		iterate.y_i -= iterate.length;
	}
	
	printf("%.1lf\n", iterate.total_area);

}


/*
 // Iterates over a circle (i.e. the fortress itself)
 
 struct IterateCircle{

	double total_area, dangle, dradius, area_grid;
	double angle;

} itcirc;


double getx(){ return (fortress.x_0 + fortress.radius * cos(itcirc.angle)); }

double gety() { return (fortress.y_0 + fortress.radius * sin(itcirc.angle)); }

void scan_circle(){

	itcirc.dangle = 5*CIRC_SCALE_FACTOR;
	itcirc.dradius = fortress.radius * CIRC_SCALE_FACTOR;
	itcirc.area_grid = itcirc.dradius * itcirc.dangle * fortress.radius;
	itcirc.total_area = 0;

	
	while(fortress.radius > 0){
		
		while(itcirc.angle < 2*M_PI){
		
			if(isHit(getx(), gety()) { itcirc.total_area += itcirc.area_grid; }
			
			itcirc.angle += itcirc.dangle;

		}

		fortress.radius -= itcirc.dradius;
		itcirc.angle = 0;
		itcirc.area_grid = itcirc.dradius * itcirc.dangle * fortress.radius;

	}

	printf("%.1lf\n", itcirc.total_area);

		
}

*/





/*  */



/* I/o Voodoo */


bool getInput() {
scanf("%lf%lf%lf", &fortress.x_0, &fortress.y_0, &fortress.radius);
if(fortress.x_0 == 0 && fortress.y_0 == 0 && fortress.radius == 0) { return false; }
scanf("%lf%lf%lf%lf", &cannon.x_0, &cannon.y_0, &cannon.angle, &cannon.spread);
cannon.angle = cannon.angle * 2*M_PI/360;
cannon.spread = cannon.spread * 2*M_PI/360;
return true;
}

/* */




int main(){

	while(getInput()){

//	if (DEBUG) { printf("%lf %lf %lf \n %lf %lf %lf %lf", fortress.x_0, fortress.y_0, fortress.radius, cannon.x_0, cannon.y_0, cannon.angle, cannon.spread); }

	scan();	
	}

	return 0;

}
