// 说白了panic会终止程序,和golang的panic类似
// panic默认会清理栈
// 如果不想要清理,而交给操作系统处理的话,参考下面的(了解下即可)
// https://kaisery.github.io/trpl-zh-cn/ch09-01-unrecoverable-errors-with-panic.html#%E5%AF%B9%E5%BA%94-panic-%E6%97%B6%E7%9A%84%E6%A0%88%E5%B1%95%E5%BC%80%E6%88%96%E7%BB%88%E6%AD%A2
//
// backtrace会打印堆栈的详细调用过程
// 通过设置环境变量 RUST_BACKTRACE=1(非0就行) 启用
fn main() {
    let v = vec![1, 2, 3];
    println!("{}", v[99]);
}
