// 在 mod front_of_house 后使用分号，而不是代码块
// 这将告诉Rust在另一个与模块同名的文件中加载模块的内容。
mod front_of_house;

use front_of_house::hosting;

fn main() {
    hosting::add_to_waitlist();
}
