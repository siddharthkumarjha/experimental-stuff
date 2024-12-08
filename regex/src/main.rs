//! Build a regex parser for the below grammer
//! (ha+)+
//! s -> h J
//! J -> a s | a J | a

mod ha_regex
{
    static G_STRING : &str = "";
    fn rule_s(l_string : &str) -> bool
    {
        return false;
    }
}

fn main() {
    println!("Hello, world!");
}
