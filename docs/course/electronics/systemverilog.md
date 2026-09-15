# 数字逻辑系统设计：SystemVerilog 语言与核心架构深度复习报告

> 面向《数字设计与计算机体系结构》（Harris & Harris）与课程实验/作业的 SystemVerilog 复习提要。

---

## 1. 绪论：HDL 与数字系统设计

在现代集成电路设计中，硬件描述语言（Hardware Description Language, HDL）已经取代传统原理图输入，成为从算法验证到物理实现的核心工具。

- 原理图方式：直观但难以扩展到百万门级 VLSI。
- HDL 方式：文本化描述硬件结构与行为，便于综合、仿真和版本管理。

**SystemVerilog** 是 Verilog 的超集：

- 被标准化为 IEEE 1800。
- 同时支持 **RTL 设计** 与 **验证**（OOP、约束随机、接口等）。
- 是工业界主流的寄存器传输级（RTL）设计语言之一。

理解 SystemVerilog 的关键是：

- 它描述的是**物理硬件**而不是软件过程。
- 每一行代码都应能在脑中对应到：
    - 逻辑门、多路复用器
    - 触发器 / 寄存器
    - 存储器阵列、连线
- 重点把握 **并发性（concurrency）**：
    - 多个 `always_*`、`assign` 同时存在并并发驱动信号。

本笔记重点围绕三个核心考点：

1. **ALU 及标志位（NZCV）生成逻辑**
2. **多端口寄存器文件（Register File）**
3. **有限状态机（FSM）标准实现方法**

---

## 2. SystemVerilog 语法基础与数据类型

SystemVerilog 对 Verilog 的数据类型系统做了较大增强，核心目标：

- 减少歧义，提高类型检查能力。
- 更贴近硬件语义而不是仿真器实现细节。

### 2.1 基础数据类型：`logic` 的统一与革新

在 Verilog-2001 中：

- `wire`：用于连续赋值（`assign`）、模块端口互连。
- `reg`：用于 `always` 过程块中的赋值。

这实际上是**仿真实现细节**，而非真正的硬件语义来源。

#### 2.1.1 逻辑类型 `logic`

SystemVerilog 引入 `logic` 类型，可在绝大多数场景中替代 `wire` 和 `reg`：

- **硬件语义**：`logic` 本身既不表示“寄存器”也不表示“连线”，
    - 在 `assign` 中驱动时 → 综合为连线（combinational net）。
    - 在 `always_ff` 中赋值 → 综合为触发器（flip-flop）。
    - 在 `always_comb` 中赋值 → 综合为组合逻辑节点。

- **四态逻辑**（4-state）：
    - `0`：逻辑低电平（GND）
    - `1`：逻辑高电平（VCC）
    - `X`：未知态（如未初始化、总线冲突、时序违例）
    - `Z`：高阻态（高阻输出、三态总线）

四态逻辑在仿真中用于暴露问题，综合后物理电路通常只有 0/1 两态（除 I/O 三态）。

#### 2.1.2 有符号与无符号（`signed` vs `unsigned`）

符号属性会影响：

- 比较运算（`<`, `>`, `<=`, `>=`）
- 算术移位
- 某些算术运算的解释

默认：

```systemverilog
logic [3:0] a;   // 默认无符号
```

- `4'b1111` 被解释为无符号 15。

显式有符号：

```systemverilog
logic signed [3:0] b; // 有符号，补码表示
```

- `4'b1111` 被解释为 -1。

**混用规则（易踩坑）：**

- 如果表达式中**有一个操作数是无符号**，整体将按**无符号**处理。
- 在实现带有 `SLT`（有符号比较）等指令时，若不加控制极易出错。

**建议：**

- 进行有符号运算/比较时，显式使用：

```systemverilog
$signed(a) < $signed(b)
```

### 2.2 模块定义与层次化结构 `module`

模块（module）是 SystemVerilog 设计的基本构建块：

- 封装逻辑功能
- 通过端口与外部通信
- 可层次化实例化（模块嵌套）

