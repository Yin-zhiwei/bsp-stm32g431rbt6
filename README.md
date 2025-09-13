##### 新建了一个STM32G431RBT6的项目工程

包含了如下内容：

- 工程是由STM32CubeMX进行配置生成的；
- 使用GCC编译器（v10.3）进行编译；
- 通过Makefile脚本来配置编译项，添加需要编译的源文件(.c)和头文件(.h)；
- 使用了Ozone工具（软件）和 Jlink调试器（硬件）进行下载和debug调试。

> 推荐主打：VSCode+GCC+Makefile+Ozone+Jlink 进行编辑代码、编译工程、下载调试。
