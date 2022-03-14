// main 函数，它是很多程序的入口点。你也见过 fn 关键字，它用来声明新函数。
fn main() {
    say_hello();
    say("Hello Rust");
    another_function(5, 6);

    let x = five();
    println!("This value of x is: {}", x);
    let x = plus_one(x);
    println!("This value of x is: {}", x);
}

// Rust 代码中的函数和变量名使用 snake case 规范风格。
// 在 snake case 中，所有字母都是小写并使用下划线分隔单词。
// Rust 中的函数定义以 fn 开始并在函数名后跟一对圆括号。大括号告诉编译器哪里是函数体的开始和结尾。
fn say_hello() {
    println!("Hello")
}

// 带参数的函数
// 函数也可以被定义为拥有 参数（parameters），参数是特殊变量，是函数签名的一部分。
// 当函数拥有参数（形参）时，可以为这些参数提供具体的值（实参）。
fn say(str: &str) {
    println!("{}", str)
}

// 当一个函数有多个参数时，使用逗号分隔，像这样：
fn another_function(x: i32, y: i32) {
    println!("The value of x is: {}", x);
    println!("The value of y is: {}", y)
}

// 语句和表达式
// 语句不返回值,表达式会计算出一个值
// 这里比较难理解的就是，什么是语句?什么是表达式?
// Rust 是一门基于表达式（expression-based）的语言
// 表达式的结尾没有分号。如果在表达式的结尾加上分号，它就变成了语句，而语句不会返回值。
//
// 什么是表达式
// 函数调用是一个表达式。宏调用是一个表达式。我们用来创建新作用域的大括号（代码块），{}，也是一个表达式
//
// 什么是语句?
// 不是表达式就是语句
// let x = 6 这个就是语句,语句不返回值

// 函数可以向调用它的代码返回值。我们并不对返回值命名，但要在箭头（->）后声明它的类型。
// 在 Rust 中，函数的返回值等同于函数体最后一个表达式的值。
// 使用 return 关键字和指定值，可从函数中提前返回；但大部分函数隐式的返回最后的表达式。
fn five() -> i32 {
    5
}

// 有参数有返回值
fn plus_one(x: i32) -> i32 {
    x + 1
}