#### 2.2.1 ANSI 风格端口声明（推荐）

推荐写法：方向、类型、位宽、名称在模块头统一声明。

```systemverilog
module alu (
    input  logic [31:0] a, b,
    input  logic [1:0]  alu_control,
    output logic [31:0] result,
    output logic [3:0]  alu_flags  // N, Z, C, V
);
    // 内部逻辑描述
endmodule
```

相对旧式 Verilog 需要：

1. 先列出端口名列表
2. 再单独声明各端口方向与类型

更繁琐且易出错。

#### 2.2.2 参数化模块 `parameter`

参数化是实现**位宽可配置、结构复用**的关键。

```systemverilog
module mux2 #(
    parameter WIDTH = 8
) (
    input  logic [WIDTH-1:0] d0, d1,
    input  logic             s,
    output logic [WIDTH-1:0] y
);
    assign y = s ? d1 : d0;
endmodule
```

实例化时覆盖参数：

```systemverilog
// 实例化一个 32 位多路复用器
mux2 #(.WIDTH(32)) mux_32bit (
    .d0(data_a),
    .d1(data_b),
    .s (sel),
    .y (out)
);
```

**好处：**

- 同一份代码可支持 8/16/32/64 位 ALU、寄存器文件、比较器等。
- 满足“写一次，复用多处”的工程要求。

---

## 3. 过程块与赋值机制：SystemVerilog 的核心

SystemVerilog 引入了三种**专用可综合 always 块**：

- `always_comb`：组合逻辑
- `always_ff`：触发器 / 时序逻辑
- `always_latch`：锁存器

以及保留的通用 `always`（多用于 testbench）。

明确区分这些过程块，可以：

- 明确设计意图（Design Intent）
- 帮助综合工具和仿真器检查潜在错误

### 3.1 四类 always 块

#### 3.1.1 `always_comb`：组合逻辑

特点：

- 自动推导敏感列表：
    - 不需要 `always @(a or b or c)` 或 `always @(*)`。
    - 工具会自动分析块内读取的所有信号。
- 在仿真时间 0 会执行一次，使输出尽早稳定。
- 如果写法推导出锁存器（某些分支没有赋值），工具会**警告或报错**。

典型用途：

- ALU 逻辑
- 解码器 / 多路复用器
- FSM **次态逻辑**（next-state logic）

#### 3.1.2 `always_ff`：时序逻辑（触发器）

特点：

- 敏感列表必须是**时钟边沿 +（可选）复位**事件：

```systemverilog
always_ff @(posedge clk or posedge reset)
```

- 明确告诉工具：这里一定是触发器。
- 如果没有时钟边沿，工具会报错。

典型用途：

- 寄存器
- 计数器
- **FSM 状态寄存器**
- 流水线寄存器

#### 3.1.3 `always_latch`：锁存器

用途：

- 显式描述电平敏感锁存器。
- 在现代同步设计中通常不推荐使用锁存器，除非为了：
    - 特定低功耗设计
    - 特定接口协议

`always_latch` 明确表明“锁存器是有意设计的”，而不是因为组合逻辑分支遗漏导致的意外锁存。

#### 3.1.4 传统 `always`

- 主要用于 **testbench** 或非综合逻辑（如时钟发生器）。
- 在可综合 RTL 中，推荐只使用：
    - `always_comb`
    - `always_ff`
    - `always_latch`

### 3.2 阻塞赋值 `=` vs 非阻塞赋值 `<=`

这两种赋值语义不同，是很多初学者 BUG 的来源。

#### 3.2.1 阻塞赋值 `=`（通常用于组合逻辑）

- 行为：**立即执行**，下一条语句在当前赋值完成后才执行。
- 对应硬件：逻辑门的级联。
- 推荐只在 `always_comb` 中使用。

```systemverilog
always_comb begin
    t = a & b;  // 先计算 t
    y = t | c;  // 再使用更新后的 t 计算 y
end
```

#### 3.2.2 非阻塞赋值 `<=`（用于触发器）

