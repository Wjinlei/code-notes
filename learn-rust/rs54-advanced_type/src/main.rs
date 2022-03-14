use std::io;

// 1.类型别名
// 因为 Kilometers 是 i32 的别名，他们是同一类型
// 可以将 i32 与 Kilometers 相加，也可以将 Kilometers 传递给获取 i32 参数的函数。
type Kilometers = i32; //这意味着 Kilometers 是 i32 的 同义词，但不是新的类型
//类型别名的主要作用是减少重复，例如，可能会有这样很长的类型：Box<dyn Fn() + Send + 'static>
/*
let f: Box<dyn Fn() + Send + 'static> = Box::new(|| println!("hi"));

fn takes_long_type(f: Box<dyn Fn() + Send + 'static>) {
    // --snip--
}

fn returns_long_type() -> Box<dyn Fn() + Send + 'static> {
    // --snip--
}
*/
// 上面写法就很麻烦，那么你就可以通过类型别名优化它
/*
type Thunk = Box<dyn Fn() + Send + 'static>; // 定义一个类型别名

let f: Thunk = Box::new(|| println!("hi"));

fn takes_long_type(f: Thunk) { // 传递这个别名就可以了
    // --snip--
}

fn returns_long_type() -> Thunk {
    // --snip--
}
*/

// 2.never type(从不返回)
// Rust 有一个叫做 ! 的特殊类型。在类型理论术语中，它被称为 empty type，因为它没有值。我们更倾向于称之为 never type。

fn main() {
    let x: i32 = 5;
    let y: Kilometers = 5;

    println!("x + y = {}", x + y);

    loop {
        let mut guess = String::new();
        io::stdin()
            .read_line(&mut guess)
            .expect("Failed to read line");
        // 我们学习了 match 的分支必须返回相同的类型。如下代码不能工作：
        /*
        let guess = match guess.trim().parse() {
            Ok(_) => 5,
            Err(_) => "hello",
        }
        */

        // 那么下面的代码为什么能编译呢？

        // 这里的 guess 必须既是整型也是字符串，而 Rust 要求 guess 只能是一个类型。
        // 那么 continue 返回了什么呢？为什么中会允许一个分支返回 u32 而另一个分支却以 continue 结束呢？

        // 正如你可能猜到的，continue 的值是 !。
        // 也就是说，当 Rust 要计算 guess 的类型时，它查看这两个分支。
        // 前者是 u32 值，而后者是 ! 值。因为 ! 并没有一个值，Rust 决定 guess 的类型是 u32。

        // 描述 ! 的行为的正式方式是 never type 可以强转为任何其他类型。
        // 允许 match 的分支以 continue 结束是因为 continue 并不真正返回一个值
        // 相反它把控制权交回上层循环，所以在 Err 的情况，事实上并未对 guess 赋值。

        let guess: u32 = match guess.trim().parse() {
            Ok(num) => num,
            Err(_) => continue,
        };
        println!("You guessed: {}", guess);
    }
}

// 还有一个知识点是动态大小类型和Sized trait，说实话没看懂，后面再说
