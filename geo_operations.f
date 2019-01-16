C FILE: GEO_OPERATIONS.F

C Resource intensive calculations written in FORTRAN
C For performance gains


       REAL FUNCTION ANGLE(X,Y)
 
C
C       given a vector defined by x and y, returns its 
C       angle according to the X axis
C

        REAL X,Y
Cf2py   intent(in) X,Y
Cf2py   intent(out) ANGLE

        ANGLE = ACOS(X/((X*X + Y*Y)**0.5))

        IF (X .LT. 0 .AND. Y .LT. 0) ANGLE = (2*(PI - ANGLE) + ANGLE)
        IF (X .GT. 0 .AND. Y .LT. 0) ANGLE = (2*PI + ANGLE)
        
        RETURN
        END

        LOGICAL FUNCTION BELONGSTOCIRCLE(X,Y,XC,YC,R)

C
C       Given a point (X,Y), determines if it is inside
C       the circle with center (XC,YC) and radius R
C
        REAL X,Y,XC,YC,R
Cf2py   intent(in) X,Y,XC,YC,R
Cf2py   intent(out) BELONGSTOCIRCLE
        BELONGSTOCIRCLE = (X - XC)*(X - XC) + (Y-YC)*(Y-YC) .LE. R*R

        RETURN
        END




C END FILE GEO_OPERATIONS.F
