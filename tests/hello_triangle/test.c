#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <rtems.h>
#include <rtems/fb.h>
#include <unistd.h>

/* Set correct channel order for RTEMS pc386 framebuffer */
#define PGL_ARGB32

#define PORTABLEGL_IMPLEMENTATION
#include "portablegl.h"

/*
** Default PortableGL test function
** See libs/PortableGL/testing/hello_triangle.c
*/
void hello_triangle(
  int argc, char** argv, void* data
)
{
  float points[] = { -0.5, -0.5, 0,
                      0.5, -0.5, 0,
                      0,    0.5, 0 };

  glEnableVertexAttribArray(PGL_ATTR_VERT);
  if (!argc) {
      GLuint triangle;
      glGenBuffers(1, &triangle);
      glBindBuffer(GL_ARRAY_BUFFER, triangle);
      glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

      glVertexAttribPointer(PGL_ATTR_VERT, 3, GL_FLOAT, GL_FALSE, 0, 0);
  } else {
      glVertexAttribPointer(PGL_ATTR_VERT, 3, GL_FLOAT, GL_FALSE, 0, points);
  }

  /*
  ** Comment from original file:
  ** Don't need a shader or uniform, just using the default shader 0
  ** which is just a passthrough vs, draw everything red fs
  */

  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

rtems_task Init(
  rtems_task_argument ignored
)
{
  printf( "\n\n*** HELLO TRIANGLE TEST ***\n" );

  /* Open frame buffer device */
  int fb_fd = open("/dev/fb0", O_RDWR);
  if (fb_fd == -1) {
      perror("Failed to open fbdevice");
      exit(1);
  }

  /* Get screen info object */
  struct fb_var_screeninfo vinfo;
  if (ioctl(fb_fd, FBIOGET_VSCREENINFO, &vinfo) != 0) {
      perror("ioctl(FBIOGET_VSCREENINFO)");
      close(fb_fd);
      exit(1);
  }

  int width  = vinfo.xres;
  int height = vinfo.yres;
  int size = width * height * sizeof(pix_t);

  /* Create backbuffer object for PortableGL to write into */
  pix_t* bbuf = malloc(size);

  glContext ctx;
  if (!init_glContext(&ctx, &bbuf, width, height)) {
      printf("Failed to initialize glContext");
      free(bbuf);
      close(fb_fd);
      exit(1);
  }

  hello_triangle(0, NULL, NULL);

  /* Write to actual frame buffer */
  write(fb_fd, bbuf, size);

  /* Free resources */
  free_glContext(&ctx);
  free(bbuf);
  close(fb_fd);

  printf( "*** END OF HELLO TRIANGLE TEST ***\n" );

  exit(0);
}

#define CONFIGURE_APPLICATION_DOES_NOT_NEED_CLOCK_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_FRAME_BUFFER_DRIVER

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE
#define CONFIGURE_MAXIMUM_TASKS 1

#define CONFIGURE_MAXIMUM_FILE_DESCRIPTORS 8

#define CONFIGURE_INIT
#include <rtems/confdefs.h>
