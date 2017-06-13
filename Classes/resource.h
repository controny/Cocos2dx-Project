#ifndef RESOURCE
#define RESOURCE

//////////////////////////////////////////////////////////////////
enum Property { Jin, Mu, Shui, Huo, Tu };

static const char IMG_OBSTACLE[] = "obstacle/hollow_circle.png";
static const char IMG_PROP[] = "prop/prop.png";

//JIN, MU, SHUI, HUO TU
static const char IMG_BALL[5][25] = { "Ball/Ball1.png","Ball/Ball2.png", "Ball/Ball3.png","Ball/Ball4.png","Ball/Ball5.png" };
static const int TAG_BALL[5] = { 2001, 2002,2003,2004,2005 };



static float GRAVITY = 0.2;

static const int TAG_OBSTACLE = 1001;
static const int TAG_PROP = 1002;

#endif