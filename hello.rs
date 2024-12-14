
fn example<'a>(input: &'a str) 
{
    let mut chars = input.chars().peekable();
    
    // Peek at the first character without consuming it
    if let Some(&first_char) = chars.peek() {
        println!("First character is: {}", first_char);
    }

    // Now move forward by consuming it
    if let Some(first_char) = chars.next() {
        println!("Consumed first character: {}", first_char);
    }

    // Peek again at the next character
    if let Some(&second_char) = chars.peek() {
        println!("Next character is: {}", second_char);
    }
}

fn main()
{
    let string : &str = "Hello, world";
    let mut itr = string.char_indices();
    for _ in 0..string.len()
    {
        match itr.next()
        {
            None => std::println!("EOF"),
            Some(chr) => {
                std::println!("got:: {} {}", chr.0, chr.1);
            }
        }
    }
    std::println!("original String:: {string}, size:: {}", string.len());
}
