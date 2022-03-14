use std::{collections::HashMap, fmt::Debug, thread, time::Duration};

// 闭包
// Rust 的 闭包（closures）是可以保存进变量或作为参数传递给其他函数的匿名函数。
// 可以在一个地方创建闭包，然后在不同的上下文中执行闭包运算。不同于函数，闭包允许捕获调用者作用域中的值。

// 请看下面这个函数
fn generate_workout(intensity: u32, random_number: u32) {
    if intensity < 25 {
        println!(
            "Today, do {} pushups!",
            simulated_expensive_calculation(intensity) // 调用函数
        );
        println!(
            "Next, do {} situps!",
            simulated_expensive_calculation(intensity) // 调用函数
        );
    } else {
        if random_number == 3 {
            println!("Take a break today! Remember to stay hydrated!");
        } else {
            println!(
                "Today, run for {} minutes!",
                simulated_expensive_calculation(intensity) // 调用函数
            );
        }
    }
}
// 现在这份代码能够应对我们的需求了
// 但数据科学部门的同学告知我们将来会对调用 simulated_expensive_calculation 的方式做出一些改变。
// 为了在要做这些改动的时候简化更新步骤
// 我们将重构代码来让它只调用 simulated_expensive_calculation 一次。
// 同时还希望去掉目前多余的连续两次函数调用，并不希望在计算过程中增加任何其他此函数的调用。
// 也就是说，我们不希望在完全无需其结果的情况调用函数，不过仍然希望只调用函数一次。

// 解决方案1
// 有多种方法可以重构此程序。我们首先尝试的是将重复的 simulated_expensive_calculation 函数调用提取到一个变量中
fn generate_workout2(intensity: u32, random_number: u32) {
    let expensive_result = simulated_expensive_calculation(intensity); // 将函数的返回值存储到一个变量中

    if intensity < 25 {
        println!(
            "Today, do {} pushups!",
            expensive_result // 调用结果
        );
        println!(
            "Next, do {} situps!",
            expensive_result // 调用结果
        );
    } else {
        if random_number == 3 {
            println!("Take a break today! Remember to stay hydrated!");
        } else {
            println!(
                "Today, run for {} minutes!",
                expensive_result // 调用结果
            );
        }
    }
}
// 这个修改统一了 simulated_expensive_calculation 调用并解决了第一个 if 块中不必要的两次调用函数的问题。
// 不幸的是，现在所有的情况下都需要调用函数并等待结果，包括那个完全不需要这一结果的内部 if 块。
// 我们希望能够在程序的一个位置指定某些代码，并只在程序的某处实际需要结果的时候 执行 这些代码。这正是闭包的用武之地！
fn generate_workout3(intensity: u32, random_number: u32) {
    // 定义闭包
    let expensive_closure = |num| {
        println!("calculating slowly...");
        thread::sleep(Duration::from_secs(2));
        num
    };
    // 闭包定义是 expensive_closure 赋值的 = 之后的部分。
    // 闭包的定义以一对竖线（|）开始，在竖线中指定闭包的参数；
    // 之所以选择这个语法是因为它与 Smalltalk 和 Ruby 的闭包定义类似。

    // 这个闭包有一个参数 num；如果有多于一个参数，可以使用逗号分隔，比如 |param1, param2|。
    // 参数之后是存放闭包体的大括号 —— 如果闭包体只有一行则大括号是可以省略的。
    // 大括号之后闭包的结尾，需要用于 let 语句的分号。
    // 因为闭包体的最后一行没有分号（正如函数体一样），所以闭包体（num）最后一行的返回值作为调用闭包时的返回值 。

    // 注意这个 let 语句意味着 expensive_closure 包含一个匿名函数的 定义，不是调用匿名函数的 返回值。

    // 定义了闭包之后，可以改变 if 块中的代码来调用闭包以执行代码并获取结果值。
    // 调用闭包类似于调用函数；指定存放闭包定义的变量名并后跟包含期望使用的参数的括号
    if intensity < 25 {
        println!("Today, do {} pushups!", expensive_closure(intensity));
        println!("Next, do {} situps!", expensive_closure(intensity));
    } else {
        if random_number == 3 {
            println!("Take a break today! Remember to stay hydrated!");
        } else {
            println!("Today, run for {} minutes!", expensive_closure(intensity));
        }
    }
}
// 现在耗时的计算只在一个地方被调用，并只会在需要结果的时候执行该代码。

