#include "main.h"
#include "api.h"

extern int sliderWidth;

extern lv_obj_t * redlowLabel;
extern lv_obj_t * redhighLabel;
extern lv_obj_t * bluelowLabel;
extern lv_obj_t * bluehighLabel;
extern lv_obj_t * saveLabel;

static void redlowSliderEventHandler();
static void redhighSliderEventHandler();
static void blueSliderEventHandler();
static void bluehighSliderEventHandler();
static void savebuttonEventHandler();
void update_ui();
static void redlowButtonEventHandler();
static void redhighButtonEventHandler();
static void bluelowButtonEventHandler();
static void bluehighButtonEventHandler();

void create_ui();