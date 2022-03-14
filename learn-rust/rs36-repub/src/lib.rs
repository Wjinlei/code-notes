//! # My Crate
//!
//! `my_crate` is a collection of utilities to make performing certain
//! calculations more convenient.

// 定义重导出,好处是什么参见main.rs
pub use self::kinds::PrimaryColor;
pub use self::kinds::SecondaryColor;
pub use self::utils::mix;

pub mod kinds {
    /// The primary colors according to the RYB color model.
    pub enum PrimaryColor {
        Red,
        Yellow,
        Blue,
    }

    /// The secondary colors according to the RYB color model.
    pub enum SecondaryColor {
        Red,
        Yellow,
        Blue,
        Orange,
        Green,
        Purple,
    }
}

pub mod utils {
    use crate::kinds::*;

    /// Combines two primary colors in equal amounts to create
    /// a secondary color.
    pub fn mix(c1: PrimaryColor, c2: PrimaryColor) -> SecondaryColor {
        let new_color = match c1 {
            PrimaryColor::Red => {
                match c2 {
                    PrimaryColor::Red => SecondaryColor::Red,
                    PrimaryColor::Yellow => SecondaryColor::Orange,
                    PrimaryColor::Blue => SecondaryColor::Purple,
                }
            }
            PrimaryColor::Yellow => {
                match c2 {
                    PrimaryColor::Red => SecondaryColor::Orange,
                    PrimaryColor::Yellow => SecondaryColor::Yellow,
                    PrimaryColor::Blue => SecondaryColor::Green,
                }
            }
            PrimaryColor::Blue => {
                match c2 {
                    PrimaryColor::Red => SecondaryColor::Purple,
                    PrimaryColor::Yellow => SecondaryColor::Green,
                    PrimaryColor::Blue => SecondaryColor::Blue,
                }
            }
        };
        new_color
    }
}

