#include "../include/osutils/io_utils.h"
#include "../include/kernel/io.h"

#define WAIT_PORT 128


static void io_wait(void){
  outb(WAIT_PORT,0);
}
