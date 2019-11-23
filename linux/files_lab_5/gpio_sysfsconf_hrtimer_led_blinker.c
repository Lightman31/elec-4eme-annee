#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/hrtimer.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/err.h>


#define PIN1 11
#define PIN2 9

//////////////////////////////////////////////////////////////////////
// Important : code defensively, handle error cases for each call ! //
//////////////////////////////////////////////////////////////////////


// declare a global variable "blink_period_ns" (in nanoseconds):
//  - it is to be updated when requested by the sysfs interface (e.g., when the device attribute "period" is update)
//  - set it by default to 1 second

// declare a global variable "current_pin":
//  - it is to be updated when requested by the sysfs interface (e.g., when the device attribute "pin" is updated)
//  - set it by default to PIN1 

// declare a global high-resolution timer hr_timer 

// other global declarations may be added here 

// "hr_timer" blink callback
enum hrtimer_restart blink_callback(struct hrtimer *timer_restart)
{
  // forward the time expiry for "hr_timer"

  // change the blinking LED when requested by the sysfs interface 

  return HRTIMER_RESTART;
}

static ssize_t set_period_callback(struct device* dev, 
                                   struct device_attribute* attr, 
                                   const char* buf, 
                                   size_t count)
{
  // convert the string newly written in the device attribute "period" to an "unsigned long" integer
  // - use a temporary variable to store the converted value
  //   ========================
  // - if the value is lesser than 10, raise an error -EINVAL
  
  // set the new value of "blink_period_ns"
  
  return count;
}

static ssize_t set_pin_callback(struct device* dev, 
                                struct device_attribute* attr, 
                                const char* buf, 
                                size_t count)
{
  // convert the string newly written in the device attribute "pin" to an "unsigned" integer
  // - use a temporary variable to store the converted value
  //   ========================
  // - if the value is different of PIN1 and PIN2, raise an error -EINVAL

  
  // set the new value of "current_pin"
  
  return count;
}

// the identifier of a character device 
static dev_t dev = 0;
static struct class *clse;
static struct device *dobj;

// declare the device attributes "period" and "pin", and attach them resp. to "set_period_callback" and "set_pin_callback"
// - use the macro DEVICE_ATTR


static int __init gpio_sysfsconf_hrtimer_led_blinker_init(void)
{
  // a variable used to save successively the error statuses of function calls
  int ret = 0; 
  
  // local variables are to be declared here

  
  printk(KERN_INFO "%s\n", __func__);


  // request PIN1 for LED D6, print a kernel success message 
  


  // request PIN2 for LED D5, print a kernel success message
  


  // set "hr_timer" as CLOCK_MONOTONIC, attach it to "blink_callback", and launch it
  


  // allocate dynamically a major number for "dev", and set its minor count 
  


  // create a sysfs class "ext_leds", and register it in "clse"

  // error case 
  BUG_ON(IS_ERR(clse));


  // create a sysfs device object "blinker" under "ext_leds", register it in "kobj", and attach it to "dev":
  // => a /dev file "blinker" will be created                                            ==================   

  // error case
  BUG_ON(IS_ERR(kobj));


  // attach the attribute "dev_attr_period" to "kobj"

  // error case
  BUG_ON(ret < 0);


  // attach the attribute "dev_attr_pin" to "kobj"

  // error case
  BUG_ON(ret < 0);
  
  return ret;
}


static void __exit gpio_sysfsconf_hrtimer_led_blinker_exit(void)
{
  // used for error statuses
  int ret = 0;
  
  printk(KERN_INFO "%s\n", __func__);

  // remove the sysFS "ext_leds" (start first by removing attributes, and device objects)

  // unregister "dev" 

  // cancel "hr_timer"
  
  // release PIN1 and PIN2 properly
  //                       ========
  
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Last1, First1 and Last2, First2 (and Last3, First3)");
MODULE_DESCRIPTION("Basic sysfs-configurable LEDs blinker using a high resolution timer.");

module_init(gpio_sysfsconf_hrtimer_led_blinker_init);
module_exit(gpio_sysfsconf_hrtimer_led_blinker_exit);
