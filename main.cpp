//deepakpatel
// this is a double ended queue implementation
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <ctype.h>
#include <time.h>
#include "myhearder.h"




// 1st function
//this function helps in inilization of some parameter for opengl porgram to run properly
void myinit() {
	// background
	glClearColor(BACKGROUND_R, BACKGROUND_G, BACKGROUND_B, BACKGROUND_A);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,SCREEN_X,0.0,SCREEN_Y);
// creates color of cube and outline color
	int i;
	for(i = 0; i < 15; i++) {
		queue[i].r = 0;
		queue[i].g = 0.25;
		queue[i].b = 0.75;
		queue[i].rl = 1;
		queue[i].gl = 0;
		queue[i].bl = 0;
	}
//Declaration of some elements
	float step = DIST/MAX;
	queue[0].x1 = OFFSET_X;
	queue[0].x2 = queue[0].x1+step;

	for(i = 1; i <= 15; i++) {
		queue[i].x1 = queue[i-1].x1+step;
		queue[i].x2 = queue[i].x1+step;
	}

}





// 2nd function
// this function creates a square for the element
void square(int x1, int y1, int x2, int y2) {
	glBegin(GL_POLYGON);
		glVertex2f(x1, y1);
		glVertex2f(x1, y2);
		glVertex2f(x2, y2);
		glVertex2f(x2, y1);
	glEnd();
}








// 3rd function
//func to draw outline to the box now its red in color
void drawOutline(int x1, int y1, int x2, int y2) {
	int temp;
	if(x1 < x2) {
		temp = x1;
		x1 = x2;
		x2 = temp;
	}
	if(y1 < y2) {
		temp = y1;
		y1 = y2;
		y2 = temp;
	}
	glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x1, y2);
		glVertex2f(x2, y2);
		glVertex2f(x2, y1);
	glEnd();
}







// 4th function
//func to draw string on the output screen and other info
void drawString(const char *str, double x=0, double y=0, double size=5.0) {
	glPushMatrix();
	glTranslatef(x,y,0);
	glScalef(size,size,4.0);
	glColor3f(1, 0, 0);
	int itemCt = 0;
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN,str[i]);
	}
	glPopMatrix();
}








// 5th function
// func to draw arrow of front and back end of the queue to show front and back end of the queue
void drawArrow(int x1, const char* s) {
	glBegin(GL_LINES);
		glVertex2f(x1, 3*SCREEN_Y/4);
		glVertex2f(x1, 3*SCREEN_Y/4-ARROW_LENGTH);
	glEnd();
	glBegin(GL_TRIANGLES);
		glVertex2f(x1, 3*SCREEN_Y/4-ARROW_LENGTH);
		glVertex2f(x1-ARROW_LENGTH/4, 3*SCREEN_Y/4-ARROW_LENGTH+ARROW_LENGTH/4);
		glVertex2f(x1+ARROW_LENGTH/4, 3*SCREEN_Y/4-ARROW_LENGTH+ARROW_LENGTH/4);
	glEnd();
	if(strcmp(s, "BACK"))
		drawString(s, x1-ARROW_LENGTH/3, 3*SCREEN_Y/4+ARROW_LENGTH/2, 1.0/(2*FONT_RATIO));
	else
		drawString(s, x1-ARROW_LENGTH/3, 3*SCREEN_Y/4+ARROW_LENGTH/4, 1.0/(2*FONT_RATIO));
}







