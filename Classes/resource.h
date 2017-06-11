#ifndef RESOURCE
#define RESOURCE

//////////////////////////////////////////////////////////////////
static const char IMG_OBSTACLE[] = "obstacle/hollow_circle.png";

static const int TAG_BALL= 1000;
static const int TAG_OBSTACLE = 1001;
static const int TAG_PROP = 1002;

const int Section = 72;
const int Half_Section = 36;
const int Circle = 360;
// (rotation >= 0 && rotation < COLOR_SHUI_MIN) ||  rotation >= COLOR_SHUI_MAX )
static const int COLOR_SHUI_MIN = Half_Section;
static const int COLOR_SHUI_MAX = Circle - Half_Section;
// ( rotation >= COLOR_XX_MIN && rotation < COLOR_XX_MAX )
static const int COLOR_MU_MIN =Half_Section;
static const int COLOR_MU_MAX = COLOR_MU_MIN + Section;
static const int COLOR_JIN_MIN = Half_Section + Section;
static const int COLOR_JIN_MAX = COLOR_JIN_MIN + Section;
static const int COLOR_HUO_MIN = Half_Section + Section * 2;
static const int COLOR_HUO_MAX = COLOR_HUO_MIN + Section;
static const int COLOR_TU_MIN = Half_Section + Section * 3;
static const int COLOR_TU_MAX = COLOR_TU_MIN + Section;

static const int GAME_STATUS_START = 10;
static const int GAME_STATUS_PLAYING = 20;
static const int GAME_STATUS_GAME_OVER = 30;
static const int GAME_STATUS_RESTART = 40;

#endif