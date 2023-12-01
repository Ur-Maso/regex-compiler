# regex-compiler
 ## What is this?
  Whenever you need to use a regex in your code you might meet with it's complexity, expecially when it become longer.
  This is compiler. You may write a regex into a several lines with spaces, variables and comments involved. Then it'll be compiled into a 
  normal regex view. I'm planning to make a quite lighweight compiler, which you may run in cmake or other compilation scripts. 
 ## Syntax
    regex</> name:
        $var = Hello, world!
        $var2:
            %var
            1234
            5678
            9
            $nested_var:
                10 11 12 13 14 15
            %nested_var %nested_var
        (regular)? (regex)+
        $var2
        # comment
        -- output
        /(regular)?(regex)+Hello,world!123456789101112131415101112131415/
    string<"> name2:
        Lets write a quote: " and_escape_char: \\n
        -- output
        "Letswriteaquote:\"and_escape_char:\\\\n"
 ## Installation
  Nothing is complex. Simply download a binary which currently will be a single static executable
 ## Usage
  Since it is just recently added you cannot use it currently.
 ## License
  This is project under MIT license. Change whatever you want on your desire.