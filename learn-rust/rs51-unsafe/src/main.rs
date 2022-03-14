// unsafe 可以让Rust在编译时对unsafe代码块中的代码不执行内存安全检查
// 使用不安全代码相当于告诉编译器，“相信我，我知道我在干什么。
// ”这么做的缺点就是你只能靠自己了：如果不安全代码出错了，比如解引用空指针，可能会导致不安全的内存使用。

// 可以通过 unsafe 关键字来切换到不安全 Rust，接着可以开启一个新的存放不安全代码的块。
// 这里有五类可以在不安全 Rust 中进行而不能用于安全 Rust 的操作，它们称之为 “不安全的超级力量。” 这些超级力量是：
//     解引用裸指针
//     调用不安全的函数或方法
//     访问或修改可变静态变量
//     实现不安全 trait
//     访问 union 的字段

fn main() {
    // 1. 解引用裸指针
    // 不安全 Rust 有两个被称为 裸指针（raw pointers）的类似于引用的新类型。
    // 和引用一样，裸指针是不可变或可变的，分别写作 *const T 和 *mut T。
    // 这里的星号不是解引用运算符；它是类型名称的一部分。在裸指针的上下文中，不可变 意味着指针解引用之后不能直接赋值。
    // 与引用和智能指针的区别在于：
    //     允许忽略借用规则，可以同时拥有不可变和可变的指针，或多个指向相同位置的可变指针
    //     不保证指向有效的内存
    //     允许为空
    //     不能实现任何自动清理功能

    // 注意这里没有引入 unsafe 关键字。
    // 可以在安全代码中 创建 裸指针，只是不能在不安全块之外 解引用 裸指针，稍后便会看到。
    // 这里使用 as 将不可变和可变引用强转为对应的裸指针类型。
    // 因为直接从保证安全的引用来创建他们，可以知道这些特定的裸指针是有效，但是不能对任何裸指针做出如此假设。
    let mut num = 5;
    let r1 = &num as *const i32;
    let r2 = &mut num as *mut i32;

    // 记得我们说过可以在安全代码中创建裸指针，不过不能 解引用 裸指针和读取其指向的数据。
    // 现在我们要做的就是对裸指针使用解引用运算符 *，这需要一个 unsafe 块
    unsafe {
        // 创建一个指针不会造成任何危险；只有当访问其指向的值时才有可能遇到无效的值。
        println!("r1 is: {}", *r1);
        println!("r2 is: {}", *r2);
    }

    // 你还可以创建一个指向任意内存地址的裸指针
    /*
    let address = 0x012345usize;
    let r = address as *const i32;
    unsafe {
        println!("r is: {}", *r);
    }
    */

    // 既然存在这么多的危险，为何还要使用裸指针呢？
    // 一个主要的应用场景便是调用 C 代码接口
    // 另一个场景是构建借用检查器无法理解的安全抽象。

    // 1.调用不安全的函数或方法
    unsafe{
        dangerous();
    }
    // 2.extern调用外部代码
    // 通常外部代码被认为是不安全的，因为Rust 无法检查它
    unsafe {
        println!("Absolute value of -3 according to C: {}", abs(-3));
    }
    // 3.创建不安全代码的安全抽象
    // 仅仅因为函数包含不安全代码并不意味着整个函数都需要标记为不安全的。
    // 事实上，将不安全代码封装进安全函数是一个常见的抽象。
    // 作为一个例子，标准库中的函数，split_at_mut，它需要一些不安全代码。
    // https://kaisery.github.io/trpl-zh-cn/ch19-01-unsafe-rust.html#%E5%88%9B%E5%BB%BA%E4%B8%8D%E5%AE%89%E5%85%A8%E4%BB%A3%E7%A0%81%E7%9A%84%E5%AE%89%E5%85%A8%E6%8A%BD%E8%B1%A1

    // 读取或修改可变静态变量
    // 目前为止全书都尽量避免讨论 全局变量（global variables），
    // Rust 确实支持他们，不过这对于 Rust 的所有权规则来说是有问题的。
    // 如果有两个线程访问相同的可变全局变量，则可能会造成数据竞争。
    add_to_count(3);
    unsafe {
        println!("COUNTER: {}", COUNTER);
    }
    // 读取或修改一个可变静态变量是不安全的
    // 因为拥有多个线程访问 COUNTER 则可能导致数据竞争。


    // 使用 unsafe 来进行这五个操作（超级力量）之一是没有问题的，甚至是不需要深思熟虑的，
    // 不过使得 unsafe 代码正确也实属不易，因为编译器不能帮助保证内存安全。
    // 当有理由使用 unsafe 代码时，是可以这么做的，通过使用显式的 unsafe 标注使得在出现错误时易于追踪问题的源头。
}

// 集成 C 标准库中的 abs 函数。
// extern 块中声明的函数在 Rust 代码中总是不安全的。
// 因为其他语言不会强制执行 Rust 的规则且 Rust 无法检查它们，所以确保其安全是程序员的责任：
extern "C" {
    fn abs(input: i32) -> i32;
}

// 从其他语言调用Rust函数
// 不同于 extern 块，就在 fn 关键字之前增加 extern 关键字并指定所用到的 ABI。
// 还需增加 #[no_mangle] 注解来告诉 Rust 编译器不要 mangle 此函数的名称。
// Mangling
// 发生于当编译器将我们指定的函数名修改为不同的名称时，
//     这会增加用于其他编译过程的额外信息，不过会使其名称更难以阅读。
// 每一个编程语言的编译器都会以稍微不同的方式 mangle 函数名
// 所以为了使 Rust 函数能在其他语言中指定，必须禁用 Rust 编译器的 name mangling。
//
// 在如下的例子中，一旦其编译为动态库并从 C 语言中链接，call_from_c 函数就能够在 C 代码中访问
//
// 这里#[no_mangle]意思就是函数符号保持call_from_c原样
// 下一节学习下如何将Rust编译成动态库
#[no_mangle]
pub extern "C" fn call_from_c(){
    println!("Just called a Rust function from C!");
}

unsafe fn dangerous() {}

static mut COUNTER: u32 = 0;

fn add_to_count(inc: u32) {
    unsafe {
        COUNTER += inc;
    }
}


// 实现不安全的trait
// 最后一个只能用在 unsafe 中的操作是实现不安全 trait。
// 当至少有一个方法中包含编译器不能验证的不变量时 trait 是不安全的。
// 可以在 trait 之前增加 unsafe 关键字将 trait 声明为 unsafe，同时 trait 的实现也必须标记为 unsafe
unsafe trait Foo {
    // methods go here
}

unsafe impl Foo for i32 {
    // method implementations go here
}
