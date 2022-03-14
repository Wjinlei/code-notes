// 对于智能指针模式来说第二个重要的 trait 是 Drop，其允许我们在值要离开作用域时执行一些代码。
// 可以为任何类型提供 Drop trait 的实现，同时所指定的代码被用于释放类似于文件或网络连接的资源。
// 我们在智能指针上下文中讨论 Drop 是因为其功能几乎总是用于实现智能指针。
// Drop 你可以把它理解为其他语言中的析构函数

// Drop trait 要求实现一个叫做 drop 的方法，它获取一个 self 的可变引用。

#[derive(Debug)]
struct CustomSmartPointer {
    data: String,
}

// 实现Drop trait
// Drop trait 包含在 prelude 中，所以无需导入它。
impl Drop for CustomSmartPointer {
    fn drop(&mut self) {
        println!("Dropping CustomSmartPointer with data: `{}`", self.data);
    }
}

fn main() {
    let c = CustomSmartPointer {
        data: String::from("ccc"),
    };
    println!("{:?} CustomSmartPointer created.", c);
    let d = CustomSmartPointer {
        data: String::from("ddd"),
    };
    println!("{:?} CustomSmartPointer created.", d);

    // 整个 Drop trait 存在的意义在于其是自动处理的。
    // 然而，有时你可能需要提早清理某个值。
    // 一个例子是当使用智能指针管理锁时；你可能希望强制运行 drop 方法来释放锁以便作用域中的其他代码可以获取锁。
    // Rust 并不允许我们主动调用 Drop trait 的 drop 方法
    // Rust 不允许我们显式调用 drop 因为 Rust 仍然会在 main 的结尾对值自动调用 drop
    // 这会导致一个 double free 错误，因为 Rust 会尝试清理相同的值两次。
    // 当我们希望在作用域结束之前就强制释放变量的话，我们应该使用的是由标准库提供的 std::mem::drop。
    // std::mem::drop 函数不同于 Drop trait 中的 drop 方法。
    // 可以通过传递希望提早强制丢弃的值作为参数。
    // std::mem::drop 位于 prelude 因此它不需要被导入

    let e = CustomSmartPointer {
        data: String::from("eee"),
    };
    println!("{:?} CustomSmartPointer created.", e);
    drop(e); // std::mem::drop
    let f = CustomSmartPointer {
        data: String::from("fff"),
    };
    println!("{:?} CustomSmartPointer created.", f);
}
