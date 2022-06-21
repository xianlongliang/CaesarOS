arch ?= x86_64
kernel := build/CaesarOS-$(arch).bin
iso := build/CaesarOS-$(arch).iso

linker_script := $(arch)/linker.ld
grub_cfg := $(arch)/grub.cfg

assembly_source_files := $(wildcard $(arch)/*.asm)
assembly_object_files := $(patsubst $(arch)/%.asm, \
	build/$(arch)/%.o, $(assembly_source_files))

c_source_files := $(wildcard kernel/*.c)
c_object_files := $(patsubst kernel/%.c, \
	build/$(arch)/%.o, $(c_source_files))

.PHONY: all clean run iso

all: $(kernel)

clean:
	@rm -r build

run: $(iso)
	@qemu-system-x86_64 -serial stdio -cdrom $(iso) -m 8192M

iso: $(iso)

$(iso): $(kernel) $(grub_cfg)
	@mkdir -p build/iso/boot/grub
	@cp $(kernel) build/iso/boot/kernel.bin
	@cp $(grub_cfg) build/iso/boot/grub
	@grub-mkrescue -o $(iso) build/iso 2> /dev/null
	@rm -r build/iso

$(kernel): $(assembly_object_files) $(linker_script) $(c_object_files)
	@ld -n -T $(linker_script) -o $(kernel) $(assembly_object_files) $(c_object_files)

# compile assembly
build/$(arch)/%.o: $(arch)/%.asm
	@mkdir -p $(shell dirname $@)
	@nasm -felf64 $< -o $@

build/$(arch)/%.o: kernel/%.c
	@mkdir -p $(shell dirname $@)
	gcc -m64 -mcmodel=kernel -ffreestanding -nostdlib -mno-red-zone -c $< -o $@