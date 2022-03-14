// 实现 Deref trait 允许我们重载 解引用运算符（dereference operator）*（与乘法运算符或通配符相区别）。
// 通过这种方式实现 Deref trait 的智能指针可以被当作常规引用来对待，可以编写操作引用的代码并用于智能指针。

use std::ops::Deref;

fn main() {
    let x = 5;
    let y = &x;
    assert_eq!(5, x);
    assert_eq!(5, *y); // 解引用后才能比较

    let x = 5;
    let y = Box::new(x);
    assert_eq!(5, x);
    assert_eq!(5, *y); // Box<T>也可以解引用

    let x = 5;
    let y = MyBox::new(x);
    assert_eq!(5, x);
    assert_eq!(5, *y); // 底层Rust实际上运行了 *(y.deref())

    // 没有 Deref trait 的话，编译器只会解引用 & 引用类型。
    // deref 方法向编译器提供了获取任何实现了 Deref trait 的类型的值
    // 并且调用这个类型的 deref 方法来获取一个它知道如何解引用的 & 引用的能力。
}

// 下面自定义一个Box<T>类型
// 从根本上说，Box<T> 被定义为包含一个元素的元组结构体
// 所以我们以相同的方式定义了 MyBox<T> 类型。
struct MyBox<T>(T);

// 我们还定义了 new 函数来对应定义于 Box<T> 的 new 函数
impl<T> MyBox<T> {
    fn new(x: T) -> MyBox<T> {
        MyBox(x)
    }
}

// 实现Deref trait来让智能指针可以被当作常规引用来对待
impl<T> Deref for MyBox<T> {
    // type Target = T; 语法定义了用于此 trait 的关联类型。
    // 关联类型是一个稍有不同的定义泛型参数的方式，现在还无需过多的担心它，后面会了解到
    type Target = T;

    // deref 方法体中写入了 &self.0，这样 deref 返回了我希望通过 * 运算符访问的值的引用。
    fn deref(&self) -> &T {
        &self.0
    }
}