- 行为：**当前仿真时间步结束时统一更新**。
- 对应硬件：同一时钟边沿上的多个触发器同时采样输入。
- 推荐只在 `always_ff` 中使用。

```systemverilog
always_ff @(posedge clk) begin
    q1 <= d;    // 时钟沿到来时，q1 采样 d 的旧值
    q2 <= q1;   // 同一个时钟沿，q2 采样 q1 的旧值 → 形成移位寄存器
end
```

如果这里误用 `=`，`q2` 会立刻看到 `q1` 的新值，移位寄存器将退化为直通导线，这是典型错误。

---

## 4. 基础操作符与陷阱：`~` 与 `-` 的区别

某些 SystemVerilog 操作符在视觉上相似，但硬件含义完全不同，典型如：

- 按位取反：`~`
- 算术取负：一元减号 `-`

### 4.1 按位取反 `~`

- 定义：bitwise NOT，对每一位单独取反。
- 硬件实现：一组并行的反相器（inverters）。

示例：

- 若 `a = 4'b0101` (十进制 5)，则 `~a = 4'b1010`。
- `4'b1010` 作为：
    - 无符号：10
    - 有符号补码：-6

> 小结：`~a` 得到的是 **反码**（one's complement），还**不是相反数**。

### 4.2 一元减号 `-`（算术取负）

- 定义：`-A` 表示数学意义上的相反数。
- 在二进制补码系统中：

