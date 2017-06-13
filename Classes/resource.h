#ifndef RESOURCE
#define RESOURCE

//////////////////////////////////////////////////////////////////
enum Property { Jin, Mu, Shui, Huo, Tu };

static const char IMG_OBSTACLE[] = "obstacle/hollow_circle.png";
static const char IMG_PROP[] = "prop/prop.png";

static float GRAVITY = 0.2;

static const int TAG_BALL= 1000;
static const int TAG_OBSTACLE = 1001;
static const int TAG_PROP = 1002;

#endif