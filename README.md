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
- Bilibili: <https://www.bilibili.com/video/BV1YG411m7rD>

主要内容：

1. 解决角色下蹲时精灵组件(Sprite Component)的偏移
2. 解决下蹲动画的BUG
3. 实现下蹲时角色的左右转向
4. 滑行(Slide)时的逻辑
5. 添加滑行时的动画状态
6. 检测滑行时头顶是不是有墙壁
7. BlueprintImplementableEvent的作用：函数在C++里声明并可调用，但在蓝图里实现
8. 实现角色的滑行

---

【Ep.04】

- 直播时间：2023年10月07日
- YouTube: <https://youtube.com/live/Sn2RV07IJL0>
- Bilibili: <https://www.bilibili.com/video/BV1Y84y117SD>

主要内容：

1. 检测下蹲时的输入状态，解决下蹲时偶尔不会恢复到正常状态的BUG
2. 解决动画蓝图蜘蛛网的大杀器：跳转节点JumpNode
3. 跳转到Fall状态
4. 跳转节点的逻辑(蓝图与C++)
5. 跳转到蹲下状态
6. 跳转到跳起状态
7. 阿严是如何学习的·其一：如何获取有用的信息(ChatGPT与官方社区)
8. 如何在虚幻引擎里声明委托(Delegate)
9. 如何使用自定义委托

---

【Ep.05】

- 直播时间：2023年10月09日
- YouTube: <https://youtube.com/live/xY8J9x9Ny6g>
- Bilibili: <https://www.bilibili.com/video/BV1qw411y7Gx>

主要内容：

1. 使用动画播放器(PaperZD Player)的播放进度(Progress)来判断动画是否播放完毕
2. 初识动画通知AnimNotify
3. PaperZD的动画资源(AnimationSource)于AnimInstance的关系
4. 如何使用动画通知
5. 如何获取游戏资产(官方商城/免费资源网站)
6. 使用动画通知来播放脚步声
7. 初识MetaSound
8. 动画通知状态(AnimNotifyState)
9. PaperZD特有的动画通知(PaperZDAnimNotify与PaperZDAnimNotifyState)
10. 如何创建并使用自定义动画通知(蓝图和C++)
11. 使用动画通知与跳转节点重构动画状态机

---

【Ep.06】

- 直播时间：2023年10月10日
- YouTube: <https://youtube.com/live/GpESkySRl7g>
- Bilibili: <https://www.bilibili.com/video/BV1qC4y157zi>
- 本期后半部分由于疏忽，忘记开麦克风了，因此没有录到阿严解说的声音 T_T

主要内容：

1. 使用#pragma region和#pragma endregion为代码分区
2. 制作角色攻击动作动画
3. 攻击的输入和逻辑
4. 虚幻引擎里如何在游戏开始时隐藏鼠标光标并聚焦到游戏窗口
5. 创建自定义玩家控制器
6. 创建命中框(HitBox)动画通知（蓝图与C++）
7. 虚幻引擎里如何实现HitBox检测(蓝图)：BoxOverlapActors节点
8. 关于虚幻引擎的C++编译环境
9. Sprite的插口(Socket)
10. 利用插口的位置偏移来实现HitBox的位移
11. 虚幻引擎里如何实现HitBox检测(C++)：OverlapMultiByChannel函数

---

【Ep.07】

- 直播时间：2023年10月11日
- YouTube: <https://youtube.com/live/L4uZ9rL1n1k>
- Bilibili: <https://www.bilibili.com/video/BV1k84y117mP>

主要内容：

1. 解决连续按下攻击键时会不断触发攻击动画的问题
2. 限制角色可以进行攻击的时机
3. Bug修复时间：修复滑行时不触发滑行动画的问题
4. 创建角色基类(CharacterBase)：玩家与所有敌人角色的父类
5. 角色基类的作用：持有所有角色共有的功能函数、字段与委托等数据
6. 声明角色攻击命中时的委托(FAttackHit)，当HitBox检测成功时调用这个委托
7. HitBox动画通知类里的代码重构与Debug功能增加
8. 实现简单的连段攻击(Combo Attacks)

---

【Ep.08】

- 直播时间：2023年10月12日
- YouTube: <https://youtube.com/live/p8QqcJVkPi4>
- Bilibili: <https://www.bilibili.com/video/BV1bu411K7ih>

主要内容：

