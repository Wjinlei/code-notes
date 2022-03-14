// 我们需要引入了三个新的 crate：proc_macro 、syn 和 quote 。
// Rust 自带 proc_macro crate，因此无需将其加到 Cargo.toml 文件的依赖中。
// proc_macro crate 是编译器用来读取和操作我们 Rust 代码的 API。
//
// syn crate 将字符串中的 Rust 代码解析成为一个可以操作的数据结构。
// quote 则将 syn 解析的数据结构转换回 Rust 代码。
// 这些 crate 让解析任何我们所要处理的 Rust 代码变得更简单：为 Rust 编写整个的解析器并不是一件简单的工作。
extern crate proc_macro;
use proc_macro::TokenStream;
use quote::quote;
use syn;

// 当用户在一个类型上指定 #[derive(HelloMacro)] 时，hello_macro_derive 函数将会被调用。
// 原因在于我们已经使用 proc_macro_derive 及其指定名称对 hello_macro_derive 函数进行了注解:HelloMacro 。
#[proc_macro_derive(HelloMacro)]
pub fn hello_macro_derive(input: TokenStream) -> TokenStream {
    // 将 Rust 代码解析为语法树以便进行操作
    // 你可能也注意到了，当调用 syn::parse 函数失败时，我们用 unwrap 来使 hello_macro_derive 函数 panic。
    // 在错误时 panic 对过程宏来说是必须的，因为 proc_macro_derive 函数必须返回 TokenStream 而不是 Result，
    // 以此来符合过程宏的 API。这里选择用 unwrap 来简化了这个例子；
    // 在生产代码中，则应该通过 panic! 或 expect 来提供关于发生何种错误的更加明确的错误信息。
    let ast = syn::parse(input).unwrap();

    // 这里我们的Panckes结构体被解析成如下形式
    // 该结构体里面有更多字段描述了所有类型的 Rust 代码，查阅 syn 中 DeriveInput 的文档
    // https://docs.rs/syn/0.14.4/syn/struct.DeriveInput.html
    /*
DeriveInput {
    // --snip--

    ident: Ident {
        ident: "Pancakes",  // 结构体的名字
        span: #0 bytes(95..103)
    },
    data: Struct(
        DataStruct {
            struct_token: Struct,
            fields: Unit,
            semi_token: Some(
                Semi
            )
        }
    )
}
*/
    // 根据syn解析出的结构，构建新的Rust代码
    impl_hello_macro(&ast)
}

fn impl_hello_macro(ast: &syn::DeriveInput) -> TokenStream {
    let name = &ast.ident; // 我们得到一个包含以 ast.ident 作为注解类型名字（标识符）的 Ident 结构体实例。

    // quote! 宏让我们可以编写希望返回的 Rust 代码。
    // quote! 宏执行的直接结果并不是编译器所期望的并需要转换为 TokenStream。
    let gen = quote! {
        impl HelloMacro for #name {
            // 这个宏也提供了一些非常酷的模板机制；我们可以写 #name ，然后 quote! 会以名为 name 的变量值来替换它。
            fn hello_macro() {
                // 此处所使用的 stringify! 为 Rust 内置宏。其接收一个 Rust 表达式，如 1 + 2 ， 
                // 然后在编译时将表达式转换为一个字符串常量，如 "1 + 2" 。
                // 这与 format! 或 println! 是不同的，它计算表达式并将结果转换为 String 。
                println!("Hello, Macro! My name is {}", stringify!(#name));
            }
        }
    };
    // 为此需要调用 into 方法，它会消费这个中间表示（intermediate representation，IR）并返回所需的 TokenStream 类型值。
    gen.into()
}
