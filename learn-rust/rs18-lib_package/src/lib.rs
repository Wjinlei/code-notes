// 模块通过关键字mod加模块定义, 例如:
// 文件src/main.rs和src/lib.rs, 对应的模块是crate,
// 箱(crate)的模块结构(module structure), 也叫做模块树(module tree):
// crate // crate是一个隐式模块,默认存在
// └── front_of_house
//     ├── hosting
//         ├── add_to_waitlist
//
// crate(箱)你可以理解为就是一个模块

mod front_of_house {
    mod hosting {
        fn add_to_waitlist() {}
    }
}
