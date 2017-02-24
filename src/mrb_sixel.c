/*
** mrb_sixel.c - Sixel class
**
** Copyright (c) Junichi Kajiwara 2017
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"
#include "mruby/data.h"
#include "mrb_sixel.h"

#include <string.h>
#include <sixel.h>

#define DONE mrb_gc_arena_restore(mrb, 0);

typedef struct {
  char *str;
  int len;
} mrb_sixel_data;

static const struct mrb_data_type mrb_sixel_data_type = {
  "mrb_sixel_data", mrb_free,
};

extern SIXELSTATUS
output_sixel(unsigned char *pixbuf, int width, int height, int ncolors, int pixelformat);

extern int
parse_ppm_header(char *buf, int len, int *w, int *h, int *depth);

static mrb_value
mrb_sixel_encoder_init(mrb_state *mrb, mrb_value self)
{
  mrb_sixel_data *data;
  char *str = "dummy";
  int len = strlen(str);

  data = (mrb_sixel_data *)DATA_PTR(self);
  if (data) {
    mrb_free(mrb, data);
  }
  DATA_TYPE(self) = &mrb_sixel_data_type;
  DATA_PTR(self) = NULL;

  // mrb_get_args(mrb, "s", &str, &len);
  data = (mrb_sixel_data *)mrb_malloc(mrb, sizeof(mrb_sixel_data));
  data->str = str;
  data->len = len;
  DATA_PTR(self) = data;

  return self;
}

static mrb_value
mrb_sixel_encode_from_ppm(mrb_state *mrb, mrb_value self)
{
  char *ppmBuf;
  int len, width, height, depth, ppm_header_length;

  mrb_get_args(mrb, "s", &ppmBuf, &len);
  ppm_header_length = parse_ppm_header(ppmBuf, len, &width, &height, &depth);
  SIXELSTATUS status = output_sixel((unsigned char *)(&ppmBuf[ppm_header_length]), width, height, 256, SIXEL_PIXELFORMAT_RGB888);
  fflush(stdout);
  return self;
}

static mrb_value
mrb_sixel_hello(mrb_state *mrb, mrb_value self)
{
  mrb_sixel_data *data = DATA_PTR(self);

  return mrb_str_new(mrb, data->str, data->len);
}

void
mrb_mruby_sixel_gem_init(mrb_state *mrb)
{
  struct RClass *sixelEncoder;
  sixelEncoder = mrb_define_class(mrb, "SixelEncoder", mrb->object_class);
  mrb_define_method(mrb, sixelEncoder, "initialize", mrb_sixel_encoder_init, MRB_ARGS_NONE());
  mrb_define_method(mrb, sixelEncoder, "hello", mrb_sixel_hello, MRB_ARGS_NONE());
  mrb_define_method(mrb, sixelEncoder, "encode_from_ppm", mrb_sixel_encode_from_ppm, MRB_ARGS_REQ(1));
  DONE;
}

void
mrb_mruby_sixel_gem_final(mrb_state *mrb)
{
}
