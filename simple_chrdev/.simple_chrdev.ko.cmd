cmd_/home/odmen/kernel_modules/simple_chrdev/simple_chrdev.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000 -T ./scripts/module-common.lds --build-id  -o /home/odmen/kernel_modules/simple_chrdev/simple_chrdev.ko /home/odmen/kernel_modules/simple_chrdev/simple_chrdev.o /home/odmen/kernel_modules/simple_chrdev/simple_chrdev.mod.o