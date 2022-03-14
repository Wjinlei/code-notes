// 函数指针
// 我们讨论过了如何向函数传递闭包，当然也可以向函数传递常规函数！
// 这在我们希望传递已经定义的函数而不是重新定义闭包作为参数时很有用。
// 通过函数指针允许我们使用函数作为另一个函数的参数。
fn add_one(x: i32) -> i32 {
    x + 1
}

// 函数的类型是 fn （使用小写的 “f” ）以免与 Fn 闭包 trait 相混淆。
// fn 被称为 函数指针（function pointer）。指定参数为函数指针的语法类似于闭包
fn do_twice(f: fn(i32) -> i32, arg: i32) -> i32 {
    f(arg) + f(arg)
}


// 返回闭包
// 这段代码尝试直接返回闭包，它并不能编译：
/*
fn returns_closure() -> Fn(i32) -> i32 {
    |x| x + 1
}
*/
// 错误又一次指向了 Sized trait！Rust 并不知道需要多少空间来储存闭包。
// 不过我们在上一部分见过这种情况的解决办法：可以使用 trait 对象：
fn returns_closure() -> Box<dyn Fn(i32) -> i32> {
    Box::new(|x| x + 1)
}

fn main() {
    let answer = do_twice(add_one, 5);
    println!("The answer is: {}", answer);

    let closure = returns_closure();
    println!("{}", closure(1));
}
