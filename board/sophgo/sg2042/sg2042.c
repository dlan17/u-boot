// SPDX-License-Identifier: GPL-2.0+

#include <common.h>
#include <cpu_func.h>
#include <dm.h>
#include <asm/sections.h>
#include <fdt_support.h>
#include <mapmem.h>

#define SG2042_DDR_BANKS 4

void *board_fdt_blob_setup(int *err)
{
	*err = 0;
	if (IS_ENABLED(CONFIG_OF_SEPARATE) || IS_ENABLED(CONFIG_OF_BOARD)) {
		if (gd->arch.firmware_fdt_addr)
			return (ulong *)(uintptr_t)gd->arch.firmware_fdt_addr;
	}

	return (ulong *)&_end;
}

int board_init(void)
{
	/* enable all cache ways */
	enable_caches();

	return 0;
}

static int board_memory_fixup(void *tgt)
{
	char node[sizeof("/memory@0")];
	void *src = map_sysmem(gd->arch.firmware_fdt_addr, 0);
	int ret;
	int i;

	/* avoid the copy if we are using the same device tree */
	if (src == tgt)
		return 0;

	for (i = 0; i < SG2042_DDR_BANKS; i++) {
		const fdt32_t *value;
		int len;

		sprintf(node, "/memory@%d", i);

		ret = fdt_path_offset(src, node);
		if (ret < 0)
			return ret;

		value = fdt_getprop(src, ret, "reg", &len);
		if (len != 2 * sizeof(fdt64_t))
			return -FDT_ERR_BADSTRUCTURE;

		ret = fdt_find_and_setprop(tgt, node, "reg", value, len, false);
		if (ret < 0)
			return ret;
	}

	return 0;
}

int board_fix_fdt(void *fdt)
{
	int ret;

	/* Copy the memory ranges inserted into the device tree by zsbl */
	ret = board_memory_fixup(fdt);
	if (ret < 0) {
		log_err("failed to fixup DT memory nodes: %d\n", ret);
		return ret;
	}

	/* Copy the reserved-memory node inserted into the device tree by OpenSBI */
	ret = riscv_board_reserved_mem_fixup(fdt);
	if (ret < 0) {
		log_err("failed to fixup DT for reserved memory: %d\n", ret);
		return ret;
	}

	return 0;
}

/* Set the memory ranges in the new device tree loaded */
int ft_board_setup(void *blob, struct bd_info *bd)
{
	char node[sizeof("/memory@0")];
	int ret;
	int i;

	for (i = 0; i < SG2042_DDR_BANKS; i++) {
		sprintf(node, "/memory@%d", i);

		if (i < CONFIG_NR_DRAM_BANKS && bd->bi_dram[i].size) {
			fdt64_t value[] = {
				cpu_to_fdt64(bd->bi_dram[i].start),
				cpu_to_fdt64(bd->bi_dram[i].size),
			};

			ret = fdt_find_and_setprop(blob, node, "reg", value, sizeof(value), false);
			if (ret)
				return ret;
		} else {
			ret = fdt_path_offset(blob, node);
			if (ret > 0) {
				ret = fdt_del_node(blob, ret);
				if (ret < 0)
					return ret;
			}
		}
	}

	return 0;
}
