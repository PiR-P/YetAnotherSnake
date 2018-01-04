//
//  main.cpp
//  YetAnotherSnake
//
//  Created by Pierre Pasquet on 02/01/2018.
//  Copyright © 2018 Pierre Pasquet. All rights reserved.
//

#include "Snake.hpp"

GLuint board { 0 };
Snake snake;
Cell pellet;


/** Prototypes **/
GLuint make_board();
void display_game();
void reshape(int w, int h);
void init();
void special(int key, int, int);
void keyboard(char key, int, int);
void timer(int extra);
/***********************************************/

GLuint make_board()
{
  GLuint handle = glGenLists(1);
  glNewList(handle, GL_COMPILE);
  glBegin(GL_LINE_LOOP);
  glColor3d(1.0, 1.0, 1.0);
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(1.0, 0.0, 0.0);
  glVertex3d(1.0, 0.0, 1.0);
  glVertex3d(0.0, 0.0, 1.0);
  glEnd();
  glBegin(GL_LINES);
  glVertex3d(1.0, 0.0, 0.0);
  glVertex3d(1.0, -2.0, 0.0);
  glVertex3d(0.0, 0.0, 1.0);
  glVertex3d(0.0, -2.0, 1.0);
  glVertex3d(1.0, 0.0, 1.0);
  glVertex3d(1.0, -2.0, 1.0);
  glEnd();
  glEndList();
  return handle;
}

void display_game()
{
  // Set the isometric projection
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(
    1.75, 1.75, 1.75,
    0.5, 0, 0.5,
    0, 1, 0
  );
  glMatrixMode(GL_MODELVIEW);
  // Draw board
  glCallList(board);
  glColor3f(1.0f, 1.0f, 1.0f);
  pellet.draw();
  snake.draw();
  glutSwapBuffers();
}

void reshape(int w, int h)
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(40.0, 1.0, 1.0, 5.0);
}

void init()
{
  board = make_board();
}

void special(int key, int, int)
{
  switch(key)
  {
    case GLUT_KEY_UP:
      snake.setDirection(Direction::south);
      break;
    case GLUT_KEY_RIGHT:
      snake.setDirection(Direction::west);
      break;
    case GLUT_KEY_DOWN:
      snake.setDirection(Direction::north);
      break;
    case GLUT_KEY_LEFT:
      snake.setDirection(Direction::east);
      break;
    default:
      break;
  }
}

void keyboard(char key, int, int)
{
}

void timer(int extra)
{
  snake.move();
  
  if(snake.eatItself() || snake.isOutOfBound())
  {
    snake = Snake();
    pellet = Cell();
  }
  const Snake_cell& front_cell = snake[0];
  if(front_cell == pellet)
  {
    ++snake;
    pellet = Cell();
  }
  
  glutPostRedisplay();
  glutTimerFunc(TIMER_DELAY, timer, 0);
}

int main(int argc, char* argv[])
{
  srand ( time(NULL) );
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
  
  glutInitWindowSize(1024, 1024);
  glutInitWindowPosition(50, 50);
  
  glutCreateWindow("Isometric");
  
  glutReshapeFunc(reshape);
  glutSpecialFunc(special);
//  glutKeyboardFunc(keyboard);
  glutDisplayFunc(display_game);
  glutTimerFunc(TIMER_DELAY, timer, 0);
  
  init();
  glutMainLoop();
  
  return 0;
}

