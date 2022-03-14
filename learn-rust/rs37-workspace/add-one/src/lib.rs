use rand::Rng;

pub fn add_one(x: i32) -> i32 {
    x + 1
}

pub fn random() -> i32 {
    let num = rand::thread_rng().gen_range(1..101);
    num
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn is_works() {
        assert_eq!(3, add_one(2))
    }
}
