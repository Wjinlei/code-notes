// 包 Packages: Cargo提供的让我们创建, 测试和分享Crates的工具.
// 箱 Crates: 提供类库或可执行文件的模块树
// 模块 Modules and use: 管理和组织路径, 及其作用域和访问权限
// 路径 Paths: 如结构体(structs), 函数(function), 或模块(module)等事物的命名方式

// 包(Package)通过Cargo创建. 每一个包(Package)都有一个Cargo.toml文件.
// 包(Package)包含箱(Crates)的规则如下:
// - 只能包含0 或 1个类库箱(library crates)
// - 可以包含任意多个二进制箱(binary crates)
// - 至少有一个箱(Crate), 可以是类库箱(library crates), 也可以是二进制箱(binary crates)

// cargo new my-project //创建二进制包
// cargo new --lib my-lib //创建类库包
//
// 默认, 一个箱(crate):
// - src/main.rs // 二进制箱(binary crate)的根文件,该箱(crate)与包(package)同名
// - src/lib.rs  // 类库箱(library crate)的根文件 ,该箱(crate)与包(package)同名
// 多个二进制箱(binary crates):
// - 在src/bin目录下创建.rs文件, 每个文件对应一个二进制箱(binary crate).
fn main() {
    println!("Hello, world!");
}
