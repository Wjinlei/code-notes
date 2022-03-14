fn main() {
    //let x = 5;
    //println!("The value of x is: {}", x);
    //x = 6; // 这里会报错,不能对不可变变量 x 二次赋值（cannot assign twice to immutable variable x）。
    // Rust 编译器保证，如果声明一个值不会变，它就真的不会变。
    // 这意味着当阅读和编写代码时，不需要追踪一个值如何和在哪可能会被改变，从而使得代码易于推导。
    //println!("The value of x is: {}", x);

    // 不过可变性也是非常有用的。变量只是默认不可变；正如在第二章所做的那样，你可以在变量名之前加 mut 来使其可变。
    // 除了允许改变值之外，mut 向读者表明了其他代码将会改变这个变量值的意图。
    let mut x = 5;
    println!("This value of x is: {}", x);
    x = 6;
    println!("This value of x is: {}", x);

    // 不允许改变值的变量，可能会使你想起另一个大部分编程语言都有的概念：常量（constants）。
    // 不过常量与变量还是有一些区别。

    // 首先，不允许对常量使用 mut。常量不光默认不能变，它总是不能变。
    // 声明常量使用 const 关键字而不是 let，并且 必须 注明值的类型。
    // 常量可以在任何作用域中声明，包括全局作用域，这在一个值需要被很多部分的代码用到时很有用。
    // 最后一个区别是，常量只能被设置为常量表达式，而不能是函数调用的结果，或任何其他只能在运行时计算出的值。
    // 下面是一个常量的例子
    const MAX_POINTS: u32 = 100_000;
    println!("This const of MAX_POINTS is: {}", MAX_POINTS);

    // 我们可以定义一个与之前变量同名的新变量，而新变量会 隐藏 之前的变量。
    // Rustacean 们称之为第一个变量被第二个 隐藏 了，这意味着使用这个变量时会看到第二个值。
    // 隐藏与将变量标记为 mut 是有区别的。当不小心尝试对变量重新赋值时，如果没有使用 let 关键字，就会导致编译时错误。
    // 通过使用 let，我们可以用这个值进行一些计算，不过计算完之后变量仍然是不变的。
    let y = 5;
    let y = y + 1;
    let y = y * 2;
    println!("This value of y is: {}", y);

    // mut 与隐藏的另一个区别是，当再次使用 let 时，实际上创建了一个新变量，我们可以改变值的类型，但复用这个名字。
    let spaces = "   ";
    let spaces = spaces.len();
    println!("This value of spaces is: {}", spaces);
}
