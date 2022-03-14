mod front_of_house {
    pub mod hosting {
        pub fn add_to_waitlist() {}
    }

    pub mod serving {
        pub fn take_order() {}
        pub fn server_order() {}
        pub fn take_payment() {}
    }
}

// 使用use关键字将模块的path引入到当前作用域
use crate::front_of_house::hosting;
// 还可以在引入时给它一个新的名字
use crate::front_of_house::hosting as h;
// 重导出
// 当使用 use 关键字将名称导入作用域时，在新作用域中可用的名称是私有的。
// 如果为了让调用你编写的代码的代码能够像在自己的作用域内引用这些类型
// 可以结合 pub 和 use。这个技术被称为 “重导出（re-exporting）”
// 因为这样做将项引入作用域并同时使其可供其他代码引入自己的作用域。
pub use crate::front_of_house::hosting as hi;

// 如果希望将一个路径下所有公有项引入作用域，可以指定路径后跟 *，glob 运算符
use front_of_house::serving::*;

// 嵌套路径来消除大量的 use 行
use front_of_house::serving::{server_order, take_payment};

pub fn eat_at_restaurant() {
    // 然后调用该路径中的项，就如同它们是本地项一样。
    hosting::add_to_waitlist();
    h::add_to_waitlist();
    hi::add_to_waitlist();

    take_order();
    server_order();
    take_payment();
}
