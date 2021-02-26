FileLog:  保证数据一定能持久化，保证数据完整性。

QuickFileLog: 日志先写入缓存，写满再写入文件，保证高效。可能会有数据丢失。

ConsoleLog: 控制台的日志。




设计参考:  
      1  https://blog.csdn.net/tjw316248269/article/details/105155724/   控制台日志颜色，格式  
	  2  https://zhuanlan.zhihu.com/p/100082717                        日系系统开发方案  
	  3  https://blog.csdn.net/devvs/article/details/48765911          设置控制台颜色  
	  4  https://www.jianshu.com/p/52b274e50371                        毫秒级时间  


