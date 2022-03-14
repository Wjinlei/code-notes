// 路径Paths
// 与文件系统类似, 文件系统的根节点是/, 箱(crate)的根节点是crate.
// 绝对路径, 从箱(crate)的根节点开始, 箱(crate)的名称, 或crate
// 相对路径, 从当前模块开始, 可以使用self, super

// 访问权限
// 所有元素, 函数functions, 方法methods, 结构体structs, 枚举enum, 模块modules, 常量constants, 默认是私有的,
// 对外公开(public), 需要通过关键字pub声明
// 即便是公有的结构体(public structs), 内部的元素(fields)和方法(methods)仍是私有的(private)
// 公有的枚举(public enums), 其所有变量(variants)也同为公有(public)
// 父模块中的元素, 不能使用子模块中的私有元素
// 子模块中的元素, 可以使用父模块的元素
mod front_of_house {
    // pub 关键字使模块变为公有的
    pub mod hosting {
        // pub 关键字使模块中的函数变为公有的
        pub fn add_to_waitlist() {}
    }
}

fn serve_order() {}

mod back_of_house {
    pub fn fix_incorrect_order() {
        cook_order();
        // super 关键字可以从父目录开始调用函数
        super::serve_order();
    }
    fn cook_order() {}
}

pub fn run_it_works() {
    // 引用模块的两种方式
    crate::front_of_house::hosting::add_to_waitlist();
    front_of_house::hosting::add_to_waitlist();

    back_of_house::fix_incorrect_order();
}
