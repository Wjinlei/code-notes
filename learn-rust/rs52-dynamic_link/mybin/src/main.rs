// crate类型
// 可以通过指定 rustc --crate-type=xxx 指定crate类型
// 也可以通过在 Cargo.toml 中指定
//
// crate类型有7种
//
// 1.bin
//     Rust 二进制类型，不能被其他crate库依赖
// 2.lib
//     Rust 依赖库类型，可以被其他crate库依赖
// 3.dylib
//     Rust 动态库类型，可以被其他crate库依赖，会生成.so文件
// 4.rlib
//     Rust 静态库类型，可以被其他crate库依赖
// 5.staticlib
//     为其他语言提供的静态库类型(C语言风格)
// 6.cdylib
//     为其他语言提供的动态库类型(C语言风格)
// 7.proc-macro
//     过程宏，后面会学习到
//
//
// 本例子演示dylib类型
// rustc采用一种复杂的手段确定链接一个rust依赖的哪一种形式的库.
// (我们这里只讨论rust的库和依赖, C依赖只能通过build.rs修改LDFLAGS链接, 因此不做讨论)
//
// 编译后，在项目根目录使用下面的命令运行target目录中的mybin文件
// 或者将.so库文件复制到系统的lib目录中再运行mybin就可以看到结果
//
// LD_LIBRARY_PATH=~/.rustup/toolchains/stable-x86_64-unknown-linux-gnu/lib/rustlib/x86_64-unknown-linux-gnu/lib:./target/debug ./target/debug/mybin
//
// 使用命令可以查看文件依赖的库:
//     readelf -d target/debug/mybin | grep NEEDED
use mylib::hello;

fn main() {
    hello("Rust")
}
