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
bool game_in_progress { true };

/** Prototypes **/
void draw_text(const char* text);
void toggle_game();
GLuint make_board();
void display_game();
void reshape_game(int w, int h);
void display_info();
void change_display();
void init();
void special(int key, int, int);
void keyboard(unsigned char key, int x, int y);
void empty_keyboard(unsigned char key, int x, int y);
void timer(int extra);
/***********************************************/

void draw_text(const std::string text)
{
  size_t len = text.size();
  for (size_t i=0;i<len;i++)
    glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
}

void toggle_game()
{
  // If a game was in progress...
  if(game_in_progress)
  {
    glutKeyboardFunc(keyboard);
  }
  else
  {
    snake = Snake();
    pellet = Cell();
    glutKeyboardFunc(empty_keyboard);
    // Reset movement
    glutTimerFunc(TIMER_DELAY, timer, 0);
  }
  // Start / stop the game
  game_in_progress = !game_in_progress;
}

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
  // Draw ONLY if game is in progress
  if(game_in_progress)
  {
    pellet.draw();
    snake.draw();
  }
  display_info();
  glutSwapBuffers();
}

void reshape_game(int w, int h)
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(40.0, 1.0, 1.0, 5.0);
}

void display_info()
{
  const float scale = 0.25f;
  // Change color for text drawing
  glColor3f(1.0f, 1.0f, 1.0f);
  // Change projection to 2D Projection
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, 1000, 0, 1000);
  // Draw score
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(20, 950, 0.0f);
  glScalef(scale, scale, 1.0f);
  draw_text(std::to_string(snake.score()));
  glPopMatrix();
  // Draw info message
  if(!game_in_progress)
  {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(400, 950, 0.0f);
    glScalef(scale, scale, 1.0f);
    draw_text(std::string("Press 's' to start a new game."));
    glPopMatrix();
  }
  // Next matrix popped will be the 3D drawing
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
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

void keyboard(unsigned char key, int x, int y)
{
  switch(key) {
    case 's': toggle_game(); break;
    default: break;
  }
}

void empty_keyboard(unsigned char key, int x, int y)
{
}

void timer(int extra)
{
  snake.move();
  if(snake.eatItself() || snake.isOutOfBound())
  {
    toggle_game();
    glutPostRedisplay();
    return;
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
  
  glutReshapeFunc(reshape_game);
  glutSpecialFunc(special);
  glutKeyboardFunc(empty_keyboard);
  glutDisplayFunc(display_game);
  glutTimerFunc(TIMER_DELAY, timer, 0);
  
  init();
  glutMainLoop();
  
  return 0;
}

