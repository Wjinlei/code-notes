use add_one;

fn main() {
    let num = 20;
    println!("Hello world! {} plus on is {}", num,add_one::add_one(num));
    println!("random is {}", add_one::random());
}
