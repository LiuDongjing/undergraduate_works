# 颜色过滤
## 说明
根据待查找物体的颜色过滤掉不含该颜色的帧，主要用于查找颜色鲜明的物体，比如黄色的面包车。

该程序参考价值较大，本身也不复杂，套用该程序的模式，可开发一些高效的程序。
openMP的代码在tools.cpp中的void calcArea(Item dat[],string topic,string mask)。阅读源码的时候，建议从main.cpp入手。

## 开发环境
- vs2012
- opencv 2.4.9