# 【虚幻引擎一起学！】2D游戏开发基础篇

## [Let's Learn Unreal Together!] Paper2D Basic For 2D Game Development

![""](Images/Cover.png)

## 【项目学习中】

---

本项目学习的是虚幻引擎的Paper2D以及PaperZD拓展插件的功能。

阿严将在学习过程中尝试将教程里大部分的蓝图逻辑转成C++，并实现C++和蓝图之间较好的通信。

本项目的主要学习目的在于为在虚幻引擎上开发2D游戏（或者2D混合3D游戏）打下坚实的基础。

---

- 本项目GitHub仓库：<https://github.com/AtCloudStudio/LetsLearnUnrealEngineTogether_Paper2DBasic>

---

- 本项目所学习的教程播放列表：<https://youtube.com/playlist?list=PLNBX4kIrA68n7ztrn7CV_SRBDcEGnPCNp&si=MyPdZO6gSX5PG2UT>

---

- 阿严的YouTube频道：<https://www.youtube.com/@RYanIndieDev/channels>
- 阿严的B站主页：<https://space.bilibili.com/27164588/>

---

【帮助我走得更远，阿严需要你的赞助】

- Patreon: <https://www.patreon.com/RYanIndieDev>
- 爱发电：<https://afdian.net/a/RYanIndieDev>

---

【Ep.01】

- 直播时间：2023年10月04日
- YouTube: <https://youtube.com/live/qUbLqcdjT-c>
- Bilibili: <https://www.bilibili.com/video/BV1ZC4y1L7LL>

主要内容：

1. 新项目的创建和编辑器偏好设置
2. 导入精灵图(Sprite)
3. 如何在虚幻引擎里切割精灵表(Sprite Sheet)
4. 如何在虚幻引擎里创建2D动画(Paper Flipbook)
5. 初识PaperZD插件
6. 动画源文件(Animation Source)以及动画序列文件(Animation Sequence)
7. 2D动画蓝图：PaperZD Anim Blueprint
8. 创建基于PaperZDCharacter的C++角色类
9. C++源码添加2D开发依赖模组(Dependency Module)
10. 适合2D开发的项目设置
11. 给Sprite设置受光材质(Lit)并开启投影(Cast Shadow)
12. 给角色添加相机伸缩臂组件(SpringArmComponent)以及相机组件(CameraComponent)
13. 角色空闲(Idle)状态与跑步(Run)状态的切换
14. BlueprintPure的功能
15. 创建增强输入(EnhancedInput)相关文件
16. 角色的移动输入
17. 实现角色的移动(Debug环节)
18. 显示编辑器帧数与内存使用

---

【Ep.02】

- 直播时间：2023年10月05日
- YouTube: <https://youtube.com/live/YK9qkoUK0PA>
- Bilibili: <https://www.bilibili.com/video/BV1V8411k7mv>

主要内容：

1. 实现角色的转向
2. 将角色的设置参数写入C++源码
3. 实现角色的跳跃
4. 添加跳跃时的动画状态
5. 角色落地时的逻辑处理
6. 添加落地时的动画状态
7. 调整角色的跳跃手感
8. 角色下蹲的逻辑
9. 添加角色下蹲时的动画状态

---

【Ep.03】

- 直播时间：2023年10月06日
- YouTube: <https://youtube.com/live/9Af0NR8xl3w>
- Bilibili: <>

主要内容：

1. 解决角色下蹲时精灵组件(Sprite Component)的偏移
2. 解决下蹲动画的BUG
3. 实现下蹲时角色的左右转向
4. 滑行(Slide)时的逻辑
5. 添加滑行时的动画状态
6. 检测滑行时头顶是不是有墙壁
7. BlueprintImplementableEvent的作用：函数在C++里声明并可调用，但在蓝图里实现
8. 实现角色的滑行
