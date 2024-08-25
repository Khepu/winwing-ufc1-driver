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
  printk("winwing_ufc1_devdrv - Probed\n");
  return 0;
}

static int input_configured(struct hid_device *hdev, struct hid_input *hidinput) {
  return 0;
}

static int raw_event(struct hid_device *hdev, struct hid_report *report, u8 *raw_data, int size) {
  return 0;
}

static struct hid_driver ww_ufc1_driver = {
  .name = "winwing_ufc1_devdrv",
  .id_table = device_table,
  .probe = probe,
  .input_configured = input_configured,
  .raw_event = raw_event
};

module_hid_driver(ww_ufc1_driver);
