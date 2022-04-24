运行A,写入数据(A会卡在getchar,请不要动), 再运行B,读取数据
如果A运行结束后,再运行B会报错,因为A已经释放FileMapping对象,B就无法打开

把Test.txt 拖入UltraEdit观察十六进制的变化,看看有没有写入和读取正确

观察Test.txt文件的前后的变化
