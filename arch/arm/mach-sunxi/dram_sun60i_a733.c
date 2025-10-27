#include <init.h>
#include <spl.h>
#include <asm/io.h>
#include <linux/sizes.h>

struct sunxi_a733_dram {
	unsigned int resv[318];
	unsigned int size;
};

unsigned long sunxi_dram_init(void)
{
	struct sunxi_a733_dram *d = (struct sunxi_a733_dram *)(CONFIG_SPL_TEXT_BASE & 0xFFFF0000);
	return (unsigned long)d->size * SZ_1M;
}
