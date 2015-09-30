/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/******* IMPORTANT ***********
 * The mouse on the _left_ shall be entitled mouse A
 */

#include <project.h>
#include <math.h>
#include <stdlib.h>

#include <navigation.h>
#include <compass.h>
#include <motor.h>

//These are in compass.c
extern int16 compass_heading;
extern double SinDeg[];
extern double CosDeg[];

//this is in mouse_a.c
extern volatile int32 loc_x_a;
extern volatile int32 loc_y_a;
extern volatile uint8 data_ready_a;
//this is in mouse_b.c
extern volatile int32 loc_x_b;
extern volatile int32 loc_y_b;
extern volatile uint8 data_ready_b;

//We store the navigation info here
struct Position location;
//The straight line distance the mouse has gone. This is continually incremented by loc_y_...
//Reset it to 0 for measurement purposes.
int32 delta_y_distance; 


struct Position calculate_dposition(double dxl, double dyl, double dxr, double dyr);

//9.4cm = 94mm = 94*4 counts/mm = 376.0 counts
#define SEPARATION 400

double signum(double x){
    if (x >= 0){
        return 1.0; 
    } else {
        return -1.0;
    }
}

void update_position(){
    if (!isRotating()){//We rotate on the spot so y should not change
        location.x += (int32) (CosDeg[compass_heading]*((double) loc_y_a)); 
        location.y += (int32) (SinDeg[compass_heading]*((double) loc_y_a));
    }
    location.angle = compass_heading;
    delta_y_distance += loc_y_a;
    loc_y_a = 0;
}

void reset_delta_y_distance(){
    delta_y_distance = 0;
}

void reset_navigation(){
    loc_x_a = 0;
    loc_y_a = 0;
    data_ready_a = 0;
    loc_x_b = 0;
    loc_y_b = 0;
    data_ready_b = 0;
    
    delta_y_distance = 0;
    
    location.x = 0;
    location.y = 0;
    location.angle = 0;
}

void start_navigation(){
    reset_navigation();
}

/* [] END OF FILE */