// 然而，我们又重新引入了前面示例中的问题：仍然在第一个 if 块中调用了闭包两次
// 这调用了慢计算代码两次而使得用户需要多等待一倍的时间。
// 可以通过在 if 块中创建一个本地变量存放闭包调用的结果来解决这个问题
// 不过闭包可以提供另外一种解决方案。

// 回到在示例3中的代码仍然把慢计算闭包调用了比所需更多的次数。
// 解决这个问题的一个方法是在全部代码中的每一个需要多个慢计算闭包结果的地方
// 可以将结果保存进变量以供复用，这样就可以使用变量而不是再次调用闭包。
// 但是这样就会有很多重复的保存结果变量的地方。

// 幸运的是，还有另一个可用的方案。可以创建一个存放闭包和调用闭包结果的结构体。
// 该结构体只会在需要结果时执行闭包，并会缓存结果值，这样余下的代码就不必再负责保存结果并可以复用该值。
// 你可能见过这种模式被称 memoization 或 lazy evaluation （惰性求值）。

// 为了让结构体存放闭包，我们需要指定闭包的类型，因为结构体定义需要知道其每一个字段的类型。
// 每一个闭包实例有其自己独有的匿名类型：也就是说，即便两个闭包有着相同的签名，他们的类型仍然可以被认为是不同。
// 为了定义使用闭包的结构体、枚举或函数参数，需要像前面章节讨论的那样使用泛型和 trait bound。

// Fn 系列 trait 由标准库提供。所有的闭包都实现了 trait Fn、FnMut 或 FnOnce 中的一个。
// 在后面的章节我们会讨论这些 trait 的区别；在这个例子中可以使用 Fn trait。

// 为了满足 Fn trait bound 我们增加了代表闭包所必须的参数和返回值类型的类型。
// 在这个例子中，闭包有一个 u32 的参数并返回一个 u32，这样所指定的 trait bound 就是 Fn(u32) -> u32。
// 结构体 Cacher 有一个泛型 T 的字段 calculation。
// T 的 trait bound 指定了 T 是一个使用 Fn 的闭包。
// 任何我们希望储存到 Cacher 实例的 calculation 字段的闭包
// 必须有一个 u32 参数（由 Fn 之后的括号的内容指定）并必须返回一个 u32（由 -> 之后的内容）。
// 字段 value 是 Option<u32> 类型的。
// 在执行闭包之前，value 将是 None。
// 如果使用 Cacher 的代码请求闭包的结果，这时会执行闭包并将结果储存在 value 字段的 Some 成员中。
// 接着如果代码再次请求闭包的结果，这时不再执行闭包，而是会返回存放在 Some 成员中的结果。
struct Cacher<T>
where
    T: Fn(u32) -> u32,
{
    calculation: T,
    value: Option<u32>,
}

// 闭包结构体要我们自己实现逻辑
impl<T> Cacher<T>
where
    T: Fn(u32) -> u32,
{
    fn new(calculation: T) -> Cacher<T> {
        Cacher {
            calculation,
            value: None,
        }
    }

    fn value(&mut self, arg: u32) -> u32 {
        match self.value {
            Some(v) => v,
            None => {
                let v = (self.calculation)(arg); // 如果没有value则调用闭包
                self.value = Some(v); // 重新给value赋值
                v // 返回value
            }
        }
    }
}