// 6th function
// display func to redraw the screen every time its needed to be drawn on the screen
void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	strcpy(displayString, enter_str);
	strcat(displayString, blinking);
	strcpy(displayString1, "Enter where you want to add element:");
	strcat(displayString1, blinking);
	drawString(displayString1, 50, 430, 1.0/(FONT_RATIO));
	drawString(displayString, ENTER_POSITION_X, ENTER_POSITION_Y+30,1.0/(FONT_RATIO));

	for(int i = 0; i < b; i++) {
		 if(isback){
 			glColor3f(queue[i].r,queue[i].g,queue[i].b);
			square(queue[i].x1, SCREEN_Y/2, queue[i].x2, SCREEN_Y/2+YD);
			glColor3f(queue[i].rl,queue[i].gl,queue[i].bl);
		}
		 else{
 			glColor3f(queue[i].r,queue[i].g,queue[i].b);
		 	square(queue[f].x1, SCREEN_Y/2, queue[f].x1-differenc, SCREEN_Y/2+YD);
			square(queue[i].x1, SCREEN_Y/2, queue[i].x2, SCREEN_Y/2+YD);
			glColor3f(queue[i].rl,queue[i].gl,queue[i].bl);
	}
		 if(isback){
			drawOutline(queue[i].x1, SCREEN_Y/2, queue[i].x2, SCREEN_Y/2+YD);
		}
		 else{
			if(f == 0){
				enqORdq = fnot;
				break;
			}
			drawOutline(queue[f].x1, SCREEN_Y/2, queue[f].x1-differenc, SCREEN_Y/2+YD);
			drawOutline(queue[i].x1, SCREEN_Y/2, queue[i].x2, SCREEN_Y/2+YD);
		}
		if(queue[i].r != 1.0 || queue[i].b != 1.0 || queue[i].g != 1.0) {
			double ln = strlen(queue[i].num);
			double width = queue[i].x2-queue[i].x1;
			double step = width/(ln+1);
			double step_y = YD/4;
			drawString(queue[i].num, queue[i].x1+step, SCREEN_Y/2+step_y, 1.0/FONT_RATIO);
		}
	}
	if(isback){
	drawArrow(queue[f].x1, "FRONT");
	drawArrow(queue[b].x1+OFFSET_X/2, "BACK");
	}
	else{
	drawArrow(queue[f].x1-differenc, "FRONT");
	drawArrow(queue[b].x1, "BACK");
	}
	if(enqORdq == ENQUEUE)
		drawString("LAST OPERATION: ENQUEUE", OPERATION_POSITION_X, OPERATION_POSITION_Y+50, 1.0/(FONT_RATIO));
	if(enqORdq == fnot)
		drawString("LAST OPERATIOPN: NOT POSSIBLE", OPERATION_POSITION_X, OPERATION_POSITION_Y+50, 1.0/(FONT_RATIO));
	else if(enqORdq == DEQUEUE1)
		drawString("LAST OPERATION: DEQUEUE from front", OPERATION_POSITION_X, OPERATION_POSITION_Y+50, 1.0/(FONT_RATIO));
	else if(enqORdq == DEQUEUE2)
		drawString("LAST OPERATION: DEQUEUE from back", OPERATION_POSITION_X, OPERATION_POSITION_Y+50, 1.0/(FONT_RATIO));
	else
		drawString("LAST OPERATION: NO OPERATION YET", OPERATION_POSITION_X, OPERATION_POSITION_Y+50, 1.0/(FONT_RATIO));
		//message
	if(message == EMPTY) {
		drawString("QUEUE EMPTY!", OPERATION_POSITION_X+80, OPERATION_POSITION_Y, 1.0/(FONT_RATIO));
	}
	else if(message == FULL) {
		drawString("QUEUE FULL!", OPERATION_POSITION_X+80, OPERATION_POSITION_Y, 1.0/(FONT_RATIO));
	}
	//instructions
	drawString("Instructions:", OPERATION_POSITION_X-280, OPERATION_POSITION_Y+40, 1.0/(1.5*FONT_RATIO));
	drawString("and F or f to dequeue from back.", OPERATION_POSITION_X-280, OPERATION_POSITION_Y, 1.0/(2*FONT_RATIO));
	drawString("Press E or e for exit.", OPERATION_POSITION_X-280, OPERATION_POSITION_Y-20, 1.0/(2*FONT_RATIO));
	drawString("Press D or d to dequeue from front.", OPERATION_POSITION_X-280, OPERATION_POSITION_Y+20, 1.0/(2*FONT_RATIO));
	glFlush();
}






// 7th function
// func to add element to the double ended queue
void enqueue(char *s) {
	int len = strlen(s);
	int i;
	if(b < MAX) {
		len = strlen(s);
		for(i = 0; i < len-1 && s[i] == '0'; i++);
		strcpy(queue[b].num, s+i);
		b++;
		enqORdq = ENQUEUE;	// indicates what the last operation was.
		message = NO_MESSAGE;
	}
	if(b == MAX)
		message = FULL;
}






