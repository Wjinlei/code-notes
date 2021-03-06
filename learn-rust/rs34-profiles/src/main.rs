// 在 Rust 中 发布配置（release profiles）是预定义的、可定制的带有不同选项的配置。
// 他们允许程序员更灵活地控制代码编译的多种选项。每一个配置都彼此相互独立。

// 当项目的 Cargo.toml 文件中没有任何 [profile.*] 部分的时候，Cargo 会对每一个配置都采用默认设置。
// 通过增加任何希望定制的配置对应的 [profile.*] 部分，我们可以选择覆盖任意默认设置的子集。

// 例如，如下是 dev 和 release 配置的 opt-level 设置的默认值：
// 文件名: Cargo.toml
/*
    [profile.dev]
    opt-level = 0

    [profile.release]
    opt-level = 3
*/

// opt-level 设置控制 Rust 会对代码进行何种程度的优化。
// 这个配置的值从 0 到 3。越高的优化级别需要更多的时间编译
// 所以如果你在进行开发并经常编译，可能会希望在牺牲一些代码性能的情况下编译得快一些。
// 这就是为什么 dev 的 opt-level 默认为 0。
// 当你准备发布时，花费更多时间在编译上则更好。
// 只需要在发布模式编译一次，而编译出来的程序则会运行很多次，所以发布模式用更长的编译时间换取运行更快的代码。
// 这正是为什么 release 配置的 opt-level 默认为 3。

fn main() {
    println!("Hello, world!");
}
