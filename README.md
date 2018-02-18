## yunshu php扩展 - php扩展学习

### 安装扩展

```
    $ git clone   
    $ git clone https://github.com/yunshu2009/yunshu 
    $ cd yunshu
    $ phpize
    $ ./configure
    $ make && make install
```

2. 在php.ini最后添加

 ```
 [yunshu]
 extension = yunshu.so
```
3. 重启php-fpm

```
service php-fpm restart
```

4. 测试扩展
在命令行下测试

```
php -m|grep yunshu
```


### 参考
1. [信海龙的博客](http://www.bo56.com/)
2. [PHP7内核剖析](https://github.com/pangudashu/php7-internal)