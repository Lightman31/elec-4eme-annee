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
struct task_struct *kt1;
struct task_struct *kt2;

// declare a global shared resource "pv" as a data struct "pins_values" of two "int" fields:
// - vpin1: storing the value of PIN1
// - vpin2: storing the value of PIN2
// - use the C primitive "typedef"
// - initially, set "pv" to {1, 0}
typedef struct pin_values
{
    int vpin1;
    int vpin2;
}t_pv;

struct pin_values pv={1,0};

// declare a global kernel "timer"
static struct timer_list timer;

// declare a spinlock "sl"
// - use the macro DEFINE_SPINLOCK
DEFINE_SPINLOCK(sl);

// "timer" blink callback
static void blink_callback(unsigned long data)
{
  printk(KERN_INFO "%s\n", __func__);
  // set the pins' values to their respective values in the shared resource "pv"
  // - is this setting should be protected by the spinlock "sl" ?
  while(spin_is_locked(&sl));
  //printk(KERN_INFO "%d", spin_is_locked(&sl)); 
  spin_lock(&sl);
  gpio_set_value(PIN1, pv.vpin1);
  gpio_set_value(PIN2, pv.vpin2);
  spin_unlock(&sl);

  // set the next time expiry for "timer"
  // run the callback at next timer interrupt, and delay until time expiry
  // - see gpio_timer_led_blinker.c
  timer.data = !data;
  timer.expires = jiffies + 1*HZ;
  add_timer(&timer);
}

static int led1_blinker_thread(void *data)
{
  printk(KERN_INFO "%s\n", __func__);

  while(!kthread_should_stop()) {
    // set the fields vpin1 and vpin2 of "pv" resp. to 1 and 0
    // - is this update should be protected by the spinlock "sl" ?
    if(!timer.data && !spin_is_locked(&sl) && pv.vpin1 == 0){
    spin_lock(&sl);
    pv.vpin1 = 1;
    pv.vpin2 = 0;
    spin_unlock(&sl);
   }
  }
  return 0;
}

static int led2_blinker_thread(void *data)
{
  printk(KERN_INFO "%s\n", __func__);

  while(!kthread_should_stop()) {
    // inversely to led1_blinker_thread, set the fields vpin1 and vpin2 of "pv" resp. to 0 and 1
    // - is this update should be protected by the spinlock "sl" ?
    if(timer.data && !spin_is_locked(&sl) && pv.vpin2 == 0){
    spin_lock(&sl);
    pv.vpin1 = 0;
    pv.vpin2 = 1;
    spin_unlock(&sl);
   }
  }
  return 0;
}

static int __init gpio_leds_blinker_init(void)
{
  // a variable used to save error statuses of API function call
  int ret = 0;

  printk(KERN_INFO "%s\n", __func__);

  // request PIN1 for LED D6, print a kernel success message
  ret = gpio_request_one(PIN1, GPIOF_OUT_INIT_LOW, "LED_D6");

  if (ret) {
    printk(KERN_ERR "Unable to request GPIOs: %d\n", ret);
    return ret;
  }
  printk(KERN_INFO "Successfully invoked %s\n", __func__);
  // request PIN2 for LED D5, print a kernel success message
  ret = gpio_request_one(PIN2, GPIOF_OUT_INIT_LOW, "LED_D5");

  if (ret) {
    printk(KERN_ERR "Unable to request GPIOs: %d\n", ret);
    return ret;
  }
  printk(KERN_INFO "Successfully invoked %s\n", __func__);

  // initialize "timer", attach it to "blink_callback", and set its first time expiry
  // run the callback and delay until time expiry
  // - see gpio_timer_led_blinker.c
  init_timer(&timer);
  timer.function = blink_callback;
  timer.data = 1L;
  timer.expires = jiffies + 1*HZ;
  add_timer(&timer);

  spin_unlock(&sl);

  // create (and attach to "kt1"), and launch the first kernel thread
  kt1=kthread_create(led1_blinker_thread, (void*)1, "kt1");
  if(!IS_ERR(kt1))
    wake_up_process(kt1);

  // create (and attach to "kt2"), and launch the second kernel thread
  kt2=kthread_create(led2_blinker_thread, (void*)1, "kt2");
  if(!IS_ERR(kt2))
    wake_up_process(kt2);


  return 0;
}

static void __exit gpio_leds_blinker_exit(void)
{
  printk(KERN_INFO "%s\n", __func__);

  // cancel the "timer"
  del_timer_sync(&timer);

  // stop the kernel threads
  kthread_stop(kt1);
  kthread_stop(kt2);

  // release PIN1 and PIN2 properly
  //                       ========
  gpio_set_value(PIN1, 0);
  gpio_free(PIN1);

  gpio_set_value(PIN2, 0);
  gpio_free(PIN2);

}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Buot, Adrien and Guicharnaud, Léo and Sabatey, Clara");
MODULE_DESCRIPTION("Basic LEDs blinker with spinlock protection");

module_init(gpio_leds_blinker_init);
module_exit(gpio_leds_blinker_exit);
