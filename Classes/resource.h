#ifndef RESOURCE
#define RESOURCE

//////////////////////////////////////////////////////////////////
static const char IMG_OBSTACLE[] = "obstacle/hollow_circle.png";
static const char IMG_PROP[] = "prop/prop.png";

static float GRAVITY = 0.2;

static float GRAVITY = 0.2;

static const int TAG_BALL= 1000;
static const int TAG_OBSTACLE = 1001;
static const int TAG_PROP = 1002;

// constants which indicates touched colors
const int Section = 72;
const int Half_Section = 36;
const int Circle = 360;
// (rotation >= 0 && rotation < CIRCLE_SHUI_MIN) ||  rotation >= CIRCLE_SHUI_MAX )
static const int CIRCLE_SHUI_MIN = Half_Section;
static const int CIRCLE_SHUI_MAX = Circle - Half_Section;
// ( rotation >= CIRCLE_XX_MIN && rotation < CIRCLE_XX_MAX )
static const int CIRCLE_MU_MIN =Half_Section;
static const int CIRCLE_MU_MAX = CIRCLE_MU_MIN + Section;
static const int CIRCLE_JIN_MIN = Half_Section + Section;
static const int CIRCLE_JIN_MAX = CIRCLE_JIN_MIN + Section;
static const int CIRCLE_HUO_MIN = Half_Section + Section * 2;
static const int CIRCLE_HUO_MAX = CIRCLE_HUO_MIN + Section;
static const int CIRCLE_TU_MIN = Half_Section + Section * 3;
static const int CIRCLE_TU_MAX = CIRCLE_TU_MIN + Section;

#endif