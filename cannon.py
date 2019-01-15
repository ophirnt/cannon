import math
import timeit

start = timeit.default_timer()


#Constant parameters for the modelling

SCALE_FACTOR = 0.01 # Scale factor of the grid that is calculated automatically by the algorithm

OVERRIDE = False # Forces the script to use a custom grid size, given by the value LENGTH
LENGTH = 0.01 # length of each square of the circle's grid

CAN_BE_INSIDE_FORTRESS = False # Determines whether the script should stop automatically if the cannon is placed inside the fortress 

DEBUG = False # If set to true, the software will be verbose. Partners with the show function, written below


# INPUT DATA HERE

X_CANNON = 8 #Cannon's X coordinate
Y_CANNON = 4 #Cannon's Y coordinate
ANGLE_CANNON = math.pi/4 # Angle the cannon points towards, in radians. Use only angles between 0 and 2 pi
SPREAD_CANNON = math.pi/4 # The protons' angle of spread, in radians. Use only angles between 0 and 2 pi
#-
X_FORTRESS = 4 # Circle's center X coordinate
Y_FORTRESS = 4 # Circle's center Y coordinate
RADIUS_FORTRESS = 3 # Circle's radius

#-----------------------------------------------------------------------------------------------------------------

# FUNCTIONS & CLASSES

# Debug function. Prints whatever information is needed if DEBUG is set to True
def show(*objects):
    if(DEBUG): print(*objects)

# Determines the vertices of the rectangle around the circle, in which the script will scan for points

def getDomain(x_0, y_0, radius):

    return (x_0 - radius, x_0 + radius, y_0 - radius, y_0 + radius)


# Defines the circle. In other words, the fortress from the problem in question.

class Circle:

    def __init__(self, x_0, y_0, radius):
        self.x_0 = x_0
        self.y_0 = y_0
        self.radius = radius

    def belongsTo(self, x, y): #Returns wether or not the point (x,y) belongs to the circle.
        return ((x - self.x_0)**2 + (y - self.y_0)**2 <= self.radius**2) 

# Defines the cannon and its area of fire

class LineOfSight: # References to the fact that the protons trajectory is similar to optical phenomena

    def __init__(self, x_0, y_0, angle, spread):

        self.x_0 = x_0
        self.y_0 = y_0
        self.angle = angle
        self.spread = spread
        #
        self.max_angle = angle + spread/2
        self.min_angle = angle - spread/2

    def getAngle(self, x, y): # given a vector defined by x and y, returns its angle

        angle = math.acos(x/((x**2 + y**2)**0.5))

        if(x > 0 and y > 0): return angle # First quad.
        if(x < 0 and y > 0): return angle # Second quad.
        if(x < 0 and y < 0): return (2*(math.pi - angle) + angle) # Third quad.
        if(x > 0 and y < 0): return (2*math.pi - angle) # Fourth quad.


    def isHit(self, x, y): # Determines if the point is within the area of sight of the cannon, or not

        self.line_angle = self.getAngle(x - self.x_0, y - self.y_0)

        return (self.line_angle >= self.min_angle and self.line_angle <= self.max_angle)


#-----------------------------------------------------------------------------------------------------------------




# Initiating the cannon and the fortress's objects

fortress = Circle(X_FORTRESS, Y_FORTRESS, RADIUS_FORTRESS)
cannon = LineOfSight(X_CANNON, Y_CANNON, ANGLE_CANNON, SPREAD_CANNON)
#
x_begin, x_end, y_end, y_iterate = getDomain(fortress.x_0, fortress.y_0, fortress.radius)

if(OVERRIDE):
    length = LENGTH
    area_grid = LENGTH**2
else:
    length = 2 * fortress.radius * SCALE_FACTOR
    area_grid = length**2



show(x_begin, x_end, y_end, y_iterate)

total_area = 0


if(not fortress.belongsTo(cannon.x_0, cannon.y_0) or CAN_BE_INSIDE_FORTRESS):

    #total_area = 0

    while(y_iterate >= y_end):

        x_iterate = x_begin

        while(x_iterate <= x_end):

            show("y:",y_iterate,"x:",x_iterate)
        
            if(fortress.belongsTo(x_iterate, y_iterate) and cannon.isHit(x_iterate, y_iterate)):
                total_area += area_grid
                show("Total area so far:", total_area)
        
            x_iterate += length
    
        y_iterate -= length

    print( "The area devastated by the proton cannon is equal to: ", total_area,", or approximately: ", float( format( total_area, '.1f' ) ) )

else:

    print("The area cannot be calculated as the cannon is inside the fortress, and the script was setup to halt in this scenario")





stop = timeit.default_timer()

print("Time: ", stop - start)


