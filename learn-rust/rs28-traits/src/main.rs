// trait 告诉 Rust 编译器某个特定类型拥有可能与其他类型共享的功能。
// 可以通过 trait 以一种抽象的方式定义共享的行为。
// 可以使用 trait bounds 指定泛型是任何拥有特定行为的类型。
//
// trait 类似于其他语言中的常被称为 接口（interfaces）的功能，虽然有一些不同。
//
// 一个类型的行为由其可供调用的方法构成。
// 如果可以对不同类型调用相同的方法的话，这些类型就可以共享相同的行为了。
// trait 定义是一种将方法签名组合起来的方法，目的是定义一个实现某些目的所必需的行为的集合。

// 定义一个trait名叫Hello
pub trait Hello1 {
    fn hello1(&self); // 定义时不必实现
}

// 默认实现
// 有时为 trait 中的某些或全部方法提供默认的行为，而不是在每个类型的每个实现中都定义自己的行为是很有用的。
// 这样当为某个特定类型实现 trait 时，可以选择保留或重载每个方法的默认行为。
pub trait Hello2 {
    fn hello2(&self) {
        println!("Hello World!");
    }
}

pub struct Java {}
pub struct Rust {}
pub struct Perl {}
pub struct Ruby {}

// 实现Trait
impl Hello1 for Java {
    fn hello1(&self) {
        println!("Hello Java!");
    }
}

impl Hello1 for Rust {
    fn hello1(&self) {
        println!("Hello Rust!");
    }
}

// 如果想要使用默认实现，而不是定义一个自己的实现，则可以指定一个空的 impl 块。
impl Hello2 for Perl {}
impl Hello1 for Perl {
    fn hello1(&self) {
        println!("Hello Perl!");
    }
}
impl Hello2 for Ruby {}
impl Hello1 for Ruby {
    fn hello1(&self) {
        println!("Hello Ruby!");
    }
}

// Trait作为参数
// 该函数支持任何实现了Hello1 trait 的类型。
fn say_hello1(item: impl Hello1) -> impl Hello1 {
    // 这里返回实现了trait的类型是为了返回所有权
    item.hello1();
    item
}

// Trait Bound 语法
// 语法糖。它等价与上面的函数
fn say_hello2<T: Hello1>(item: T) -> T {
    // 这里返回实现了trait的类型是为了返回所有权
    item.hello1();
    item
}

// 通过+号指定多个trait
fn say_hello3(item: impl Hello1 + Hello2) -> impl Hello1 + Hello2 {
    // 这里返回实现了trait的类型是为了返回所有权
    item.hello1();
    item.hello2();
    item
}

fn say_hello4<T: Hello1 + Hello2>(item: T) -> T {
    // 这里返回实现了trait的类型是为了返回所有权
    item.hello1();
    item.hello2();
    item
}

// 使用where语句简化trait
// 有多个泛型参数的函数在名称和参数列表之间会有很长的 trait bound 信息，这使得函数签名难以阅读。
fn some_function1<T: Hello1, U: Hello1 + Hello2>(t: T, u: U) {
    t.hello1();
    u.hello1();
    u.hello2();
}
// 为此，Rust 有另一个在函数签名之后的 where 从句中指定 trait bound 的语法。
fn some_function2<T, U>(t: T, u: U)
where
    T: Hello1,
    U: Hello1 + Hello2,
{
    t.hello1();
    u.hello1();
    u.hello2();
}

// 根据trait有条件的实现
pub struct Language<T> {
    instance: T,
}

// 对于任何类型的Language都实现了new_instance
impl<T> Language<T> {
    fn new_instance(instance: T) -> Self {
        // 注意这不是一个方法,是关联函数
        Self { instance }
    }
}
// 对于实现了Hello1 + Hello2 trait的类型实现print_hello方法
impl<T: Hello1 + Hello2> Language<T> {
    fn print_hello(&self) {
        self.instance.hello1();
        self.instance.hello2();
    }
}

fn main() {
    let java = Java {};
    let rust = Rust {};
    let perl = Perl {};
    let ruby = Ruby {};
    java.hello1();
    rust.hello1();
    perl.hello2();
    ruby.hello2();

    // 必须是实现了Hello1
    let java = say_hello1(java);
    let rust = say_hello1(rust);

    // 必须是实现了Hello2
    let java = say_hello2(java);
    let rust = say_hello2(rust);

    // 必须是实现了Hello1 和Hello2的类型
    let perl = say_hello3(perl);
    let ruby = say_hello3(ruby);

    // 必须是实现了Hello1 和Hello2的类型
    let perl = say_hello4(perl);
    let ruby = say_hello4(ruby);

    some_function1(java, perl);
    some_function2(rust, ruby);

    //let java2 = Language::new_instance(Java {});
    //java2.print_hello(); // Java 由于没有实现Hello2 trait 所以它没有实现print_hello方法
    let ruby2 = Language::new_instance(Ruby {});
    ruby2.print_hello();
}
