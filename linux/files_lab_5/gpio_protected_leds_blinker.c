#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/spinlock.h>
#include <linux/slab.h>

#define PIN1 11
#define PIN2 9

//////////////////////////////////////////////////////////////////////
// Important : code defensively, handle error cases for each call ! //
//////////////////////////////////////////////////////////////////////

// declare two kernel thread pointers "kt1" and "kt2"
// - they are used to update alternatively the LED pins' values

// declare a global shared resource "pv" as a data struct "pins_values" of two "int" fields:
// - vpin1: storing the value of PIN1
// - vpin2: storing the value of PIN2
// - use the C primitive "typedef"
// - initially, set "pv" to {1, 0}

// declare a global kernel "timer"

// declare a spinlock "sl"
// - use the macro DEFINE_SPINLOCK


// "timer" blink callback
static void blink_callback(unsigned long data)
{
  // set the pins' values to their respective values in the shared resource "pv"
  // - is this setting should be protected by the spinlock "sl" ?

  // set the next time expiry for "timer"
  // run the callback at next timer interrupt, and delay until time expiry
  // - see gpio_timer_led_blinker.c 
}

static int led1_blinker_thread(void *data)
{
  printk(KERN_INFO "%s\n", __func__);
  
  while(!kthread_should_stop()) {
    // set the fields vpin1 and vpin2 of "pv" resp. to 1 and 0
    // - is this update should be protected by the spinlock "sl" ?

    
  }
  
  return 0;
}

static int led2_blinker_thread(void *data)
{
  printk(KERN_INFO "%s\n", __func__);
  
  while(!kthread_should_stop()) {
    // inversely to led1_blinker_thread, set the fields vpin1 and vpin2 of "pv" resp. to 0 and 1
    // - is this update should be protected by the spinlock "sl" ?

    
  }
  
  return 0;
}

static int __init gpio_leds_blinker_init(void)
{
  // a variable used to save error statuses of API function call
  int ret = 0;
  
  printk(KERN_INFO "%s\n", __func__);

  // request PIN1 for LED D6, print a kernel success message 
  
  // request PIN2 for LED D5, print a kernel success message 


  // initialize "timer", attach it to "blink_callback", and set its first time expiry
  // run the callback and delay until time expiry
  // - see gpio_timer_led_blinker.c 
  

  // create (and attach to "kt1"), and launch the first kernel thread 

  // create (and attach to "kt2"), and launch the second kernel thread


  return 0;
}

static void __exit gpio_leds_blinker_exit(void)
{
  printk(KERN_INFO "%s\n", __func__);

  // cancel the "timer" 

  // stop the kernel threads

  // release PIN1 and PIN2 properly
  //                       ========

}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Last1, First1 and Last2, First2 (and Last3, First3)");
MODULE_DESCRIPTION("Basic LEDs blinker with spinlock protection");

module_init(gpio_leds_blinker_init);
module_exit(gpio_leds_blinker_exit);
