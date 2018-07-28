一、工程说明：
此工程是参考下一代基站，搭建了一个小的在linux环境测试代码的工程。
目录：mycodeLIB/codeLIB 存放我们自己的代码
目录：mycodeLIB/main    存放主函数所在的源文件
目录：mycodeLIB/build   存放外部库，比如平台的pub库

二、如何编译
1.在mycodeLIB/codeLIB/目录下，make，生成mycode.a
2.在mycodeLIB/main/目录下，make，生成可执行程序linux_mycode_1.0.0.1_t

三、如何添加新的文件
测试代码文件，请添加到mycodeLIB/codeLIB/test目录下，makefile无需改动。
功能性代码文件，请添加到mycodeLIB/codeLIB/core目录下，makefile无需改动。

四、如何添加外部库
将外部库的.a放到mycodeLIB/build目录，然后在mycodeLIB/main/目录下的makefile中"#other module"处添加新的外部库的名称。
目前build下已经添加了一个平台的pub库。