//! Build a regex parser for the below grammer
//! (ha+)+
//! s -> h J
//! J -> a s | a J | a

mod ha_regex
{
    pub(crate) struct HaRegexStruct<'a>
    {
        input_str : &'a str,
        str_iterator : std::iter::Peekable<std::str::CharIndices<'a>>,
        last_matched_index : usize
    }

    impl<'a> HaRegexStruct<'a>
    {
        fn match_char(&mut self, char_to_match : char) -> bool
        {
            match self.str_iterator.peek()
            {
                None => {
                    return false;
                },
                Some(chr) => {
                    if chr.1 == char_to_match 
                    { 
                        self.last_matched_index = chr.0;
                        _ = self.str_iterator.next();
                        return true;
                    }
                    return false;
                }
            }
        }
        fn rule_j(&mut self) -> bool
        {
            if self.match_char('a') 
            {
                if self.last_matched_index == (self.input_str.len() - 1)
                {
                    return true;
                }
                else if self.rule_s() //swap this with ruleJ to trigger bug!
                {
                    return true;
                }
                else if self.rule_j()
                {
                    return true;
                }
            }
            return false;
        }
        fn rule_s(&mut self) -> bool
        {
            if self.match_char('h') 
            {
                return self.rule_j();
            }
            return false;
        }
        pub fn parse(&mut self) -> (bool, String)
        {
            if self.input_str.is_empty()
            {
                return (false, String::from("Empty String"));
            }
            else if !self.input_str.starts_with('h') || !self.input_str.ends_with('a')
            {
                return (false, 
                String::from("unexpected tokens at the start/end of input string parsing \
                stopped, expected \"h\" at start and \"a\" at the end"));
            }

            if self.rule_s() &&
                self.last_matched_index == (self.input_str.len() - 1)
            {
                    return (true, String::from("Parsing Successful! String matches regex"));
            }
            return (false, 
                std::format!("parsing failed: unexpected end of input after index, {}\
                    \nFor String:: {}\n{:>13}{:->width$}^", self.last_matched_index, self.input_str, ' ',  "", 
                    width = self.last_matched_index + 1));
        }
    }
    pub fn new(str_to_store: &str) -> HaRegexStruct<'_>
    {
        HaRegexStruct {
            input_str : str_to_store,
            str_iterator : str_to_store.char_indices().peekable(),
            last_matched_index : 0
        }
    }
}

fn main() 
{
    let mut regex_obj = crate::ha_regex::new("haahahhaa");
    let (parse_status, parse_errors) = regex_obj.parse();
    std::println!("Parse results:: {parse_status}, {parse_errors}");
    std::println!("haahahhaa");
}
