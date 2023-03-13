# 银行管理系统
#### 文件功能
* date.h  日期类头文件
* date.cpp 日期类实现文件
* account.h  储蓄账户类定义头文件
* account.cpp 储蓄类账户类实现文件
* main.cpp   主函数文件
* Array.h 数组模版的头文件
* Controller类保存账户列表，当前日期和处理指定命令

#### 实现功能
* 类SavingsAccount
	* 成员数据:活期储备账户:账户id,余额balance，年利率rate
	* 函数成员:显示账户信息show,存款deposit,取款withdraw，结算利息settle,
	* total:总金额，static
	* 信用账户，使用类的继承


#### 数据保存思路:
* 可以在程序结束时将每个账户的当前状态和国王的账户写入文件
* 或者将用户输入的存款，取款，结算等各种命令保存下来，下次启动程序再将这些命令读出来执行


#### 参考资料
* C++学习过程中，练习巩固
* 参考书籍:《C++语言程序设计》
* [B站郑莉课堂](https://www.bilibili.com/video/BV17v411w78t/?spm_id_from=333.788&vd_source=bbdb06e93493e220b071abdb0bda65f5)[^1]


[^1]:https://www.bilibili.com/video/BV17v411w78t/?spm_id_from=333.788&vd_source=bbdb06e93493e220b071abdb0bda65f5
