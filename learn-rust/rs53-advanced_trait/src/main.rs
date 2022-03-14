// 1.关联类型
// 关联类型（associated types）是一个将类型占位符与 trait 相关联的方式，这样 trait 的方法签名中就可以使用这些占位符类型。
// trait 的实现者会针对特定的实现在这个类型的位置指定相应的具体类型。
use std::fmt;
use std::option::Option;
use std::ops::Add;

pub struct Counter {}

pub trait MyIterator {
    type Item; // Item 是一个占位类型

    fn next(&mut self) -> Option<Self::Item>; //同时 next 方法定义表明它返回 Option<Self::Item> 类型的值。
}

impl MyIterator for Counter {
    type Item = u32; // 实现的时候这里指定关联类型
    fn next(&mut self) -> Option<Self::Item> {
        Some(1)
    }
}
// 看起来和泛型很像，为什么不用泛型？
// 区别在于当使用泛型时，则不得不在每一个实现中标注类型。
// 这是因为我们也可以实现为 MyIterator<String> for Counter，或任何其他类型，这样就可以有多个 Counter 的 MyIterator 的实现。
// 换句话说，当 trait 有泛型参数时，可以多次实现这个 trait，每次需改变泛型参数的具体类型。
// 接着当使用 Counter 的 next 方法时，必须提供类型注解来表明希望使用 MyIterator 的哪一个实现。


#[derive(Debug, PartialEq)]
struct Point {
    x: i32,
    y: i32,
}

// 2.运算符重载
// Rust 并不允许创建自定义运算符或重载任意运算符，
// 不过 std::ops 中所列出的运算符和相应的 trait 可以通过实现运算符相关 trait 来重载
impl Add for Point {
    type Output = Point;

    fn add(self, other: Point) -> Point {
        Point {
            x: self.x + other.x,
            y: self.y + other.y,
        }
    }
}

// 3.默认泛型参数
// 我们来看一下 Add trait中的定义
/*
trait Add<RHS=Self> {
    type Output;

    fn add(self, rhs: RHS) -> Self::Output;
}
*/
// 这是一个带有一个方法和一个关联类型的 trait。
// 比较陌生的部分是尖括号中的 RHS=Self：这个语法叫做 默认类型参数（default type parameters）。
// RHS 是一个泛型类型参数（“right hand side” 的缩写）
// 它用于定义 add 方法中的 rhs 参数。
// 如果实现 Add trait 时不指定 RHS 的具体类型，RHS 的类型将是默认的 Self 类型，也就是在其上实现 Add 的类型。
// 当为 Point 实现 Add 时，使用了默认的 RHS，因为我们希望将两个 Point 实例相加。
// 也就是说如果你不指定泛型参数，那么你实现add方法的时候rhs的类型就是Self，也就是说你只能+同类型的对象
//
// 现在让我们看看一个实现 Add trait 时希望自定义 RHS 类型而不是使用默认类型的例子。
// 这里有两个存放不同单元值的结构体，Millimeters 和 Meters。
// 我们希望能够将毫米值与米值相加，并让 Add 的实现正确处理转换。
// 可以为 Millimeters 实现 Add 并以 Meters 作为 RHS
struct Millimeters(u32);
struct Meters(u32);

// 指定泛型参数类型为Meters
impl Add<Meters> for Millimeters {
    type Output = Millimeters;

    // 由于指定了泛型参数，因此这里实现add方法是rhs的类型就是Meters
    // 这样就可以两个不同类型相加了
    fn add(self, other: Meters) -> Millimeters {
        Millimeters(self.0 + (other.0 * 1000))
    }
}

// 4.消除歧义，调用同名方法
trait Pilot {
    fn fly(&self);
}

trait Wizard {
    fn fly(&self);
}

struct Human;

impl Pilot for Human {
    fn fly(&self) {
        println!("This is your captain speaking.");
    }
}

impl Wizard for Human {
    fn fly(&self) {
        println!("Up!");
    }
}

impl Human {
    fn fly(&self) {
        println!("*waving arms furiously*");
    }
}

// 5.完全限定语法
// 有时候我们使用的是关联函数，它没有 self 参数，这时候消除歧义就不好使了。
// 因为Rust 不能计算出我们期望的是哪一个类型，这时候就需要使用安全限定语法
trait Animal {
    fn baby_name() -> String;
}

struct Dog;

impl Dog {
    fn baby_name() -> String {
        String::from("Spot")
    }
}

impl Animal for Dog {
    fn baby_name() -> String {
        String::from("puppy")
    }
}

// 6.一个trait依赖另一个trait的功能
trait OutlinePrint: fmt::Display {
    fn outline_print(&self) {
        // 因为指定了 OutlinePrint 需要 Display trait，则可以在 outline_print 中使用 to_string，
        // 其会为任何实现 Display 的类型自动实现。
        // 如果不在 trait 名后增加 : Display 并尝试在 outline_print 中使用 to_string，
        // 则会得到一个错误说在当前作用域中没有找到用于 &Self 类型的方法 to_string。
        let output = self.to_string(); // 依赖Display trait的to_string功能
        let len = output.len();
        println!("{}", "*".repeat(len + 4));
        println!("*{}*", " ".repeat(len + 2));
        println!("* {} *", output);
        println!("*{}*", " ".repeat(len + 2));
        println!("{}", "*".repeat(len + 4));
    }
}

// OutlinePrint 需要实现fmt::Display
impl fmt::Display for Point {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "({}, {})", self.x, self.y)
    }
}

impl OutlinePrint for Point {}


// 7.newtype 模式(实现外部trait)
// 例如，如果想要在 Vec<T> 上实现 Display，而孤儿规则阻止我们直接这么做，
// 因为 Display trait 和 Vec<T> 都定义于我们的 crate 之外。
// 可以创建一个包含 Vec<T> 实例的 Wrapper 结构体，接着可以在 Wrapper 上实现 Display 并使用 Vec<T> 的值：
struct Wrapper(Vec<String>); // 元祖结构体

// 对于Wrapper实现Display
impl fmt::Display for Wrapper {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        // Display 的实现使用 self.0 来访问其内部的 Vec<T>
        // 因为 Wrapper 是元组结构体而 Vec<T> 是结构体总位于索引 0 的项。接着就可以使用 Wrapper 中 Display 的功能了。
        write!(f, "[{}]", self.0.join(", "))
    }
}


fn main() {
    let person = Human;
    // 因为trait的fly方法是有self的，因此Rust 可以根据 self 的类型计算出应该使用哪一个 trait 实现。
    Pilot::fly(&person);
    Wizard::fly(&person);
    person.fly();

    // 运算符重载
    assert_eq!(Point { x: 1, y: 0 } + Point { x: 2, y: 3 },
               Point { x: 3, y: 3 });

    // 想调用Animal实现的baby_name方法
    println!("A baby dog is called a {}", Dog::baby_name()); // 这个调用的是Dog默认的实现，也就是Spot
    // 这样就可以调用Animal上的baby_name方法，这个叫做安全限定语法
    println!("A baby dog is called a {}", <Dog as Animal>::baby_name());

    // 一个trait依赖另一个trait的功能
    let point = Point{x:1, y:2};
    point.outline_print();

    // 实现外部trait
    let w = Wrapper(vec![String::from("hello"), String::from("world")]);
    println!("w = {}", w);
}
