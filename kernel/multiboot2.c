/**
 * @file multiboot2.c
 * @author liang.xianlong@zte.com.cn
 * @brief Function for multiboot2
 * @version 0.1
 * @date 2022-06-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../include/multiboot2.h"
#include "../include/lib64/logging.h"

#define  NULL 0

reserved_areas_t build_reserved_areas();
static multiboot_info_t* saved_mbi = NULL;

static reserved_areas_t reserved_areas = { .kernel_start = 0,
                                           .kernel_end = 0,
                                           .multiboot_start = 0,
                                           .multiboot_end = 0,
                                           .start = 0,
                                           .end = 0 };

static const char* cmdline = NULL;
static multiboot_tag_framebuffer_t* framebuffer = NULL;
static multiboot_tag_mmap_t* mmap = NULL;

void multiboot_init(multiboot_info_t* mbi)
{
	saved_mbi = mbi;
	reserved_areas = build_reserved_areas();
}

multiboot_tag_framebuffer_t* multiboot_get_framebuffer()
{
	return framebuffer;
}

const char* multiboot_get_cmdline()
{
	return cmdline;
}

reserved_areas_t multiboot_get_reserved_areas()
{
	return reserved_areas;
}

multiboot_info_t* multiboot_get_info()
{
	return saved_mbi;
}

multiboot_tag_mmap_t* multiboot_get_mmap()
{
	return mmap;
}

void* multiboot_find(uint16_t type)
{
	multiboot_tag_t* tag = NULL;
	// `*tag` points to the first tag of the multiboot_info_t struct
	for (tag = (multiboot_tag_t*)saved_mbi->tags;
		tag->type != MULTIBOOT_TAG_TYPE_END;
		tag = (multiboot_tag_t*)((uint8_t*)tag + ((tag->size + 7) & ~7))) {
		pr_debug("found tag with type=%d\n", tag->type);
		if (tag->type == type) {
			pr_debug("found tag for type=%d\n", type);
			return tag;
		}
	}

	pr_debug("could not find tag for type=%d\n", type);
	return NULL;
}

reserved_areas_t build_reserved_areas() {
	multiboot_tag_t* tag = NULL;
  	reserved_areas_t reserved = { .kernel_start = 0,
                                .kernel_end = 0,
                                .multiboot_start = (uint64_t)saved_mbi,
                                .multiboot_end = 0,
                                .start = 0,
                                .end = 0 };

  	pr_debug("announced MBI size %#x\n", saved_mbi->size);

  	for (tag = (multiboot_tag_t*)saved_mbi->tags; tag->type != MULTIBOOT_TAG_TYPE_END;
    	tag = (multiboot_tag_t*)((uint8_t*)tag + ((tag->size + 7) & ~7))) {
    	pr_debug("found tag with type=%d\n", tag->type);

    	switch (tag->type) {
    		case MULTIBOOT_TAG_TYPE_CMDLINE: {
        		cmdline = ((multiboot_tag_string_t*)tag)->string;
        		pr_debug("command line=%s\n", cmdline);
        		break;
    		}

      		case MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME:
        		pr_debug("boot loader name=%s\n", ((multiboot_tag_string_t*)tag)->string);
        		break;

      		case MULTIBOOT_TAG_TYPE_MODULE: {
        		reserved.end = ((multiboot_tag_module_t*)tag)->mod_end;
        		pr_debug("module at %p-%p with command line=%s\n",
                ((multiboot_tag_module_t*)tag)->mod_start,
                ((multiboot_tag_module_t*)tag)->mod_end,
                ((multiboot_tag_module_t*)tag)->cmdline);
        		break;
      		}

    		case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO:
        		pr_debug("mem_lower = %dKB, mem_upper = %dKB\n",
                ((multiboot_tag_basic_meminfo_t*)tag)->mem_lower,
                ((multiboot_tag_basic_meminfo_t*)tag)->mem_upper);
        		break;

    		case MULTIBOOT_TAG_TYPE_BOOTDEV:
        		pr_debug("boot device %#x, %u, %u\n",
                ((multiboot_tag_bootdev_t*)tag)->biosdev,
                ((multiboot_tag_bootdev_t*)tag)->slice,
                ((multiboot_tag_bootdev_t*)tag)->part);
        		break;

    		case MULTIBOOT_TAG_TYPE_MMAP: {
        		mmap = (multiboot_tag_mmap_t*)tag;
        		for (multiboot_mmap_entry_t* entry = mmap->entries;
             		(uint8_t*)entry < (uint8_t*)tag + tag->size;
             		entry = (multiboot_mmap_entry_t*)((uint64_t)entry +
                    ((multiboot_tag_mmap_t*)tag)->entry_size)) {
          			pr_debug("mmap entry: base_addr = %p, length = %#x, type = %#x\n",
                    entry->addr,
                    entry->len,
                    entry->type);
        		}
        		break;
      		}

      		case MULTIBOOT_TAG_TYPE_FRAMEBUFFER: {
        		framebuffer = (multiboot_tag_framebuffer_t*)tag;
        		pr_debug("framebuffer framebuffer_addr=%p common_addr=%p\n",
                   framebuffer->common.framebuffer_addr,
                   (void*)&framebuffer->common);
        		break;
    		}

    		case MULTIBOOT_TAG_TYPE_APM:
        		pr_debug("%s\n", "apm");
        		break;

      		case MULTIBOOT_TAG_TYPE_ACPI_OLD:
        		pr_debug("%s\n", "acpi old");
        		break;

    		case MULTIBOOT_TAG_TYPE_ACPI_NEW:
        		pr_debug("%s\n", "acpi new");
        		break;

    		case MULTIBOOT_TAG_TYPE_ELF_SECTIONS: {
    			multiboot_elf_sections_entry_t* elf = NULL;
				uint32_t i = 0;
				for (i = 0, elf = ((multiboot_tag_elf_sections_t*)tag)->sections;
          			i < ((multiboot_tag_elf_sections_t*)tag)->num;
					elf = (multiboot_elf_sections_entry_t*)((uint64_t)elf +
					((multiboot_tag_elf_sections_t*)tag)->section_size), i++) {
          			pr_debug("elf section #%02d addr = %p, type = %#x, size = %#x, "
                    "flags = %#x\n",
                    i,
                    elf->addr,
                    elf->type,
                    elf->size,
                    elf->flags);

        			if (elf->type == MULTIBOOT_ELF_SECTION_TYPE_NULL) {
            			continue;
          			}

        			if (elf->addr < reserved.kernel_start || reserved.kernel_start == 0) {
            			reserved.kernel_start = elf->addr;
          			}

          			if ((elf->addr + elf->size) > reserved.kernel_end) {
            			reserved.kernel_end = elf->addr + elf->size;
          			}
        		}
        		break;
      		}

			case MULTIBOOT_TAG_TYPE_NETWORK:
        		pr_debug("%s\n", "network");
        		break;

      		case MULTIBOOT_TAG_TYPE_LOAD_BASE_ADDR:
        		pr_debug("%s\n", "load base addr");
        		break;

      		default:
				break;
        		pr_debug("tag %#x, size %#x\n", tag->type, tag->size);
    	}
  	}

	tag = (multiboot_tag_t*)((uint8_t*)tag + ((tag->size + 7) & ~7));
	reserved.multiboot_end = (uint64_t)tag;

	pr_debug("total MBI size %#x\n", (uint64_t)tag - (uint64_t)saved_mbi);

	reserved.start = reserved.kernel_start;

	if (reserved.end < reserved.multiboot_end) {
		reserved.end = reserved.multiboot_end;
	}

	pr_debug("kernel_start=%#x kernel_end=%#x multiboot_start=%#x "
        "multiboot_end=%#x reserved start=%#x end=%#x\n",
        reserved.kernel_start,
        reserved.kernel_end,
        reserved.multiboot_start,
        reserved.multiboot_end,
        reserved.start,
        reserved.end);

	return reserved;
}