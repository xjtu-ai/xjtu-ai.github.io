/*
 * MathJax 配置，以及和「即时加载」（theme.features 里的 navigation.instant）的适配。
 *
 * 两个关键点，改动前请先看这里：
 *
 * 1. 本文件必须排在 extra_javascript 中 MathJax 本体之前。
 *    MathJax 在脚本执行时读取 window.MathJax；配置写在加载之后不但不生效，
 *    还会把 MathJax.startup / MathJax.typesetPromise 等 API 覆盖掉。
 *
 * 2. navigation.instant 只替换页面内容，不会重新加载页面，MathJax 不会自己重新排版。
 *    因此要订阅 Material 的 document$，在每次内容替换后重新排版。
 *    少了这段订阅，从左侧目录点开的页面就会一直显示 \(...\) 原文，必须手动刷新。
 */
window.MathJax = {
  tex: {
    // 公式编号（\tag、\label / \eqref 等）
    tags: "ams",
    packages: { "[+]": ["ams", "boldsymbol"] },
    inlineMath: [["\\(", "\\)"], ["$", "$"]],
    displayMath: [["\\[", "\\]"], ["$$", "$$"]],
    processEscapes: true,
    processEnvironments: true,
  },
  options: {
    // 只排版 pymdownx.arithmatex (generic: true) 生成的 .arithmatex 元素，
    // 避免正文里偶然出现的 $ 被当作公式起始符。
    ignoreHtmlClass: ".*|",
    processHtmlClass: "arithmatex",
  },
};

// document$ 由 Material 主题挂到 window 上（assets/javascripts/bundle.*.js），
// 初始加载和每次即时加载完成后都会推送一次当前文档。
document$.subscribe(() => {
  // MathJax.startup.output 要等 loader 就绪、本体完成初始化后才有。
  // 首屏若还没就绪，交给 MathJax 自己的 startup 排版即可，这里跳过。
  if (!window.MathJax?.startup?.output) return;
  MathJax.startup.output.clearCache();
  MathJax.typesetClear();
  MathJax.texReset();
  MathJax.typesetPromise();
});