1. 跳跃攻击的简单实现
2. 制作蓄力攻击(Charge Attack)三个阶段的动画(Pre-Charge, Charging, Release);
3. 蓄力攻击的逻辑和动画调用
4. 初始虚幻引擎的新粒子系统Niagara System
5. Niagara粒子系统的工作原理和基础模块
6. 制作蓄力攻击的粒子特效
7. PaperZD动画状态的回调事件(进入状态/离开状态)
8. 给蓄力攻击动画添加粒子效果（蓝图逻辑与C++源码）

---

【Ep.09】

- 直播时间：2023年10月13日
- YouTube: <https://youtube.com/live/eYBqefb9feQ>
- Bilibili: <https://www.bilibili.com/video/BV14j411x7Jg>

主要内容：

1. 使用状态机实现灵活的攻击连段系统(Combo Attacks System)
2. 蓝图接口(Blueprint Interface)
3. 虚幻引擎的枚举类型蓝图(Enumeration Blueprint)
4. 虚幻引擎的Gameplay Tags
5. 使用Gameplay Tags来取代Boolean Flags进行条件判断
6. 攻击连段系统的实现(蓝图逻辑，未成功)

---

【Ep.10】

- 直播时间：2023年10月14日
- YouTube: <https://youtube.com/live/w1RmBcdk9M0>
- Bilibili: <https://www.bilibili.com/video/BV1Vu411T7Am>

主要内容：

1. 给玩家角色添加连招组件(Combo Component)
2. 在连招组件中实现连招系统(C++结合蓝图)
3. 如何在虚幻引擎的C++源码里声明蓝图可调用的枚举类型
4. 如何在蓝图里绑定C++声明的动态多播委托
5. 阿严的代码编写习惯：函数封装 - 将片段性功能逻辑封装成一个个方便阅读的函数
6. 代码重构与Bug修复

---

【Ep.11】

- 直播时间：2023年10月16日
- YouTube: <https://youtube.com/live/P1dNPuqcfC8>
- Bilibili: <https://www.bilibili.com/video/BV1P84y1d7r4>

主要内容：

1. 实现玩家的冲刺(Dash)功能
2. 实现玩家的冲刺攻击(Dash Attack)功能
3. 虚幻引擎如何限制玩家只能在某个轴向移动 - 平面移动Planar Movement
4. 滑墙(Wall Slide)检测
5. 实现玩家的滑墙功能

---

【Ep.12】

- 直播时间：2023年10月17日
- YouTube: <https://youtube.com/live/xMMywpzX7ic>
- Bilibili: <https://www.bilibili.com/video/BV17y4y1K7Dr>

主要内容：

1. 冲刺功能的修正与改进
2. 虚幻引擎中给角色施加力的几种方法
3. 滑墙动画的改进
4. 实现蹬墙跳(Wall Jump)
5. 如何防止玩家在地面移动时掉下悬崖
6. 学习时如何获取有用的信息 - 官方文档
7. 创建敌人角色死亡使者(Bringer Of Death)
8. PaperZD的PlayAnimationOverride（类似3D动画里Montage的功能）
9. 简单实现角色受伤时的效果(受伤动画)

---

【Ep.13】

- 直播时间：2023年10月17日
- YouTube: <https://youtube.com/live/GFgtB6GtL1c>
- Bilibili: <https://www.bilibili.com/video/BV1ww411X7rr>

主要内容：

1. 什么是命中停顿(Hit Stop)
2. 关于樱井政博以及他的游戏开发知识频道
3. 如何在虚幻引擎里实现命中停顿
4. 虚幻引擎的时间膨胀(Time Dilation)与帧间隔时间(Delta Seconds)
5. 什么是命中震动(Hit Shake)
6. 在虚幻引擎里实现命中震动的几种方法
7. 初识虚幻引擎的材质编辑器(Material Editor)
8. 材质与材质实例的关系(Material &. Material Instance)
9. 让材质UV产生偏移
10. 正弦波(Sine)材质节点的应用
11. 如何实时地切换材质
12. 如何在虚幻引擎里实现命中震动
13. 添加攻击命中时的屏幕震动
14. 什么是数据资产(Data Asset)：虚幻引擎的ScriptableObject
15. 创建攻击数据类(AttackData)：角色攻击数据的容器
16. 攻击数据的使用：让角色的每一段攻击都有自己独立的数据
