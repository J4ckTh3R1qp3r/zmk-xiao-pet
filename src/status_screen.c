#include <lvgl.h>
#include <zmk/display/status_screen.h>

static lv_obj_t *status_label;
static unsigned int current_status;

static const char *const statuses[] = {
    "IDLE",
    "WORKING",
    "NEEDS\nINPUT",
    "DONE",
};

static void change_status(lv_timer_t *timer) {
    ARG_UNUSED(timer);

    current_status = (current_status + 1) % 4;
    lv_label_set_text(status_label, statuses[current_status]);
    lv_obj_align(status_label, LV_ALIGN_CENTER, 0, 0);
}

lv_obj_t *zmk_display_status_screen(void) {
    lv_obj_t *screen = lv_obj_create(NULL);

    lv_obj_set_style_bg_color(screen, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_border_width(screen, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(screen, 0, LV_PART_MAIN);

    status_label = lv_label_create(screen);
    lv_label_set_text(status_label, statuses[0]);

    lv_obj_set_style_text_color(
        status_label, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(
        status_label, &lv_font_montserrat_24, LV_PART_MAIN);
    lv_obj_set_style_text_align(
        status_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

    lv_obj_align(status_label, LV_ALIGN_CENTER, 0, 0);

    lv_timer_create(change_status, 2000, NULL);

    return screen;
}