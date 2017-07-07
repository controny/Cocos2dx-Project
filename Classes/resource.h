#ifndef RESOURCE
#define RESOURCE

//////////////////////////////////////////////////////////////////
enum Property { Jin, Mu, Shui, Huo, Tu };

static const char IMG_OBSTACLE[] = "obstacle/hollow_circle.png";
static const char IMG_PROP[] = "prop/prop.png";

//JIN, MU, SHUI, HUO TU
static const char IMG_BALL[5][25] = { "Ball/Ball1.png","Ball/Ball2.png", "Ball/Ball3.png","Ball/Ball4.png","Ball/Ball5.png" };
static const int TAG_BALL[5] = { 2001, 2002,2003,2004,2005 };

static const int Section = 72;
static const int CIRCLE_SHUI_MIN = Section / 2;
static const int CIRCLE_SHUI_MAX = 360 - Section / 2;
static const int CIRCLE_MU_MIN = Section / 2;
static const int CIRCLE_MU_MAX = CIRCLE_MU_MIN + Section;
static const int CIRCLE_JIN_MIN = Section / 2 + Section;
static const int CIRCLE_JIN_MAX = CIRCLE_JIN_MIN + Section;
static const int CIRCLE_HUO_MIN = Section + 180;
static const int CIRCLE_HUO_MAX = CIRCLE_HUO_MIN + Section;
static const int CIRCLE_TU_MIN = 180;
static const int CIRCLE_TU_MAX = CIRCLE_TU_MIN + Section;

static float GRAVITY = 0.2;

static const int TAG_OBSTACLE = 1001;
static const int TAG_PROP = 1002;

#endif