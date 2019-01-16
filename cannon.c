#import "stdio.h"
#import "math.h"
#import "time.h" //For calculating elapsed time 

typedef int bool;
#define true 1 
#define false 0


/* System constants & Debug miscellania */

#define SCALE_FACTOR 0.001
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
bool belongsTo(double x, double y, double x_0, double y_0, double radius){

	return (x - x_0)*(x - x_0) + (y - y_0)*(y - y_0) <= radius*radius;  

}

/* 		*/

/* Defining the Cannon's struct and functions */

struct LineOfSight {

	double x_0, y_0, angle, spread;

} cannon;

// Given a vector defined by x and y, returns its angle in relation to the x axis
double getAngle(double x, double y){
	
	double angle;
	angle = acos( x/( pow( (x*x + y*y),0.5) ) );

	if(x < 0 && y < 0) { return (2*(M_PI - angle) + angle); } //Third quad.
	else if(x > 0 && y < 0) { return (2*M_PI - angle); } //Fourth quad.
	else { return angle; } //Defaults

}


// Determines if the point is within the area of sight of the cannon, or not
bool isHit(double x, double y, double x_0, double y_0, double angle, double spread){
	
	double vector_angle = getAngle(x - x_0, y - y_0);
	double hspread = spread/2; // stores half the spread value for performance reasons

	return (vector_angle >= angle - hspread && vector_angle <= angle + hspread);
}


/*  */

/* Main iteration */

struct Iteration {

	double x_i, y_i, x_begin, y_begin, x_end, y_end;
	double length, area_grid, total_area;



} iterate;

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

			if( belongsTo(iterate.x_i, iterate.y_i, fortress.x_0, fortress.y_0, fortress.radius) && isHit (iterate.x_i, iterate.y_i, cannon.x_0, cannon.y_0, cannon.angle, cannon.spread) ) {
				iterate.total_area += iterate.area_grid;
				if(DEBUG) { printf("Total area so far: %lf", iterate.total_area); }
			}

			iterate.x_i += iterate.length;

		}
		iterate.y_i -= iterate.length;
	}
	
	printf("%.1lf", iterate.total_area);

}

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