// 8th function
// func to delete element from back end of the queue
void backDequeue(void) {
	if(f >= MAX || f >= b) {
		message = EMPTY;
		return;
	}

	// set all as background color
	queue[f].r = BACKGROUND_R;
	queue[f].g = BACKGROUND_G;
	queue[f].b = BACKGROUND_B;

	// outline colors. set all as same as background color.
	queue[f].rl = BACKGROUND_R;
	queue[f].gl = BACKGROUND_G;
	queue[f].bl = BACKGROUND_B;

	f++;
	enqORdq = DEQUEUE1;	// indicates what the last operation was dequeue from back

	if(f >= b) {
		message = EMPTY;
	}
	if(b >= MAX)
		message = FULL;
}









// 9th function
// function to delete element from back end of queue
void frontDequeue(void){
	if(f >= MAX || f >= b) {
		message = EMPTY;
		return;
	}
    // set all as background color
    queue[b].r = BACKGROUND_R;
    queue[b].g = BACKGROUND_G;
    queue[b].b = BACKGROUND_B;

    // outline colors. set all as same as background color.
    queue[b].rl = BACKGROUND_R;
    queue[b].gl = BACKGROUND_G;
    queue[b].bl = BACKGROUND_B;

    b--;
    enqORdq = DEQUEUE2;    // indicates what the last operation was deQueue at front
		if(f >= b) {
			message = EMPTY;

		}
		if(b >= MAX)
			message = FULL;
}







//10th function
// max func to check which is greater in two arguments
int max(int a, int b) {
	return a?(a>b):b;
}








// 11th function
// func to check which is key is pressed by user and what are app functions to that key
void mykey(unsigned char key, int x, int y) {
	if(f == MAX && b == MAX) exit(0);

	int len = strlen(enter_str);
	if((key == 'd' || key == 'D') && (cnt_of_chars == 0))
		//printf("d is pressed\n");
		backDequeue();
  if((key == 'f' || key== 'F') && (cnt_of_chars == 0))
		//printf("f is pressed\n");
		frontDequeue();
	if((key=='E' || key == 'e')&& (cnt_of_chars == 0))
		exit(0);
	else if(isdigit(key) && strlen(enter_str) <= 28) {
		// printf("1\n");
		enter_str[len+1] = '\0';
		enter_str[len] = key;
		cnt_of_chars++;
	 	printf("Want to enter element in fornt end or back end\n(front end:0\tback end:1)");
	 	scanf("%d",&isback);
	}
	else if(key == '\b' && len > start_of_num) {
		// printf("2\n");
		enter_str[len -1] = '\0';
		cnt_of_chars--;
	}
	else if(!isgraph(key)) {
	// printf("Want to enter element in fornt end or back end\n(front end:1\tback end:0)");
	// scanf("%d",&forb);
		// printf("3\n");
		char newint[4];
		strncpy(newint, enter_str+start_of_num, 3);
		if(newint[0]) {
			enqueue(newint);
			enter_str[start_of_num] = '\0';
		}
		cnt_of_chars = 0;
	}
	glutPostRedisplay();
}







//12th function
//main function this is main bock of program
int  main(int argc,char **argv) {
	char number[1000];
	int i, j, len;
	char c;
	strcpy(enter_str, "Enter Element to deQueue: ");
	start_of_num = strlen(enter_str);
	printf("\n\n\n");
	printf("------------------------------------\n");
	printf("Simulation of  deQueue in OpenGL\n");
	printf("------------------------------------\n\n");
	printf("Enter the number of elements in the deQueue\n(Not greater than 15 and not lesser than 3):\n");
	scanf("%d", &MAX);

	while(MAX > 15 || MAX < 3) {
		printf("ERROR: Invalid value! \nEnter again: ");
		scanf("%d", &MAX);
	}
	printf("\n\nVALUE ACCEPTED! Program Running...\n");

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(SCREEN_X,SCREEN_Y);
	glutInitWindowPosition(10,10);
	glutCreateWindow("double ended Queue Simulation");
	glutDisplayFunc(display);
	glutKeyboardFunc(mykey);
	myinit();
	glutMainLoop();
	return 0;
}
