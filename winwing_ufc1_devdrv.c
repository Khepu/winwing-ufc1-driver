#include <linux/module.h>
#include <linux/init.h>
#include <linux/hid.h>
#include <linux/hidraw.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Giorgos Makris");
MODULE_DESCRIPTION("Driver for the WinWing UFC1");

#define VENDOR_ID 0x4098
#define PRODUCT_ID 0xbed0

static struct hid_device_id device_table[] = {
  {HID_USB_DEVICE(VENDOR_ID, PRODUCT_ID)},
  {},
};

MODULE_DEVICE_TABLE(hid, device_table);

static int probe(struct hid_device *hdev, const struct hid_device_id *id) {
  printk(KERN_INFO "winwing_ufc1_devdrv: probed\n");

  int ret = hid_parse(hdev);

  if (ret) {
    printk(KERN_ERR "winwing_ufc1_devdrv: parse failed");
    return ret;
  }

  ret = hid_hw_start(hdev, HID_CONNECT_HIDRAW);

  if (ret) {
    printk(KERN_ERR "winwing_ufc1_devdrv: hw start failed");
    return ret;
  }

  ret = hid_hw_open(hdev);
  if (ret) {
    printk(KERN_ERR "winwing_ufc1_devdrv: hw open failed");
    hid_hw_stop(hdev);
    return ret;
  }

  return 0;
}

static void remove(struct hid_device *hdev) {
  hid_hw_close(hdev);
  hid_hw_stop(hdev);
}

/* static int input_configured(struct hid_device *hdev, struct hid_input *hidinput) { */
/*   return 0; */
/* } */

static int raw_event(struct hid_device *hdev,
                     struct hid_report *report,
                     u8 *raw_data,
                     int size) {
  printk("winwing_ufc1_devdrv: [debug] raw_event");
  struct input_dev *data = hid_get_drvdata(hdev);

  /* if (!data) { */
  /*   return -EINVAL; */
  /* } */

  printk(KERN_INFO "winwing_ufc1_devdrv: data:");

  for (int i = 0; i < size && i < 16; i++) {
    printk(KERN_CONT " %02x", raw_data[i]);
  }
  printk(KERN_CONT "\n");

  return 0;
}

static struct hid_driver ww_ufc1_driver = {
  .name = "winwing_ufc1_devdrv",
  .id_table = device_table,
  .probe = probe,
  .remove = remove,
  //  .input_configured = input_configured,
  .raw_event = raw_event
};

module_hid_driver(ww_ufc1_driver);
