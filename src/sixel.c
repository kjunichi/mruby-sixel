/* sixel.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sixel.h>

extern int
parse_ppm_header(char *buf, int len, int *width, int *height, int *depth);

extern SIXELSTATUS
output_sixel(unsigned char *pixbuf, int width, int height, int ncolors, int pixelformat);

static int
sixel_write(char *data, int size, void *priv)
{
  return fwrite(data, 1, size, (FILE *)priv);
}

SIXELSTATUS
output_sixel(unsigned char *pixbuf, int width, int height, int ncolors, int pixelformat)
{
  sixel_output_t *context;
  sixel_dither_t *dither;
  SIXELSTATUS status;
  /*
int index=0;
for(int y=0; y< height; y++) {
        for(int x =0;x< width; x++) {
                printf("%d, ",pixbuf[index++]);
                printf("%d, ",pixbuf[index++]);
                printf("%d\n",pixbuf[index++]);
        }
}*/

  context = sixel_output_create(sixel_write, stdout);
  dither = sixel_dither_create(ncolors);
  status = sixel_dither_initialize(dither, pixbuf, width, height, pixelformat, SIXEL_LARGE_AUTO,
                                   SIXEL_REP_AUTO, SIXEL_QUALITY_AUTO);
  if (SIXEL_FAILED(status))
    return status;
  status = sixel_encode(pixbuf, width, height, pixelformat, dither, context);
  if (SIXEL_FAILED(status))
    return status;
  sixel_output_unref(context);
  sixel_dither_unref(dither);

  return status;
}

int
findChar(const char *str, const char target, int len)
{
  for (int i = 0; i < len; i++) {
    if (str[i] == target) {
      return i;
    }
  }
  return -1;
}

int
readLine_(char *buf, char *line, int len)
{
  int pos = findChar(buf, '\n', len);
  if (pos < 0) {
    return -1;
  }
  strncpy(line, buf, pos);
  line[pos] = '\0';
  return pos + 1;
}

int
readLine(char *buf, char *line, int len)
{
  char *tmpbuf = buf;
  int n = 0;

  do {
    int nn = readLine_(tmpbuf, line, 1024);
    if (nn < 0) {
      return -1;
    }
    n += nn;
    // printf("line = %s\n", line);
    tmpbuf = &tmpbuf[n];
  } while (line[0] == '#' && n < len);
  return n;
}
void
getImageSize(char *buf, int *width, int *height)
{
  char tmpStr[256];

  int pos = findChar(buf, ' ', strlen(buf));
  strncpy(tmpStr, buf, pos);
  tmpStr[pos] = '\0';
  *width = atoi(tmpStr);
  *height = atoi(&buf[pos + 1]);
}

int
parse_ppm_header(char *ppmbuf, int len, int *width, int *height, int *depth)
{
  char line[1024];
  char *tmpbuf = &ppmbuf[0];
  int headerLength = 0;

  // PNM TYPE
  int n = readLine(tmpbuf, line, sizeof(line));
  //printf("line = %s\n", line);
  tmpbuf = &tmpbuf[n];
  headerLength += n;

  // width heigth
  n = readLine(tmpbuf, line, sizeof(line));
  //printf("line = %s\n", line);
  tmpbuf = &tmpbuf[n];
  headerLength += n;
  getImageSize(line, width, height);
  //printf("w, h = %d, %d\n", *width, *height);

  n = readLine(tmpbuf, line, sizeof(line));
  //printf("line = %s\n", line);
  *depth = atoi(line);
  headerLength += n;
  return headerLength;
}
