# 学校线上讲座脚本说明与修改记录

## 概述
本仓库包含学校线上讲座页面的前端代码。本 README 说明：原程序为何在失焦时暂停、为何禁止快进、它是如何检测用户行为的，以及我们如何修改使其“失焦不暂停并允许快进”。

> 重要说明：以下描述的是对页面前端脚本的分析与临时修改方法，仅用于学习/调试目的。请遵守学校和平台的使用规范与法律法规。

---

## 原程序行为（回顾）
- 失焦暂停：页面注册了 `window.onblur` 事件处理器，处理器内部调用 `video.pause()`，因此当用户切换到其它标签或窗口（窗口失焦）时视频被暂停。
- 禁止快进：页面通过一个短周期的 `setInterval`（约 500ms）不断读取 `video.currentTime` 并与先前记录的时间比较；若发现当前位置比上一次突然“跳跃”超过阈值，则把 `currentTime` 回退到之前的记录（或上次上报的时间），从而阻断用户通过拖动进度条或直接跳转来快进。
- 进度上报：另有一个较长周期的 `setInterval`（约 10000ms），用于按规则把播放进度通过 AJAX POST 发送到服务器（接口 `/study/online/selection`），以记录学习进度。

## 为什么会“失焦就暂停”
代码里类似：

```js
window.onblur = function() {
  var video = document.querySelector('#video');
  video.pause(); // 当窗口失焦时暂停
}
```

浏览器在切换标签或窗口时会触发 `onblur`（或 `visibilitychange`）；原开发者利用该事件强制在离开页面时暂停播放，目的是“检测并阻止离开课堂”的一种简单客户端策略。

## 禁止快进的检测机制详解
原代码的核心检测逻辑包含几部分变量和定时器：
- `sym`：在每次 500ms 检查循环结束时，保存当时的 `video.currentTime`（作为“上一次时间快照”）。
- `lastTime`：代表上次被认为合法并上报到服务器的时间（通常初始化为课程允许的起始时间）。

500ms 的检测逻辑（伪代码）：

```js
setInterval(function() {
  var time = video.currentTime;
  if (time - sym > 1 && time > lastTime + 1) {
    // 检测到播放时间瞬间跳跃（可能是用户快进）
    if (sym < lastTime) {
      video.currentTime = lastTime;
    } else {
      video.currentTime = sym;
    }
  }
  sym = video.currentTime;
}, 500);
```

判断思路：若当前时间 `time` 与上一次快照 `sym` 差值很大（>1s），且当前时间大于 `lastTime + 1`（即比已上报的时间明显前进），则认为发生了用户拖动或快进，于是把 `currentTime` 回退到 `sym` 或 `lastTime`。

另外 10s 的上报逻辑会检查 `time - sym < 1 && time > lastTime + 1`（即在没有拖动的情况下有正常进展且超过上次上报），则发送 AJAX 上报并更新 `lastTime`。这两个检测配合起来既上报正常播放进度，又尽量阻止异常跳跃。

### 该机制的意图与弱点
- 意图：防止用户通过快进来跳过视频并虚假记录学习时长；同时尽量只在“自然播放”时上报。
- 弱点：机制完全基于客户端 JavaScript，任何能执行控制台命令的用户都可以绕过（移除 handler、清除 interval、修改变量）。另外玩家在网络缓冲、跳跃回退或播放器自身行为下也可能误判导致回退。

## 我们如何修改以“允许失焦继续播放并允许快进”
在已经修改的版本中，我们做了两项主要改动：

1. 注释/移除 `window.onblur` 中的 `video.pause()`，使窗口失焦时视频不再自动暂停。示例修改：

```js
// 原：
// window.onblur = function() { video.pause(); }

// 修改为（注释掉处理器）：
// window.onblur = function() { /* video.pause(); */ }
window.onblur = null; // 或直接置空
```

2. 删除/替换 500ms 的“禁止快进”回退逻辑，改为仅保留每 10 秒对当前播放时间的上报（若时间比上次上报大则上报）。即允许用户自由 seek/快进，但仍周期性上报最新播放位置：

```js
var lastTime = 5; // 初始记录值
var video = document.querySelector('#video');
setInterval(function() {
  var time = Math.trunc(video.currentTime || 0);
  if (time > lastTime) {
    // 上报到后端
    $.ajax({ url: '/study/online/selection', type: 'post', data: { scheduleId: $('#scheduleId').val(), time: time, alltime: Math.trunc(video.duration) }});
    lastTime = time;
  }
}, 10000);
```

这样：
- 用户切换标签后不会被暂停；
- 用户可以拖动进度条或快进；
- 平台仍能以 10 秒为单位获取当前播放时间（注意：服务器可能会有额外校验）。

## 如何在浏览器 DevTools（F12）临时实现（快速方法）
在实际页面上，你可以直接打开控制台（Console）粘贴下列脚本来临时生效（刷新后失效）：

- 最温和的做法（仅移除 onblur）

```js
// 只禁止失焦暂停
window.onblur = function(){};
```

- 如果页面注册了禁止快进的 interval 且你想移除它（冒险）：

```js
// 清除所有 interval（会影响页面上其他定时器，谨慎）
let highest = window.setInterval(()=>{}, 1000);
for (let i = 1; i <= highest; i++) window.clearInterval(i);

// （可选）恢复简单的每 10s 上报脚本：
(function(){
  let video = document.querySelector('#video');
  if(!video) return;
  let lastTime = Math.trunc(video.currentTime || 0);
  window.setInterval(function(){
    let t = Math.trunc(video.currentTime || 0);
    if(t > lastTime){
      fetch('/study/online/selection',{
        method: 'POST',
        headers: {'Content-Type':'application/x-www-form-urlencoded'},
        body: 'scheduleId=' + encodeURIComponent((document.getElementById('scheduleId')||{}).value || '') + '&time=' + t + '&alltime=' + Math.trunc(video.duration || 0)
      }).catch(()=>{});
      lastTime = t;
    }
  }, 10000);
})();
```

> 提示：更安全的做法是只把 `window.onblur` 置空（避免清除页面其他重要定时器）。

## 测试步骤
1. 打开页面并开始播放视频。  
2. 切换到其它标签或窗口，确认视频继续播放（若失焦仍暂停，可能没有成功移除 handler）。  
3. 在进度条上拖动快进，确认可以跳转到目标位置。  
4. 在 DevTools 的 Network 面板中观察对 `/study/online/selection` 的 POST 请求（若保留上报脚本），确认 `time` 参数按预期上报。

## 合规与安全提醒
- 这些修改仅改变你本地浏览器对页面的行为，不会改变服务器端逻辑或其他用户的体验。若平台在服务器端对进度存在更严格的校验（例如检测不合理速率、IP/会话绑定、证书/token 校验等），客户端修改不能伪造真实合法记录。  
- 请在合规、道德和学校规定允许的前提下使用这些技巧。若你是学习/调试目的，建议和平台管理员沟通获取正式权限或开发测试环境。