fn generate_workout4(intensity: u32, random_number: u32) {
    let mut expensive_result = Cacher::new(|num| {
        println!("calculating slowly...");
        thread::sleep(Duration::from_secs(2));
        num
    });

    if intensity < 25 {
        println!(
            "Today, do {} pushups!",
            expensive_result.value(intensity) // 调用闭包中存储的值,如果没有则调用闭包函数
        );
        println!(
            "Next, do {} situps!",
            expensive_result.value(intensity) // 调用闭包中存储的值
        );
    } else {
        if random_number == 3 {
            println!("Take a break today! Remember to stay hydrated!");
        } else {
            println!(
                "Today, run for {} minutes!",
                expensive_result.value(intensity) // 调用闭包中存储的值
            );
        }
    }
}
// 上面的Cacher实现2个小问题
// 1.当我们调用过一次expensive_result.value(intensity)
//   后其值就已经存储在Some中，之后无论我们再传什么参数进去也是之前的值，也就是说我们无法修改。
// 2.第二个问题是它被限制为只接受获取一个 u32 值并返回一个 u32 值的闭包。
//   我们可以尝试引入更多泛型参数来增加 Cacher 功能的灵活性。

//下面我们来增强它
struct Cacher2<T, U>
where
    T: Fn(U) -> U,
    U: Copy,
{
    calculation: T,
    value: HashMap<String, U>,
}

// 闭包结构体要我们自己实现逻辑
impl<T, U> Cacher2<T, U>
where
    T: Fn(U) -> U,
    U: Copy,
{
    fn new(calculation: T) -> Cacher2<T, U> {
        let value = HashMap::new();
        Cacher2 { calculation, value }
    }
    fn value(&mut self, key: &String, arg: U) -> U {
        let v = (self.calculation)(arg);
        self.value.insert(key.clone(), v);
        v
    }
}

fn generate_workout5<T: Copy + Debug>(
    key: &String,
    intensity: T,
    intensity2: T,
    random_number: u32,
) {
    let mut expensive_result = Cacher2::new(|num| {
        println!("calculating slowly...");
        thread::sleep(Duration::from_secs(2));
        num
    });

    if random_number == 3 {
        println!("Take a break today! Remember to stay hydrated!");
    } else {
        println!(
            "expensive_result.value = {:?}",
            expensive_result.value(key, intensity)
        );
        println!(
            "expensive_result.value = {:?}",
            expensive_result.value(key, intensity2)
        );
    }
}

fn main() {
    let simulated_user_specified_value = 10;
    let simulated_user_specified_value2 = 20;
    let simulated_user_specified_value3 = "Hello World";
    let simulated_user_specified_value4 = "Hello Rust";
    let simulated_random_number = 7;

    generate_workout(simulated_user_specified_value, simulated_random_number);
    generate_workout2(simulated_user_specified_value, simulated_random_number);
    generate_workout3(simulated_user_specified_value, simulated_random_number);
    generate_workout4(simulated_user_specified_value, simulated_random_number);

    generate_workout5(
        &String::from("v1"),
        simulated_user_specified_value,
        simulated_user_specified_value2,
        simulated_random_number,
    );

    generate_workout5(
        &String::from("v2"),
        simulated_user_specified_value3,
        simulated_user_specified_value4,
        simulated_random_number,
    );

    // 闭包会捕获其环境
    // 闭包还有另一个函数所没有的功能：他们可以捕获其环境并访问其被定义的作用域的变量。
    let x = 4;
    let equal_to_x = |z| z == x; // 这里闭包函数可以使用变量x
    let y = 4;
    assert!(equal_to_x(y));
    // 这里，即便 x 并不是 equal_to_x 的一个参数，equal_to_x 闭包也被允许使用变量 x
    // 因为它与 equal_to_x 定义于相同的作用域。
    // 函数则不能做到同样的事
}

fn simulated_expensive_calculation(num: u32) -> u32 {
    num
}

// PS:关于闭包参数类型和返回值类型
// https://kaisery.github.io/trpl-zh-cn/ch13-01-closures.html#%E9%97%AD%E5%8C%85%E7%B1%BB%E5%9E%8B%E6%8E%A8%E6%96%AD%E5%92%8C%E6%B3%A8%E8%A7%A3
// 简单来说,闭包不需要定义参数类型和返回值类型,因为Rust可以自己推断
// 至于它是如何推断的请参考上面的链接

// 关于闭包Fn trait, FnMut trait,FnOnce trait 没看懂
// https://kaisery.github.io/trpl-zh-cn/ch13-01-closures.html#%E9%97%AD%E5%8C%85%E4%BC%9A%E6%8D%95%E8%8E%B7%E5%85%B6%E7%8E%AF%E5%A2%83
// 后面遇到再研究吧
