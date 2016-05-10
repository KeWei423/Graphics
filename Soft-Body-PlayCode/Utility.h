#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include "Utility.h"
#include <math.h>

#define PI 3.14159265359

using namespace sf ;
using namespace std ;

Vector2f Diff(Vector2f const& v1, Vector2f const& v2,  float const& deltaTime);
float Diff(float const& a1, float const& a2,  float const& deltaTime);

float Distance(Vector2f const& v1, Vector2f const& v2) ;
float Norm (Vector2f const& v) ;
Vector2f Normalize(Vector2f const& v) ;
float determinant(Vector2f const& u, Vector2f const& v) ;
float dotProduct(Vector2f const& u, Vector2f const& v) ;

Vector2f rotatePoint(Vector2f const& point, Vector2f const& center, float const& angle) ;

bool checkSegmentIntersection(Vector2f const& A, Vector2f const& B, Vector2f const& C, Vector2f const& D) ;
Vector2f getSegmentIntersection(Vector2f const& A, Vector2f const& B, Vector2f const& C, Vector2f const& D) ;

void drawLine(Vector2f pos, Vector2f dir, float norm, RenderWindow &window, Color color) ;
void drawLine(Vector2f pos, Vector2f dir, RenderWindow &window, Color color) ;
void drawPoint(Vector2f p, RenderWindow &window) ;

float gaussianFunction(float maxVal, float wideness, float x) ;

float clamp(float value, float min, float max) ;

bool mouseClickedOnce(Mouse::Button const& button, bool &mouseFlag) ;
bool keyPressedOnce(Keyboard::Key const& key, bool &keyFlag) ;

bool collisionTrianglePoint(Vector2f a, Vector2f b, Vector2f c, Vector2f point) ;