$$
-A = \text{two's complement of } A = \sim A + 1
$$

硬件实现：

- 一组并行反相器 + 一个加法器的 `+1` 逻辑（可以利用加法器的进位输入）。

示例：

- `a = 4'b0101` (5)
- `-a = (~4'b0101) + 1 = 4'b1010 + 1 = 4'b1011`（补码 -5）

### 4.3 ALU 中的常见错误

实现减法时：

- 错误：`result = A + ~B;`（少了 `+1`）
- 正确：
    - `result = A - B;` 或
    - `result = A + ~B + 1;`

在硬件实现中，通常利用加法器的 **进位输入 `Cin`** 来实现这个 `+1`。

---

## 5. 核心考点一：带 NZCV 标志位的 ALU

算术逻辑单元（ALU）是处理器数据通路的核心。本节基于 Harris 架构的一个 32 位 ALU，重点：

- 控制信号 `ALUControl[1:0]`
- 算术/逻辑运算
- NZCV 标志位的生成

### 5.1 `ALUControl` 码表

假设 ALU 接收 2 位控制信号 `ALUControl[1:0]`：

| ALUControl | 功能     | 表达式                      |
|------------|----------|-----------------------------|
| 2'b00      | 加法 ADD | `Y = A + B`                 |
| 2'b01      | 减法 SUB | `Y = A - B`                 |
| 2'b10      | 与 AND   | `Y = A & B`                 |
| 2'b11      | 或 OR    | <code>Y = A &#124; B</code> |

设计上的规律：

- `ALUControl[1] = 0` → 算术运算（ADD/SUB）。
- `ALUControl[1] = 1` → 逻辑运算（AND/OR）。
- `ALUControl == 2'b01` → 减法，需要：
    - `B` 按位取反
    - 加法器 `Cin = 1` 实现 `A + ~B + 1`。

### 5.2 ALU 核心逻辑实现

示例 SystemVerilog 代码（结构化且可综合）：

```systemverilog
module alu (
    input  logic [31:0] a, b,
    input  logic [1:0]  alu_control,
    output logic [31:0] result,
    output logic [3:0]  alu_flags   // {N, Z, C, V}
);

    logic [31:0] cond_inv_b; // 条件取反后的 B
    logic [32:0] sum;        // 33 位保存加法结果及进位
    logic        is_arith;   // 当前是否为算术运算（ADD/SUB）
    logic        is_sub;     // 是否为 SUB

    assign is_arith = (alu_control[1] == 1'b0);   // 00/01 为算术
    assign is_sub   = (alu_control == 2'b01);     // SUB

    // 1. B 操作数预处理
    assign cond_inv_b = is_sub ? ~b : b;

    // 2. 加法器核心
    assign sum = a + cond_inv_b + is_sub;         // SUB 时 Cin = 1

    // 3. 结果多路选择
    always_comb begin
        unique case (alu_control)
            2'b00: result = sum[31:0];   // ADD
            2'b01: result = sum[31:0];   // SUB
            2'b10: result = a & b;       // AND
            2'b11: result = a | b;       // OR
            default: result = 'x;
        endcase
    end

    // 4. 标志位生成（见 5.3）
    logic N, Z, C, V;

    // N: 结果为负（有符号）
    assign N = result[31];

    // Z: 结果为零
    assign Z = (result == 32'b0);

    // C: 进位 / 非借位（仅对算术运算有意义）
    assign C = is_arith ? sum[32] : 1'b0;

    // V: 有符号溢出
    // 对于 ADD/SUB，V = (~(Sa ^ Sb') & (Sa ^ Sr))
    // 其中 Sb' 为送入加法器的第二操作数 cond_inv_b
    assign V = is_arith
             ? ( ~(a[31] ^ cond_inv_b[31]) & (a[31] ^ result[31]) )
             : 1'b0;

    assign alu_flags = {N, Z, C, V};

endmodule
```

> 上面代码修正了常见的教学笔误：
>
> - 只在算术操作时使用加法器的 `sum` 及其进位 `sum[32]`。
> - 将 NZCV 拆分为单独逻辑，再统一打包到 `alu_flags`。

### 5.3 NZCV 标志位详解

NZCV 标志用于：

- 条件跳转（如 BEQ、BLT、BGE 等）
- 某些条件执行指令

#### 5.3.1 N（Negative）—— 负号标志

- 含义：将结果视为**有符号数**时是否为负数。
- 实现：

```systemverilog
N = result[31];
```

#### 5.3.2 Z（Zero）—— 零标志

- 含义：结果是否为 0。
- 实现等价写法：

```systemverilog
Z = (result == 32'b0);
// 或
Z = ~(|result);   // 归约或后取反
```

#### 5.3.3 C（Carry）—— 进位 / 非借位标志

对 **ARM / Harris 架构**（注意和 x86 的差别）：

- 加法 `A + B`：
    - 若最高位产生进位（无符号溢出） → `C = 1`。
- 减法 `A - B`：
    - 实现为 `A + ~B + 1`。
    - 若 `A >= B`（无借位） → 加法器会产生进位 `Cout = 1`。
    - 若 `A < B`（需要借位） → `Cout = 0`。

> 结论：在该体系中，`C = 1` 表示 **“无借位（Not Borrow）”**，
> 而不是“有借位”！这与 x86 恰好相反，需要特别记住。

对逻辑运算（AND/OR）：

- C 常被设为 0 或保持旧值。
- 在简单课程 ALU 中通常直接置 0。

实现：

```systemverilog
C = is_arith ? sum[32] : 1'b0;
```

#### 5.3.4 V（Overflow）—— 有符号溢出标志

有符号溢出仅在：

- 输入操作数符号相同
- 结果符号与输入相反

时发生。

设：

- `Sa = a[31]`，
- `Sb' = cond_inv_b[31]`（经过取反/不取反后进入加法器的第二操作数），
- `Sr = result[31]`。

溢出条件：

$$
V = \neg(S_a \oplus S_{b'}) \land (S_a \oplus S_r)
$$

SystemVerilog 实现：

```systemverilog
V = is_arith
  ? ( ~(a[31] ^ cond_inv_b[31]) & (a[31] ^ result[31]) )
  : 1'b0;
```

> 注：另一种等价写法是使用最高位进位的“进位入 / 进位出”判断，但行为级代码中使用符号位关系更直观。

---

## 6. 核心考点二：多端口寄存器文件（Register File）

寄存器文件是 CPU 内部用于暂存操作数的高速存储器阵列。

典型单周期 CPU 需要：

- **两个并发读端口**（用于 A、B 源操作数）
- **一个并发写端口**（用于写回结果）

### 6.1 端口命名与含义

读端口（Read Ports）：

- `A1`：读地址 1（源寄存器 1，类似 MIPS `rs`）
- `RD1`：读数据 1
- `A2`：读地址 2（源寄存器 2，类似 MIPS `rt`）
- `RD2`：读数据 2

特点：

- **组合逻辑读**（异步读）：
    - 地址一旦变化，读数据在组合延迟后立即更新。
    - 无需等待时钟边沿。

写端口（Write Port）：

- `A3`：写地址 3（目标寄存器 rd）
- `WD3`：写数据 3
- `WE3`：写使能，高电平有效

特点：

- **时序写**（同步写）：
    - 在 `posedge clk` 时刻并且 `WE3 = 1` 时写入。

### 6.2 SystemVerilog 实现

示例：16 × 32 位寄存器文件，2 读 1 写端口。

```systemverilog
module regfile (
    input  logic        clk,
    input  logic        we3,
    input  logic [3:0]  a1, a2, a3, // 4 位地址 → 16 个寄存器
    input  logic [31:0] wd3,
    output logic [31:0] rd1, rd2
);

    // 16 个 32 位通用寄存器
    logic [31:0] rf [15:0];

    // 同步写：posedge clk
    always_ff @(posedge clk) begin
        if (we3)
            rf[a3] <= wd3;
    end

    // 组合读：异步输出
    assign rd1 = rf[a1];
    assign rd2 = rf[a2];

endmodule
```

> 注意：
>
> - 在 MIPS / RISC-V 中通常要求寄存器 x0 恒为 0，可写作：
>     - `assign rd1 = (a1 != 0) ? rf[a1] : 32'b0;`
>     - 同理对 `rd2` 处理。

---

## 7. 核心考点三：有限状态机（FSM）实现

控制单元常用有限状态机（FSM）来产生时序控制信号。

SystemVerilog 通过 `enum`（枚举类型）极大简化了 FSM 编码。

### 7.1 “抄状态图法”（Copy State Transition Diagram）

推荐流程：

1. 先画清楚状态转换图（状态节点 + 箭头 + 输入条件）。
2. 按图直接翻译成 `case` 语句，不做人工卡诺图化简。
3. 用两段式或三段式写法，清晰分离：
    - 状态寄存器（时序逻辑）
    - 次态逻辑（组合逻辑）
    - 输出逻辑（组合逻辑）

### 7.2 示例：三态 FSM

假设：

- 状态：`S0`, `S1`, `S2`
- 输入：`a`
- 输出：`y`

#### 第一步：状态类型定义

```systemverilog
typedef enum logic [1:0] {S0, S1, S2} statetype;

statetype state, nextstate;
```

#### 第二步：状态寄存器（时序逻辑）

```systemverilog
always_ff @(posedge clk or posedge reset) begin
    if (reset)
        state <= S0;
    else
        state <= nextstate;
end
```

#### 第三步：次态逻辑（组合逻辑）

```systemverilog
always_comb begin
    unique case (state)
        S0: if (a) nextstate = S1;
            else   nextstate = S0;

        S1:       nextstate = S2;  // 无条件转移

        S2: if (a) nextstate = S0;
            else   nextstate = S1;

        default:  nextstate = S0;  // 防御性编程
    endcase
end
```

#### 第四步：输出逻辑（Moore / Mealy）

- **Moore 型**：只依赖状态。

```systemverilog
assign y = (state == S2);
```

- **Mealy 型**：依赖状态 + 输入。

```systemverilog
assign y = (state == S1) & a;
```

---

## 8. 验证与仿真：Testbench 编写

Testbench 是验证 RTL 设计正确性的关键工具：

- 自己本身也是一个模块
- 一般**没有端口**，只在内部：
    - 产生时钟和复位
    - 产生激励信号
    - 实例化 DUT（Device Under Test）
    - 比对期望结果并打印日志

### 8.1 基础结构

示例：ALU 的简单自检 testbench。

```systemverilog
module testbench;

    logic        clk, reset;
    logic [31:0] a, b;
    logic [31:0] result;
    logic [31:0] result_expected;
    logic [1:0]  control;
    logic [3:0]  flags;

    // 实例化 DUT
    alu dut (
        .a          (a),
        .b          (b),
        .alu_control(control),
        .result     (result),
        .alu_flags  (flags)
    );

    // 时钟生成：10ns 周期
    always begin
        clk = 1; #5;
        clk = 0; #5;
    end

    initial begin
        // 1. 初始化
        reset = 1; a = 0; b = 0; control = 2'b00;
        #20;  // 等待一段时间
        reset = 0;

        // 2. 用例 1：2 + 3 = 5
        a = 32'd2;
        b = 32'd3;
        control = 2'b00;   // ADD
        #10;               // 等待组合逻辑与一次时钟

        if (result !== 32'd5)
            $display("Error: 2+3 failed. Got %0d", result);
        else
            $display("Pass: 2+3 = 5");

        // 3. 用例 2：10 - 5 = 5
        a = 32'd10;
        b = 32'd5;
        control = 2'b01;   // SUB
        #10;

        if (result !== 32'd5)
            $display("Error: 10-5 failed. Got %0d", result);

        $stop; // 停止仿真
    end

endmodule
```

> 注意：
>
> - Testbench 中可以使用 `initial`、`#delay`、`$display` 等非综合语句。
> - Testbench 不会被综合成硬件，只用于仿真验证。

### 8.2 基于测试向量文件的自检

对复杂 ALU / CPU：

- 手写几十个用例远远不够。
- 通常使用外部文件（如 `.tv` / `.mem` / `.hex`）：
    - 每一行是一组测试向量
    - 包含输入（A, B, Control）和期望输出（Result, Flags）

核心 SystemVerilog 系统任务：

```systemverilog
$readmemh("alu.tv", tv_array);   // 按十六进制读取
$readmemb("alu.tv", tv_array);   // 按二进制读取
```

然后在 `always @(posedge clk)` 或 `initial` 中循环遍历测试向量、自动比较并打印通过/失败信息。这种方式称为 **基于向量的自检测试**，是工业界常见的验证模式。

---

## 9. 总结与复习建议

通过本笔记，应重点掌握：

- **类型与过程块**：
    - `logic` 四态类型与 `signed`/`unsigned` 区别
    - `always_comb` / `always_ff` / `always_latch` 的使用原则
    - 阻塞 `=` 与非阻塞 `<=` 的使用场景

- **ALU 与标志位**：
    - 补码运算本质：减法 `A - B = A + ~B + 1`
    - `Cin` 的用法与 `ALUControl` 编码
    - NZCV 各标志位的定义与硬件实现，尤其是：
        - `C` 在减法中表示“无借位”
        - `V` 的溢出条件（符号位关系）

- **寄存器文件**：
    - 组合读 & 时序写
    - 多端口结构（2 读 1 写）
    - 特殊寄存器（如 x0 恒为 0）的处理技巧

- **FSM 实现**：
    - 使用 `enum` 编写状态机
    - 两段式（状态寄存器 + 次态逻辑）或三段式风格
    - 直接“抄状态图”，避免人为化简错误

- **验证与仿真**：
    - 会写简单的 self-checking testbench
    - 会使用 `$readmemh` 等读入测试向量

> 建议复习方式：
>
> 1. 对着本笔记，在纸上画出 ALU / 寄存器文件 / FSM 结构。
> 2. 尝试独立从零写出：
>     - 一个带 NZCV 的 32 位 ALU
>     - 一个 2R1W 寄存器文件
>     - 一个简单的 Moore FSM
> 3. 再为每个模块写一个最小可用的 testbench 并在仿真器中跑通。

这样可以在考试与后续处理器设计课程中对 SystemVerilog 用得更加熟练。
